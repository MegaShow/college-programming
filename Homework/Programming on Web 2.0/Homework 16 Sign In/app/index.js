const express = require('express')
const app = express()
const bodyParser = require('body-parser')
const session = require('express-session')
const userRouter = require('./router/user.js')
const log = console.log

app.use(session({
  secret: 'hello,world',
  resave: true,
  saveUninitialized: true
}))
app.use(bodyParser.urlencoded({ extended: false }))
app.use(bodyParser.json())
app.use(express.static('public'))
app.use('/User', userRouter)

let server = app.listen(8000, function () {
  let host = server.address().address
  let port = server.address().port
  log('Listening at', host, port)
})
