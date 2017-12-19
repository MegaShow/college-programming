// MegaShow
let gameStateStart = false;
let gameBox = null;
let step = 0;

let GameInit = function () {
  gameBox = document.getElementById('gameBox');
  for (let i = 0; i < 15; i++) {
    let div = document.createElement('div');
    div.id = 'gamePic' + i;
    div.setAttribute('pos', i);
    div.classList.add('game-pic-left-' + (i % 4), 'game-pic-top-' + Math.floor(i / 4), 'game-bg-' + i);
    div.onclick = GamePicButtonClick;
    gameBox.appendChild(div);
  }
  let span = document.createElement('span');
  span.id = 'gameBlank';
  span.setAttribute('pos', 15);
  span.classList.add('game-blank', 'game-pic-left-3', 'game-pic-top-3');
  gameBox.appendChild(span);
  document.getElementById('gameButton').onclick = GameButtonClick;
};


let GameButtonClick = function () {
  if (gameStateStart === false) {
    gameStateStart = true;
    document.getElementById('gameButton').innerHTML = '重新开始';
  } else {
    for (let i = 0; i < 15; i++) {
      let x = document.getElementById('gamePic' + i);
      x.className = 'game-pic-left-' + (i % 4) + ' game-pic-top-' + Math.floor(i / 4) + ' game-bg-' + i;
      x.setAttribute('pos', i);
    }
    document.getElementById('gameBlank').className = 'game-blank game-pic-left-3 game-pic-top-3';
    document.getElementById('gameBlank').setAttribute('pos', 15);
  }
  GamePicRandom(200);
  step = 0;
  document.getElementById('gameStep').innerHTML = step;
};


let GamePicButtonClick = function () {
  if (gameStateStart === false) {
    return;
  }
  let divPos = parseInt(this.getAttribute('pos'));
  let span = document.getElementById('gameBlank');
  let spanPos = parseInt(span.getAttribute('pos'));
  if ((divPos - 1 === spanPos && divPos % 4 !== 0) ||  // left
      (divPos + 1 === spanPos && spanPos % 4 !== 0) ||  // right
      (divPos + 4 === spanPos) ||  // down
      (divPos - 4 === spanPos)) {  // up
    this.classList.remove('game-pic-left-' + divPos % 4, 'game-pic-top-' + Math.floor(divPos / 4));
    this.classList.add('game-pic-left-' + spanPos % 4, 'game-pic-top-' + Math.floor(spanPos / 4));
    this.setAttribute('pos', spanPos);
    span.classList.remove('game-pic-left-' + spanPos % 4, 'game-pic-top-' + Math.floor(spanPos / 4));
    span.classList.add('game-pic-left-' + divPos % 4, 'game-pic-top-' + Math.floor(divPos / 4));
    span.setAttribute('pos', divPos);
    step++;
    document.getElementById('gameStep').innerHTML = step;
  }
  if (divPos === 15) {
    let flag = true;
    for (let i = 0; i < 15; i++) {
      if (parseInt(document.getElementById('gamePic' + i).getAttribute('pos')) !== i) {
        flag = false;
        break;
      }
    }
    if (flag === true) {
      alert('You win ~ - ~ ' + step + ' steps');
      gameStateStart = false;
    }
  }
};


let GamePicRandom = function (count) {
  let arr = [];
  let index = 15;
  for (let x = 0; x < 16; x++) {
    arr[x] = x;
  }
  for (let i = 0; true; i++) {
    if (i >= 10000) {
      alert('Puzzle: something wrong ~ TAT ~ please refresh the website ~');
      break;
    } else if (i >= count && index === 15) {
      break;
    }
    let opr = Math.floor(Math.random() * 4);
    switch (opr) {
      // blank to left
      case 0: {
        if (index % 4 !== 0) {
          arr[index] = arr[index - 1];
          index--;
        }
        break;
      }
      // blank to right
      case 1: {
        if (index % 4 !== 3) {
          arr[index] = arr[index + 1];
          index++;
        }
        break;
      }
      // blank to up
      case 2: {
        if (index > 3) {
          arr[index] = arr[index - 4];
          index -= 4;
        }
        break;
      }
      // blank to down
      case 3: {
        if (index < 12) {
          arr[index] = arr[index + 4];
          index += 4;
        }
        break;
      }
    }
  }
  for (let i = 0; i < 15; i++) {
    let x = document.getElementById('gamePic' + i);
    x.className = 'game-pic-left-' + (arr[i] % 4) + ' game-pic-top-' + Math.floor(arr[i] / 4) + ' game-bg-' + i;
    x.setAttribute('pos', arr[i]);
  }
};


GameInit();
