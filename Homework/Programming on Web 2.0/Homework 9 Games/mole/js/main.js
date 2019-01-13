// MegaShow

window.onload = function () {
  let gameBox = document.getElementById('game-box');
  for (let i = 0; i < 60; i++) {
    let node = document.createElement('input');
    node.id = 'mole-' + i;
    node.type = 'radio';
    node.value = i;
    node.onclick = function (e) {
      if (gameStateStart === true && gameStatePause == false) {
        e.target.checked = false;
        if (e.target.value === moleId.toString()) {
          gameScore++;
          document.getElementById('gameScore').value = gameScore;
          CreateMole();
        } else {
          gameScore--;
          document.getElementById('gameScore').value = gameScore;
        }
      } else if (e.target.value !== moleId.toString()) {
        e.target.checked = false;
      }
    };
    gameBox.appendChild(node);
  }
};


let gameStateStart = false;
let gameStatePause = false;
let gameStateOver = false;
let gameTime = 30;
let gameScore = 0;
let timeId = 0;
let moleId = -1;


let GameInit = function () {
  document.getElementById('gameStart').onclick = function () {
    GameStart();
  };
  UpdateState();
};

let CreateMole = function () {
  moleId = Math.round(Math.random() * 59);
  document.getElementById('mole-' + moleId).checked = true;
};

let FuncTimer = function () {
  if (gameTime > 0) {
    gameTime--;
  } else {
    document.getElementById('mole-' + moleId).checked = false;
    moleId = -1;
    window.clearInterval(timeId);
    gameStateStart = false;
    gameStatePause = false;
    gameStateOver = true;
    alert('Game Over!\nYour score is ' + gameScore + '.');
  }
  UpdateState();
};


let GameStart = function () {
  if (gameStateStart === false) {
    gameStateStart = true;
    gameTime = 30;
    gameScore = 0;
    CreateMole();
    timeId = setInterval(FuncTimer, 1000);
  } else if (gameStateStart === true && gameStatePause === false) {
    gameStatePause = true;
    window.clearInterval(timeId);
  } else if (gameStateStart === true && gameStatePause === true) {
    gameStatePause = false;
    timeId = setInterval(FuncTimer, 1000);
  }
  UpdateState();
};


let UpdateState = function () {
  document.getElementById('gameTime').value = gameTime;
  document.getElementById('gameScore').value = gameScore;
  if (gameStateStart === false && gameStateOver === false) {
    document.getElementById('gameStart').innerHTML = 'Start Game';
    document.getElementById('gameState').value = '~Nothing~';
  } else if (gameStateStart === false && gameStateOver === true) {
    document.getElementById('gameStart').innerHTML = 'Start Game';
    document.getElementById('gameState').value = '~Game Over~';
  } else if (gameStateStart === true && gameStatePause === false) {
    document.getElementById('gameStart').innerHTML = 'Pause Game';
    document.getElementById('gameState').value = '~In Game~';
  } else if (gameStateStart === true && gameStatePause === true) {
    document.getElementById('gameStart').innerHTML = 'Start Game';
    document.getElementById('gameState').value = '~Pause~';
  }
};



GameInit();
