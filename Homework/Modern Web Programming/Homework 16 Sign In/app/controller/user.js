const cryptogram = require('../../lib/cryptogram')
const userDB = require('../model/user.js')
const log = console.log

exports.getUser = async (req, res) => {
  log('Query: /User, GET')
  log('Description: Get user\'s information by username.')
  log('Session:', req.session.uid)
  log('Params:', req.body)
  let result
  if (req.session.uid) result = await userDB.getUserById(req.session.uid)
  else if (req.body.username) result = await userDB.getUserByUsername(req.body.username)
  else result = null
  if (result && result.state === 'success') {
    result = {
      state: 'success',
      email: result.data.email,
      username: result.data.username,
      studentId: result.data.studentId,
      phone: result.data.phone
    }
  } else {
    result = { state: 'fail', err: '用户名错误或不存在' }
  }
  log('Result:', result, '\n')
  res.send(result)
}

exports.postUser = async (req, res) => {
  log('Query: /User, POST')
  log('Description: Sign up with user\'s information.')
  log('Params:', {
    email: req.body.email,
    username: req.body.username,
    password: '******',
    studentId: req.body.studentId,
    phone: req.body.phone
  })
  let salt = cryptogram.createSaltString(6)
  let result = await userDB.createUser({
    email: req.body.email,
    username: req.body.username,
    password: cryptogram.sha512WithSalt(req.body.password, salt),
    studentId: req.body.studentId,
    phone: req.body.phone,
    salt: salt
  })
  if (result.state === 'success') {
    req.session.uid = result.id
    result = { state: 'success' }
  }
  log('Create Session:', req.session.uid)
  log('Result:', result, '\n')
  res.send(result)
}

exports.postLogin = async(req, res) => {
  log('Query: /User/Login, POST')
  log('Description: Log in by username and password')
  log('Params:', {
    username: req.body.username,
    password: '******'
  })
  let result = await userDB.getUserByUsername(req.body.username)
  if (result.state === 'success' && cryptogram.sha512WithSalt(req.body.password, result.data.salt) === result.data.password) {
    log(result.data._id)
    req.session.uid = result.data._id
    result = {
      state: 'success',
      email: result.data.email,
      username: result.data.username,
      studentId: result.data.studentId,
      phone: result.data.phone
    }
  } else {
    result = { state: 'fail', err: '用户名或密码错误' }
  }
  log('Create Session:', req.session.uid)
  log('Result:', result, '\n')
  res.send(result)
}

exports.deleteLogin = async(req, res) => {
  log('Query: /User/Login, DELETE')
  log('Desciption: Log out')
  let result
  if (req.session.uid) {
    req.session.uid = null
    result = { state: 'success' }
  } else {
    result = { state: 'fail', err: 'error' }
  }
  log('Result:', result, '\n')
  res.send(result)
}
