const fs = require('fs')

let routeTo = {
  'http://www.sysu.edu.cn/2012/cn/zdgk/index.htm': 'http://www.sysu.edu.cn/2012/cn/zdgk/zdgk01/index.htm',
  'http://www.sysu.edu.cn/2012/cn/xksz/index.htm': 'http://www.sysu.edu.cn/2012/cn/xksz/xksz01/index.htm',
  'http://www.sysu.edu.cn/2012/cn/jgsz/index.htm': 'http://www.sysu.edu.cn/2012/cn/jgsz/yx/index.htm',
  'http://www.sysu.edu.cn/2012/cn/jyjx/index.htm': 'http://www.sysu.edu.cn/2012/cn/jyjx/jyjx01/index.htm',
  'http://www.sysu.edu.cn/2012/cn/kxyj/index.htm': 'http://www.sysu.edu.cn/2012/cn/kxyj/kxyj01/kxyj01a/index.htm'
}
const data = require('./data')
let output = JSON.stringify(data)
for (let i in routeTo) {
  output = output.replace(new RegExp(i, 'g'), routeTo[i])
}
fs.writeFileSync('./items(deal).json', output)
