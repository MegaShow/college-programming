const fs = require('fs')
const path = 'database/user.json'

const userSchema = {
  username: String,
  studentId: String,
  phone: String,
  email: String
}

exports.getByUsername = async(username) => {
  let db = JSON.parse(await fs.readFileSync(path))
  for (let user of db.user) {
    if (user.username === username) return user
  }
  return { err: '用户不存在' }
}

exports.add = async(tUser) => {
  let db = JSON.parse(await fs.readFileSync(path))
  for (let user of db.user) {
    if (user.username === tUser.username) return { err: '用户名重复' }
    if (user.studentId === tUser.studentId) return { err: '学号重复' }
    if (user.phone === tUser.phone) return { err: '电话重复' }
    if (user.email === tUser.email) return { err: '邮箱重复' }
  }
  db.user.push(tUser)
  await fs.writeFileSync(path, JSON.stringify(db))
  return { success: '添加用户成功' }
}
