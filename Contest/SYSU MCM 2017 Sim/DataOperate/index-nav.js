const data = require('./data')
const fs = require('fs')

// let matrix = {}
let matrix = {
  'http://www.sysu.edu.cn/2012/cn/zdgk/zdgk02/zdgk02a/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://news2.sysu.edu.cn/news01/151994.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://www.sysu.edu.cn/2012/cn/jgsz/zdgk04/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://news2.sysu.edu.cn/news04/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://news2.sysu.edu.cn/news02/139239.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://www.sysu.edu.cn/2012/cn/info/info01/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://www.sysu.edu.cn/2012/cn/jyjx/jyjx02/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://www.sysu.edu.cn/2012/cn/zdgk/zdgk02/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://www.sysu.edu.cn/2012/cn/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
  'http://www.sysu.edu.cn/2012/cn/jgsz/fsyy/index.htm': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
}
let counter = {}
for (let link of data) {
  if (!counter[link.orgin]) {
    counter[link.orgin] = {}
      // matrix[link.orgin] = {}
  }
}
// console.log(counter)


for (let link of data) {
  if (counter[link.href] === undefined) continue
  if (counter[link.orgin][link.href]) {
    counter[link.orgin][link.href]++
  } else {
    counter[link.orgin][link.href] = 1
  }
}
fs.writeFileSync('output.json', JSON.stringify(counter))

/* let arr = (new Array(Object.keys(counter).length)).fill(0)
for (let i in matrix) {
  matrix[i] = arr
} */

function getIndex(name) {
  let count = 0;
  for (let i in matrix) {
    if (i === name) return count;
    count++;
  }
  return 11;
}

let output = ''
for (let i in counter) {
  matrix[i].fill(0)
  for (let j in counter[i]) {
    matrix[i][getIndex(j)] = counter[i][j]
  }
  for (let num of matrix[i]) {
    output += num + ' '
  }
  output += '\n'
}

for (let i in matrix) {
  console.log(matrix[i])
}
output = output.replace(/ \n/g, '\n')
fs.writeFileSync('matrix.txt', output)
