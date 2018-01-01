const mongoose = require('mongoose')
const cfg = require('../config/mongo')

mongoose.connect(`mongodb://${cfg.user}:${cfg.password}@${cfg.ip}:${cfg.port}/${cfg.db}`, {
  useMongoClient: true
})
mongoose.Promise = global.Promise

db = mongoose.connection
db.on('error', console.error.bind(console, 'connection error:'))
db.on('disconnected', () => { console.log('disconnection\n') })
db.on('connected', () => { console.log('connection sucess\n') })

module.exports = mongoose
