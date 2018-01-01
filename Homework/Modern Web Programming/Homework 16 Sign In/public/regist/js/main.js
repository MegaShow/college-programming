let username = document.getElementById('username')
let studentId = document.getElementById('studentId')
let phone = document.getElementById('phone')
let email = document.getElementById('email')
let password = document.getElementById('password')
let againPassword = document.getElementById('againPassword')
let state = document.getElementById('state')

let reset = () => {
  username.value = ''
  password.value = ''
  againPassword.value = ''
  studentId.value = ''
  phone.value = ''
  email.value = ''
  state.innerHTML = ''
}

let signup = () => {
  state.innerHTML = ''
  if (email.value.length === 0) state.innerHTML = '邮箱不能为空'
  else if (!/^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/.test(email.value))
    state.innerHTML = '邮箱不合法'
  else if (username.value.length === 0) state.innerHTML = '用户名不能为空'
  else if (!/^[a-zA-Z][a-zA-Z0-9_]{5,17}$/.test(username.value)) state.innerHTML = '用户名不合法'
  else if (password.value.length === 0) state.innerHTML = '密码不能为空'
  else if (!/^[A-Za-z0-9_\-]{6,12}$/.test(password.value)) state.innerHTML = '密码不合法'
  else if (againPassword.value.length === 0) state.innerHTML = '确认密码不能为空'
  else if (againPassword.value !== password.value) state.innerHTML = '密码不一致'
  else if (studentId.value.length === 0) state.innerHTML = '学号不能为空'
  else if (!/^[1-9]\d{7}$/.test(studentId.value)) state.innerHTML = '学号不合法'
  else if (phone.value.length === 0) state.innerHTML = '电话不能为空'
  else if (!/^[1-9]\d{10}$/.test(phone.value)) state.innerHTML = '电话不合法'
  else {
    axios.post('/User', {
      email: email.value,
      username: username.value,
      password: sha512(password.value),
      studentId: studentId.value,
      phone: phone.value
    }).then((data) => {
      data = data.data
      if (data.state === 'fail') document.getElementById('state').innerHTML = data.err
      else window.location.href = '/'
    })
  }
}

let init = () => {
  document.getElementById('reset').onclick = reset
  document.getElementById('signup').onclick = signup
}

let sha512 = (str) => {
  let shaObj = new jsSHA("SHA-512", 'TEXT')
  shaObj.update(str)
  return shaObj.getHash("HEX")
}

init()
