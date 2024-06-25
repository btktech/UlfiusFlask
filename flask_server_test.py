from flask import Flask
from flask import Response
from flask import request

app = Flask(__name__)

def log_request_method_and_path(request):
    print(f'[{request.method}] {request.path}')
   


@app.route('/new_users', methods = ['POST', 'GET'])
def new_users():
    # username = request.json.get('username')
    # password = request.json.get('password')
    # username=request.form.get("username")
    # password=request.form.get("password")
    
    # json_file = {}
    # json_file['query'] = 'login requested'
    
    # connection_data = request.get_json()
    # print(connection_data)

    # log_request_method_and_path(request)
    username = request.get_json().get('username')
    password = request.get_json().get('password')

    print("FLASK Server: username = ", username)
    print("FLASK Server: password = ", password)
    if username is None or password is None:
        abort(400) # missing arguments
    # if User.query.filter_by(username = username).first() is not None:
    #     abort(400) # existing user
    # user = User(username = username)
    # user.hash_password(password)
    # db.session.add(user)
    # db.session.commit()
    if username == 'admin' and password == 'admin':
        return Response("{'a':'b'}", status=201, mimetype='application/json')
    else:
        return Response("{'a':'b'}", status=404, mimetype='application/json')
        # return jsonify({ 'username': user.username }), 201, {'Location': url_for('get_user', id = user.id, _external = True)}



@app.route('/home', methods=['POST', 'GET'])
def home():
    return Response("Welcome to Flask Server Home page !", status=200, mimetype='application/json')

@app.route('/login', methods=['POST', 'GET'])
def login():
    return Response("{'a':'b'}", status=201, mimetype='application/json')

@app.route('/logout', methods=['POST', 'GET'])
def logout():
    return Response("{'a':'b'}", status=201, mimetype='application/json')

if __name__ == '__main__':
    app.run()


