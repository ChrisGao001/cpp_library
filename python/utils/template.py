#!/usr/bin/python
#coding:utf8
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import sys
import json
import urllib
import urllib2
import time
import logging
import datetime
import time
import warnings
warnings.filterwarnings('ignore')

reload(sys)
sys.setdefaultencoding("utf8")

#for python3
def make_sure(bool_val, error_msg, *args):
    if not bool_val:
        raise ValueError("make_sure failure: " + error_msg % args)

def shell_v3(cmd):
	import subprocess
	s,o = subprocess.getstatusoutput(cmd)
	return s,o


def shell(cmd):
	import commands
	s,o = commands.getstatusoutput(cmd)
	return s,o

def date2unix(text, fmt="%Y-%m-%d %H:%M:%S"):
    dt = datetime.datetime.strptime(text, fmt)
    tm = time.mktime(dt.timetuple())
    return int(tm)

def date2str(dt, fmt="%Y-%m-%d %H:%M:%S"):
    ret = dt.strftime(fmt)
    return ret

def get_offset_date(dt, offset):
    ret = dt + datetime.timedelta(days=offset)
    return ret

def request(url):
	res = None
	try:
		res = urllib2.urlopen(url).read()
	except Exception,e:
		pass
	return res

def get_value(text, start_delim, end_delim):
	start = text.find(start_delim)
	if start == -1:
		return None
	end = text.find(end_delim, start + len(start_delim))
	if end == -1:
		ret = text[start+len(start_delim):]
	else:
		ret = text[start+len(start_delim) : end]
	return ret

def json_decode(text, coding='utf8'):
	ret = {}
	try:
		ret = json.loads(text, encoding=coding)
	except Exception,e:
		print e
		pass
	return ret

def json_encode(text, coding='utf-8'):
	ret = None
	try:
		ret = json.dumps(text, encoding="utf-8", ensure_ascii=True)
	except Exception,e:
		print e
		pass
	return ret
	

def url_unquote(term):
	ret = urllib.unquote(term)
	return ret

def url_quote(term):
	ret = urllib.quote(term)
	return ret

def get_gbk_term(word):
	word = word.replace("|", "")
	return word
	#ret = urllib.unquote(word).decode("gbk").encode("utf-8")
	print ret
	return ret

def json_encode(js):
	text = json.dumps(js,ensure_ascii=False)
	return text


def get_req_url(id):
	url = None
	try:
		url = '''https://d.jd.com/area/get?fid={}'''.format(id)
	except Exception,e:
		pass
	return url

## Global Setting begin 
 
logging.basicConfig(level=logging.DEBUG,format="[%(asctime)s] %(levelname)s %(message)s", datefmt="%Y-%m-%d %H:%M:%S")

## Global Setting end
dest = open("./area_id.txt", "wb")
for areaid in range(1,100):
	url = get_req_url(areaid)
	data = request(url)
	js = json_decode(data)
	data = json_encode(js)
	if data:
		text = "{}\t{}\n".format(areaid, data)
		dest.write(text)
dest.close()

