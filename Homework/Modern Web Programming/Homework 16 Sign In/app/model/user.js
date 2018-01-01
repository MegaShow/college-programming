const db = require('../../lib/mongo')
const log = console.log

const userSchema = db.Schema({
  email: String,
  username: String,
  password: String,
  studentId: String,
  phone: String,
  salt: String
}, {
  collection: 'user'
})
const userDB = db.model('user', userSchema)

exports.createUser = async user => {
  try {
    let uniqueEmail = await userDB.findOne({ email: user.email })
    let uniqueUsername = await userDB.findOne({ username: user.username })
    let uniqueStudentId = await userDB.findOne({ studentId: user.studentId })
    let uniquePhone = await userDB.findOne({ phone: user.phone })
    if (uniqueEmail) return { state: 'fail', err: '邮箱重复' }
    if (uniqueUsername) return { state: 'fail', err: '用户名重复' }
    if (uniqueStudentId) return { state: 'fail', err: '学号重复' }
    if (uniquePhone) return { state: 'fail', err: '电话重复' }
    let result = await userDB.create(user)
    return { state: 'success', id: result._id }
  } catch(err) {
    return { state: 'fail', err: 'Oops, something error.' }
  }
}

exports.getUserById = async id => {
  try {
    let result = await userDB.findById(id)
    return { state: 'success', data: result }
  } catch(err) {
    return { state: 'fail', err: 'Oops, something error.' }
  }
}

exports.getUserByUsername = async username => {
  try {
    let result = await userDB.findOne({ username: username })
    if (result) return { state: 'success', data: result }
    else return { state: 'fail', err: '用户不存在' }
  } catch(err) {
    return { state: 'fail', err: 'Oops, something error.' }
  }
}
