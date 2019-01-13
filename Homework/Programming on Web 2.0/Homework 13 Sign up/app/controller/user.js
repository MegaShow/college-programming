const userDB = require('../modal/user')
const log = console.log

exports.getInfo = async(req, res) => {
  let result = await userDB.getByUsername(req.params.username)
  if (result.err) log('Error:', result.err, '\n')
  log('Return:', JSON.stringify(result))
  res.write(JSON.stringify(result))
  res.end()
}

exports.postInfo = async(req, res) => {
  let result = await userDB.add(req.params)
  if (result.err) log('Error:', result.err)
  log('Return:', JSON.stringify(result))
  res.write(JSON.stringify(result))
  res.end()
}
