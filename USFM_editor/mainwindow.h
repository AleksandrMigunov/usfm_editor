/*
Copyright (C) 2021 Aleksandr Migunov

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString language;

private slots:
    void on_actionExit_triggered();

    void on_actionNew_Text_1_triggered();

    void on_actionNew_Text_2_triggered();

    void on_actionNew_Text_3_triggered();

    void on_actionOpen_Text_1_triggered();

    void on_actionOpen_Text_2_triggered();

    void on_actionOpen_Text_3_triggered();

    void on_actionSave_Text_1_triggered();

    void on_actionSave_Text_2_triggered();

    void on_actionSave_Text_3_triggered();

    void on_actionUndo_in_Text_1_triggered();

    void on_actionUndo_in_Text_2_triggered();

    void on_actionRedo_in_Text_1_triggered();

    void on_actionUndo_in_Text_3_triggered();

    void on_actionRedo_in_Text_2_triggered();

    void on_actionRedo_in_Text_3_triggered();

    void on_actionCut_from_Text_1_triggered();

    void on_actionCut_from_Text_2_triggered();

    void on_actionCut_from_Text_3_triggered();

    void on_actionCopy_from_Text_1_triggered();

    void on_actionCopy_from_Text_2_triggered();

    void on_actionCopy_from_Text_3_triggered();

    void on_actionPaste_into_Text_1_triggered();

    void on_actionPaste_into_Text_2_triggered();

    void on_actionPaste_into_Text_3_triggered();

    void on_actionFind_in_Text_1_triggered();

    void on_actionSelect_All_in_Text_1_triggered();

    void on_actionSelect_All_in_Text_2_triggered();

    void on_actionSelect_All_in_Text_3_triggered();

    void on_actionFind_in_Text_2_triggered();

    void on_actionFind_in_Text_3_triggered();

    void on_actionFont_of_Text_1_triggered();

    void on_actionFont_of_Text_2_triggered();

    void on_actionFont_of_Text_3_triggered();

    void on_actionColor_of_Text_1_triggered();

    void on_actionColor_of_Text_2_triggered();

    void on_actionColor_of_Text_3_triggered();

    void on_actionHighlight_in_Text_1_triggered();

    void on_actionHighlight_in_Text_2_triggered();

    void on_actionHighlight_in_Text_3_triggered();

    void on_actionZoom_In_Text_1_triggered();

    void on_actionZoom_In_Text_2_triggered();

    void on_actionZoom_In_Text_3_triggered();

    void on_actionZoom_Out_Text_1_triggered();

    void on_actionZoom_Out_Text_2_triggered();

    void on_actionZoom_Out_Text_3_triggered();

    void on_actionAbout_triggered();

    void on_actionFormatted_Text_1_triggered();

    void on_actionFormatted_Text_2_triggered();

    void on_actionFormatted_Text_3_triggered();

    void on_actionUnformatted_Text_1_triggered();

    void on_actionUnformatted_Text_2_triggered();

    void on_actionUnformatted_Text_3_triggered();

    void on_textEdit_Text_1_customContextMenuRequested();

    void on_textEdit_Text_2_customContextMenuRequested();

    void on_textEdit_Text_3_customContextMenuRequested();

    void on_actionEnglish_triggered();

    void on_actionRussian_triggered();

    void on_actionFind_and_Replace_in_Text_1_triggered();

    void on_actionFind_and_Replace_in_Text_2_triggered();

    void on_actionFind_and_Replace_in_Text_3_triggered();

    void on_actionFind_and_Replace_All_in_Text_1_triggered();

    void on_actionFind_and_Replace_All_in_Text_2_triggered();

    void on_actionFind_and_Replace_All_in_Text_3_triggered();

    void on_actionShow_file_paths_and_names_triggered();

    void on_actionHide_file_paths_and_names_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    void formatted(QString document_name);
    void unformatted(QString document_name);
    QString file_1;
    QString file_2;
    QString file_3;
    void writeSettings();
    void search_word(QString document_name);
};

#endif // MAINWINDOW_H
