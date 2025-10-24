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

const server = http.createServer((req, res) => {
  try {
    // normalize URL and remove query
    let requested = decodeURIComponent(req.url.split('?')[0]);
    if (requested === '/' || requested === '') requested = DEFAULT_PAGE;

    // prevent path traversal
    const safePath = path.normalize(requested).replace(/^(\.\.|\/)+/, '');
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
      const backend = child_process.spawn(backendPath, { cwd: path.join(ROOT, 'src'), stdio: 'inherit' });

      // on backend exit, print message but keep server running
      backend.on('exit', (code, sig) => {
        console.log(`Backend exited with code=${code} signal=${sig}`);
      });

      const cleanup = () => {
        if (!backend.killed) {
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
