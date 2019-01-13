# Homework 16 Sign In

> Web 16周作业

## Build Setup

```shell
# 安装依赖项
npm install

# Update: 为了方便各位dalao测试, 已经将数据库搬到线上,
#         如果各位dalao还希望跑本地的数据库, 可以修改./config/mongo.js配置文件,
#         然后用下述命令运行mongo
#
# 运行mongod (PS: 不会输出任何东西, 但是mongod真的在运行)
# 可通过mongo查看是否连接上database
# mongod --config ./database/mongo.cfg

# 启动于 localhost:8000
npm run dev
```
## About

* node_module已删除, 请通过`npm install`安装, 依赖项均写入package, 无需一个个安装
* 请不要直接跑`node index.js`, 请使用`npm run dev`
* Build Setup里面命令均在README所在目录执行
* 如果database里面的数据库无法运行, 可通过修改`./config/mongo.js`的配置文件, 使用各位大佬搭设的数据库测试, 谢谢~

## Update

* 登录界面已添加注册链接
* 登录和注册没有跳转的情况, 怀疑是数据库无法正常连接, 因此, 这里已经将数据库部署到线上, 当然, 线下的数据库依然可用, 可修改配置文件使用本地数据库

---

by MegaShow.
