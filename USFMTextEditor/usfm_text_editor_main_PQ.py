# Copyright (C) 2021 Aleksandr Migunov

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
  
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

import sys
from usfm_text_editor_gui_PQ import *
from PyQt5 import QtCore, QtGui, QtWidgets

class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.actionExit.triggered.connect(self.close)

        self.ui.actionNew_Text_1.triggered.connect(self.clearText_1)
        self.ui.actionNew_Text_2.triggered.connect(self.clearText_2)
        self.ui.actionNew_Text_3.triggered.connect(self.clearText_3)
        self.ui.actionOpen_Text_1.triggered.connect(self.openFile_1)
        self.ui.actionOpen_Text_2.triggered.connect(self.openFile_2)
        self.ui.actionOpen_Text_3.triggered.connect(self.openFile_3)
        self.ui.actionSave_Text_1.triggered.connect(self.saveToFile_1)
        self.ui.actionSave_Text_2.triggered.connect(self.saveToFile_2)
        self.ui.actionSave_Text_3.triggered.connect(self.saveToFile_3)
        
        self.ui.actionUndo_in_Text_1.triggered.connect(self.ui.textEdit_Text_1.undo)
        self.ui.actionUndo_in_Text_2.triggered.connect(self.ui.textEdit_Text_2.undo)
        self.ui.actionUndo_in_Text_3.triggered.connect(self.ui.textEdit_Text_3.undo)
        self.ui.actionRedo_in_Text_1.triggered.connect(self.ui.textEdit_Text_1.redo)
        self.ui.actionRedo_in_Text_2.triggered.connect(self.ui.textEdit_Text_2.redo)
        self.ui.actionRedo_in_Text_3.triggered.connect(self.ui.textEdit_Text_3.redo)
        self.ui.actionCut_from_Text_1.triggered.connect(self.ui.textEdit_Text_1.cut)
        self.ui.actionCut_from_Text_2.triggered.connect(self.ui.textEdit_Text_2.cut)
        self.ui.actionCut_from_Text_3.triggered.connect(self.ui.textEdit_Text_3.cut)
        self.ui.actionCopy_from_Text_1.triggered.connect(self.ui.textEdit_Text_1.copy)
        self.ui.actionCopy_from_Text_2.triggered.connect(self.ui.textEdit_Text_2.copy)
        self.ui.actionCopy_from_Text_3.triggered.connect(self.ui.textEdit_Text_3.copy)
        self.ui.actionPaste_into_Text_1.triggered.connect(self.ui.textEdit_Text_1.paste)
        self.ui.actionPaste_into_Text_2.triggered.connect(self.ui.textEdit_Text_2.paste)
        self.ui.actionPaste_into_Text_3.triggered.connect(self.ui.textEdit_Text_3.paste)
        self.ui.actionSelect_All_in_Text_1.triggered.connect(self.ui.textEdit_Text_1.selectAll)
        self.ui.actionSelect_All_in_Text_2.triggered.connect(self.ui.textEdit_Text_2.selectAll)
        self.ui.actionSelect_All_in_Text_3.triggered.connect(self.ui.textEdit_Text_3.selectAll)

        self.ui.actionFind_in_Text_1.triggered.connect(self.findTextDialog_1)
        self.ui.actionFind_in_Text_2.triggered.connect(self.findTextDialog_2)
        self.ui.actionFind_in_Text_3.triggered.connect(self.findTextDialog_3)

        self.ui.actionZoom_In_Text_1.triggered.connect(self.ui.textEdit_Text_1.zoomIn)
        self.ui.actionZoom_In_Text_2.triggered.connect(self.ui.textEdit_Text_2.zoomIn)
        self.ui.actionZoom_In_Text_3.triggered.connect(self.ui.textEdit_Text_3.zoomIn)
        self.ui.actionZoom_Out_Text_1.triggered.connect(self.ui.textEdit_Text_1.zoomOut)
        self.ui.actionZoom_Out_Text_2.triggered.connect(self.ui.textEdit_Text_2.zoomOut)
        self.ui.actionZoom_Out_Text_3.triggered.connect(self.ui.textEdit_Text_3.zoomOut)

        self.ui.actionFont_of_Text_1.triggered.connect(self.chooseFont_1)
        self.ui.actionFont_of_Text_2.triggered.connect(self.chooseFont_2)
        self.ui.actionFont_of_Text_3.triggered.connect(self.chooseFont_3)
        self.ui.actionColor_of_Text_1.triggered.connect(self.chooseFontColor_1)
        self.ui.actionColor_of_Text_2.triggered.connect(self.chooseFontColor_2)
        self.ui.actionColor_of_Text_3.triggered.connect(self.chooseFontColor_3)
        self.ui.actionHighlight_in_Text_1.triggered.connect(self.chooseFontBackgroundColor_1)
        self.ui.actionHighlight_in_Text_2.triggered.connect(self.chooseFontBackgroundColor_2)
        self.ui.actionHighlight_in_Text_3.triggered.connect(self.chooseFontBackgroundColor_3)

        self.ui.actionAbout.triggered.connect(self.aboutDialog)

    def closeEvent(self, e):
        result = QtWidgets.QMessageBox.question(self, "Confirm Dialog",
                                                "Really quit?",
                                                QtWidgets.QMessageBox.Yes |
                                                QtWidgets.QMessageBox.No,
                                                QtWidgets.QMessageBox.No)
        if result == QtWidgets.QMessageBox.Yes:
            e.accept()
        else:
            e.ignore()
            

    def clearText_1(self):
        answer = QtWidgets.QMessageBox.question(self, "Clear Text", 
            "Do you want to clear the text?", QtWidgets.QMessageBox.No | QtWidgets.QMessageBox.Yes,
            QtWidgets.QMessageBox.Yes)
        if answer == QtWidgets.QMessageBox.Yes:
            self.ui.textEdit_Text_1.clear()
        else:
            pass
        

    def clearText_2(self):
        answer = QtWidgets.QMessageBox.question(self, "Clear Text", 
            "Do you want to clear the text?", QtWidgets.QMessageBox.No | QtWidgets.QMessageBox.Yes,
            QtWidgets.QMessageBox.Yes)
        if answer == QtWidgets.QMessageBox.Yes:
            self.ui.textEdit_Text_2.clear()
        else:
            pass


    def clearText_3(self):
        answer = QtWidgets.QMessageBox.question(self, "Clear Text", 
            "Do you want to clear the text?", QtWidgets.QMessageBox.No | QtWidgets.QMessageBox.Yes,
            QtWidgets.QMessageBox.Yes)
        if answer == QtWidgets.QMessageBox.Yes:
            self.ui.textEdit_Text_3.clear()
        else:
            pass


    def openFile_1(self):
        file_name, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open File",
            "", "HTML Files (*.html);;Text Files (*.txt);;Paratext Files (*.SFM *.sfm)")

        if file_name:
            with open(file_name, 'r') as f:
                notepad_text = f.read()
            self.ui.textEdit_Text_1.setText(notepad_text)
        else:
            QtWidgets.QMessageBox.information(self, "Error", 
                "Unable to open file.", QtWidgets.QMessageBox.Ok)  

    def openFile_2(self):
        file_name, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open File",
            "", "HTML Files (*.html);;Text Files (*.txt);;Paratext Files (*.SFM *.sfm)")

        if file_name:
            with open(file_name, 'r') as f:
                notepad_text = f.read()
            self.ui.textEdit_Text_2.setText(notepad_text)
        else:
            QtWidgets.QMessageBox.information(self, "Error", 
                "Unable to open file.", QtWidgets.QMessageBox.Ok)


    def openFile_3(self):
        file_name, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open File",
            "", "HTML Files (*.html);;Text Files (*.txt);;Paratext Files (*.SFM *.sfm)")

        if file_name:
            with open(file_name, 'r') as f:
                notepad_text = f.read()
            self.ui.textEdit_Text_3.setText(notepad_text)
        else:
            QtWidgets.QMessageBox.information(self, "Error", 
                "Unable to open file.", QtWidgets.QMessageBox.Ok)           

            
    def saveToFile_1(self):
        file_name, _ = QtWidgets.QFileDialog.getSaveFileName(self, 'Save File',
            "","HTML Files (*.html);;Text Files (*.txt);;Paratext Files (*.SFM *.sfm)")

        if (file_name.endswith('.txt') or file_name.endswith('.SFM') or file_name.endswith('.sfm')):
            notepad_text = self.ui.textEdit_Text_1.toPlainText()
            with open(file_name, 'w') as f:            
                f.write(notepad_text)
        elif file_name.endswith('.html'):
            notepad_richtext = self.ui.textEdit_Text_1.toHtml()
            with open(file_name, 'w') as f:            
                f.write(notepad_richtext)
        else:
            QtWidgets.QMessageBox.information(self, "Error", 
                "Unable to save file.", QtWidgets.QMessageBox.Ok)

    def saveToFile_2(self):
        file_name, _ = QtWidgets.QFileDialog.getSaveFileName(self, 'Save File',
            "","HTML Files (*.html);;Text Files (*.txt);;Paratext Files (*.SFM *.sfm)")

        if (file_name.endswith('.txt') or file_name.endswith('.SFM') or file_name.endswith('.sfm')):
            notepad_text = self.ui.textEdit_Text_2.toPlainText()
            with open(file_name, 'w') as f:            
                f.write(notepad_text)
        elif file_name.endswith('.html'):
            notepad_richtext = self.ui.textEdit_Text_2.toHtml()
            with open(file_name, 'w') as f:            
                f.write(notepad_richtext)
        else:
            QtWidgets.QMessageBox.information(self, "Error", 
                "Unable to save file.", QtWidgets.QMessageBox.Ok)

    def saveToFile_3(self):
        file_name, _ = QtWidgets.QFileDialog.getSaveFileName(self, 'Save File',
            "","HTML Files (*.html);;Text Files (*.txt);;Paratext Files (*.SFM *.sfm)")

        if (file_name.endswith('.txt') or file_name.endswith('.SFM') or file_name.endswith('.sfm')):
            notepad_text = self.ui.textEdit_Text_3.toPlainText()
            with open(file_name, 'w') as f:            
                f.write(notepad_text)
        elif file_name.endswith('.html'):
            notepad_richtext = self.ui.textEdit_Text_3.toHtml()
            with open(file_name, 'w') as f:            
                f.write(notepad_richtext)
        else:
            QtWidgets.QMessageBox.information(self, "Error", 
                "Unable to save file.", QtWidgets.QMessageBox.Ok)           


    def findTextDialog_1(self):
        find_text, ok = QtWidgets.QInputDialog.getText(self, "Search Text", "Find:")
        extra_selections = []
        if ok and not self.ui.textEdit_Text_1.isReadOnly():
            self.ui.textEdit_Text_1.moveCursor(QtGui.QTextCursor.Start)
            color = QtGui.QColor(QtCore.Qt.yellow)
            while(self.ui.textEdit_Text_1.find(find_text)):
                selection = QtWidgets.QTextEdit.ExtraSelection()
                selection.format.setBackground(color)
                selection.cursor = self.ui.textEdit_Text_1.textCursor()
                extra_selections.append(selection)
            for i in extra_selections:
                self.ui.textEdit_Text_1.setExtraSelections(extra_selections)            


    def findTextDialog_2(self):
        find_text, ok = QtWidgets.QInputDialog.getText(self, "Search Text", "Find:")
        extra_selections = []
        if ok and not self.ui.textEdit_Text_2.isReadOnly():
            self.ui.textEdit_Text_2.moveCursor(QtGui.QTextCursor.Start)
            color = QtGui.QColor(QtCore.Qt.yellow)
            while(self.ui.textEdit_Text_2.find(find_text)):
                selection = QtWidgets.QTextEdit.ExtraSelection()
                selection.format.setBackground(color)
                selection.cursor = self.ui.textEdit_Text_2.textCursor()
                extra_selections.append(selection)
            for i in extra_selections:
                self.ui.textEdit_Text_2.setExtraSelections(extra_selections)


    def findTextDialog_3(self):
        find_text, ok = QtWidgets.QInputDialog.getText(self, "Search Text", "Find:")
        extra_selections = []
        if ok and not self.ui.textEdit_Text_3.isReadOnly():
            self.ui.textEdit_Text_3.moveCursor(QtGui.QTextCursor.Start)
            color = QtGui.QColor(QtCore.Qt.yellow)
            while(self.ui.textEdit_Text_3.find(find_text)):
                selection = QtWidgets.QTextEdit.ExtraSelection()
                selection.format.setBackground(color)
                selection.cursor = self.ui.textEdit_Text_3.textCursor()
                extra_selections.append(selection)
            for i in extra_selections:
                self.ui.textEdit_Text_3.setExtraSelections(extra_selections)                

                
    def chooseFont_1(self):
        current = self.ui.textEdit_Text_1.currentFont()
        font, ok = QtWidgets.QFontDialog.getFont(current, self, options=QtWidgets.QFontDialog.DontUseNativeDialog)
        if ok:
            self.ui.textEdit_Text_1.setCurrentFont(font)  
        self.ui.textEdit_Text_1.setCurrentFont(font)


    def chooseFont_2(self):
        current = self.ui.textEdit_Text_2.currentFont()
        font, ok = QtWidgets.QFontDialog.getFont(current, self, options=QtWidgets.QFontDialog.DontUseNativeDialog)
        if ok:
            self.ui.textEdit_Text_2.setCurrentFont(font)  
        self.ui.textEdit_Text_2.setCurrentFont(font)


    def chooseFont_3(self):
        current = self.ui.textEdit_Text_3.currentFont()
        font, ok = QtWidgets.QFontDialog.getFont(current, self, options=QtWidgets.QFontDialog.DontUseNativeDialog)
        if ok:
            self.ui.textEdit_Text_3.setCurrentFont(font)  
        self.ui.textEdit_Text_3.setCurrentFont(font)
        
                
    def chooseFontColor_1(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            self.ui.textEdit_Text_1.setTextColor(color)


    def chooseFontColor_2(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            self.ui.textEdit_Text_2.setTextColor(color)


    def chooseFontColor_3(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            self.ui.textEdit_Text_3.setTextColor(color)
            

    def chooseFontBackgroundColor_1(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            self.ui.textEdit_Text_1.setTextBackgroundColor(color)


    def chooseFontBackgroundColor_2(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            self.ui.textEdit_Text_2.setTextBackgroundColor(color)


    def chooseFontBackgroundColor_3(self):
        color = QtWidgets.QColorDialog.getColor()
        if color.isValid():
            self.ui.textEdit_Text_3.setTextBackgroundColor(color)            


    def aboutDialog(self):
        QtWidgets.QMessageBox.about(self, "About Program", "This is a program for editing texts \n\nCopyright (C) 2021 Aleksandr Migunov \n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version. \n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. \n\nYou should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.")     
   

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = MyWin()
    myapp.show()
    sys.exit(app.exec_())
