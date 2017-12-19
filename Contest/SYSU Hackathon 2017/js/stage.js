
function stageFirst() {
  var msgList = new Array('我是谁？', '我这是在哪里？');
  talk(msgList, tmp);

  function tmp() {
    bppStart();
    containerOld.alpha = 0.8;
    displayNow();
    containerOld.x = - app.renderer.width;
    containerOld.y = - app.renderer.height;
    updateTimeButton();
    stageGo();
  }
}



/*function stage2() {
  var gameBG2 = PIXI.Sprite.fromImage('rc/gameBG.png');
  var gameBG3 = PIXI.Sprite.fromImage('rc/gameStart.png');
  containerOld.addChild(gameBG3);
  containerNow.addChild(gameBG2);
  containerOld.alpha = 0.8;
  displayNow();
  updateTimeButton();

  var manBodyNow = PIXI.Sprite.fromImage('rc/take1.png');
  var manBodyOld = PIXI.Sprite.fromImage('rc/take1.png');

  manBodyNow.height = 200;
  manBodyNow.width = 100;
  manBodyOld.height = 200;
  manBodyOld.width = 100;
  containerNow.addChild(manBodyNow);
  containerOld.addChild(manBodyOld);

  moveTo(manBodyOld, 100, 600);

}*/

function stageGo() {
  // 移动
  var goStreet = PIXI.Sprite.fromImage('rc/go.png');
  var goStreetOld = PIXI.Sprite.fromImage('rc/go.png');
  npcCreate(goStreet, goStreetOld, 950, 425, funcGoStreet, funcGoStreet);

  function funcGoStreet() {
    if (nowtime) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }
    function tmp() {
      containerNow.removeChildren();
      containerOld.removeChildren();

      stageStreet();
    }

  }
  playerNow = PIXI.Sprite.fromImage('rc/taker.png');
  playerOld = PIXI.Sprite.fromImage('rc/staker.png');
  npcCreate(playerNow, playerOld, 800, 400, null, null);
}


//////////////////////////////////////////////////////////////////////////////////
// 五羊
function stagePark() {
  var gameBGNow = PIXI.Sprite.fromImage('rc/park.png');
  var gameBGOld = PIXI.Sprite.fromImage('rc/parkOld.png');
  createBG(gameBGNow, gameBGOld);

  var screenNow = PIXI.Sprite.fromImage('rc/blank.png');
  var screenOld = PIXI.Sprite.fromImage('rc/blank.png');
  screenNow.width = 400;
  screenNow.height = 200;
  screenOld.width = 400;
  screenOld.height = 200;
  npcCreate(screenNow, screenOld, 300, 250, screenFunc);

  function screenFunc() {
    if (nowtime && this == screenNow) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    }
    else if (nowtime == false && this == screenOld) {
      talk(['由岭南著名雕塑艺术家尹积昌、陈本宗、孔繁纬创作, 始建于1960年04月.',
        '作为广州的象征, 象征着幸福吉祥, 为广州迎来“羊城”, “穗城”的美誉.']);
    }
    function tmp() {
      clickGoat++;
      if (clickGoat == 3) {
        getItem(2);
      }
      else if (clickGoat < 3) {
        talk(['???: 这雕像弄得真是好逼真呀, 等等, 这里面好有什么东西?'])
      }
      else {
        talk(['???: 这雕像弄得真是好逼真呀.']);
      }
    }
  }


  // 老人(x)
  var npcWalkerNow = PIXI.Sprite.fromImage('rc/npcWalker.png');
  npcCreate(npcWalkerNow, null, 750, 300, npcWalkerClick);

  function npcWalkerClick() {
    if (nowtime && this == npcWalkerNow) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    }
    function tmp() {
      if (item[2] == true) {
        talk(["(递过收音机.)", "老人: 谢谢你啊, 我正好需要一部收音机."]);

      } else {
        talk(["老人: 得闲嚟呢度散散步, 几好啊!好想要一部收音机."]);
      }
    }
  }


  // 移动
  var goRiver = PIXI.Sprite.fromImage('rc/go.png');
  var goRiverOld = PIXI.Sprite.fromImage('rc/go.png');
  npcCreate(goRiver, goRiverOld, 950, 425, funcGoRiver);

  function funcGoRiver() {
    if (nowtime && this == goRiver) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else if (nowtime == false && this == goRiverOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }
    function tmp() {
      containerNow.removeChildren();
      containerOld.removeChildren();

      stageRiver();
      sssonButtonDown();
      sssonButtonDown();
    }

  }

  playerNow = PIXI.Sprite.fromImage('rc/taker.png');
  playerOld = PIXI.Sprite.fromImage('rc/staker.png');
  npcCreate(playerNow, playerOld, 0, 400, null);

}


//////////////////////////////////////////////////////////////////////
// 上下九
function stageStreet() {
  var gameBGNow = PIXI.Sprite.fromImage('rc/street.png');
  var gameBGOld = PIXI.Sprite.fromImage('rc/streetOld.png');
  createBG(gameBGNow, gameBGOld);

  var screenNow = PIXI.Sprite.fromImage('rc/blank.png');
  var screenOld = PIXI.Sprite.fromImage('rc/blank.png');
  screenNow.width = 600;
  screenNow.height = 50;
  screenOld.width = 600;
  screenOld.height = 50;
  npcCreate(screenNow, screenOld, 300, 100, screenFunc);

  function screenFunc() {
    if (nowtime && this == screenNow) {
      talk(['平安大戏院是广州市剧场的老字号, 自1953年创建, 以演出经营为主体, 粤剧、曲艺等多剧种演出.']);
    }
    else if (nowtime == false && this == screenOld) {
      talk(['平安大戏院是广州市剧场的老字号, 自1953年创建, 以演出经营为主体, 粤剧、曲艺等多剧种演出.']);
    }
  }

  // 鸡公榄(黄牛)
  var npcFoodNow = PIXI.Sprite.fromImage('rc/npcFood.png');
  var npcFoodOld = PIXI.Sprite.fromImage('rc/npcYellow.png');
  npcCreate(npcFoodNow, npcFoodOld, 750, 250, npcFoodClick);

  function npcFoodClick() {
    if (nowtime && this == npcFoodNow) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else if (nowtime == false && this == npcFoodOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }

    function tmp() {
      if (nowtime == true && isGirlLeave == false && isNeedFood == true && item[0] == false) {
        talk(["老汉: 鸡公榄要不要啊, 靓女?", "???: 给我一包."], function () { getItem(0); });
      }
      else if (nowtime == true) {
        talk(["老汉: 鸡公榄要不要啊, 靓女?"]);
      }
      else if (nowtime == false) {
        talk(["黄老汉: 走过路过不要错过啊, 全上下九我最便!", "???: ???"]);
      }
    }
  }


  // 小女孩(车夫)
  var npcGirlNow = isGirlLeave ? null : PIXI.Sprite.fromImage('rc/girlDown.png');
  var npcGirlOld = PIXI.Sprite.fromImage('rc/npcCar.png');
  npcCreate(npcGirlNow, npcGirlOld, 150, 300, npcGirlClick);

  function npcGirlClick() {
    if (nowtime && this == npcGirlNow) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else if (nowtime == false && this == npcGirlOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }
    function tmp() {
      if (nowtime == true && item[0] == true && isGirlLeave == false) {
        talk(["???: (递给小女孩鸡公榄)",
          "小女孩: 谢谢姐姐!",
          "???: 不客气.",
          "???: 这是什么?"], function () {
            getItem(1, function () {
              containerOld.x = 0;
              containerOld.y = 0;
              sssonButtonDown();
              setTimeout(function() { talk(['???: 我怎么变小了?']); }, 500);
            });
          });
        isGirlLeave = true;
      }
      else if (nowtime == true && isGirlLeave == false) {
        talk(["小女孩: 呜呜呜~我要鸡公榄嘛~呜~",
          "???: (这个小女孩好眼熟啊)"]);
        isNeedFood = true;
      }
      else if (nowtime == false) {
        talk(["壮年男子: 小姐坐车么?"]);
      }
    }
  }


  // 售票员(售票员)
  var npcSoldNow = PIXI.Sprite.fromImage('rc/npcSold.png');
  var npcSoldOld = PIXI.Sprite.fromImage('rc/npcSold.png');
  npcCreate(npcSoldNow, npcSoldOld, 550, 280, npcSoldClick);

  function npcSoldClick() {
    if (nowtime && this == npcSoldNow) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else if (nowtime == false && this == npcSoldOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }
    function tmp() {
      if (nowtime == 1) {
        talk(["售票员: 在这里卖了十多年票了, 什么时候才有出路.", "???: 母鸡啊!"]);
      } else if (nowtime == 0) {
        talk(["售票员: 你好, 我是这里的新职员, 不要跟老板说我偷懒哦.", "???: 嘤嘤嘤."]);
      }
    }
  }


  var goPart = PIXI.Sprite.fromImage('rc/go.png');
  var goPartOld = PIXI.Sprite.fromImage('rc/go.png');
  npcCreate(goPart, goPartOld, 950, 425, funcGoPart);

  function funcGoPart() {
    if (nowtime && this == goPart) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else if (nowtime == false && this == goPartOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }
    function tmp() {
      containerNow.removeChildren();
      containerOld.removeChildren();

      stagePark();

      sssonButtonDown();
      sssonButtonDown();
    }

  }

  playerNow = PIXI.Sprite.fromImage('rc/taker.png');
  playerOld = PIXI.Sprite.fromImage('rc/staker.png');
  npcCreate(playerNow, playerOld, 0, 400, null);

}


// 珠江
function stageRiver() {
  var gameBGNow = PIXI.Sprite.fromImage('rc/river.png');
  var gameBGOld = PIXI.Sprite.fromImage('rc/riverOld.png');
  createBG(gameBGNow, gameBGOld);

  var screenNow = PIXI.Sprite.fromImage('rc/blank.png');
  screenNow.width = 50;
  screenNow.height = 200;
  npcCreate(screenNow, null, 700, 0, screenFunc);

  function screenFunc() {
    if (nowtime && this == screenNow) {
      talk(['???: 好美的景色也为什么我以前没有注意到呢?',
        '???: 远方那是广州塔吧，或许什么时候我也可以去一下!']);
    }
  }

  //情侣
  var npcFriendNow = PIXI.Sprite.fromImage('rc/npcFriend.png');
  var npcFriendOld = PIXI.Sprite.fromImage('rc/npcFriend.png');
  npcCreate(npcFriendNow, npcFriendOld, 700, 275, npcFriendClick);

  function npcFriendClick() {
    if (nowtime && this == npcFriendNow) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else if (nowtime == false && this == npcFriendOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }

    function tmp() {
      if (nowtime == true) {
        talk(["女孩子:珠江边景色真美啊！", "男孩子: 是啊,不过你最美."]);
      }
      else if (nowtime == false) {
        talk(["女孩子: 这座城市好落后啊", "男孩子: 对啊，什么时候才能发展"]);
      }
    }
  }
  // 移动
  var goStreet = PIXI.Sprite.fromImage('rc/go.png');
  var goStreetOld = PIXI.Sprite.fromImage('rc/go.png');
  npcCreate(goStreet, goStreetOld, 950, 425, funcGoStreet);

  function funcGoStreet() {
    if (nowtime && this == goStreet) {
      moveTo(1, playerNow, this.x, this.y, tmp);
      moveTo(0, playerOld, this.x / 4, this.y / 4);
    } else if (nowtime == false && this == goStreetOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }
    function tmp() {
      containerNow.removeChildren();
      containerOld.removeChildren();

      stageStreet();

      sssonButtonDown();
      sssonButtonDown();

    }

  }

  var npcMonOld = PIXI.Sprite.fromImage('rc/npcMon.png');
  if (item[2] == true)
    npcCreate(null, npcMonOld, 250, 275, npcMonClick);

  function npcMonClick() {
    if (nowtime == false && this == npcMonOld) {
      moveTo(0, playerOld, this.x, this.y, tmp);
      moveTo(1, playerNow, this.x / 4, this.y / 4);
    }

    function tmp() {
      talk(["妈妈: 女儿我终于找到你了, 太开心了.",
        "???: 你是我妈妈么?",], function () { gameOver(); });
    }
  }

  playerNow = PIXI.Sprite.fromImage('rc/taker.png');
  playerOld = PIXI.Sprite.fromImage('rc/staker.png');
  npcCreate(playerNow, playerOld, 0, 400, null);


}



//////////////////////////////////////////////////

function npcCreate(npcNow, npcOld, x, y, func) {
  if (npcNow != null) {
    npcNow.x = x;
    npcNow.y = y;
    if (nowtime == 0) {
      npcNow.x = x / 4;
      npcNow.y = y / 4;
      npcNow.width = npcNow.width / 4;
      npcNow.height = npcNow.height / 4;
    }
    containerNow.addChild(npcNow);
    npcNow.interactive = true;
    npcNow.buttonMode = true;
    npcNow.on('pointerdown', func);
  }
  if (npcOld != null) {
    npcOld.x = x;
    npcOld.y = y;
    if (nowtime == 1) {
      npcOld.x = x / 4;
      npcOld.y = y / 4;
      npcOld.width = npcOld.width / 4;
      npcOld.height = npcOld.height / 4;
    }
    containerOld.addChild(npcOld);

    npcOld.interactive = true;
    npcOld.buttonMode = true;
    npcOld.on('pointerdown', func);
  }
}


function createBG(BGNow, BGOld) {
  BGNow.width = app.renderer.width / (nowtime ? 1 : 4);
  BGNow.height = app.renderer.height / (nowtime ? 1 : 4);
  BGOld.width = app.renderer.width / (nowtime ? 4 : 1);
  BGOld.height = app.renderer.height / (nowtime ? 4 : 1);
  containerNow.addChild(BGNow);
  containerOld.addChild(BGOld);
}



function getItem(type, func) {
  if (type >= 0 && type <= 10) {
    item[type] = true;
    talk(["获得" + itemStr[type]], func);
  }
}
