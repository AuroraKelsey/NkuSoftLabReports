## 命令行
打开终端
输入` mysql -u 用户名 -p`
然后输入密码
## workbench
图形化客户端工具

更改主题色问题，困扰多天终于解决
[Mac 上修改 MySQL Workbench 主题配色-CSDN博客](https://blog.csdn.net/qq_35752021/article/details/106677297)

## navicat
更好用

## python调用mysql
```c
import pymysql  
db = pymysql.connect(host='localhost',  
                     user='root',  
                     password='',  
                     database='schema1')  
cursor = db.cursor()  
# 使用 execute()  方法执行 SQL 查询  
cursor.execute("SELECT VERSION()")  
  
# 使用 fetchone() 方法获取单条数据.  
data = cursor.fetchone()  
  
print("Database version : %s " % data)  
  
# 关闭数据库连接  
db.close()
```