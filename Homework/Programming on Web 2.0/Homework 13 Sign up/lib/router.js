const fs = require('fs')
const url = require('url')
const qs = require('querystring')
const http = require('http')
const log = console.log

const methods = {
  get: 'GET',
  post: 'POST',
  put: 'PUT',
  patch: 'PATCH',
  delete: 'DELETE'
}

module.exports = class Application {
  constructor() {
    this.middleware = []
    for (let method in methods) {
      this[method] = (tUrl, fn) => {
        let tFn = async (req, res) => {
          if (url.parse(req.url).pathname === tUrl && req.method === methods[method]) await fn(req, res)
        }
        this.middleware.push(tFn)
      }
    }
  }

  listen(...args) {
    const server = http.createServer(this.callback())
    return server.listen(...args)
  }

  use(fn) {
    this.middleware.push(fn)
  }

  callback() {
    return async (req, res) => {
      log('Request:', req.url, ' Method:', req.method)
      let tUrl = url.parse(req.url, true)
      if (req.method === methods.get) req.params = tUrl.query
      else req.params = ''
      req.on('data', (chunk) => {
        req.params += chunk
      })
      req.on('end', async() => {
        if (req.method !== methods.get) req.params = qs.parse(req.params)
        log('Query:', req.params)
        for (let fn of this.middleware) {
          await fn(req, res)
        }
        res.end()
      })
    }
  }
}
