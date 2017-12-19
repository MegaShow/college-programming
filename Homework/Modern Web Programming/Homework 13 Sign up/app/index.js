const router = require('../lib/router')
const static = require('../lib/static')
const app = new router()

const user = require('./controller/user')

app.get('/user', user.getInfo)
app.post('/user', user.postInfo)

app.use(static.callback('public'))

app.listen(8000)
