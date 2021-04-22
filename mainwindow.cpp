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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h"
#include "dialogfind.h"
#include "dialogreplace.h"
#include "dialogreplaceall.h"
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_dir_1->hide();
    ui->label_dir_2->hide();
    ui->label_dir_3->hide();
    ui->label_dir_1->setText("");
    ui->label_dir_2->setText("");
    ui->label_dir_3->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMessageBox* messagebox = new QMessageBox (QMessageBox::Question,
                                               tr("Confirm"), tr("Exit program?"),
                                               QMessageBox::Yes | QMessageBox::No, this);
    messagebox->setButtonText(QMessageBox::Yes, tr("Yes"));
    messagebox->setButtonText(QMessageBox::No, tr("No"));
    int n = messagebox->exec();
    delete messagebox;

    if (n == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_actionNew_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QMessageBox* messagebox = new QMessageBox (QMessageBox::Question, tr("Clear Text"), tr("Do you want to clear the text?"),
                                   QMessageBox::No | QMessageBox::Yes, this);
    messagebox->setButtonText(QMessageBox::Yes, tr("Yes"));
    messagebox->setButtonText(QMessageBox::No, tr("No"));
    int answer = messagebox->exec();
    delete messagebox;

    if (answer == QMessageBox::Yes) {
        ui->textEdit_Text_1->clear();
        ui->label_dir_3->setText("");
    }
}

void MainWindow::on_actionNew_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QMessageBox* messagebox = new QMessageBox (QMessageBox::Question, tr("Clear Text"), tr("Do you want to clear the text?"),
                                   QMessageBox::No | QMessageBox::Yes, this);
    messagebox->setButtonText(QMessageBox::Yes, tr("Yes"));
    messagebox->setButtonText(QMessageBox::No, tr("No"));
    int answer = messagebox->exec();
    delete messagebox;

    if (answer == QMessageBox::Yes) {
        ui->textEdit_Text_2->clear();
        ui->label_dir_2->setText("");
    }
}

void MainWindow::on_actionNew_Text_3_triggered()
{
    textEdit_focused("Text 3");

    QMessageBox* messagebox = new QMessageBox (QMessageBox::Question, tr("Clear Text"), tr("Do you want to clear the text?"),
                                   QMessageBox::No | QMessageBox::Yes, this);
    messagebox->setButtonText(QMessageBox::Yes, tr("Yes"));
    messagebox->setButtonText(QMessageBox::No, tr("No"));
    int answer = messagebox->exec();
    delete messagebox;

    if (answer == QMessageBox::Yes) {
        ui->textEdit_Text_3->clear();
        ui->label_dir_3->setText("");
    }
}

void MainWindow::on_actionOpen_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));

    if (!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");

            QString text = in.readAll();
            File.close();

            if (file.endsWith(".html") || file.endsWith(".htm")) {
                ui->textEdit_Text_1->setAcceptRichText(true);
            }
            else {
                ui->textEdit_Text_1->setAcceptRichText(false);
            }
            ui->textEdit_Text_1->setText(text);
        }
        file_1 = file;
        ui->label_dir_1->setText(file_1);
    }

    else {
        QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
    }
}

void MainWindow::on_actionOpen_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));

    if (!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");

            QString text = in.readAll();
            File.close();

            if (file.endsWith(".html") || file.endsWith(".htm")) {
                ui->textEdit_Text_2->setAcceptRichText(true);
            }
            else {
                ui->textEdit_Text_2->setAcceptRichText(false);
            }
            ui->textEdit_Text_2->setText(text);
        }
        file_2 = file;
        ui->label_dir_2->setText(file_2);
    }

    else {
        QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
    }
}

void MainWindow::on_actionOpen_Text_3_triggered()
{
    textEdit_focused("Text 3");

    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));

    if (!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");

            QString text = in.readAll();
            File.close();

            if (file.endsWith(".html") || file.endsWith(".htm")) {
                ui->textEdit_Text_3->setAcceptRichText(true);
            }
            else {
                ui->textEdit_Text_3->setAcceptRichText(false);
            }
            ui->textEdit_Text_3->setText(text);
        }
        file_3 = file;
        ui->label_dir_3->setText(file_3);
    }

    else {
        QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QString file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                              tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));

    if (!file.isEmpty())
    {
        QFile File(file);
        if (File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);
            out.setCodec("UTF-8");

            if (file.endsWith(".html") || file.endsWith(".htm")) {
                out << ui->textEdit_Text_1->toHtml();

            }
            else {
                out << ui->textEdit_Text_1->toPlainText();
            }

            File.flush();
            File.close();
            file_1 = file;
            ui->label_dir_1->setText(file_1);
        }
    }
    else {
        QMessageBox::information(this, tr("Error"), tr("Unable to save file."), QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QString file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                              tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));

    if (!file.isEmpty())
    {
        QFile File(file);
        if (File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);
            out.setCodec("UTF-8");

            if (file.endsWith(".html") || file.endsWith(".htm")) {
                out << ui->textEdit_Text_2->toHtml();

            }
            else {
                out << ui->textEdit_Text_2->toPlainText();
            }

            File.flush();
            File.close();
            file_2 = file;
            ui->label_dir_2->setText(file_2);
        }
    }
    else {
        QMessageBox::information(this, tr("Error"), tr("Unable to save file."), QMessageBox::Ok);
    }
}

void MainWindow::on_actionSave_Text_3_triggered()
{
    textEdit_focused("Text 3");

    QString file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                              tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));

    if (!file.isEmpty())
    {
        QFile File(file);
        if (File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);
            out.setCodec("UTF-8");

            if (file.endsWith(".html") || file.endsWith(".htm")) {
                out << ui->textEdit_Text_3->toHtml();

            }
            else {
                out << ui->textEdit_Text_3->toPlainText();
            }

            File.flush();
            File.close();
            file_3 = file;
            ui->label_dir_3->setText(file_3);
        }
    }
    else {
        QMessageBox::information(this, tr("Error"), tr("Unable to save file."), QMessageBox::Ok);
    }
}

void MainWindow::on_actionUndo_in_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->undo();
}

void MainWindow::on_actionUndo_in_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->undo();
}

void MainWindow::on_actionUndo_in_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->undo();
}

void MainWindow::on_actionRedo_in_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->redo();
}

void MainWindow::on_actionRedo_in_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->redo();
}

void MainWindow::on_actionRedo_in_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->redo();
}

void MainWindow::on_actionCut_from_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->cut();
}

void MainWindow::on_actionCut_from_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->cut();
}

void MainWindow::on_actionCut_from_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->cut();
}

void MainWindow::on_actionCopy_from_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->copy();
}

void MainWindow::on_actionCopy_from_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->copy();
}

void MainWindow::on_actionCopy_from_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->copy();
}

void MainWindow::on_actionPaste_into_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->paste();
}

void MainWindow::on_actionPaste_into_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->paste();
}

void MainWindow::on_actionPaste_into_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->paste();
}

void MainWindow::on_actionSelect_All_in_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->selectAll();
}

void MainWindow::on_actionFont_of_Text_1_triggered()
{
    textEdit_focused("Text 1");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_1->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_2_triggered()
{
    textEdit_focused("Text 2");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_2->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_3_triggered()
{
    textEdit_focused("Text 3");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_3->setFont(font);
    } else return;
}

void MainWindow::on_actionColor_of_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_1->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_2->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_3_triggered()
{
     textEdit_focused("Text 3");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_3->setTextColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_1->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_2->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_3_triggered()
{
    textEdit_focused("Text 3");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_3->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionZoom_In_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->zoomIn();
}

void MainWindow::on_actionZoom_Out_Text_1_triggered()
{
    textEdit_focused("Text 1");

    ui->textEdit_Text_1->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_2_triggered()
{
    textEdit_focused("Text 2");

    ui->textEdit_Text_2->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_3_triggered()
{
    textEdit_focused("Text 3");

    ui->textEdit_Text_3->zoomOut();
}

void MainWindow::on_actionAbout_triggered()
{
    QString about_text;
    about_text  = tr("Program for editing Bible texts") + "\n\n";

    about_text += tr("Copyright (C) 2021 Aleksandr Migunov") + "\n\n";

    about_text += "This program is free software; you can redistribute it and/or modify \
it under the terms of the GNU General Public License as published by \
the Free Software Foundation; either version 3 of the License, or \
(at your option) any later version. \n\n";

    about_text += "This program is distributed in the hope that it will be useful, \
but WITHOUT ANY WARRANTY; without even the implied warranty of \
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \
GNU General Public License for more details. \n\n";

    about_text += "You should have received a copy of the GNU General Public License \
along with this program; if not, write to the Free Software \
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.";

    QMessageBox::about(this, tr("About Program"), about_text);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(0);
}

void MainWindow::on_actionFormatted_Text_1_triggered()
{
    textEdit_focused("Text 1");

    formatted("Text_1");
}


void MainWindow::on_actionFormatted_Text_2_triggered()
{
    textEdit_focused("Text 2");

    formatted("Text_2");
}


void MainWindow::on_actionFormatted_Text_3_triggered()
{
    textEdit_focused("Text 3");

    formatted("Text_3");
}

void MainWindow::on_actionUnformatted_Text_1_triggered()
{
    textEdit_focused("Text 1");

    unformatted("Text_1");
}

void MainWindow::on_actionUnformatted_Text_2_triggered()
{
    textEdit_focused("Text 2");

    unformatted("Text_2");
}

void MainWindow::on_actionUnformatted_Text_3_triggered()
{
    textEdit_focused("Text 3");

    unformatted("Text_3");
}

void MainWindow::formatted(QString document_name) {
    QString file = "";

    if (document_name == "Text_1") {
        file = file_1;
    }
    else if (document_name == "Text_2") {
        file = file_2;
    }
    else if (document_name == "Text_3") {
        file = file_3;
    }
    else return;

    if (file.isEmpty() || file.isNull()) {
        file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                             tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));
    }

    if(!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");
            QString text = in.readAll();
            File.close();
            QString text_converted = converter_to_html(text);

            if (document_name == "Text_1") {
                ui->textEdit_Text_1->setHtml(text_converted);
                file_1 = file;
                ui->label_dir_1->setText(file_1);
            }
            else if (document_name == "Text_2") {
                ui->textEdit_Text_2->setHtml(text_converted);
                file_2 = file;
                ui->label_dir_2->setText(file_2);
            }
            else if (document_name == "Text_3") {
                ui->textEdit_Text_3->setHtml(text_converted);
                file_3 = file;
                ui->label_dir_3->setText(file_3);
            }
        }
    }
}

void MainWindow::unformatted(QString document_name)
{
    QString file = "";

    if (document_name == "Text_1") {
        file = file_1;
    }
    else if (document_name == "Text_2") {
        file = file_2;
    }
    else if (document_name == "Text_3") {
        file = file_3;
    }
    else return;

    if (file.isEmpty() || file.isNull()) {
        file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                             tr("Paratext Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;Text Files (*.txt)"));
    }

    if(!file.isEmpty())
    {
        QFile File(file);
        if(File.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&File);
            in.setCodec("UTF-8");
            QString text = in.readAll();
            File.close();
            QString text_converted = converter_to_html(text);

            if (document_name == "Text_1") {
                ui->textEdit_Text_1->setHtml(text_converted);
                file_1 = file;
                ui->label_dir_1->setText(file_1);
            }
            else if (document_name == "Text_2") {
                ui->textEdit_Text_2->setHtml(text_converted);
                file_2 = file;
                ui->label_dir_2->setText(file_2);
            }
            else if (document_name == "Text_3") {
                ui->textEdit_Text_3->setHtml(text_converted);
                file_3 = file;
                ui->label_dir_3->setText(file_3);
            }
        }
    }
}


void MainWindow::on_textEdit_Text_1_customContextMenuRequested()
{
    textEdit_focused("Text 1");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_1_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_1_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_1_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_1_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_1_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_1_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_1_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_1_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_1_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_1_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_1_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_1_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_1_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_1_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_1_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_1_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionUndo);
    contextMenu->addAction(actionRedo);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionCut);
    contextMenu->addAction(actionCopy);
    contextMenu->addAction(actionPaste);
    contextMenu->addAction(actionSelectAll);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionZoomIn);
    contextMenu->addAction(actionZoomOut);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionFormatted);
    contextMenu->addAction(actionUnformatted);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionFind);
    contextMenu->addAction(actionReplace);
    contextMenu->addAction(actionReplaceAll);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_2_customContextMenuRequested()
{
    textEdit_focused("Text 2");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_2_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_2_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_2_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_2_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_2_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_2_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_2_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_2_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_2_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_2_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_2_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_2_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_2_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_2_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_2_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_2_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionUndo);
    contextMenu->addAction(actionRedo);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionCut);
    contextMenu->addAction(actionCopy);
    contextMenu->addAction(actionPaste);
    contextMenu->addAction(actionSelectAll);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionZoomIn);
    contextMenu->addAction(actionZoomOut);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionFormatted);
    contextMenu->addAction(actionUnformatted);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionFind);
    contextMenu->addAction(actionReplace);
    contextMenu->addAction(actionReplaceAll);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_3_customContextMenuRequested()
{
    textEdit_focused("Text 3");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_3_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_3_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_3_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_3_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_3_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_3_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_3_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_3_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_3_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_3_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_3_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_3_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_3_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_3_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_3_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_3_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionUndo);
    contextMenu->addAction(actionRedo);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionCut);
    contextMenu->addAction(actionCopy);
    contextMenu->addAction(actionPaste);
    contextMenu->addAction(actionSelectAll);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionZoomIn);
    contextMenu->addAction(actionZoomOut);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionFormatted);
    contextMenu->addAction(actionUnformatted);
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionFind);
    contextMenu->addAction(actionReplace);
    contextMenu->addAction(actionReplaceAll);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_actionEnglish_triggered()
{
    language = "English";
    QMessageBox::information(this, tr("Language change"),
                             tr("Interface language will be changed after the program restarts."));
    writeSettings();
}

void MainWindow::on_actionRussian_triggered()
{
    language = "Russian";
    QMessageBox::information(this, tr("Language change"),
                                 tr("Interface language will be changed after the program restarts."));
    writeSettings();
}

void MainWindow::writeSettings() {
    QSettings *m_settings = new QSettings("usfm_editor_settings.ini", QSettings::IniFormat);
    m_settings->beginGroup("MainWindow");
    m_settings->setValue("language", language);
    m_settings->endGroup();
    m_settings->sync();
}

void MainWindow::search_word(QString document_name) {
    DialogFind dialogfindDocument;
    dialogfindDocument.exec();
    dialogfindDocument.show(); //in this way, this dialog will be shown when search continues

    bool Found = false;

    QFlags<QTextDocument::FindFlag> searchOptions;

    if (dialogfindDocument.CaseSensitive == true) {
        if (dialogfindDocument.WholeWord == true) {
            if (dialogfindDocument.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords;
            }
            else if (dialogfindDocument.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively |
                        QTextDocument::FindWholeWords;
            }
        }
        else {
            if (dialogfindDocument.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively;
            }
            else if (dialogfindDocument.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively;
            }
        }
    }

    else {
        if (dialogfindDocument.WholeWord == true) {
            if (dialogfindDocument.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindWholeWords;
            }
            else if (dialogfindDocument.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindWholeWords;
            }

        }
        else {
            if (dialogfindDocument.SearchDirection == "Forward") {
                searchOptions = 0;
            }
            else if (dialogfindDocument.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward;
            }
        }
    }

    if (document_name == "Text 1") {
        Found = ui->textEdit_Text_1->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text 2") {
        Found = ui->textEdit_Text_2->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text 3") {
        Found = ui->textEdit_Text_3->find(dialogfindDocument.search, searchOptions);
    }
    else return;

    if ((!(dialogfindDocument.search.isEmpty() || dialogfindDocument.search.isNull())) & !Found) {
        QMessageBox* notFound = new QMessageBox(QMessageBox::Warning, tr("Not found"),
                                                tr("The word was not found"));
        notFound->exec();
        delete notFound;
    }

    if ((!(dialogfindDocument.search.isEmpty() || dialogfindDocument.search.isNull())) & Found) {
        bool continueSearch = true;
        bool foundNew = true;

        while (continueSearch & foundNew) {
            QMessageBox* findNext =
                    new QMessageBox(QMessageBox::Question, tr("Continue?"), tr("Find next?"),
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            findNext->setButtonText(QMessageBox::Yes, tr("Yes"));
            findNext->setButtonText(QMessageBox::No, tr("No"));
            findNext->setButtonText(QMessageBox::Cancel, tr("Cancel"));

            int n = findNext->exec();
            delete findNext;

            if (n == QMessageBox::Yes) {
                if (document_name == "Text 1") {
                    foundNew = ui->textEdit_Text_1->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text 2") {
                    foundNew = ui->textEdit_Text_2->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text 3") {
                    foundNew = ui->textEdit_Text_3->find(dialogfindDocument.search, searchOptions);
                }
                else return;
            }
            else if ((n == QMessageBox::No) || (n == QMessageBox::Cancel)) {
                continueSearch = false;
            }
        }

        if (!foundNew) {
            QMessageBox* noNewFound = new QMessageBox(QMessageBox::Warning, tr("End of search"),
                                                      tr("End of search is reached"));
            noNewFound->exec();
            delete noNewFound;
        }
    }
}


void MainWindow::on_actionFind_in_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QString str = ui->textEdit_Text_1->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text 1");
}

void MainWindow::on_actionFind_in_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QString str = ui->textEdit_Text_2->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text 2");
}

void MainWindow::on_actionFind_in_Text_3_triggered()
{
    textEdit_focused("Text 3");

    QString str = ui->textEdit_Text_3->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text 3");
}

void MainWindow::on_actionFind_and_Replace_in_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QString str = ui->textEdit_Text_1->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }

    DialogReplace dialogreplace;
    dialogreplace.exec();
    dialogreplace.show(); //in this way, this dialog will be shown when search continues
    bool Found = false;

    QFlags<QTextDocument::FindFlag> searchOptions;

    if (dialogreplace.CaseSensitive == true) {
        if (dialogreplace.WholeWord == true) {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively |
                        QTextDocument::FindWholeWords;
            }
        }
        else {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively;
            }
        }
    }

    else {
        if (dialogreplace.WholeWord == true) {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindWholeWords;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindWholeWords;
            }
        }
        else {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = 0;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward;
            }
        }
    }

    Found = ui->textEdit_Text_1->find(dialogreplace.search, searchOptions);

    if ((!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) & !Found) {
        QMessageBox* notFound = new QMessageBox(QMessageBox::Warning, tr("Not found"),
                                                tr("The word was not found"));
        notFound->exec();
        delete notFound;
    }

    else if (!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) {
        ui->textEdit_Text_1->cut();
        ui->textEdit_Text_1->insertPlainText(dialogreplace.replace);
    }

    if ((!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) & Found) {
        bool continueSearch = true;
        bool foundNew = true;

        while (continueSearch & foundNew) {
            QMessageBox* findNext =
                    new QMessageBox(QMessageBox::Question, tr("Continue?"), tr("Find and replace next?"),
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            findNext->setButtonText(QMessageBox::Yes, tr("Yes"));
            findNext->setButtonText(QMessageBox::No, tr("No"));
            findNext->setButtonText(QMessageBox::Cancel, tr("Cancel"));

            int n = findNext->exec();
            delete findNext;

            if (n == QMessageBox::Yes) {
                foundNew = ui->textEdit_Text_1->find(dialogreplace.search, searchOptions);

                if (foundNew) {
                    ui->textEdit_Text_1->cut();
                    ui->textEdit_Text_1->insertPlainText(dialogreplace.replace);
                }
            }

            else if ((n == QMessageBox::No) || (n == QMessageBox::Cancel)) {
                continueSearch = false;
            }
        }

        if (!foundNew) {
            QMessageBox* noNewFound = new QMessageBox(QMessageBox::Warning, tr("End of search"),
                                                      tr("End of search is reached"));
            noNewFound->exec();
            delete noNewFound;
        }
    }

}

void MainWindow::on_actionFind_and_Replace_in_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QString str = ui->textEdit_Text_2->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }

    DialogReplace dialogreplace;
    dialogreplace.exec();
    dialogreplace.show(); //in this way, this dialog will be shown when search continues
    bool Found = false;

    QFlags<QTextDocument::FindFlag> searchOptions;

    if (dialogreplace.CaseSensitive == true) {
        if (dialogreplace.WholeWord == true) {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively |
                        QTextDocument::FindWholeWords;
            }
        }
        else {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively;
            }
        }
    }

    else {
        if (dialogreplace.WholeWord == true) {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindWholeWords;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindWholeWords;
            }
        }
        else {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = 0;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward;
            }
        }
    }

    Found = ui->textEdit_Text_2->find(dialogreplace.search, searchOptions);

    if ((!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) & !Found) {
        QMessageBox* notFound = new QMessageBox(QMessageBox::Warning, tr("Not found"),
                                                tr("The word was not found"));
        notFound->exec();
        delete notFound;
    }

    else if (!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) {
        ui->textEdit_Text_2->cut();
        ui->textEdit_Text_2->insertPlainText(dialogreplace.replace);
    }

    if ((!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) & Found) {
        bool continueSearch = true;
        bool foundNew = true;

        while (continueSearch & foundNew) {
            QMessageBox* findNext =
                    new QMessageBox(QMessageBox::Question, tr("Continue?"), tr("Find and replace next?"),
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            findNext->setButtonText(QMessageBox::Yes, tr("Yes"));
            findNext->setButtonText(QMessageBox::No, tr("No"));
            findNext->setButtonText(QMessageBox::Cancel, tr("Cancel"));

            int n = findNext->exec();
            delete findNext;

            if (n == QMessageBox::Yes) {
                foundNew = ui->textEdit_Text_2->find(dialogreplace.search, searchOptions);

                if (foundNew) {
                    ui->textEdit_Text_2->cut();
                    ui->textEdit_Text_2->insertPlainText(dialogreplace.replace);
                }
            }

            else if ((n == QMessageBox::No) || (n == QMessageBox::Cancel)) {
                continueSearch = false;
            }
        }

        if (!foundNew) {
            QMessageBox* noNewFound = new QMessageBox(QMessageBox::Warning, tr("End of search"),
                                                      tr("End of search is reached"));
            noNewFound->exec();
            delete noNewFound;
        }
    }
}

void MainWindow::on_actionFind_and_Replace_in_Text_3_triggered()
{
    textEdit_focused("Text 3");

    QString str = ui->textEdit_Text_3->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }

    DialogReplace dialogreplace;
    dialogreplace.exec();
    dialogreplace.show(); //in this way, this dialog will be shown when search continues
    bool Found = false;

    QFlags<QTextDocument::FindFlag> searchOptions;

    if (dialogreplace.CaseSensitive == true) {
        if (dialogreplace.WholeWord == true) {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively |
                        QTextDocument::FindWholeWords;
            }
        }
        else {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindCaseSensitively;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindCaseSensitively;
            }
        }
    }

    else {
        if (dialogreplace.WholeWord == true) {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = QTextDocument::FindWholeWords;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward | QTextDocument::FindWholeWords;
            }
        }
        else {
            if (dialogreplace.SearchDirection == "Forward") {
                searchOptions = 0;
            }
            else if (dialogreplace.SearchDirection == "Backward") {
                searchOptions = QTextDocument::FindBackward;
            }
        }
    }

    Found = ui->textEdit_Text_3->find(dialogreplace.search, searchOptions);

    if ((!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) & !Found) {
        QMessageBox* notFound = new QMessageBox(QMessageBox::Warning, tr("Not found"),
                                                tr("The word was not found"));
        notFound->exec();
        delete notFound;
    }

    else if (!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) {
        ui->textEdit_Text_3->cut();
        ui->textEdit_Text_3->insertPlainText(dialogreplace.replace);
    }

    if ((!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) & Found) {
        bool continueSearch = true;
        bool foundNew = true;

        while (continueSearch & foundNew) {
            QMessageBox* findNext =
                    new QMessageBox(QMessageBox::Question, tr("Continue?"), tr("Find and replace next?"),
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            findNext->setButtonText(QMessageBox::Yes, tr("Yes"));
            findNext->setButtonText(QMessageBox::No, tr("No"));
            findNext->setButtonText(QMessageBox::Cancel, tr("Cancel"));

            int n = findNext->exec();
            delete findNext;

            if (n == QMessageBox::Yes) {
                foundNew = ui->textEdit_Text_3->find(dialogreplace.search, searchOptions);

                if (foundNew) {
                    ui->textEdit_Text_3->cut();
                    ui->textEdit_Text_3->insertPlainText(dialogreplace.replace);
                }
            }

            else if ((n == QMessageBox::No) || (n == QMessageBox::Cancel)) {
                continueSearch = false;
            }
        }

        if (!foundNew) {
            QMessageBox* noNewFound = new QMessageBox(QMessageBox::Warning, tr("End of search"),
                                                      tr("End of search is reached"));
            noNewFound->exec();
            delete noNewFound;
        }
    }
}

void MainWindow::on_actionFind_and_Replace_All_in_Text_1_triggered()
{
    textEdit_focused("Text 1");

    QString str = ui->textEdit_Text_1->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }

    DialogReplaceAll dialogreplaceall;
    dialogreplaceall.exec();
    dialogreplaceall.show();

    if (!(dialogreplaceall.search.isEmpty() || dialogreplaceall.search.isNull())) {
        QString text = ui->textEdit_Text_1->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_1->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

void MainWindow::on_actionFind_and_Replace_All_in_Text_2_triggered()
{
    textEdit_focused("Text 2");

    QString str = ui->textEdit_Text_2->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }

    DialogReplaceAll dialogreplaceall;
    dialogreplaceall.exec();
    dialogreplaceall.show();

    if (!(dialogreplaceall.search.isEmpty() || dialogreplaceall.search.isNull())) {
        QString text = ui->textEdit_Text_2->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_2->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

void MainWindow::on_actionFind_and_Replace_All_in_Text_3_triggered()
{
    textEdit_focused("Text 3");

    QString str = ui->textEdit_Text_3->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }

    DialogReplaceAll dialogreplaceall;
    dialogreplaceall.exec();
    dialogreplaceall.show();

    if (!(dialogreplaceall.search.isEmpty() || dialogreplaceall.search.isNull())) {
        QString text = ui->textEdit_Text_3->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_3->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

void MainWindow::on_actionShow_file_paths_and_names_triggered()
{
    ui->label_dir_1->show();
    ui->label_dir_2->show();
    ui->label_dir_3->show();
}

void MainWindow::on_actionHide_file_paths_and_names_triggered()
{
    ui->label_dir_1->hide();
    ui->label_dir_2->hide();
    ui->label_dir_3->hide();
}

//setting highlighted textEdit
//all the methods that affect textEdits will call this method in the beginning
void MainWindow::textEdit_focused(QString textEditName) {
    //setting the chosen textEdit and corresponding label as highlighted
    if (textEditName == "Text 1") {
        ui->textEdit_Text_1->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_1->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text 2") {
        ui->textEdit_Text_2->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_2->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text 3") {
        ui->textEdit_Text_3->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_3->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }

    //unsetting highlightening of others
    if (textEditName != "Text 1") {
        ui->textEdit_Text_1->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_1->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text 2") {
        ui->textEdit_Text_2->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_2->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text 3") {
        ui->textEdit_Text_3->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_3->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
}

void MainWindow::on_textEdit_Text_1_selectionChanged()
{
    textEdit_focused("Text 1");
}

void MainWindow::on_textEdit_Text_2_selectionChanged()
{
    textEdit_focused("Text 2");
}

void MainWindow::on_textEdit_Text_3_selectionChanged()
{
    textEdit_focused("Text 3");
}

