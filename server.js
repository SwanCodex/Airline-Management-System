const http = require('http');
const fs = require('fs');
const path = require('path');
const child_process = require('child_process');

const PORT = process.env.PORT || 8000;
const ROOT = process.cwd();
const DEFAULT_PAGE = '/Frontend/dashboard.html';

// Simple MIME map
const MIME = {
  '.html': 'text/html; charset=utf-8',
  '.htm': 'text/html; charset=utf-8',
  '.js': 'application/javascript; charset=utf-8',
  '.css': 'text/css; charset=utf-8',
  '.json': 'application/json; charset=utf-8',
  '.png': 'image/png',
  '.jpg': 'image/jpeg',
  '.jpeg': 'image/jpeg',
  '.gif': 'image/gif',
  '.svg': 'image/svg+xml',
  '.ico': 'image/x-icon',
  '.txt': 'text/plain; charset=utf-8'
};

function send404(res) {
  res.statusCode = 404;
  res.setHeader('Content-Type', 'text/plain; charset=utf-8');
  res.end('404 Not Found');
}

// Backend process and simple state
let backend = null;
let backendInWebMode = false;

// write a sequence of lines to backend stdin with small delays
function writeSequence(lines, delayMs = 120) {
  return new Promise((resolve, reject) => {
    if (!backend || !backend.stdin || backend.killed) {
      return reject(new Error('Backend is not running'));
    }
    let i = 0;
    const interval = setInterval(() => {
      if (i >= lines.length) {
        clearInterval(interval);
        return resolve();
      }
      try {
        backend.stdin.write(String(lines[i]) + "\n");
      } catch (e) {
        clearInterval(interval);
        return reject(e);
      }
      i++;
    }, delayMs);
  });
}

// ensure we are at web mode prompt
async function ensureWebMode() {
  if (!backendInWebMode) {
    await writeSequence(['11']);
    backendInWebMode = true;
  }
}

// ensure we are at main menu (exit web mode if needed)
async function ensureMainMenu() {
  if (backendInWebMode) {
    await writeSequence(['q']);
    backendInWebMode = false;
  }
}

const server = http.createServer((req, res) => {
  try {
    // normalize URL and remove query
    let requested = decodeURIComponent(req.url.split('?')[0] || '/');

    // Handle API routes early (works on Windows and POSIX)
    if (requested.startsWith('/api/')) {
      const apiPath = requested.replace(/^\/+/, ''); // remove leading slashes
      handleApi(req, res, apiPath);
      return;
    }

    if (requested === '/' || requested === '') requested = DEFAULT_PAGE;

    // prevent path traversal; normalize for platform and strip leading slashes
    const normalized = path.normalize(requested);
    const safePath = normalized.replace(/^([.][.][\\/]|[\\/])+/g, '');
    const filePath = path.join(ROOT, safePath);

    // restrict to ROOT
    if (!filePath.startsWith(ROOT)) {
      send404(res);
      return;
    }

    fs.stat(filePath, (err, stats) => {
      if (err) {
        send404(res);
        return;
      }

      if (stats.isDirectory()) {
        // try index.html
        const indexFile = path.join(filePath, 'index.html');
        if (fs.existsSync(indexFile)) {
          streamFile(indexFile, res);
        } else {
          send404(res);
        }
        return;
      }

      streamFile(filePath, res);
    });
  } catch (e) {
    console.error('Server error:', e);
    send404(res);
  }
});

function streamFile(filePath, res) {
  const ext = path.extname(filePath).toLowerCase();
  const mime = MIME[ext] || 'application/octet-stream';
  res.setHeader('Content-Type', mime);
  // allow same-origin fetches; harmless if left
  res.setHeader('Access-Control-Allow-Origin', '*');
  const stream = fs.createReadStream(filePath);
  stream.on('error', () => send404(res));
  stream.pipe(res);
}

server.listen(PORT, () => {
  console.log(`Static server running at http://localhost:${PORT}/`);
  console.log(`Serving files from ${ROOT}`);
  console.log(`Default page: ${DEFAULT_PAGE}`);

  // Attempt to spawn backend executable if available and not disabled
  const args = process.argv.slice(2);
  if (args.includes('--no-backend') || process.env.NO_BACKEND === '1') {
    console.log('Backend start disabled (flag or NO_BACKEND=1)');
    return;
  }

  const backendPath = path.join(ROOT, 'src', 'airport_system.exe');
  if (fs.existsSync(backendPath)) {
    console.log('Starting backend executable:', backendPath);
    try {
      backend = child_process.spawn(backendPath, { cwd: path.join(ROOT, 'src'), stdio: ['pipe', 'inherit', 'inherit'] });

      // on backend exit, print message but keep server running
      backend.on('exit', (code, sig) => {
        console.log(`Backend exited with code=${code} signal=${sig}`);
        backendInWebMode = false;
        backend = null;
      });

      const cleanup = () => {
        if (backend && !backend.killed) {
          try { backend.kill(); } catch (e) {}
        }
        process.exit();
      };

      process.on('SIGINT', cleanup);
      process.on('SIGTERM', cleanup);
      process.on('exit', cleanup);
    } catch (e) {
      console.error('Failed to start backend:', e);
    }
  } else {
    console.log('Backend executable not found at', backendPath);
    console.log('If you want to run without backend, start with: npm run serve-only');
  }
});

// graceful shutdown for the server
process.on('SIGINT', () => {
  console.log('Shutting down server...');
  server.close(() => process.exit());
});

// Parse JSON body helper
function parseBody(req) {
  return new Promise((resolve) => {
    let data = '';
    req.on('data', chunk => {
      data += chunk;
      if (data.length > 1e6) {
        req.connection.destroy();
      }
    });
    req.on('end', () => {
      try {
        const json = data ? JSON.parse(data) : {};
        resolve(json);
      } catch {
        resolve({});
      }
    });
  });
}

function sendJSON(res, status, obj) {
  res.statusCode = status;
  res.setHeader('Content-Type', 'application/json; charset=utf-8');
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.end(JSON.stringify(obj));
}

async function handleApi(req, res, safePath) {
  // simple CORS
  if (req.method === 'OPTIONS') {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET,POST,OPTIONS');
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
    res.statusCode = 204;
    res.end();
    return;
  }
  try {
    if (req.method !== 'POST') return sendJSON(res, 405, { error: 'Method not allowed' });
    if (!backend) return sendJSON(res, 503, { error: 'Backend not running' });
    const body = await parseBody(req);

    switch (safePath) {
      case 'api/init': {
        // Initialize program at startup prompts: select algorithm and add samples
        const algo = Number(body.algo) || 1; // 1-4
        const addSamples = body.addSamples ? 'y' : 'n';
        // At program start, prompts are: algorithm (1-4), then add samples (y/n)
        await writeSequence([String(algo), addSamples]);
        return sendJSON(res, 200, { ok: true });
      }
      case 'api/algorithm': {
        const algo = Number(body.algo) || 1;
        await ensureMainMenu();
        await writeSequence(['10', String(algo), '']);
        return sendJSON(res, 200, { ok: true });
      }
      case 'api/simulate': {
        const minutes = Math.max(1, Number(body.minutes) || 20);
        await ensureMainMenu();
        await writeSequence(['6', String(minutes), '']);
        return sendJSON(res, 200, { ok: true });
      }
      case 'api/webmode/start': {
        await ensureWebMode();
        return sendJSON(res, 200, { ok: true, inWebMode: true });
      }
      case 'api/webmode/cmd': {
        const cmd = String(body.cmd || '').toLowerCase();
        await ensureWebMode();
        if (!['s','p','a','q'].includes(cmd)) {
          return sendJSON(res, 400, { error: 'Unsupported command' });
        }
        await writeSequence([cmd]);
        if (cmd === 'q') backendInWebMode = false;
        return sendJSON(res, 200, { ok: true });
      }
      case 'api/emergency': {
        const {
          type = 4,
          id = 'EM999',
          airline = 'Airline',
          source = 'CityA',
          destination = 'CityB',
          processingTime = 10,
          details = 'Emergency'
        } = body || {};
        await ensureWebMode();
        const seq = ['e', String(type), String(id), String(airline), String(source), String(destination), String(processingTime), String(details)];
        await writeSequence(seq);
        return sendJSON(res, 200, { ok: true });
      }
      case 'api/add-flight': {
        const {
          id, airline, source, destination,
          scheduledTime = 600,
          priority = 1,
          operation = 0,
          processingTime = 5
        } = body || {};
        if (!id || !airline || !source || !destination) {
          return sendJSON(res, 400, { error: 'Missing required fields' });
        }
        await ensureMainMenu();
        const seq = ['1', String(id), String(airline), String(source), String(destination), String(scheduledTime), String(priority), String(operation), String(processingTime), ''];
        await writeSequence(seq);
        return sendJSON(res, 200, { ok: true });
      }
      case 'api/delete-flight': {
        const { id } = body || {};
        if (!id) return sendJSON(res, 400, { error: 'Missing id' });
        await ensureMainMenu();
        await writeSequence(['3', String(id), '']);
        return sendJSON(res, 200, { ok: true });
      }
      default:
        return sendJSON(res, 404, { error: 'Unknown API endpoint' });
    }
  } catch (e) {
    console.error('API error', e);
    return sendJSON(res, 500, { error: e.message || 'Internal error' });
  }
}
