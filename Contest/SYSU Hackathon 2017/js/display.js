
var containerOld = new PIXI.Container();
containerOld.width = app.renderer.width;
containerOld.height = app.renderer.height;
var containerNow = new PIXI.Container();
containerNow.width = app.renderer.width;
containerNow.height = app.renderer.height;
var buttonChange = PIXI.Sprite.fromImage('rc/change.png');



//按钮
var buttonChangeUP = PIXI.Texture.fromImage('rc/change.png');
var buttonChangeOn = PIXI.Texture.fromImage('rc/change.png');


function updateTimeButton() {
  buttonChange.y = 10;
  buttonChange.width = 50;
  buttonChange.height = 50;
  buttonChange.interactive = true;
  buttonChange.buttonMode = true;
  buttonChange.x = app.renderer.width - buttonChange.width;
  buttonChange.on('pointerdown', sssonButtonDown);  // 按下按钮
  buttonChange.on('pointerover', onButtonOver);  // 移动到按钮上方
  buttonChange.on('pointerout', onButtonOut);    // 移动离开按钮*/
  app.stage.addChild(buttonChange);


  function onButtonOver() {
    this.y -= 10;
    //this.texture = buttonChangeOn;
  }

  function onButtonOut() {
    this.y += 10;
    //this.texture = buttonChangeUP;
  }
}


function sssonButtonDown() {
  if (isGirlLeave == true) {
    if (nowtime) {
      displayOld();
      nowtime = 0;
    } else {
      displayNow();
      nowtime = 1;
    }
  }
}
//////////////////////////////////////////////////////////

function onDragStart(event) {
  this.data = event.data;
  this.alpha = 0.5;
  this.dragging = true;
  inContainerMove = true;
}

function onDragEnd() {
  this.alpha = 0.8;
  this.dragging = false;
  this.data = null;
  if (this.x > app.renderer.width - this.width)
    this.x = app.renderer.width - this.width;
  if (this.x < 0)
    this.x = 0;
  if (this.y > app.renderer.height - this.height)
    this.y = app.renderer.height - this.height;
  if (this.y <= 0)
    this.y = 0;
  inContainerMove = false;
}

function onDragMove() {
  if (this.dragging) {
    var newPosition = this.data.getLocalPosition(this.parent);
    this.x = newPosition.x - this.width / 2;
    this.y = newPosition.y - this.height / 2;
  }
}
function displayNow() {
  containerOld.x = containerNow.x;
  containerOld.y = containerNow.y;
  containerNow.x = 0;
  containerNow.y = 0;
  containerNow.alpha = 1;
  containerOld.alpha = 0.8;
  containerNow.width = app.renderer.width;
  containerNow.height = app.renderer.height;
  containerOld.width = app.renderer.width / 4;
  containerOld.height = app.renderer.height / 4;
  app.stage.removeChild(containerNow);
  app.stage.removeChild(containerOld);
  app.stage.removeChild(buttonChange);
  app.stage.addChild(containerNow);
  app.stage.addChild(containerOld);
  app.stage.addChild(buttonChange);

  containerNow.interactive = false;
  containerNow.buttonMode = false;
  containerOld.interactive = true;
  containerOld.buttonMode = true;
  containerOld.on('pointerdown', onDragStart)
    .on('pointerup', onDragEnd)
    .on('pointerupoutside', onDragEnd)
    .on('pointermove', onDragMove);
}


function displayOld() {
  containerNow.x = containerOld.x;
  containerNow.y = containerOld.y;
  containerOld.x = 0;
  containerOld.y = 0;
  containerOld.alpha = 1;
  containerNow.alpha = 0.8;
  containerOld.width = app.renderer.width;
  containerOld.height = app.renderer.height;
  containerNow.width = app.renderer.width / 4;
  containerNow.height = app.renderer.height / 4;
  app.stage.removeChild(containerNow);
  app.stage.removeChild(containerOld);
  app.stage.removeChild(buttonChange);
  app.stage.addChild(containerOld);
  app.stage.addChild(containerNow);
  app.stage.addChild(buttonChange);
  // containerNow.anchor.set(0.5);
  // containerNow.scale.set(3);
  containerOld.interactive = false;
  containerOld.buttonMode = false;
  containerNow.interactive = true;
  containerNow.buttonMode = true;
  containerNow.on('pointerdown', onDragStart)
    .on('pointerup', onDragEnd)
    .on('pointerupoutside', onDragEnd)
    .on('pointermove', onDragMove);
}
