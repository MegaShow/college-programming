var inTalk = false;          // 是否在对话
var isWalk = false;          // 行走
var inContainerMove = false; // 容器是否拖动状态
var inItemMsgShow = false;   // 是否展示item
var process = 0;             // 主线进程
var sprite = new Array();    // 精灵
var nowtime = true;          // 是否在现在时间

var itemSprite;              // 物品栏精灵
var item = new Array(false, false, false);      // 物品是否拥有

var itemStr = new Array('鸡公榄', '旧照片', '收音机');
var clickGoat = 0;



var player;

var isNeedFood = false;      // 小女孩是否需要食物
var isGirlLeave = false;     // 小女孩获取鸡公榄之后离开



// player
var playerNow = PIXI.Sprite.fromImage('rc/taker.png');
var playerOld = PIXI.Sprite.fromImage('rc/staker.png');
