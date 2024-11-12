import os
import pymysql
from datetime import datetime, timedelta
import sys

# 获取目录信息
def get_directory_info(directory):
    files = []
    dirs = []
    for root, directories, filenames in os.walk(directory):
        for directory in directories:
            dir_path = os.path.join(root, directory)
            try:
                size = os.path.getsize(dir_path)
                mtime = os.path.getmtime(dir_path)
                depth = len(dir_path.split(os.sep))
                dirs.append((directory, size, mtime, depth))
            except (FileNotFoundError,PermissionError):
                continue  # 文件不存在，跳过

        for filename in filenames:
            file_path = os.path.join(root, filename)
            try:
                size = os.path.getsize(file_path)
                mtime = os.path.getmtime(file_path)
                readonly = os.access(file_path, os.R_OK) and not os.access(file_path, os.W_OK)
                files.append((filename, size, mtime, readonly))
            except (FileNotFoundError,PermissionError):
                continue  # 文件不存在，跳过

    return files, dirs


def create_tables(cursor):
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS files (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(2048) NOT NULL,
        size BIGINT NOT NULL,
        mtime TIMESTAMP NOT NULL,
        readonly BOOLEAN NOT NULL
    )
    """)

    cursor.execute("""
    CREATE TABLE IF NOT EXISTS directories (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(2048) NOT NULL,
        size BIGINT NOT NULL,
        mtime TIMESTAMP NOT NULL,
        depth INT NOT NULL
    )
    """)


def insert_data(cursor, files, dirs):
    for file in files:
        cursor.execute("INSERT INTO files (name, size, mtime, readonly) VALUES (%s, %s, FROM_UNIXTIME(%s), %s)", file)
    for directory in dirs:
        cursor.execute("INSERT INTO directories (name, size, mtime, depth) VALUES (%s, %s, FROM_UNIXTIME(%s), %s)",directory)



def query1(cursor):
    cursor.execute("SELECT COUNT(*) FROM files")
    file_count = cursor.fetchone()[0]

    cursor.execute("SELECT COUNT(*) FROM directories")
    dir_count = cursor.fetchone()[0]

    print(f"普通文件数量: {file_count}, 目录数量: {dir_count}")

def query2(cursor):
    cursor.execute("SELECT SUM(size) FROM files")
    total_file_size = cursor.fetchone()[0]
    total_blocks = total_file_size // 512
    print(f"总字节数: {total_file_size}, 总占用空间（数据块512字节单位）: {total_blocks}")

def query3(cursor):
    one_week_ago = datetime.now() - timedelta(days=7)
    cursor.execute("SELECT name, size, mtime FROM files WHERE mtime >= %s", (one_week_ago,))
    recent_files = cursor.fetchall()
    print(f"最近1周内修改的普通文件总数: {len(recent_files)}")
    for file in recent_files:
        print(f"文件名: {file[0]}, 大小: {file[1]}")
def query4(cursor):
    cursor.execute("""
    SELECT directories.name, COUNT(files.id) AS file_count 
    FROM directories 
    JOIN files ON files.name LIKE CONCAT(directories.name, '/%')
    GROUP BY directories.id 
    HAVING file_count > 100
    """)
    large_dirs = cursor.fetchall()

    for dir in large_dirs:
        print(f"目录名: {dir[0]}, 文件数量: {dir[1]}")
def query5(cursor):
    cursor.execute("SELECT name FROM directories WHERE depth > 10")
    deep_dirs = cursor.fetchall()
    for dir in deep_dirs:
        print(f"目录名: {dir[0]}")
def query6(cursor):
    cursor.execute("SELECT COUNT(*), SUM(size) FROM files WHERE readonly = 1")
    readonly_files = cursor.fetchone()

    print(f"只读文件数量: {readonly_files[0]}, 所占字节数: {readonly_files[1]}")
def query7(cursor):
    size_ranges = [
        (1, 1024),  # 1KB
        (1024, 512 * 1024),  # 512KB
        (512 * 1024, 1024 * 1024),  # 1MB
        (1024 * 1024, 10 * 1024 * 1024),  # 10MB
        (10 * 1024 * 1024, 512 * 1024 * 1024),  # 512MB
        (512 * 1024 * 1024, 1024 * 1024 * 1024),  # 1GB
        (1024 * 1024 * 1024, 2 * 1024 * 1024 * 1024),  # 2GB
        (2 * 1024 * 1024 * 1024, 4 * 1024 * 1024 * 1024),  # 4GB
        (4 * 1024 * 1024 * 1024, float('inf'))  # 4GB以上
    ]

    for min_size, max_size in size_ranges:
        cursor.execute("SELECT COUNT(*) FROM files WHERE size >= %s AND size < %s", (min_size, max_size))
        count = cursor.fetchone()[0]
        print(f"文件大小范围: {min_size} - {max_size} 字节, 数量: {count}")


def main():
    connection = pymysql.connect(user='root', password='', host='localhost', database='lab13')

    try:
        cursor = connection.cursor()
        create_tables(cursor)

        files, dirs = get_directory_info('/Users/liukexin')

        insert_data(cursor, files, dirs)
        connection.commit()

        query1(cursor)
        query2(cursor)
        query3(cursor)
        query4(cursor)
        query5(cursor)
        query6(cursor)
        query7(cursor)
    finally:
        connection.close()


if __name__ == "__main__":
    with open('output.txt', 'a', buffering=1) as f:
        # 保存原始的sys.stdout
        original_stdout = sys.stdout

        # 重定向sys.stdout到文件对象
        sys.stdout = f
        main()
