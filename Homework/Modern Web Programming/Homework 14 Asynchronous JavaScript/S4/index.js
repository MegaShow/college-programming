let app = new Ajax()
let inButtonState = false
let inRobotState = false
let inRobotCounter = 0

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
  let callback = function (i) {
    let node = document.getElementById(arr[i].toLowerCase() + 'n')
    node.innerHTML = '...'
    node.style.visibility = 'visible'
    app.get('/', {}, (data) => {
      if (inButtonState) {
        if (data.state === 'success') {
          node.innerHTML = data.text
          changeColorExceptX()
          if (i === 4 && inButtonState) {
            document.getElementById('info-bar').classList.remove('color-gray')
            document.getElementById('info-bar').classList.add('color-blue')
            clickInfoBar()
            inRobotState = false
          } else if (inButtonState) callback(i + 1)
        } else {
          node.style.visibility = 'hidden'
          changeColorExceptX()
          inRobotState = false
        }
      }
    })
    changeColorExceptX(arr[i].toLowerCase())
  }
  callback(0)
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
    inButtonState = false
    for (let x of 'abcde') {
      document.getElementById(x).classList.remove('color-gray')
      document.getElementById(x).classList.add('color-blue')
      document.getElementById(x + 'n').style.visibility = 'hidden'
    }
    document.getElementById('info-bar').classList.remove('color-blue')
    document.getElementById('info-bar').classList.add('color-gray')
    document.getElementById('sum').innerHTML = ''
    document.getElementById('state').innerHTML = ''
  }

  document.getElementById('button').onmouseenter = function () {
    inButtonState = true
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
