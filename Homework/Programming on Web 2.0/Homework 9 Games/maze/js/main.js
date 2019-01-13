// MegaShow
let gameStateStart = false;
let gameStateInBox = false;
let gameWallRed = null;

let GameInit = function () {
  document.getElementById('buttonS').onmouseenter = function () {
    gameStateStart = true;
    gameStateInBox = true;
    document.getElementById('gameBox').className = 'game-box game-box-in-game';
    document.getElementById('gameState').innerHTML = 'In game!';
  };

  document.getElementById('buttonE').onmouseenter = function () {
    if (gameStateStart === false) {
      document.getElementById('gameState').innerHTML = 'Please start from \'S\'!';
    } else if (gameStateStart === true && gameStateInBox === false) {
      document.getElementById('gameState').innerHTML = 'Don\'t cheat, you should start from the \'S\' and move to the \'E\' inside the maze!';
    } else {
      document.getElementById('gameState').innerHTML = 'You win!';
    }
    gameStateStart = false;
    document.getElementById('gameBox').className = 'game-box';
  };

  document.getElementById('gameBox').onmouseleave = function () {
    gameStateInBox = false;
  };

  for (let x of document.getElementsByClassName('game-wall')) {
    x.onmouseover = function (e) {
      if (gameStateStart === true) {
        document.getElementById('gameState').innerHTML = 'You lose!';
        e.target.className = e.target.className + ' game-wall-red';
        gameWallRed = e.target;
        gameStateStart = false;
        document.getElementById('gameBox').className = 'game-box';
      }
    };

    x.onmouseout = function (e) {
      if (gameWallRed === e.target) {
        gameWallRed.className = gameWallRed.className.replace(' game-wall-red', '');
        gameWallRed = null;
      }
    }
  }
};

GameInit();
