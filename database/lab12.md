# lab12  2213513  刘可新
1. 打印文件系统的结构信息
代码：
```python
import os  
  
rootDir ='/Users/liukexin/study/code/py_code/sqlite-autoconf-3230100'  
for (dirName, dirs, files) in os.walk(rootDir):  
    for fileName in files:  
        filePath = os.path.join(dirName, fileName)  
        parentFileName = os.path.basename(dirName)  
        print(fileName, ':', parentFileName, ':', os.path.getsize(filePath))  
    for dir in dirs:  
        print(dir)
```
输出：
```
Makefile.msc : sqlite-autoconf-3230100 : 27932
install-sh : sqlite-autoconf-3230100 : 14675
configure.ac : sqlite-autoconf-3230100 : 6461
INSTALL : sqlite-autoconf-3230100 : 15744
ltmain.sh : sqlite-autoconf-3230100 : 324089
sqlite3.rc : sqlite-autoconf-3230100 : 1992
sqlite3.c : sqlite-autoconf-3230100 : 7391127
configure : sqlite-autoconf-3230100 : 474456
config.guess : sqlite-autoconf-3230100 : 42938
depcomp : sqlite-autoconf-3230100 : 23566
sqlite3.pc.in : sqlite-autoconf-3230100 : 267
missing : sqlite-autoconf-3230100 : 6872
Makefile.am : sqlite-autoconf-3230100 : 828
shell.c : sqlite-autoconf-3230100 : 491779
config.sub : sqlite-autoconf-3230100 : 35987
compile : sqlite-autoconf-3230100 : 7333
sqlite3.1 : sqlite-autoconf-3230100 : 8928
sqlite3.h : sqlite-autoconf-3230100 : 531695
sqlite3ext.h : sqlite-autoconf-3230100 : 31394
Replace.cs : sqlite-autoconf-3230100 : 7272
README.txt : sqlite-autoconf-3230100 : 3558
Makefile.in : sqlite-autoconf-3230100 : 37703
aclocal.m4 : sqlite-autoconf-3230100 : 372375
tea
pkgIndex.tcl.in : tea : 167
configure.ac : tea : 8308
configure : tea : 280772
license.terms : tea : 257
README : tea : 1338
Makefile.in : tea : 15902
aclocal.m4 : tea : 147
tclconfig
win
doc
generic
install-sh : tclconfig : 13868
tcl.m4 : tclconfig : 134055
makefile.vc : win : 13830
nmakehlp.c : win : 17368
rules.vc : win : 18743
sqlite3.n : doc : 494
tclsqlite3.c : generic : 117731
```

2. 将指定目录夹及子目录文件信息存储数据库中，并在数据库中查询目录
```python
import pymysql  
import os  
  
rootDir = '/Users/liukexin/study/code/py_code/sqlite-autoconf-3230100'  
db = pymysql.connect(user='root', password='', host='localhost', database='dbsclab2024')  
  
# 创建一个表来存储文件信息  
create_table_query = '''  
CREATE TABLE IF NOT EXISTS files (  
    id INT AUTO_INCREMENT PRIMARY KEY,    
    parent_id INT,    
    name VARCHAR(255),    
    path VARCHAR(255),    
    is_directory BOOLEAN,    
    size BIGINT,    
    FOREIGN KEY (parent_id) REFERENCES files(id));  
'''  
try:  
    with db.cursor() as cursor:  
        cursor.execute(create_table_query)  
    db.commit()  
except pymysql.Error as e:  
    print(f"Error creating table: {e}")  
    db.rollback()  
  
# 插入文件信息的函数  
def insert_file_info(db, parent_id,  name, path, is_directory, size):  
    insert_query = "INSERT INTO files (parent_id, name, path, is_directory, size) VALUES (%s, %s, %s, %s, %s)"  
    try:  
        with db.cursor() as cursor:  
            cursor.execute(insert_query, (parent_id, name, path, is_directory, size))  
        db.commit()  
    except pymysql.Error as e:  
        print(f"Error inserting file info: {e}")  
        db.rollback()  
  
# 遍历目录并存储信息  
for dirName, dirs, files in os.walk(rootDir):  
    parent_id = None  # 根目录没有父目录  
    for dir in dirs:  
        dir_path = os.path.join(dirName, dir)  
        insert_file_info(db, parent_id, dir, dir_path, True, 0)  
    for fileName in files:  
        file_path = os.path.join(dirName, fileName)  
        insert_file_info(db, parent_id, fileName, file_path, False, os.path.getsize(file_path))  
  
  
# 查询 
def query_files(db, path=None):  
    query = "SELECT * FROM files"  
    if path:  
        query += " WHERE path = %s"  
        with db.cursor() as cursor:  
            cursor.execute(query, (path,))  
    else:  
        with db.cursor() as cursor:  
            cursor.execute(query)  
    return cursor.fetchall()  
  
files = query_files(db)  
for file in files:  
    print(file)  
  
db.close()
```
成功运行截图见下：
![](../../assets/Pasted%20image%2020240531150007.png)

感觉这里的参考pdf给的代码有问题，参考代码给的是查询instructor表，和任务好像并无关系。
```python
sql= 'SELECT name,dept_name,salary from instructor'
```