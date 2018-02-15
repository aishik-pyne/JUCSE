#!/usr/bin/python3
from PyQt5 import QtCore, QtGui, QtWidgets, uic

class StudentForm(QtWidgets.QWidget):

    def __init__(self):
        super(StudentForm, self).__init__()
        uic.loadUi('newstudent.ui', self)
        from sql_connector import SqlConnector
        self.sql = SqlConnector()
        self.setupParams()
        self.setupEvents()

    def setupParams(self):
        for dept in self.sql.get_dept_names():
            self.deptBox.addItem(dept)

    def setupEvents(self):
        self.saveButton.clicked.connect(self.on_save)


    def on_save(self):
        self.sql.add_student({'name':self.nameLine.text(),'dept':self.deptBox.currentText()})
        
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    widget = StudentForm()
    widget.show()
    sys.exit(app.exec_())
