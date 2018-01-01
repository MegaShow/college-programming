const crypto = require('crypto')
const cryptoRandomString = require('crypto-random-string')

exports.sha512 = val => {
  return crypto.createHash('sha512')
    .update(val)
    .digest('hex')
}

exports.sha512WithSalt = (val, salt) => {
  return this.sha512(this.sha512(val) + salt)
}

exports.createSaltString = num => {
  return cryptoRandomString(num)
}
