import pymysql.cursors

class SqlConnector:
    def __init__(self):
        self.connection = pymysql.connect(host='localhost',
                             user='root',
                             password='mummum10',
                             db='university',
                             charset='utf8mb4',
                             cursorclass=pymysql.cursors.DictCursor)


    def get_dept_names(self):
        try:
            with self.connection.cursor() as cursor:
                sql = "SELECT * FROM `departments` "
                cursor.execute(sql)
                result = cursor.fetchall()
                return [r['dept_short_name'] for r in result]
        except Exception as e:
            print(e)

    def get_students(self):
        try:
            with self.connection.cursor() as cursor:
                sql = "SELECT * FROM `students` "
                cursor.execute(sql)
                result = cursor.fetchall()
                return result
        except Exception as e:
            print(e)

    def add_student(self, student):
        try:
            with self.connection.cursor() as cursor:
                sql = """INSERT INTO `students` (name, dept) VALUES ('{0}','{1}');""".format(student['name'], student['dept'])
                cursor.execute(sql)
            self.connection.commit()
        except Exception as e:
            print(e)
