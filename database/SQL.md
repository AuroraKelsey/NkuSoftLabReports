解决登录报错问题
https://blog.csdn.net/m0_47505062/article/details/122342121

SQL 结构化查询语言 Structured Query Language
用SQL访问和处理数据系统中的数据，这类数据库包括：[[SQL]]、SQL Server、Access、Oracle、Sybase、DB2

[mysql](mysql.md)
**python操作mysql**
1. 终端安装
```
pip install pymysql
```
2. 测试以下代码 [pymysql](pymysql.md)
## sql刷题网站：
牛客
leet
w3school
hackerrank

https://www.zhihu.com/question/23463146

http://sqlmother.yupi.icu/#/learn 已学完

[SQLBolt - Learn SQL - SQL Lesson 4: Filtering and sorting Query results](https://sqlbolt.com/lesson/filtering_sorting_query_results) 
这个[中文](http://xuesql.cn/)是他的盗版，后半部分要vip
[在sqlbolt上学习SQL - 文杰2000 - 博客园 (cnblogs.com)](https://www.cnblogs.com/wenjie2000/p/15468498.html)完整答案

https://www.w3cschool.cn/sql/

https://www.lintcode.com/?utm_source=sc-zhihu-ztt09013



大小写都可以，下面默认关键字大写，其他小写

其它如果怕和关键字冲突，可以用反引号包起来
```
`xx`
```
`comment`注释
# 术语
| 正式          | 理解      |
| ----------- | ------- |
| relation关系  | table表  |
| tuple元组     | row行    |
| attribute属性 | column列 |
|             |         |
|             |         |

#  SQL 分类
DDL（Data Definition Language）：数据定义语言，用来定义数据库对象：库、表、列等；
DML（Data Manipulation Language）：数据操作语言，用来定义数据库记录（数据）；
DCL（Data Control Language）：数据控制语言，用来定义访问权限和安全级别；
DQL（Data Query Language）：数据查询语言，用来查询记录（数据）

# DDL
查看所有数据库：`show databases；`

切换数据库mydb1：`use mydb1;`

删除数据库：`DROP DATABASE IF EXISTS mydb1;`


- 创建新数据库
```c
create database `db2024`;
create database `db2024` defalut charset `;
```


- 创建新表
```c
create table student(
	stu_name varchar(20),
	stu_id char(5) ,
	col_id char(10) comment '所属学院'
	-- 主键
	primary key(stu_id)，
	-- 唯一的
	CONSTRAINT `约束名` UNIQUE(`列名`)
	--外键(student里学院必须是department里有的)
	FOREIGN KEY (col_id) REFERENCES department (col_id)
);
```


- 修改表
```c
alter table `table1` convert to 字符集;
```


- 改变表
- 添加一列
```c
ALTER table `xx` ADD column `stu` varchar(20);
```

- 修改列
```c
ALTER table `xx` MODIFY column `stu` char(20);
```

- 增加约束
```c
ALTER table `xx` ADD COSNSTRAINT `stu` char(20);
```

- 删除表
```c
drop table student;
```

- 查看表
```c
describe student;
```

- _CREATE INDEX_ - 创建索引（搜索键）
- _DROP INDEX_ - 删除索引


### 数据类型

| 类型        | 解释                                                   |
| --------- | ---------------------------------------------------- |
| double    | 浮点型，例如 double(5,2)表示最多 5 位，其中必须有 2 位小数，即最大值为 999.99； |
| int       | 整型                                                   |
| decimal   | 泛型型，在表单线方面使用该类型，因为不会出现精度缺失问题；                        |
| char      | 固定长度字符串类型；(当输入的字符不够长度时会补空格                           |
| varchar   | 可变长度字符串类型；有最多位数                                      |
| text      | 字符串类型；                                               |
| blob      | 字节类型；                                                |
| date      | 日期类型，格式为：yyyy-MM-dd；                                 |
| time      | 时间类型，格式为：hh:mm:ss                                    |
| timestamp | 时间戳类型；                                               |


# DML

查表名为`student`的所有元素
`select * from student`

选出列名为name,age
```
select name,age from student
```

别名
{原始字段名} as {别名}， as 也可以省略
```sql
select name as 员工姓名, position as 职位名称 from employees;
```

# 条件查询
```sql
SELECT 列1, 列2, ...
FROM 表名
WHERE 条件;
```

case
```sql
CASE WHEN (条件1) THEN 结果1
	   WHEN (条件2) THEN 结果2
	   ...
	   ELSE 其他结果 END
```


运算符
between
```sql
where age between 25 and 30
```
使用 "IS NULL" 和 "IS NOT NULL" 来判断字段是否为空值或非空值

## 模糊查询
关键字like，not like
如下 2 种通配符：

- 百分号（`%`）：表示任意长度的任意字符序列。
- 下划线（`_`）：表示任意单个字符

## 逻辑运算
`and`,`or`,`not`  

# 去重
`distinct`

# 排序
```sql
order by xx asc 
#升序
order by xx desc 
#降序
```

# 截断和偏移
`limit`
```sql
-- LIMIT 后只跟一个整数，表示要截断的数据条数（一次获取几条）
select task_name, due_date from tasks limit 2;

-- LIMIT 后跟 2 个整数，依次表示从第几条数据开始、一次获取几条
select task_name, due_date from tasks limit 2, 2;
```

# 函数
## 时间函数
```sql
-- 获取当前日期
SELECT DATE() AS current_date;

-- 获取当前日期时间
SELECT DATETIME() AS current_datetime;

-- 获取当前时间
SELECT TIME() AS current_time;
```

## 字符串函数
`UPPER` 转换为大写
`LOWER` 转换为小写
`LENGTH` 计算长度

## 聚合函数

- COUNT：计算指定列的行数或非空值的数量。
- SUM：计算指定列的数值之和。
- AVG：计算指定列的数值平均值。
- MAX：找出指定列的最大值。
- MIN：找出指定列的最小值。
## 分组函数
`group by`

`having`在分组后过滤

# 关联查询 
## cross join

```sql
SELECT e.emp_name, e.salary, e.department, d.manager
FROM employees e  #表1 
CROSS JOIN departments d; #表2
```

##  inner join
将满足条件的行组合在一起
 只返回两个表中满足关联条件的交集部分
 ```sql
SELECT e.emp_name, e.salary, e.department, d.manager
FROM employees e
JOIN departments d ON e.department = d.department;
```

## outer join
将两个表中满足条件的行组合在一起，并 **包含没有匹配的行** 。
```sql
SELECT e.emp_name, e.salary, e.department, d.manager
FROM employees e
LEFT JOIN departments d ON e.department = d.department;
```

# 子查询
当执行包含子查询的查询语句时，数据库引擎会首**先执行子查询**，然后将其结果作为条件或数据源来执行外层查询。
```
select
  name,
  age,
  class_id
from
  student
where
  not exists (
    select
      class_id
    from
      class
    where
      class.id = student.class_id
  );
```

# 组合查询

1. UNION 操作：它用于将两个或多个查询的结果集合并， **并去除重复的行** 。即如果两个查询的结果有相同的行，则只保留一行。
    
2. UNION ALL 操作：它也用于将两个或多个查询的结果集合并， **但不去除重复的行** 。即如果两个查询的结果有相同的行，则全部保留。

# 开窗函数
## sum over

```sql
SUM(计算字段名) OVER (PARTITION BY 分组字段名)
```
## Rank
有并列排名
```sql
RANK() OVER (PARTITION BY 分组字段名)
```
## Row_Number
**分配唯一连续排名**
```sql
ROW_NUMBER() OVER (
  PARTITION BY column1, column2, ... -- 可选，用于指定分组列
  ORDER BY column3 [ASC|DESC], column4 [ASC|DESC], ... -- 用于指定排序列及排序方式
) AS row_number_column
```

##  lag / lead
获取在当前行之前或之后的行的值
```sql
LAG(column_name, offset, default_value) OVER (PARTITION BY partition_column ORDER BY sort_column)
```
- `column_name`：要获取值的列名。
- `offset`：表示要向上偏移的行数。例如，offset为1表示获取上一行的值，offset为2表示获取上两行的值，以此类推。
- `default_value`：可选参数，用于指定当没有前一行时的默认值。
- `PARTITION BY`和`ORDER BY`子句可选，用于分组和排序数据。
