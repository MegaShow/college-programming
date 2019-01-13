# coding: utf-8
from flask import Flask, jsonify, session, request

app = Flask(__name__)

'''
User
{
    'username': username,
    'password': plain password,
    'deck': [
        {
            # Key for cardname, value for count
            'Black Magician': 2,
            'Black Magicina Girl': 2,
            'Star Dust Dragon': 1
        }
    ]
}
'''

# Yes, I'm a db
fake_db = {
    'users': {}
}

def auth_check(func):
    def _decorator(*args, **kwargs):
        if 'username' in session:
            return func(*args, **kwargs)
        else:
            return jsonify({
                'status': False,
                'msg': 'Unauthorized access'
            })
    return _decorator

def form_check(required_field):
    def wrapper(func):
        def _decorator(form):
            flag = True
            for i in required_field:
                if not i in form:
                    flag = False
                    break
            if flag:
                return func(form)
            else:
                return jsonify({
                    'status': False,
                    'msg': 'Incomplete form'
                })
        return _decorator
    return wrapper

@app.route('/')
def hello_world():
    return jsonify({
        "data": "Hello"
    })

@form_check(['username', 'password'])
def create_user(form):
    status = True
    msg = 'Create succeeded!'
    username = form['username']
    password = form['password']
    # no hash here
    if not username in fake_db['users']:
        # insert user
        user = {
            'username': username,
            'password': password,
            'deck': []
        }
        fake_db['users'][username] = user
    else:
        status = False
        msg = 'Duplicate username'
    return jsonify({
        'status': status,
        'msg': msg
    })

def query_user(querys):
    status = True
    msg = 'Query succeeded!'
    limit_query = querys.get('limit', 10)
    limit = 10
    try:
        limit = int(limit_query)
    except:
        return jsonify({
            'status': False,
            'msg': 'Wrong parameter'
        })
    print("limit %d" % limit)
    cnt = 1
    ret = []
    for k, v in fake_db['users'].items():
        if cnt > limit:
            break
        cnt += 1
        new_dict = v.copy()
        del new_dict['password']
        # del new_dict['deck']
        ret.append(new_dict)
    return jsonify({
        'data': ret,
        'status': status,
        'msg': msg
    })

@auth_check
@form_check(['deck'])
def update_user(form):
    status = True
    msg = 'Update succeeded!'
    deck = form['deck']
    username = session['username']
    print(fake_db)
    fake_db['users'][username]['deck'] = deck
    return jsonify({
        'status': status,
        'msg': msg
    })

@app.route('/users', methods=['POST', 'GET', 'PUT'])
def users():
    if request.method == 'POST':
        form = request.get_json(force=True)
        return create_user(form)
    elif request.method == 'GET':
        querys = request.args
        return query_user(querys)
    elif request.method == 'PUT':
        form = request.get_json(force=True)
        return update_user(form)

@form_check(['username', 'password'])
def login(form):
    status = True
    msg = 'Login succeeded!'
    username = form['username']
    password = form['password']
    if 'username' in session and username == session['username']:
        msg = 'Already logined'
    elif username in fake_db['users']:
        # auth
        user = fake_db['users'][username]
        if user['password'] == password:
            # auth ok
            session['username'] = username
        else:
            # auth fail
            status = False
            msg = 'Wrong username or password'
    else:
        status = False
        msg = 'Wrong username or password'
    return jsonify({
        'status': status,
        'msg': msg
    })

@app.route('/auth', methods=['POST'])
def auth():
    if request.method == 'POST':
        form = request.get_json(force=True)
        return login(form)

app.secret_key = '!\x0f\r\xc8\x87wQ\xe6\xe0O\x807\x06?\xc7^gIm\xeaae\x1a\xa5\x93G\t\x8b\x0ci\x119'

app.run(host='127.0.0.1', port=8000, debug=True)
