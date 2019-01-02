
Program PL0;
{带有代码生成的PL0编译程序}

Const
  norw = 11;   {保留字的个数}
  txmax = 100; {标识符表长度}
  nmax = 14;   {数字的最大位数}
  al = 10;     {标识符的长度}
  amax = 2047; {最大地址}
  levmax = 3;  {程序体嵌套的最大深度}
  cxmax = 200; {代码数组的大小}

Type
  symbol = (nul, ident, number, plus, minus, times, slash, oddsym,
    eql, neq, lss, leq, gtr, geq, lparen, rparen, comma, semicolon,
    period, becomes, beginsym, endsym, ifsym, thensym,
    whilesym, dosym, callsym, constsym, varsym, procsym);
  alfa = packed array [1..al] Of char;
  objecttype = (constant, variable, procedures);
  symset = set Of symbol;
  fct = (lit, opr, lod, sto, cal, int, jmp, jpc); {functions}
  instruction = packed Record
    f : fct;       {功能码}
    l : 0..levmax; {相对层数}
    a : 0..amax;   {相对地址}
  End;

{LIT 0,a : 取常数a}
{OPR 0,a : 执行运算a}
{LOD l,a : 取层差为l的层﹑相对地址为a的变量}
{STO l,a : 存到层差为l的层﹑相对地址为a的变量}
{CAL l,a : 调用层差为l的过程}
{INT 0,a : t寄存器增加a}
{JMP 0,a : 转移到指令地址a处}
{JPC 0,a : 条件转移到指令地址a处}

Var
  ch: char; {最近读到的字符}
  sym: symbol; {最近读到的符号}
  id: alfa; {最近读到的标识符}
  num: integer; {最近读到的数}
  cc: integer; {当前行的字符计数}
  ll: integer; {当前行的长度}
  kk, err: integer;
  cx: integer; {代码数组的当前下标}
  line: array [1..81] Of char; {当前行}
  a: alfa; {当前标识符的字符串}
  code: array [0..cxmax] Of instruction; {中间代码数组}
  word: array [1..norw] Of alfa; {存放保留字的字符串}
  wsym: array [1..norw] Of symbol; {存放保留字的记号}
  ssym: array [char] Of symbol; {存放算符和标点符号的记号}
  mnemonic: array [fct] Of packed array [1..3] Of char;
  {中间代码算符的字符串}
  declbegsys, statbegsys, facbegsys: symset;
  table: array [0..txmax] Of {符号表}
    Record
      name: alfa;
      Case kind: objecttype Of
        constant: (val: integer);
        variable, procedures: (level, adr: integer)
    End;
  fin, fout, foutStack, foutAsm: textfile;

{结束程序处理}
Procedure programExit;
Begin
  close(fin);
  close(fout);
  close(foutStack);
  close(foutAsm);
  exit;
End; {programExit}

{错误处理}
Procedure error(n: integer);
Begin
  writeln(fout, '*****', ' ':cc-1, '^', n:2);
  err := err + 1
  {cc为当前行已读的字符数, n为错误号, 错误数err加1}
End; {error}


{词法分析}
Procedure getsym;
Var i, j, k: integer;
{获取下一个字符}
Procedure getch;
Begin
  If cc = ll Then {如果cc指向行末}
    Begin
      If eof(fin) Then
        Begin
          writeln('Program Incomplete');
          programExit;
        End;
      {读新的一行}
      ll := 0;
      cc := 0;
      write(fout, cx:5, ' ');
      While Not eoln(fin) Do
        Begin
          ll := ll + 1;
          read(fin, ch);
          write(fout, ch);
          line[ll] := ch;
        End;
      writeln(fout);
      ll := ll + 1;
      readln(fin, line[ll]); {line[ll]中是行末符}
    End;
  cc := cc + 1;
  ch := line[cc] {ch取line中下一个字符}
End; {getch}

Begin {getsym}
  While (ch = ' ') Or (ord(ch) = 10) Or (ord(ch) = 13) Do
    getch; {跳过无用空白}
  If ch In ['A'..'Z', 'a'..'z'] Then
    Begin {标识符或保留字}
      k := 0;
      Repeat
        If k < al Then
          Begin
            k := k + 1;
            a[k] := ch
          End;
        getch
      Until Not (ch In ['A'..'Z', 'a'..'z', '0'..'9']);
      If k >= kk Then kk := k
      Else
        Repeat {如果标识符长度不是最大长度, 后面补空白}
          a[kk] := ' ';
          kk := kk - 1
        Until kk = k;
      id := a; {id中存放当前标识符或保留字的字符串}
      i := 1;
      j := norw;
      Repeat {用二分查找法在保留字表中找当前的标识符id}
        k := (i + j) Div 2;
        If id <= word[k] Then j := k - 1;
        If id >= word[k] Then i := k + 1
      Until i > j;
      {如果找到, 当前记号sym为保留字, 否则sym为标识符}
      If i - 1 > j Then sym := wsym[k]
      Else sym := ident
    End
  Else If ch In ['0'..'9'] Then
    Begin {数字}
      k := 0;
      num := 0;
      sym := number; {当前记号sym为数字}
      Repeat {计算数字串的值}
        num := 10 * num + (ord(ch) - ord('0'));
        k := k + 1;
        getch;
      Until Not (ch In ['0'..'9']);
      If k > nmax Then error(30)
      {当前数字串的长度超过上界,则报告错误}
    End
  Else If ch = ':' Then {处理赋值号}
    Begin
      getch;
      If ch = '=' Then
        Begin
          sym := becomes;
          getch;
        End
      Else sym := nul;
    End
  Else If ch = '<' Then {处理不等号、小于号、小于等于号}
    Begin
      getch;
      If ch = '=' Then
        Begin
          sym := leq;
          getch;
        End
      Else If ch = '>' Then
        Begin
          sym := neq;
          getch;
        End
      Else sym := lss;
    End
  Else If ch = '>' Then {处理大于号、大于等于号}
    Begin
      getch;
      If ch = '=' Then
        Begin
          sym := geq;
          getch;
        End
      Else sym := gtr;
    End
  Else {处理其它算符或标点符号}
    Begin
      sym := ssym[ch];
      getch;
    End
End; {getsym}


{生成汇编}
Procedure gen(x: fct; y, z: integer);
Begin
  If cx > cxmax Then {如果当前指令序号>代码的最大长度}
    Begin
      writeln('Program Too Long');
      programExit;
    End;
  With code[cx] Do {在代码数组cx位置生成一条新代码}
    Begin
      f := x; {功能码}
      l := y; {层号}
      a := z  {地址}
    End;
  cx := cx + 1;
End; {gen}


Procedure test(s1, s2: symset; n: integer);
Begin
  If Not (sym In s1) Then
    {如果当前记号不属于集合S1,则报告错误n}
    Begin
      error(n);
      s1 := s1 + s2;
      While Not (sym In s1) Do getsym;
      {跳过一些记号, 直到当前记号属于S1∪S2}
    End
End; {test}


Procedure block(lev, tx: integer; fsys: symset);
Var
  dx: integer;  {本过程数据空间分配下标}
  tx0: integer; {本过程标识表起始下标}
  cx0: integer; {本过程代码起始下标}

Procedure enter(k: objecttype);
Begin {把object填入符号表中}
  tx := tx + 1; {符号表指针加1}
  With table[tx] Do {在符号表中增加新的一个条目}
    Begin
      name := id; {当前标识符的名字}
      kind := k; {当前标识符的种类}
      Case k Of
        constant:
          Begin {当前标识符是常数名}
            If num > amax Then
              Begin
                error(30);
                num := 0
              End;
            val := num;
          End;
        variable:
          Begin {当前标识符是变量名}
            level := lev;
            adr := dx;
            dx := dx +1;
          End;
        procedures: level := lev {本过程的嵌套层数}
      End
    End
End; {enter}

Function position(id: alfa) : integer; {返回id在符号表的入口}
Var i: integer;
Begin {在标识符表中查标识符id}
  table[0].name := id; {在符号表栈的最下方预填标识符id}
  i := tx; {符号表栈顶指针}
  While table[i].name <> id Do
    i := i - 1; {从符号表栈顶往下查标识符id}
  position := i; {若查到,i为id的入口,否则i=0 }
End; {position}

Procedure constdeclaration;
Begin
  If sym = ident Then {当前记号是常数名}
    Begin
      getsym;
      If sym In [eql, becomes] Then {当前记号是等号或赋值号}
        Begin
          If sym = becomes Then error(1);
          getsym;
          If sym = number Then {等号后面是常数}
            Begin
              enter(constant);
              getsym;
            End
          Else error(2) {等号后面不是常数出错}
        End
      Else error(3) {标识符后不是等号或赋值号出错}
    End
  Else error(4) {常数说明中没有常数名标识符}
End; {constdeclaration}

Procedure vardeclaration;
Begin
  If sym = ident Then {如果当前记号是标识符}
    Begin
      enter(variable);
      getsym;
    End
  Else error(4) {如果变量说明未出现标识符,则出错}
End; {vardeclaration}

Procedure listcode;
Var i: integer;
Begin {列出本程序体生成的代码}
  For i := cx0 To cx - 1 Do
    With code[i] Do {打印第i条代码}
      writeln(foutAsm, i:5, mnemonic[f]:6, l:3, a:5)
      {i: 代码序号}
      {mnemonic[f]: 功能码的字符串}
      {l: 相对层号(层差)}
      {a: 相对地址或运算号码}
End; {listcode}

Procedure statement(fsys: symset);
Var i, cx1, cx2: integer;
Procedure expression(fsys: symset);
Var addop: symbol;
Procedure term(fsys: symset);
Var mulop: symbol;
Procedure factor(fsys: symset);
Var i : integer;
Begin {factor}
  test(facbegsys, fsys, 24);
  While sym In facbegsys Do
    {如果当前的记号是否因子的开始符号}
    Begin
      If sym = ident Then {当前记号是标识符}
        Begin
          i := position(id);
          If i = 0 Then error(11)
          Else
            With table[i] Do
              Case kind Of
                {若id是常数, 生成指令,将常数val取到栈顶}
                constant: gen(lit, 0, val);
                {若id是变量, 生成指令,将该变量取到栈顶;}
                {lev: 当前语句所在过程的层号;}
                {level: 定义该变量的过程层号;}
                {adr: 变量在其过程的数据空间的相对地址}
                variable: gen(lod, lev-level, adr);
                {若id是过程名, 则出错}
                procedures: error(21);
              End;
          getsym;
        End
      Else If sym = number Then {当前记号是数字}
        Begin
          If num > amax Then
            Begin
              error(30);
              num := 0
            End;
          gen(lit, 0, num);
          getsym;
        End
      Else If sym = lparen Then {如果当前记号是左括号}
        Begin
          getsym;
          expression([rparen]+fsys);
          If sym = rparen Then getsym
          Else error(22)
        End;
      {测试当前记号是否同步, 否则出错, 跳过一些记号}
      test(fsys, [lparen], 23)
    End {while}
End; {factor}
Begin {term}
  factor(fsys+[times, slash]); {处理项中第一个因子}
  While sym In [times, slash] Do
    Begin
      mulop := sym;
      getsym;
      factor(fsys+[times, slash]);
      If mulop = times Then gen(opr, 0, 4)
      Else gen(opr, 0, 5)
    End
End; {term}
Begin {expression}
  If sym In [plus, minus] Then {若第一个记号是加号或减号}
    Begin
      addop := sym;
      getsym;
      term(fsys+[plus, minus]);
      If addop = minus Then gen(opr, 0, 1)
    End
  Else term(fsys+[plus, minus]);
  {第一个记号不是加号或减号, 则处理一个项}
  While sym In [plus, minus] Do {若当前记号是加号或减号}
    Begin
      addop := sym;
      getsym;
      term(fsys+[plus, minus]);
      If addop = plus Then gen(opr, 0, 2)
      Else gen(opr, 0, 3)
    End
End; {expression}

Procedure  condition(fsys: symset);
Var relop: symbol;
Begin
  If sym = oddsym Then {如果当前记号是“odd”}
    Begin
      getsym;
      expression(fsys);
      gen(opr, 0, 6)
    End
  Else {如果当前记号不是“odd”}
    Begin
      expression([eql, neq, lss, gtr, leq, geq] + fsys);
      If Not (sym In [eql, neq, lss, leq, gtr, geq]) Then
        error(20)
      Else
        Begin
          relop := sym;
          getsym;
          expression(fsys); {处理关系符右边的算术表达式}
          Case relop Of
            eql: gen(opr, 0, 8);
            neq: gen(opr, 0, 9);
            lss: gen(opr, 0, 10);
            geq: gen(opr, 0, 11);
            gtr: gen(opr, 0, 12);
            leq: gen(opr, 0, 13);
          End
        End
    End
End; {condition}
Begin {statement}
  If sym = ident Then {处理赋值语句}
    Begin
      i := position(id);
      If i = 0 Then error(11)
      Else If table[i].kind <> variable Then
        Begin {对非变量赋值}
          error(12);
          i := 0;
        End;
      getsym;
      If sym = becomes Then getsym
      Else error(13);
      expression(fsys);
      If i <> 0 Then {若赋值号左边的变量id有定义}
        With table[i] Do
          gen(sto, lev-level, adr)
          {生成一条存数指令, 将栈顶(表达式)的值存入变量id中}
          {lev: 当前语句所在过程的层号}
          {level: 定义变量id的过程的层号}
          {adr: 变量id在其过程的数据空间的相对地址}
    End
  Else If sym = callsym Then {处理过程调用语句}
    Begin
      getsym;
      If sym <> ident Then error(14)
      Else
        Begin
          i := position(id);
          If i = 0 Then error(11)
          Else
            With table[i] Do
              If kind = procedures Then
                {如果在符号表中id是过程名}
                gen(cal, lev-level, adr)
                {生成一条过程调用指令}
                {lev: 当前语句所在过程的层号}
                {level: 定义过程名id的层号}
                {adr: 过程id的代码中第一条指令的地址}
              Else error(15);
          getsym
        End
    End
  Else If sym = ifsym Then {处理条件语句}
    Begin
      getsym;
      condition([thensym, dosym]+fsys);
      If sym = thensym Then getsym
      Else error(16);
      cx1 := cx;
      gen(jpc, 0, 0);
      {生成指令,表达式为“假”转到某地址(待填), 否则顺序执行}
      statement(fsys);
      code[cx1].a := cx;
      {将下一个指令的地址回填到上面的jpc指令地址栏}
    End
  Else If sym = beginsym Then {处理语句序列}
    Begin
      getsym;
      statement([semicolon, endsym]+fsys);
      While sym In [semicolon]+statbegsys Do
        Begin
          If sym = semicolon Then getsym
          Else error(10);
          statement([semicolon, endsym]+fsys)
        End;
      If sym = endsym Then getsym
      Else error(17);
    End
  Else If sym = whilesym Then {处理循环语句}
    Begin
      cx1 := cx;
      getsym;
      condition([dosym]+fsys);
      cx2 := cx;
      gen(jpc, 0, 0);
      {生成一条指令,表达式为“假”转到某地址(待回填), 否则顺序执行}
      If sym = dosym Then getsym
      Else error(18);
      statement(fsys);
      gen(jmp, 0, cx1);
      {生成无条件转移指令, 转移到“while”后的条件表达式的代码的第一条指令处}
      code[cx2].a := cx
      {把下一指令地址回填到前面生成的jpc指令的地址栏}
    End;
  test(fsys, [], 19);
End; {statement}
Begin {block}
  dx := 3; {本过程数据空间栈顶指针}
  tx0 := tx; {标识符表的长度(当前指针)}
  table[tx].adr := cx; {本过程名的地址, 即下一条指令的序号}
  gen(jmp, 0, 0); {生成一条转移指令}
  If lev > levmax Then error(32);
  Repeat
    If sym = constsym Then {处理常数说明语句}
      Begin
        getsym;
        Repeat
          constdeclaration; {处理一个常数说明}
          While sym = comma Do
            Begin
              getsym;
              constdeclaration
            End;
          If sym = semicolon Then getsym
          Else error(5)
        Until sym <> ident
      End;
    If sym = varsym Then {当前记号是变量说明语句开始符号}
      Begin
        getsym;
        Repeat
          vardeclaration; {处理一个变量说明}
          While sym = comma Do
            Begin
              getsym;
              vardeclaration
            End;
          If sym = semicolon Then getsym
          Else error(5)
        Until sym <> ident;
      End;
    While sym = procsym Do {处理过程说明}
      Begin
        getsym;
        If sym = ident Then
          Begin
            enter(procedures);
            getsym
          End
        Else error(4);
        If sym = semicolon Then getsym
        Else error(5);
        block(lev+1, tx, [semicolon]+fsys); {处理过程体}
        {lev+1: 过程嵌套层数加1}
        {tx: 符号表当前栈顶指针,也是新过程符号表起始位置}
        {[semicolon]+fsys: 过程体开始和末尾符号集}
        If sym = semicolon Then {如果当前记号是分号}
          Begin
            getsym;
            test(statbegsys+[ident, procsym], fsys, 6)
          End
        Else error(5)
      End; {while}
    test(statbegsys+[ident], declbegsys, 7)
  Until Not (sym In declbegsys);
  code[table[tx0].adr].a := cx;
  With table[tx0] Do
    Begin
      adr := cx;
    End;
  cx0 := cx;
  gen(int, 0, dx);
  statement([semicolon, endsym]+fsys);
  gen(opr, 0, 0);
  test(fsys, [], 8);
  listcode;
End; {block}

Procedure interpret;
Const stacksize = 500; {运行时数据空间(栈)的上界}
Var
  p, b, t: integer; {程序地址寄存器, 基地址寄存器,栈顶地址寄存器}
  i: instruction; {指令寄存器}
  s: array [1..stacksize] Of integer; {数据存储栈}

Function base(l: integer): integer;
Var b1: integer;
Begin
  b1 := b; {顺静态链求层差为l的外层的基地址}
  While l > 0 Do
    Begin
      b1 := s[b1];
      l := l-1
    End;
  base := b1
End; {base}
Begin
  writeln(foutStack, 'START PL/0:');
  t := 0; {栈顶地址寄存器}
  b := 1; {基地址寄存器}
  p := 0; {程序地址寄存器}
  s[1] := 0;
  s[2] := 0;
  s[3] := 0;
  {最外层主程序数据空间栈最下面预留三个单元}
  {每个过程运行时的数据空间的前三个单元是:SL, DL, RA;}
  {SL: 指向本过程静态直接外层过程的SL单元;}
  {DL: 指向调用本过程的过程的最新数据空间的第一个单元;}
  {RA: 返回地址 }
  Repeat
    i := code[p];
    p := p + 1;
    With i Do
      Case f Of
        lit: {当前指令是取常数指令(lit, 0, a)}
          Begin
            t := t+1;
            s[t] := a
          End;
        opr: Case a Of {当前指令是运算指令(opr, 0, a)}
          0: {返回调用过程指令}
            Begin
              t := b-1;
              p := s[t+3];
              b := s[t+2];
            End;
          1: s[t] := -s[t]; {一元负运算, 栈顶元素的值反号}
          2: {加法}
            Begin
              t := t-1;
              s[t] := s[t] + s[t+1]
            End;
          3: {减法}
            Begin
              t := t-1;
              s[t] := s[t]-s[t+1]
            End;
          4: {乘法}
            Begin
              t := t-1;
              s[t] := s[t] * s[t+1]
            End;
          5: {整数除法}
            Begin
              t := t-1;
              s[t] := s[t] Div s[t+1]
            End;
          6: s[t] := ord(odd(s[t])); {s[t]是否奇数}
          8: {判两个表达式的值是否相等}
            Begin
              t := t-1;
              s[t] := ord(s[t] = s[t+1])
            End;
          9: {判两个表达式的值是否不等}
            Begin
              t := t-1;
              s[t] := ord(s[t] <> s[t+1])
            End;
          10: {判前一表达式是否小于后一表达式}
            Begin
              t := t-1;
              s[t] := ord(s[t] < s[t+1])
            End;
          11: {判前一表达式是否大于或等于后一表达式}
            Begin
              t := t-1;
              s[t] := ord(s[t] >= s[t+1])
            End;
          12: {判前一表达式是否大于后一表达式}
            Begin
              t := t-1;
              s[t] := ord(s[t] > s[t+1])
            End;
          13: {判前一表达式是否小于或等于后一表达式}
            Begin
              t := t-1;
              s[t] := ord(s[t] <= s[t+1])
            End;
          End;
        lod: {当前指令是取变量指令(lod, l, a)}
          Begin
            t := t + 1;
            s[t] := s[base(l) + a]
          End;
        sto: {当前指令是保存变量值(sto, l, a)指令}
          Begin
            s[base(l) + a] := s[t];
            writeln(foutStack, s[t]);
            t := t-1
          End;
        cal: {当前指令是(cal, l, a)}
          Begin
            s[t+1] := base(l);
            s[t+2] := b;
            s[t+3] := p;
            b := t+1;
            p := a
          End;
        int: t := t + a; {若当前指令是(int, 0, a)}
        jmp: p := a; {若当前指令是(jmp, 0, a)}
        jpc: {当前指令是(jpc, 0, a)}
          Begin
            If s[t] = 0 Then p := a;
              t := t-1
            End
      End {with, case}
  Until p = 0;
  writeln(foutStack, 'End PL/0');
End; {interpret}

Begin {主程序}
  If ParamCount <> 4 Then
    Begin
      writeln('Please input filenames.');
      writeln('Format: pl0 [source_file] [output_src_file] [output_stack_file] [output_asm_file]');
      exit;
    End;
  assign(fin, ParamStr(1));
  assign(fout, ParamStr(2));
  assign(foutStack, ParamStr(3));
  assign(foutAsm, ParamStr(4));
  writeln('Input File: ' + ParamStr(1));
  writeln('Output File: ' + ParamStr(2));
  writeln('Stack File: ' + ParamStr(3));
  writeln('Asm File: ' + ParamStr(4));
  writeln('Compile...');
  reset(fin);
  rewrite(fout);
  rewrite(foutStack);
  rewrite(foutAsm);
  For ch := 'A' To ';' Do
    ssym[ch] := nul;
  {ASCII码的顺序}
  word[1] := 'Begin     ';
  word[2] := 'Call      ';
  word[3] := 'Const     ';
  word[4] := 'Do        ';
  word[5] := 'End       ';
  word[6] := 'If        ';
  word[7] := 'Odd       ';
  word[8] := 'Procedure ';
  word[9] := 'Then      ';
  word[10] := 'Var       ';
  word[11] := 'While     ';
  wsym[1] := beginsym;
  wsym[2] := callsym;
  wsym[3] := constsym;
  wsym[4] := dosym;
  wsym[5] := endsym;
  wsym[6] := ifsym;
  wsym[7] := oddsym;
  wsym[8] := procsym;
  wsym[9] := thensym;
  wsym[10] := varsym;
  wsym[11] := whilesym;
  ssym['+'] := plus;
  ssym['-'] := minus;
  ssym['*'] := times;
  ssym['/'] := slash;
  ssym['('] := lparen;
  ssym[')'] := rparen;
  ssym['='] := eql;
  ssym[','] := comma;
  ssym['.'] := period;
  {ssym['<>'] := neq;}
  {ssym['<'] := lss;}
  {ssym['>'] := gtr;}
  {ssym['<='] := leq;}
  {ssym['>='] := geq;}
  ssym[';'] := semicolon;
  {算符和标点符号的记号}
  mnemonic[lit] := 'LIT';
  mnemonic[opr] := 'OPR';
  mnemonic[lod] := 'LOD';
  mnemonic[sto] := 'STO';
  mnemonic[cal] := 'CAL';
  mnemonic[int] := 'INT';
  mnemonic[jmp] := 'JMP';
  mnemonic[jpc] := 'JPC';
  {中间代码指令的字符串}
  declbegsys := [constsym, varsym, procsym];
  {说明语句的开始符号}
  statbegsys := [beginsym, callsym, ifsym, whilesym];
  {语句的开始符号}
  facbegsys := [ident, number, lparen];
  {因子的开始符号}
  {page(output);}
  err := 0; {发现错误的个数}
  cc := 0; {当前行中输入字符的指针}
  cx := 0; {代码数组的当前指针}
  ll := 0; {输入当前行的长度}
  ch := ' '; {当前输入的字符}
  kk := al; {标识符的长度}
  getsym; {取下一个记号}
  block(0, 0, [period]+declbegsys+statbegsys); {处理程序体}
  If sym <> period Then error(9);
  {如果当前记号不是句号, 则出错}
  If err = 0 Then interpret
  {如果编译无错误, 则解释执行中间代码}
  Else write('ERRORS In PL/0 Program');
  programExit;
End.
