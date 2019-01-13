let username = document.getElementById('username')
let studentId = document.getElementById('studentId')
let phone = document.getElementById('phone')
let email = document.getElementById('email')
let password = document.getElementById('password')
let againPassword = document.getElementById('againPassword')
let state = document.getElementById('state')


let login = () => {
  state.innerHTML = ''
  if (username.value.length === 0) state.innerHTML = '用户名不能为空'
  else if (password.value.length === 0) state.innerHTML = '密码不能为空'
  else {
    axios.post('/User/Login', {
      username: username.value,
      password: sha512(password.value),
    }).then((data) => {
      data = data.data
      if (data.state === 'fail') document.getElementById('state').innerHTML = data.err
      else change(true, data)
    })
  }
}

let exit = () => {
  axios.delete('/User/Login', {}).then((data) => {
    data = data.data
    if (data.state === 'fail') return
    window.location.href = '/'
  })
}

let change = (isYourself, user) => {
  if (isYourself) document.getElementById('state').innerHTML = ''
  else document.getElementById('state').innerHTML = '只能够访问自己的数据'
  email.value = user.email
  username.value = user.username
  studentId.value = user.studentId
  phone.value = user.phone
  document.getElementById('input-email').style.display = 'block'
  document.getElementById('input-password').style.display = 'none'
  document.getElementById('input-studentId').style.display = 'block'
  document.getElementById('input-phone').style.display = 'block'
  username.setAttribute('disabled', 'disabled')
  document.getElementById('title').innerHTML = '用户详情'
  document.getElementById('login-exit').innerHTML = '退出'
  document.getElementById('login-exit').onclick = exit
  document.getElementById('signup').style.display = 'none'
}

let signup = () => {
  window.location.href = '/regist'
}

let init = () => {
  document.getElementById('login-exit').onclick = login
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
  }
  axios.get('/User', { username: params.username }).then((data) => {
    data = data.data
    if (data.state === 'fail' && !params.username) return
    if (data.state === 'fail') window.location.href = '/'
    else if (!params.username || params.username === data.username) change(true, data)
    else change(false, data)
  })
}

let sha512 = (str) => {
  let shaObj = new jsSHA("SHA-512", 'TEXT')
  shaObj.update(str)
  return shaObj.getHash("HEX")
}

init()
