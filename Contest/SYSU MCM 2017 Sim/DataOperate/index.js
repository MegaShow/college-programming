const data = require('./data')
const fs = require('fs')

let matrix = {}

let counter = {}
for (let link of data) {
  if (!counter[link.orgin]) {
    counter[link.orgin] = {}
    matrix[link.orgin] = {}
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

let arr = (new Array(Object.keys(counter).length)).fill(0)
for (let i in matrix) {
  matrix[i] = arr
}

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
