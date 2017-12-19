function moveTo(num,man, posX, posY,func) {

  if(isWalk == true)
    return;
  isWalk = true;
  if(man == null)
    return;
  var swalkR1 = PIXI.Texture.fromImage('rc/swalkr1.png');
  var swalkR2 = PIXI.Texture.fromImage('rc/swalkr2.png');
  var swalkL1 = PIXI.Texture.fromImage('rc/swalkl1.png');
  var swalkL2 = PIXI.Texture.fromImage('rc/swalkl2.png');
  var walkR1 = PIXI.Texture.fromImage('rc/walkr1.png');
  var walkR2 = PIXI.Texture.fromImage('rc/walkr2.png');
  var walkL1 = PIXI.Texture.fromImage('rc/walkl1.png');
  var walkL2 = PIXI.Texture.fromImage('rc/walkl2.png');
  var stakeL = PIXI.Texture.fromImage('rc/stakel.png');
  var stakeR = PIXI.Texture.fromImage('rc/staker.png');
  var takeL = PIXI.Texture.fromImage('rc/takel.png');
  var takeR = PIXI.Texture.fromImage('rc/taker.png');
  var takeover;
  var walk1;
  var walk2;
  var takeTime = new PIXI.ticker.Ticker();
  takeTime.started = false;
  takeTime.deltaTime = 10;
  takeTime.speed = 10;
  var count_m = 0;
  var movespeedx = (posX - man.x);
  var movespeedy = (posY - man.y);
  if(movespeedx > 0){
    movespeedx = 10;
    if(num){
      walk1 = walkR1;
      walk2 = walkR2;
      takeover = takeR;
    } else {
      walk1 = swalkR1;
      walk2 = swalkR2;
      takeover = stakeR;
    }
  } else {
    movespeedx = -10;
    if(num){
      walk1 = walkL1;
      walk2 = walkL2;
      takeover = takeL;
    } else {
      walk1 = swalkL1;
      walk2 = swalkL2;
      takeover = stakeL;
    }
  }
  if(movespeedy > 0){
    movespeedy = 10;
  } else {
    movespeedy = -10;
  }
  takeTime.add(function(){
    count_m++;
    if (count_m > 2) count_m = 0;

    switch (count_m) {
      case 1:
      man.texture = walk1;
      break;
      case 2:
      man.texture = walk2;
      break;
    }
    if (Math.abs(posX - man.x) < 15 && Math.abs(posY - man.y) < 15){
      takeTime.stop();
      takeTime.destroy();
      man.texture = takeover;
      if(func != null)
        func();
      isWalk = false;

    }
    if (Math.abs(posX - man.x) > 11) {
      man.x += movespeedx;
    }
    if (Math.abs(posY - man.y) > 11) {
      man.y += movespeedy;
    }
  });
  takeTime.start();
}
