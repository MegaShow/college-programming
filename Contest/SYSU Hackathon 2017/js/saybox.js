var mysaybox = PIXI.Sprite.fromImage('rc/saybox.png');
var richText = new PIXI.Text(0, style);


// call function
function talk(msgList, func) {
  inTalk = true;
  var click = PIXI.Sprite.fromImage('rc/saybox.png');
  click.alpha = 0;
  click.width = app.renderer.width;
  click.height = app.renderer.height;
  click.interactive = true;
  click.buttonMode = true;
  click.on('pointerdown', onClick);
  app.stage.addChild(click);
  msgboxNew(msgList[0], 1);
  var msgCount = 1;

  function onClick() {
    /*if (msgCount == 0) {
      app.stage.removeChild(click);
    }*/
    if (msgCount < msgList.length) {
      msgboxDel();
      msgboxNew(msgList[msgCount], 1);
      msgCount++;
    }
    else if (msgCount == msgList.length) {
      msgboxDel();
      msgCount = 0;
      app.stage.removeChild(click);
      inTalk = false;
      if (func != null)
        func();
    }
  }
}



/////////////////////////////////////////////////////////////

var style = new PIXI.TextStyle({
  fontFamily: 'Arial',
  fontSize: 36,
  fontStyle: 'italic',
  fontWeight: 'bold',
  fill: ['#ffffff', '#00ff99'],  // gradient
  stroke: '#4a1850',
  strokeThickness: 5,
  dropShadow: true,
  dropShadowColor: '#000000',
  dropShadowBlur: 4,
  dropShadowAngle: Math.PI / 6,
  dropShadowDistance: 6,
  wordWrap: true,
  wordWrapWidth: 1000
});


function msgboxNew(mytext, pos) {
  richText = new PIXI.Text(mytext, style);
  if (pos) {
    mysaybox.y = 407;
    richText.y = 427;
  } else {
    mysaybox.y = 0;
    richText.y = 20;
  }
  richText.x = 30;
  app.stage.addChild(mysaybox);
  app.stage.addChild(richText);
}


function msgboxDel() {
  richText.destroy()
  app.stage.removeChild(richText);
  app.stage.removeChild(mysaybox);
}
