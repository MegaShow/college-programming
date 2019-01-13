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
    xhr.responseType = 'text'
    if (method === methods.get) xhr.open(method, path + '?' + query, true)
    else xhr.open(method, path, true)
    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    xhr.onreadystatechange = function () {
      if (xhr.readyState === 4) {
        if (next) next(JSON.parse(this.responseText))
      }
    }
    if (method !== methods.get) xhr.send(query)
    else xhr.send()
  }
}
