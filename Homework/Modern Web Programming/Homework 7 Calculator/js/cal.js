// MegaShow

let new_loop = true; // 等待CE新的一轮
let wait_for_new_val = true; // 处于刚输入数字状态
let wait_for_val = true; // 处于输入数字状态
let wait_for_lpth = true; // 处于输入左括号状态
let wait_for_opr = false; // 处于输入操作符状态
let wait_for_rpth = 0; // 需要的右括号个数
let lpth_index = new Array(); // 需要匹配的左括号位置

let exp = document.getElementById('win-exp');
let res = document.getElementById('win-res');


document.onkeydown = function (e) {
  let keycode = e.keyCode || e.which || e.charCode;;
  let shiftcode = e.shiftKey;
  let realkey = String.fromCharCode(e.which);
  //alert("按键码: " + keycode + " 字符: " + realkey);
  if (!shiftcode && isVal(realkey)) {
    clickNumberButton(realkey);
  } else if (keycode == 110 || keycode == 190) {
    clickNumberButton('.');
  } else if (keycode >= 96 && keycode <= 105) {
    clickNumberButton(keycode - 96);
  } else if (keycode == 107 || (shiftcode && keycode == 187)) {
    clickOperatingButton('+');
  } else if (keycode == 109 || (shiftcode && keycode == 189)) {
    clickOperatingButton('-');
  } else if (keycode == 106 || (shiftcode && keycode == 56)) {
    clickOperatingButton('*');
  } else if (keycode == 111 || keycode == 191) {
    clickOperatingButton('/');
  } else if (keycode == 187 /* || keycode == 13 */) {
    clickOperatingButton('=');
  } else if (keycode == 8) {
    clickOperatingButtonBackSpcae();
  } else if (shiftcode && keycode == 57) {
    clickParenthesesButton('(');
  } else if (shiftcode && keycode == 48) {
    clickParenthesesButton(')');
  }
};


let isVal = function (c) { return '0123456789.'.indexOf(c) != -1; };
let isOpr = function (c) { return '+-*/'.indexOf(c) != -1; };
let hasDP = function (str) { return str.indexOf('.') != -1; };


let clickNumberButton = function (val) {
  if (new_loop) {
    setExpInnerHTML('');
    new_loop = false;
  }
  if (wait_for_val) {
    if (wait_for_new_val) {
      setResInnerHTML('0');
    }
    wait_for_new_val = false;
    wait_for_lpth = false;
    wait_for_opr = true;
    if (res.innerHTML == '0' && val != '.') {
      setResInnerHTML(val);
    } else if (val == '.' && hasDP(res.innerHTML)) {
      return false;
    } else {
      setResInnerHTML(res.innerHTML + val);
      if (res.innerHTML.length >= 13) {
        let str = exp.innerHTML;
        clickOperatingButtonCE();
        setResInnerHTML('数据太大');
        setExpInnerHTML(str);
      }
    }
  }
};


let clickOperatingButton = function (opr) {
  if (new_loop) {
    setExpInnerHTML('');
    new_loop = false;
  }
  if (wait_for_new_val && !wait_for_opr && opr == '-') {
    setExpInnerHTML(exp.innerHTML + '0-');
  }
  if (wait_for_opr) {
    if (exp.innerHTML[exp.innerHTML.length - 1] == '=') {
      setExpInnerHTML('');
    }
    if (opr == '=' && wait_for_rpth != 0) {
      return false;
    }
    if (opr != '=') {
      wait_for_opr = false;
    }
    wait_for_new_val = true;
    wait_for_lpth = true;
    wait_for_val = true;
    if (exp.innerHTML[exp.innerHTML.length - 1] != ')') {
      setExpInnerHTML(exp.innerHTML + res.innerHTML);
    }
    setResInnerHTML(calculatorEval());
    if (res.innerHTML != '结果未定义' && res.innerHTML != '除数不能为零') {
      setExpInnerHTML(exp.innerHTML + opr);
    }
  } else {
    if (isOpr(exp.innerHTML[exp.innerHTML.length - 1]) && isOpr(opr)) {
      setExpInnerHTML(exp.innerHTML.substring(0, exp.innerHTML.length - 1) + opr);
    }
  }
};


let clickOperatingButtonCE = function () {
  new_loop = true;
  wait_for_new_val = true; // 处于刚输入数字状态
  wait_for_val = true; // 处于输入数字状态
  wait_for_lpth = true; // 处于输入左括号状态
  wait_for_opr = false; // 处于输入操作符状态
  wait_for_rpth = 0; // 需要的右括号个数
  lpth_index = [];
  setResInnerHTML('0');
  setExpInnerHTML('');
};


let clickOperatingButtonBackSpcae = function () {
  if (new_loop) {
    setExpInnerHTML('');
    new_loop = false;
  }
  if (res.innerHTML.length != 0) {
    setResInnerHTML(res.innerHTML.substring(0, res.innerHTML.length - 1));
    if (res.innerHTML.length == 0) {
      setResInnerHTML('0');
      wait_for_new_val = true;
      wait_for_opr = false;
    }
  } else {

  }
};


let clickParenthesesButton = function (opr) {
  if (new_loop) {
    setExpInnerHTML('');
    new_loop = false;
  }
  if (opr == '(' && wait_for_lpth) {
    if (exp.innerHTML[exp.innerHTML.length - 1] == '=') {
      setExpInnerHTML('');
    }
    wait_for_val = true;
    wait_for_new_val = true;
    wait_for_opr = false;
    wait_for_lpth = true;
    wait_for_rpth += 1;
    setExpInnerHTML(exp.innerHTML + '(');
    lpth_index.push(exp.innerHTML.length - 1);
  } else if (opr == ')' && wait_for_rpth != 0 && wait_for_opr) {
    wait_for_new_val = false;
    wait_for_val = false;
    wait_for_opr = true;
    wait_for_lpth = false;
    wait_for_rpth -= 1;
    if (exp.innerHTML[exp.innerHTML.length - 1] != ')') {
      setExpInnerHTML(exp.innerHTML + res.innerHTML);
    }
    setResInnerHTML(calculatorEval());
    if (res.innerHTML != '结果未定义' && res.innerHTML != '除数不能为零') {
      setExpInnerHTML(exp.innerHTML + opr);
      lpth_index.pop();
    }
  }
};


let calculatorEval = function () {
  try {
    let index = 0;
    if (lpth_index.length != 0) {
      index = lpth_index[lpth_index.length - 1] + 1;
    }
    let calculator_result = eval(exp.innerHTML.substring(index));
    //console.log(calculator_result);
    if (isNaN(calculator_result)) {
      let str = exp.innerHTML;
      clickOperatingButtonCE();
      setExpInnerHTML(str);
      return '结果未定义';
    } else if (!isFinite(calculator_result)) {
      let str = exp.innerHTML;
      clickOperatingButtonCE();
      setExpInnerHTML(str);
      return '除数不能为零';
    }
    let m = Math.pow(10, 6);
    let n = parseInt(calculator_result * m + 0.5, 10);
    return n / m;
  } catch (e) {
    console.log('Exception: ' + e);
  }
}



for (let x of document.getElementsByClassName('btn-val')) {
  x.onclick = function () {
    clickNumberButton(x.innerHTML);
  };
}

for (let x of document.getElementsByClassName('btn-opr')) {
  x.onclick = function () {
    if (x.innerHTML == 'CE') {
      clickOperatingButtonCE();
    } else if (x.innerHTML == '←') {
      clickOperatingButtonBackSpcae();
    } else {
      clickOperatingButton(x.innerHTML);
    }
  }
}

for (let x of document.getElementsByClassName('btn-pth')) {
  x.onclick = function () {
    clickParenthesesButton(x.innerHTML);
  }
}


// set innerHTML
let setResInnerHTML = function (str) {
  if (str.length >= 12) {
    let s = exp.innerHTML;
    clickOperatingButtonCE();
    setExpInnerHTML(s);
    res.innerHTML = "数据太大";
    return false;
  }
  res.innerHTML = str;
}

let setExpInnerHTML = function (str) {
  if (str.length >= 35) {
    let s = exp.innerHTML;
    clickOperatingButtonCE();
    setExpInnerHTML(s);
    res.innerHTML = "表达式过长";
    return false;
  }
  exp.innerHTML = str;
}
