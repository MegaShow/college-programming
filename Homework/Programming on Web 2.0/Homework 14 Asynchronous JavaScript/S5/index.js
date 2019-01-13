let app = new Ajax()
let inRobotState = false
let inRobotCounter = 0

let msg = {
  success: {
    a: '这是个天大的秘密',
    b: '我不知道',
    c: '你不知道',
    d: '他不知道',
    e: '才怪',
    sum: '楼主异步调用战斗力感人，目测不超过'
  },
  fail: {
    a: '这不是个天大的秘密',
    b: '我知道',
    c: '你知道',
    d: '他知道',
    e: '不怪',  // ...
    sum: '楼主异步调用战斗力感人，目测不低于'
  }
}

let handle = {
  a: null,
  b: null,
  c: null,
  d: null,
  e: null,
  sum: null
}

for (let method in handle) {
  if (method !== 'sum') {
    handle[method] = (counter, next) => {
      let node = document.getElementById(method + 'n')
      node.innerHTML = '...'
      node.style.visibility = 'visible'
      app.get('/', {}, (data) => {
        if (data.state === 'success') {
          node.innerHTML = data.text
          changeColorExceptX()
          document.getElementById('msg').innerHTML = msg.success[method]
        } else {
          node.style.visibility = 'hidden'
          changeColorExceptX()
          document.getElementById('msg').innerHTML = msg.fail[method]
        }
        let fn = next.shift()
        fn(counter + parseInt(data.text), next)
      })
      changeColorExceptX(method)
    }
  } else {
    handle[method] = (counter, next) => {
      let n = document.getElementById('info-bar')
      document.getElementById('sum').innerHTML = counter
      n.classList.remove('color-blue')
      n.classList.add('color-gray')
      if (counter === 0 || counter === null) {
        document.getElementById('msg').innerHTML = msg.fail[method] + counter
      } else {
        document.getElementById('msg').innerHTML = msg.success[method] + counter
      }
      inRobotState = false
    }
  }
}


let changeColorExceptX = function (x) {
  for (let t of 'abcde') {
    if (!x || t !== x) {
      let node = document.getElementById(t)
      if (node.classList.contains('color-blue')) {
        node.classList.remove('color-blue')
        node.classList.add('color-gray')
      } else if (document.getElementById(t + 'n').style.visibility === 'hidden') {
        node.classList.remove('color-gray')
        node.classList.add('color-blue')
      }
    }
  }
}

let click = function (alpha) {
  let node = document.getElementById(alpha + 'n')
  node.innerHTML = '...'
  node.style.visibility = 'visible'
  app.get('/', {}, (data) => {
    if (data.state === 'success') {
      node.innerHTML = data.text
      changeColorExceptX()
      for (let x of 'abcde') {
        if (document.getElementById(x + 'n').style.visibility === 'hidden') return
      }
      document.getElementById('info-bar').classList.remove('color-gray')
      document.getElementById('info-bar').classList.add('color-blue')
    } else {
      node.style.visibility = 'hidden'
      changeColorExceptX()
    }
  })
  changeColorExceptX(alpha)
}


let robotOperate = function () {
  inRobotState = true
  let arr = []
  let str = 'ABCDE'
  while (arr.length !== 5) {
    let x = Math.floor(Math.random() * 5)
    if (arr.includes(x) === false) arr.push(x)
  }
  for (let i = 0; i < 5; i++) {
    arr[i] = str[arr[i]]
  }
  document.getElementById('state').innerHTML = arr.toString()
  let fnArr = []
  for (let x of arr) {
    fnArr.push(handle[x.toLowerCase()])
  }
  fnArr.push(handle.sum)
  let fn = fnArr.shift()
  fn(0, fnArr)
}


let clickInfoBar = function () {
  let n = document.getElementById('info-bar')
  if (n.classList.contains('color-blue')) {
    let sum = 0
    for (let x of 'abcde') {
      sum += parseInt(document.getElementById(x + 'n').innerHTML)
    }
    document.getElementById('sum').innerHTML = sum
    n.classList.remove('color-blue')
    n.classList.add('color-gray')
  }
}

let init = function () {
  document.getElementById('button').onmouseleave = function () {
    for (let x of 'abcde') {
      document.getElementById(x).classList.remove('color-gray')
      document.getElementById(x).classList.add('color-blue')
      document.getElementById(x + 'n').style.visibility = 'hidden'
    }
    document.getElementById('info-bar').classList.remove('color-blue')
    document.getElementById('info-bar').classList.add('color-gray')
    document.getElementById('sum').innerHTML = ''
    document.getElementById('state').innerHTML = ''
    document.getElementById('msg').innerHTML = ''
  }

  document.getElementById('info-bar').onclick = function () {
    if (inRobotState === false) clickInfoBar()
  }

  document.getElementById('apb').onclick = robotOperate

  for (let x of 'abcde') {
    document.getElementById(x + 'n').style.visibility = 'hidden'
    document.getElementById(x).onclick = function () {
      if (document.getElementById(x + 'n').style.visibility === 'hidden' && inRobotState === false) click(x)
    }
  }
}

init()
