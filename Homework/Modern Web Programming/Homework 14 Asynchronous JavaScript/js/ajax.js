const methods = {
  get: 'GET',
  post: 'POST',
  put: 'PUT',
  patch: 'PATCH',
  delete: 'DELETE'
}

class Ajax {
  constructor() {
    for (let method in methods) {
      this[method] = (path, data, next) => {
        this.ajax(path, methods[method], data, next)
      }
    }
  }

  ajax(path, method, data, next) {
    let query = ''
    for (let x in data) {
      query += (x + '=' + data[x] + '&')
    }
    if (query.length !== 1) query = query.substr(0, query.length - 1)
    let xhr = new XMLHttpRequest()
    xhr.timeout = 5000
    xhr.responseType = 'text'
    if (method === methods.get) xhr.open(method, path + '?' + query, true)
    else xhr.open(method, path, true)
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.onload = function () {
      if (xhr.status === 200) {
        if (next) next({ state: 'success', text: this.responseText })
      } else {
        if (next) next({ state: 'fail', text: this.responseText })
      }
    }
    xhr.ontimeout = function () {
      if (next) next({ state: 'timeout', text: this.responseText })
    }
    xhr.onerror = function () {
      if (next) next({ state: 'error', text: this.responseText })
    }
    if (method !== methods.get) xhr.send(query)
    else xhr.send()
  }
}
