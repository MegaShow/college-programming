# Homework 13 Sign up

> Web 13周作业

## Build Setup

```shell
# 依赖项, 实际上没有, 请忽视
npm install

# 启动于 localhost:8000
npm run dev
```

## FAQ

Q: node index.js 就显示404

A: npm的项目一般都有依赖npm的script来运行、调试、编译，这个script的具体信息写在package.json里面，执行npm的script是要在项目根目录下执行的。上面的Build Setup上写了，调试执行请输入npm run dev。如果在app里面跑index.js，跟在项目根目录上跑app/index.js，那么执行的js跟别的文件的相对路径是不一样的。所以，请在项目根目录使用npm run dev执行npm脚本。谢谢~ (逃~

## About

`app/index.js`: 项目入口

`app/controller/`: 路由逻辑

`app/modal/`: 数据库modal

`database/user.json`: 用户数据储存

`lib/`: 封装lib

`public/`: 网站根目录

---

by MegaShow.
