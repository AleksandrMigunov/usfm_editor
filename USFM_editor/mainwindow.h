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
#include <QSettings>

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

    //void on_actionShow_file_paths_and_names_triggered();

    void on_actionHide_file_paths_and_names_triggered();

    void on_textEdit_Text_1_selectionChanged();

    void on_textEdit_Text_2_selectionChanged();

    void on_textEdit_Text_3_selectionChanged();

    void on_actionAbout_Qt_triggered();

    //void on_actionShow_only_file_names_triggered();

    void on_actionSave_Text_1_As_triggered();

    void on_actionSave_Text_2_As_triggered();

    void on_actionSave_Text_3_As_triggered();

    void on_actionNew_Text_4_triggered();

    void on_actionOpen_Text_4_triggered();

    void on_actionSave_Text_4_triggered();

    void on_actionSave_Text_4_As_triggered();

    void on_actionUndo_in_Text_4_triggered();

    void on_actionRedo_in_Text_4_triggered();

    void on_actionCut_from_Text_4_triggered();

    void on_actionCopy_from_Text_4_triggered();

    void on_actionPaste_into_Text_4_triggered();

    void on_actionSelect_All_in_Text_4_triggered();

    void on_actionFind_in_Text_4_triggered();

    void on_actionFind_and_Replace_in_Text_4_triggered();

    void on_actionFind_and_Replace_All_in_Text_4_triggered();

    void on_actionZoom_In_Text_4_triggered();

    void on_actionZoom_Out_Text_4_triggered();

    void on_actionFormatted_Text_4_triggered();

    void on_actionUnformatted_Text_4_triggered();

    void on_actionFont_of_Text_4_triggered();

    void on_actionColor_of_Text_4_triggered();

    void on_actionHighlight_in_Text_4_triggered();

    void on_textEdit_Text_4_selectionChanged();

    void on_textEdit_Text_4_customContextMenuRequested();

    void on_textEdit_Text_5_customContextMenuRequested();

    void on_textEdit_Text_6_customContextMenuRequested();

    void on_textEdit_Text_7_customContextMenuRequested();

    void on_textEdit_Text_8_customContextMenuRequested();

    //void on_actionIn_All_Windows_triggered();

    //void on_actionShow_file_paths_In_all_windows_triggered();

    //void on_actionShow_file_names_In_All_Windows_triggered();

    void on_actionShow_file_path_of_Text_1_triggered();

    void on_actionShow_file_path_of_Text_2_triggered();

    void on_actionShow_file_path_of_Text_3_triggered();

    void on_actionShow_file_path_of_Text_4_triggered();

    void on_actionShow_file_name_of_Text_1_triggered();

    void on_actionShow_file_name_of_Text_2_triggered();

    void on_actionShow_file_name_of_Text_3_triggered();

    void on_actionShow_file_name_of_Text_4_triggered();

    void on_actionShow_file_paths_in_all_windows_triggered();

    void on_actionShow_file_names_in_all_windows_triggered();

    void on_actionShow_Text_1_triggered();

    void on_actionShow_Texts_1_2_triggered();

    void on_actionShow_Texts_1_3_triggered();

    void on_actionShow_Texts_1_4_triggered();

    void on_actionShow_Texts_1_5_triggered();

    void on_actionShow_Texts_1_2_5_6_triggered();

    void on_actionShow_Texts_1_3_5_7_triggered();

    void on_actionShow_Texts_1_8_triggered();

    void on_textEdit_Text_5_selectionChanged();

    void on_textEdit_Text_6_selectionChanged();

    void on_textEdit_Text_7_selectionChanged();

    void on_textEdit_Text_8_selectionChanged();

    void on_actionReset_screen_size_triggered();

    void on_actionNew_Text_5_triggered();

    void on_actionNew_Text_6_triggered();

    void on_actionNew_Text_7_triggered();

    void on_actionNew_Text_8_triggered();

    void on_actionOpen_Text_5_triggered();

    void on_actionOpen_Text_6_triggered();

    void on_actionOpen_Text_7_triggered();

    void on_actionOpen_Text_8_triggered();

    void on_actionSave_Text_5_triggered();

    void on_actionSave_Text_6_triggered();

    void on_actionSave_Text_7_triggered();

    void on_actionSave_Text_8_triggered();

    void on_actionSave_Text_5_As_triggered();

    void on_actionSave_Text_6_As_triggered();

    void on_actionSave_Text_7_As_triggered();

    void on_actionSave_Text_8_As_triggered();

    void on_actionUndo_in_Text_5_triggered();

    void on_actionUndo_in_Text_6_triggered();

    void on_actionUndo_in_Text_7_triggered();

    void on_actionUndo_in_Text_8_triggered();

    void on_actionRedo_in_Text_5_triggered();

    void on_actionRedo_in_Text_6_triggered();

    void on_actionRedo_in_Text_7_triggered();

    void on_actionRedo_in_Text_8_triggered();

    void on_actionCut_from_Text_5_triggered();

    void on_actionCut_from_Text_6_triggered();

    void on_actionCut_from_Text_7_triggered();

    void on_actionCut_from_Text_8_triggered();

    void on_actionCopy_from_Text_5_triggered();

    void on_actionCopy_from_Text_6_triggered();

    void on_actionCopy_from_Text_7_triggered();

    void on_actionCopy_from_Text_8_triggered();

    void on_actionPaste_into_Text_5_triggered();

    void on_actionPaste_into_Text_6_triggered();

    void on_actionPaste_into_Text_7_triggered();

    void on_actionPaste_into_Text_8_triggered();

    void on_actionSelect_All_in_Text_5_triggered();

    void on_actionSelect_All_in_Text_6_triggered();

    void on_actionSelect_All_in_Text_7_triggered();

    void on_actionSelect_All_in_Text_8_triggered();

    void on_actionFind_in_Text_5_triggered();

    void on_actionFind_in_Text_6_triggered();

    void on_actionFind_in_Text_7_triggered();

    void on_actionFind_in_Text_8_triggered();

    void on_actionFind_and_Replace_in_Text_5_triggered();

    void on_actionFind_and_Replace_in_Text_6_triggered();

    void on_actionFind_and_Replace_in_Text_7_triggered();

    void on_actionFind_and_Replace_in_Text_8_triggered();

    void on_actionFind_and_Replace_All_in_Text_5_triggered();

    void on_actionFind_and_Replace_All_in_Text_6_triggered();

    void on_actionFind_and_Replace_All_in_Text_7_triggered();

    void on_actionFind_and_Replace_All_in_Text_8_triggered();

    void on_actionZoom_In_Text_5_triggered();

    void on_actionZoom_In_Text_6_triggered();

    void on_actionZoom_In_Text_7_triggered();

    void on_actionZoom_In_Text_8_triggered();

    void on_actionZoom_Out_Text_5_triggered();

    void on_actionZoom_Out_Text_6_triggered();

    void on_actionZoom_Out_Text_7_triggered();

    void on_actionZoom_Out_Text_8_triggered();

    void on_actionFormatted_Text_5_triggered();

    void on_actionFormatted_Text_6_triggered();

    void on_actionFormatted_Text_7_triggered();

    void on_actionFormatted_Text_8_triggered();

    void on_actionUnformatted_Text_5_triggered();

    void on_actionUnformatted_Text_6_triggered();

    void on_actionUnformatted_Text_7_triggered();

    void on_actionUnformatted_Text_8_triggered();

    void on_actionFont_of_Text_5_triggered();

    void on_actionFont_of_Text_6_triggered();

    void on_actionFont_of_Text_7_triggered();

    void on_actionFont_of_Text_8_triggered();

    void on_actionColor_of_Text_5_triggered();

    void on_actionColor_of_Text_6_triggered();

    void on_actionColor_of_Text_7_triggered();

    void on_actionColor_of_Text_8_triggered();

    void on_actionHighlight_in_Text_5_triggered();

    void on_actionHighlight_in_Text_6_triggered();

    void on_actionHighlight_in_Text_7_triggered();

    void on_actionHighlight_in_Text_8_triggered();

    void on_actionShow_file_path_of_Text_5_triggered();

    void on_actionShow_file_path_of_Text_6_triggered();

    void on_actionShow_file_path_of_Text_7_triggered();

    void on_actionShow_file_path_of_Text_8_triggered();

    void on_actionShow_file_name_of_Text_5_triggered();

    void on_actionShow_file_name_of_Text_6_triggered();

    void on_actionShow_file_name_of_Text_7_triggered();

    void on_actionShow_file_name_of_Text_8_triggered();

    void on_actionZoom_In_all_windows_triggered();

    void on_actionZoom_Out_all_windows_triggered();

    void on_actionClose_not_close_invisible_files_triggered();

    void on_actionLoad_files_automatically_triggered();



private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    void formatted(QString document_name);
    void unformatted(QString document_name);
    QString file_1;
    QString file_2;
    QString file_3;
    QString file_4;
    QString file_5;
    QString file_6;
    QString file_7;
    QString file_8;
    QString fileName_1;
    QString fileName_2;
    QString fileName_3;
    QString fileName_4;
    QString fileName_5;
    QString fileName_6;
    QString fileName_7;
    QString fileName_8;
    void writeSettings();
    void search_word(QString document_name);
    void textEdit_focused(QString textEditName);
    bool formatted_1;
    bool formatted_2;
    bool formatted_3;
    bool formatted_4;
    bool formatted_5;
    bool formatted_6;
    bool formatted_7;
    bool formatted_8;
    void show_file_path(QString document_name);
    void show_file_name(QString document_name);
    bool text_1_visible;
    bool text_2_visible;
    bool text_3_visible;
    bool text_4_visible;
    bool text_5_visible;
    bool text_6_visible;
    bool text_7_visible;
    bool text_8_visible;
    void open_text(QString document_name);
    void save_text(QString document_name);
    void save_text_as(QString document_name);
    void find_and_replace(QString document_name);
    bool hidden_files_close;

    bool FilesNotLoadAuto;
    void readSettings();
    int zoom_1;
    int zoom_2;
    int zoom_3;
    int zoom_4;
    int zoom_5;
    int zoom_6;
    int zoom_7;
    int zoom_8;
    void set_zoom_at_start();
    void open_files_at_start();

protected:
    QSettings *m_settings;
    QVariant files_not_load_auto;
    QVariant text_1;
    QVariant text_2;
    QVariant text_3;
    QVariant text_4;
    QVariant text_5;
    QVariant text_6;
    QVariant text_7;
    QVariant text_8;
    QVariant lang;
    QVariant zoom1;
    QVariant zoom2;
    QVariant zoom3;
    QVariant zoom4;
    QVariant zoom5;
    QVariant zoom6;
    QVariant zoom7;
    QVariant zoom8;
};

#endif // MAINWINDOW_H
