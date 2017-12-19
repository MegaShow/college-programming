function gameOver() {
  containerNow.removeChildren();
  containerOld.removeChildren();
  talk(['Game End!'], tmp);
  function tmp() {
    sssonButtonDown();
    app.stage.removeChildren();
  }
}


function start() {

  // game button
  var buttonStart = PIXI.Texture.fromImage('rc/gameStart.png');
  var buttonStartOn = PIXI.Texture.fromImage('rc/gameStartOn.png');
  var gameStart = PIXI.Sprite.fromImage('rc/gameStart.png');
  gameStart.interactive = true;
  gameStart.buttonMode = true;
  gameStart.on('pointerdown', onButtonDown);  // 按下按钮
  gameStart.on('pointerover', onButtonOver);  // 移动到按钮上方
  gameStart.on('pointerout', onButtonOut);    // 移动离开按钮*/
  gameStart.width = 200;
  gameStart.height = 80;
  gameStart.x = (app.renderer.width - gameStart.width) / 2;
  gameStart.y = 400;

  // game background
  var gameBG = PIXI.Sprite.fromImage('rc/gameBG.png');
  gameBG.width = app.renderer.width;
  gameBG.height = app.renderer.height;
  app.stage.addChild(containerNow);
  app.stage.addChild(containerOld);
  // updata
  containerNow.addChild(gameBG);
  containerNow.addChild(gameStart);


  // Button function
  function onButtonDown() {
    containerNow.removeChild(gameBG);
    containerNow.removeChild(gameStart);
    stageFirst();
  }

  function onButtonOver() {
    this.texture = buttonStartOn;
    this.y -= 10;
  }

  function onButtonOut() {
    this.texture = buttonStart;
    this.y += 10;
  }
}




function bppStart() {
  /*  document.body.appendChild(bpp.view);
    itemSprite = PIXI.Sprite.fromImage("rc/itemList.png");
    itemSprite.x = 0;
    itemSprite.y = 0;
    bpp.stage.addChild(itemSprite);
    itemSprite.interactive = true;
    itemSprite.buttonMode = true;
    itemSprite.on('pointerover', showItem);
    itemSprite.on('pointerout', hideItem);
  
    function showItem() {
      if (inContainerMove == false && inTalk == false && isWalk == false) {
        msgboxNew('hello, item!', 1);
        inItemMsgShow = true;
      }
    }
  
    function hideItem() {
      if (inItemMsgShow == true) {
        msgboxDel();
        inItemMsgShow = false;
      }
    }*/
}
