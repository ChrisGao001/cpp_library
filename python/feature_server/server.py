#!/usr/bin/python
#coding:utf8

from flask import Flask, request, redirect, url_for,session,jsonify
from flask import render_template,make_response
from flask import send_from_directory
import datetime
import os.path
import os

app = Flask(__name__)
tool_path = os.path.abspath(os.path.dirname(__file__))
data_path = os.path.join(tool_path,"data/")
app.config['UPLOAD_FOLDER'] = data_path

app.config['SECRET_KEY'] = os.urandom(24)
app.config['PERMANENT_SESSION_LIFETIME'] = 7200

dest_file = None
dest_file_name = None
g_host_ip = "localhost" # need change

def make_response(code, err):
    result = dict()
    result["code"] = code
    result["data"] = err
    return jsonify(result)

def get_now_str():
    import datetime
    return datetime.datetime.now().strftime("%Y%m%d%H%M%S")

@app.route('/', methods=['GET', 'POST'])
def get_feat_data():
    data = request.get_data()
    if not dest_file:
        return make_response(400, "no open file")
    dest_file.write("{0}\n".format(data.decode("utf8")))
    print(data, type(data))
    return make_response(200, data.decode("utf8"))
    
@app.route('/begin_test', methods=['GET'])
def begin_test():
    global dest_file_name
    global dest_file
    case_name = request.args.get("casename")
    if case_name is None:
        case_name = ""
    dest_file_name = "{0}{1}_{2}".format(data_path, case_name,get_now_str()) 
    if dest_file:
        dest_file.close()
    dest_file = open(dest_file_name, "w")
    code = 200
    err = dest_file_name
    return make_response(code, err)
    
@app.route('/end_test', methods=['GET'])
def end_test():
    global dest_file_name
    global dest_file
    global g_host_ip
    if dest_file:
        dest_file.close()
        dest_file = None
    url = "http://{0}:6432/feature/{1}".format(os.path.basename(g_host_ip, dest_file_name))
    return make_response(200, url)

@app.route('/feature/<filename>')
def upload_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port= 6432)
