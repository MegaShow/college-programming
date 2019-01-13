const fs = require('fs')
const url = require('url')
const path = require('path')
const log = console.log

const index = 'index.html'
const exttype = {
  'unknown': 'text/plain',
  'html': 'text/html',
  'css': 'text/css',
  'js': 'text/javascript',
  'ico': 'image/x-icon',
  'gif': 'image/gif',
  'jpg': 'imag/jpeg',
  'jpeg': 'image/jpeg',
  'png': 'image/png',
  'svg': 'image/svg+xml'
}

exports.basepath = ''

exports.callback = basepath => {
  exports.basepath = basepath
  return async(req, res) => {
    if (res.finished || req.method !== 'GET') return
    let realpath = exports.basepath + url.parse(req.url).pathname
    try {
      let stat = await fs.statSync(realpath)
      if (stat.isFile()) {
        await write(res, realpath, 200)
      } else if (!stat.isFile() && stat.isDirectory()) {
        realpath = realpath.replace(/\/$/, '') + '/' + index
        await write(res, realpath, 200)
      } else {
        log('Route to 404')
        await write(res, realpath, 404)
      }
    } catch(e) {
      log('Route to 404')
      await write(res, realpath, 404)
    }
    log('RealPath:', realpath, '\n')
  }
}

const write = async(res, tPath, code) => {
  let str = path.extname(tPath).replace('.', '').toLowerCase()
  if (str === '' || !exttype[str]) str = 'unknown'
  if (code === 404) str = 'html'
  res.writeHead(code, { 'Content-Type': exttype[str] })
  if (code === 404) tPath = exports.basepath + '/404.html'
  let file = await fs.readFileSync(tPath)
  res.write(file)
}
