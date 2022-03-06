from urllib.request import urlopen 
import json
num = "25"
# 從field2抓資料，抓到0就執行判斷式之類的
urlGet = "https://api.thingspeak.com/channels/1467821/fields/2/last.json?key=IOQU4ZHV8H7RDSHU"
# 把資料丟到field1給arduino
urlSend = "http://api.thingspeak.com/update?api_key=2BG7NSL1HYBXHD1K&field1=%s" % num

reqGet = urlopen(urlGet)
data = reqGet.read()
pyControl = json.loads(data.decode('utf-8'))
#reqSend = urlopen(urlSend)
#print(reqSend.read())
print(pyControl['field2'])