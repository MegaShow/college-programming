let username = document.getElementById('username')
let studentId = document.getElementById('studentId')
let phone = document.getElementById('phone')
let email = document.getElementById('email')
let state = document.getElementById('state')
let app = new Ajax()

let reset = () => {
  username.value = ''
  studentId.value = ''
  phone.value = ''
  email.value = ''
  state.innerHTML = ''
}

let signup = () => {
  state.innerHTML = ''
  if (username.value.length === 0) state.innerHTML = '用户名不能为空'
  else if (!/^[a-zA-Z][a-zA-Z0-9_]{5,17}$/.test(username.value)) state.innerHTML = '用户名不合法'
  else if (studentId.value.length === 0) state.innerHTML = '学号不能为空'
  else if (!/^[1-9]\d{7}$/.test(studentId.value)) state.innerHTML = '学号不合法'
  else if (phone.value.length === 0) state.innerHTML = '电话不能为空'
  else if (!/^[1-9]\d{10}$/.test(phone.value)) state.innerHTML = '电话不合法'
  else if (email.value.length === 0) state.innerHTML = '邮箱不能为空'
  else if (!/^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/.test(email.value))
    state.innerHTML = '邮箱不合法'
  else {
    app.post('/user', {
      username: username.value,
      studentId: studentId.value,
      phone: phone.value,
      email: email.value
    }, (data) => {
      if (data.err) document.getElementById('state').innerHTML = data.err
      else change()
    })
  }
}

let change = () => {
  username.setAttribute('disabled', 'disabled')
  studentId.setAttribute('disabled', 'disabled')
  phone.setAttribute('disabled', 'disabled')
  email.setAttribute('disabled', 'disabled')
  document.getElementById('title').innerHTML = '用户详情'
  document.getElementById('user').removeChild(document.getElementById('button'))
}

let init = () => {
  document.getElementById('reset').onclick = reset
  document.getElementById('signup').onclick = signup
  let query = window.location.search
  let params = {}
  if (query[0] === '?') {
    let arr = query.substr(1).split('&')
    for (let i of arr) {
      i = i.split('=')
      if (i.length !== 2) continue
      params[i[0]] = i[1]
    }
    if (params.username) {
      app.get('/user', { username: params.username }, (data) => {
        if (data.err) window.location.href = '/'
        username.value = data.username
        studentId.value = data.studentId
        phone.value = data.phone
        email.value = data.email
        change()
      })
    }
  }
}

init()
