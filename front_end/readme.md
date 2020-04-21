
## flask access control problem fix
app = Flask(__name__)

# 跨域支持
```python
def after_request(resp):
    resp.headers['Access-Control-Allow-Origin'] = '*'
    return resp

app.after_request(after_request)
```
