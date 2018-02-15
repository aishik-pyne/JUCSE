#!/usr/bin/python3
from PyQt5 import QtCore, QtGui, QtWidgets, uic
from PyQt5.QtWidgets import *
class StudentForm(QtWidgets.QWidget):

    def __init__(self):
        super(StudentForm, self).__init__()
        uic.loadUi('liststudent.ui', self)
        from sql_connector import SqlConnector
        self.sql = SqlConnector()
        self.setupParams()
        self.setupEvents()

    def setupParams(self):
        pass

    def setupEvents(self):
        self.refreshButton.clicked.connect(self.on_refresh)


    def on_refresh(self):
        self.studentView.setColumnCount(3)
        self.studentView.setRowCount(20)
        result = self.sql.get_students()
        print(result)
        for row, student in enumerate(result):
            for col, (key, value) in enumerate(student.items()):
                self.studentView.setItem(row, col, QTableWidgetItem(value))

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    widget = StudentForm()
    widget.show()
    sys.exit(app.exec_())
