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
  for (let x of 'abced') {
    let node = document.getElementById(x + 'n')
    node.innerHTML = '...'
    node.style.visibility = 'visible'
    // url不同用于防止chrome ajax缓存策略
    app.get('/' + x, {}, (data) => {
      if (data.state === 'success') {
        node.innerHTML = data.text
        inRobotCounter += 1
        document.getElementById(x).classList.remove('color-blue')
        document.getElementById(x).classList.add('color-gray')
        if (inRobotCounter === 5 && inButtonState) {
          document.getElementById('info-bar').classList.remove('color-gray')
          document.getElementById('info-bar').classList.add('color-blue')
          clickInfoBar()
          inRobotState = false
          inRobotCounter = 0
        }
      } else {
        node.style.visibility = 'hidden'
        inRobotState = false
      }
    })
  }
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
