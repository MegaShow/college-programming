let express = require('express')
let router = express.Router()
let userCtrl = require('../controller/user.js')

module.exports = router

/**
 * @function '/User'
 *
 * @method 'GET'
 * @description - 获取用户信息
 * @param {Number} userId
 * @returns {Object}
 *    - 201 {
 *            state: 'success',
 *            username: String,
 *            email: String
 *            studentId: String,
 *            phone: String
 *          }
 *
 * @method 'POST'
 * @description - 创建用户
 * @param {String} email     - 邮箱
 * @param {String} username  - 用户名
 * @param {String} password  - 密码
 * @param {String} studentId - 学号
 * @param {String} phone     - 电话
 * @returns {Object}
 *    - 201 { state: 'success' }
 *    - 400 { state: 'fail', err: String }
 */

router.get('/', userCtrl.getUser)
router.post('/', userCtrl.postUser)


/**
 * @function '/User/Login'
 *
 * @method 'POST'
 * @description - 登录
 * @param {String} username - 用户名
 * @param {String} password - 密码
 * @returns {Object}
 *    - 201 {
 *            state: 'success',
 *            username: String,
 *            email: String
 *            studentId: String,
 *            phone: String
 *          }
 *    - 400 { state: 'fail', err: '用户名或密码错误' }
 *
 * @method 'DELETE'
 * @description - 登出
 * @return {Object}
 *    - 201 { state: 'success' }
 *    - 400 { state: 'fail', err: String }
 */

router.post('/Login', userCtrl.postLogin)
router.delete('/Login', userCtrl.deleteLogin)
