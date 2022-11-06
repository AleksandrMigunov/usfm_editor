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
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QInputDialog>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QDateTime>
#include <QPushButton>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QSettings>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QDir>
#include <QTextCodec>
#include <QByteArray>
#include <QWidget>
#include "converter.h"
#include "dialogfind.h"
#include "dialogreplace.h"
#include "dialogreplaceall.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_dir_1->hide();
    ui->label_dir_2->hide();
    ui->label_dir_3->hide();
    ui->label_dir_4->hide();
    ui->label_dir_5->hide();
    ui->label_dir_6->hide();
    ui->label_dir_7->hide();
    ui->label_dir_8->hide();

    ui->label_dir_1->setText("");
    ui->label_dir_2->setText("");
    ui->label_dir_3->setText("");
    ui->label_dir_4->setText("");
    ui->label_dir_5->setText("");
    ui->label_dir_6->setText("");
    ui->label_dir_7->setText("");
    ui->label_dir_8->setText("");

    ui->label_file_1->hide();
    ui->label_file_2->hide();
    ui->label_file_3->hide();
    ui->label_file_4->hide();
    ui->label_file_5->hide();
    ui->label_file_6->hide();
    ui->label_file_7->hide();
    ui->label_file_8->hide();

    ui->label_file_1->setText("");
    ui->label_file_2->setText("");
    ui->label_file_3->setText("");
    ui->label_file_4->setText("");
    ui->label_file_5->setText("");
    ui->label_file_6->setText("");
    ui->label_file_7->setText("");
    ui->label_file_8->setText("");

    formatted_1 = false;
    formatted_2 = false;
    formatted_3 = false;
    formatted_4 = false;
    formatted_5 = false;
    formatted_6 = false;
    formatted_7 = false;
    formatted_8 = false;

    text_1_visible = true;
    text_2_visible = true;
    text_3_visible = true;
    text_4_visible = true;
    text_5_visible = true;
    text_6_visible = true;
    text_7_visible = true;
    text_8_visible = true;

    textEdit_focused("Text_1");

    QDesktopWidget desk;
    QRect rect = desk.availableGeometry();
    QPoint pos = QPoint(0,0);
    QSize size = rect.size();
    resize(size);
    move(pos);
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

// /////////////////////////////////////////////////////////////////////////////////////////
//Menu "File"
// /////////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////////////////////////
//Option "New"
// /////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionNew_Text_1_triggered()
{
    textEdit_focused("Text_1");

    ui->textEdit_Text_1->clear();
    ui->label_dir_1->setText("");
    ui->label_file_1->setText("");
}

void MainWindow::on_actionNew_Text_2_triggered()
{
    textEdit_focused("Text_2");

    ui->textEdit_Text_2->clear();
    ui->label_dir_2->setText("");
    ui->label_file_2->setText("");
}

void MainWindow::on_actionNew_Text_3_triggered()
{
    textEdit_focused("Text_3");

    ui->textEdit_Text_3->clear();
    ui->label_dir_3->setText("");
    ui->label_file_3->setText("");
}

void MainWindow::on_actionNew_Text_4_triggered()
{
    textEdit_focused("Text_4");

    ui->textEdit_Text_4->clear();
    ui->label_dir_4->setText("");
    ui->label_file_4->setText("");
}

void MainWindow::on_actionNew_Text_5_triggered()
{
    textEdit_focused("Text_5");

    ui->textEdit_Text_5->clear();
    ui->label_dir_5->setText("");
    ui->label_file_5->setText("");
}

void MainWindow::on_actionNew_Text_6_triggered()
{
    textEdit_focused("Text_6");

    ui->textEdit_Text_6->clear();
    ui->label_dir_6->setText("");
    ui->label_file_6->setText("");
}

void MainWindow::on_actionNew_Text_7_triggered()
{
    textEdit_focused("Text_7");

    ui->textEdit_Text_7->clear();
    ui->label_dir_7->setText("");
    ui->label_file_7->setText("");
}

void MainWindow::on_actionNew_Text_8_triggered()
{
    textEdit_focused("Text_8");

    ui->textEdit_Text_8->clear();
    ui->label_dir_8->setText("");
    ui->label_file_8->setText("");
}

// ////////////////////////////////////////////////////////////////////////////////////
//Function for opening text
// ////////////////////////////////////////////////////////////////////////////////////

void MainWindow::open_text(QString document_name)
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                              tr("USFM Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;XML Files (*.xml);;Text Files (*.txt)"));

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
                if (document_name == "Text_1")
                {
                    ui->textEdit_Text_1->setAcceptRichText(true);
                    formatted_1 = true;
                }
                else if (document_name == "Text_2")
                {
                    ui->textEdit_Text_2->setAcceptRichText(true);
                    formatted_2 = true;
                }
                else if (document_name == "Text_3")
                {
                    ui->textEdit_Text_3->setAcceptRichText(true);
                    formatted_3 = true;
                }
                else if (document_name == "Text_4")
                {
                    ui->textEdit_Text_4->setAcceptRichText(true);
                    formatted_4 = true;
                }
                else if (document_name == "Text_5")
                {
                    ui->textEdit_Text_5->setAcceptRichText(true);
                    formatted_5 = true;
                }
                else if (document_name == "Text_6")
                {
                    ui->textEdit_Text_6->setAcceptRichText(true);
                    formatted_6 = true;
                }
                else if (document_name == "Text_7")
                {
                    ui->textEdit_Text_7->setAcceptRichText(true);
                    formatted_7 = true;
                }
                else if (document_name == "Text_8")
                {
                    ui->textEdit_Text_8->setAcceptRichText(true);
                    formatted_8 = true;
                }
            }
            else {
                if (document_name == "Text_1")
                {
                    ui->textEdit_Text_1->setAcceptRichText(false);
                }
                else if (document_name == "Text_2")
                {
                    ui->textEdit_Text_2->setAcceptRichText(false);
                }
                else if (document_name == "Text_3")
                {
                    ui->textEdit_Text_3->setAcceptRichText(false);
                }
                else if (document_name == "Text_4")
                {
                    ui->textEdit_Text_4->setAcceptRichText(false);
                }
                else if (document_name == "Text_5")
                {
                    ui->textEdit_Text_5->setAcceptRichText(false);
                }
                else if (document_name == "Text_6")
                {
                    ui->textEdit_Text_6->setAcceptRichText(false);
                }
                else if (document_name == "Text_7")
                {
                    ui->textEdit_Text_7->setAcceptRichText(false);
                }
                else if (document_name == "Text_8")
                {
                    ui->textEdit_Text_8->setAcceptRichText(false);
                }
            }
            if (document_name == "Text_1")
            {
                ui->textEdit_Text_1->setText(text);
            }
            else if (document_name == "Text_2")
            {
                ui->textEdit_Text_2->setText(text);
            }
            else if (document_name == "Text_3")
            {
                ui->textEdit_Text_3->setText(text);
            }
            else if (document_name == "Text_4")
            {
                ui->textEdit_Text_4->setText(text);
            }
            else if (document_name == "Text_5")
            {
                ui->textEdit_Text_5->setText(text);
            }
            else if (document_name == "Text_6")
            {
                ui->textEdit_Text_6->setText(text);
            }
            else if (document_name == "Text_7")
            {
                ui->textEdit_Text_7->setText(text);
            }
            else if (document_name == "Text_8")
            {
                ui->textEdit_Text_8->setText(text);
            }
        }

        QFileInfo fi(file);
        if (document_name == "Text_1")
        {
            file_1 = file;
            ui->label_dir_1->setText(file_1);
            fileName_1 = fi.fileName();
            ui->label_file_1->setText(fileName_1);
        }
        else if (document_name == "Text_2")
        {
            file_2 = file;
            ui->label_dir_2->setText(file_2);
            fileName_2 = fi.fileName();
            ui->label_file_2->setText(fileName_2);
        }
        else if (document_name == "Text_3")
        {
            file_3 = file;
            ui->label_dir_3->setText(file_3);
            fileName_3 = fi.fileName();
            ui->label_file_3->setText(fileName_3);
        }
        else if (document_name == "Text_4")
        {
            file_4 = file;
            ui->label_dir_4->setText(file_4);
            fileName_4 = fi.fileName();
            ui->label_file_4->setText(fileName_4);
        }
        else if (document_name == "Text_5")
        {
            file_5 = file;
            ui->label_dir_5->setText(file_5);
            fileName_5 = fi.fileName();
            ui->label_file_5->setText(fileName_5);
        }
        else if (document_name == "Text_6")
        {
            file_6 = file;
            ui->label_dir_6->setText(file_6);
            fileName_6 = fi.fileName();
            ui->label_file_6->setText(fileName_6);
        }
        else if (document_name == "Text_7")
        {
            file_7 = file;
            ui->label_dir_7->setText(file_7);
            fileName_7 = fi.fileName();
            ui->label_file_7->setText(fileName_7);
        }
        else if (document_name == "Text_8")
        {
            file_8 = file;
            ui->label_dir_8->setText(file_8);
            fileName_8 = fi.fileName();
            ui->label_file_8->setText(fileName_8);
        }
    }

    else {
        QMessageBox::information(this, tr("Error"), tr("Unable to open file."), QMessageBox::Ok);
    }
}

// ////////////////////////////////////////////////////////////////////////////////////////////
//Option "Open"
// ////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionOpen_Text_1_triggered()
{
    textEdit_focused("Text_1");
    open_text("Text_1");
}

void MainWindow::on_actionOpen_Text_2_triggered()
{
    textEdit_focused("Text_2");
    open_text("Text_2");
}

void MainWindow::on_actionOpen_Text_3_triggered()
{
    textEdit_focused("Text_3");
    open_text("Text_3");
}

void MainWindow::on_actionOpen_Text_4_triggered()
{
    textEdit_focused("Text_4");
    open_text("Text_4");
}

void MainWindow::on_actionOpen_Text_5_triggered()
{
    textEdit_focused("Text_5");
    open_text("Text_5");
}

void MainWindow::on_actionOpen_Text_6_triggered()
{
    textEdit_focused("Text_6");
    open_text("Text_6");
}

void MainWindow::on_actionOpen_Text_7_triggered()
{
    textEdit_focused("Text_7");
    open_text("Text_7");
}

void MainWindow::on_actionOpen_Text_8_triggered()
{
    textEdit_focused("Text_8");
    open_text("Text_8");
}

// /////////////////////////////////////////////////////////////
//Function for saving file
// ////////////////////////////////////////////////////////////

void MainWindow::save_text(QString document_name)
{
    QString file;
    if (document_name == "Text_1")
    {
        file = file_1;
    }
    else if (document_name == "Text_2")
    {
        file = file_2;
    }
    else if (document_name == "Text_3")
    {
        file = file_3;
    }
    else if (document_name == "Text_4")
    {
        file = file_4;
    }
    else if (document_name == "Text_5")
    {
        file = file_5;
    }
    else if (document_name == "Text_6")
    {
        file = file_6;
    }
    else if (document_name == "Text_7")
    {
        file = file_7;
    }
    else if (document_name == "Text_8")
    {
        file = file_8;
    }

    if ((file.endsWith(".htm")) || (file.endsWith(".html")))
    {
        QMessageBox* messagebox1 = new QMessageBox (QMessageBox::Question,
                                                   tr("Confirm"),
                                                   tr("Do you want to save this HTML file with another name?"),
                                                   QMessageBox::Yes | QMessageBox::No, this);
        messagebox1->setButtonText(QMessageBox::Yes, tr("Yes"));
        messagebox1->setButtonText(QMessageBox::No, tr("No"));
        int n = messagebox1->exec();
        delete messagebox1;

        if (n == QMessageBox::Yes) {
            if (document_name == "Text_1")
            {
                on_actionSave_Text_1_As_triggered();
            }
            else if (document_name == "Text_2")
            {
                on_actionSave_Text_2_As_triggered();
            }
            else if (document_name == "Text_3")
            {
                on_actionSave_Text_3_As_triggered();
            }
            else if (document_name == "Text_4")
            {
                on_actionSave_Text_4_As_triggered();
            }
            else if (document_name == "Text_5")
            {
                on_actionSave_Text_5_As_triggered();
            }
            else if (document_name == "Text_6")
            {
                on_actionSave_Text_6_As_triggered();
            }
            else if (document_name == "Text_7")
            {
                on_actionSave_Text_7_As_triggered();
            }
            else if (document_name == "Text_8")
            {
                on_actionSave_Text_8_As_triggered();
            }

        } else {
            QMessageBox::information(this, tr("File not saved"), tr("File was not saved."), QMessageBox::Ok);
        }
        return;
    }

    if (formatted_1 == true)
    {
        if (document_name == "Text_1")
        {
            unformatted("Text_1");
            formatted_1 = false;
            ui->textEdit_Text_1->setReadOnly(false);
        }
        else if (document_name == "Text_2")
        {
            unformatted("Text_2");
            formatted_2 = false;
            ui->textEdit_Text_2->setReadOnly(false);
        }
        else if (document_name == "Text_3")
        {
            unformatted("Text_3");
            formatted_3 = false;
            ui->textEdit_Text_3->setReadOnly(false);
        }
        else if (document_name == "Text_4")
        {
            unformatted("Text_4");
            formatted_4 = false;
            ui->textEdit_Text_4->setReadOnly(false);
        }
        else if (document_name == "Text_5")
        {
            unformatted("Text_5");
            formatted_5 = false;
            ui->textEdit_Text_5->setReadOnly(false);
        }
        else if (document_name == "Text_6")
        {
            unformatted("Text_6");
            formatted_6 = false;
            ui->textEdit_Text_6->setReadOnly(false);
        }
        else if (document_name == "Text_7")
        {
            unformatted("Text_7");
            formatted_7 = false;
            ui->textEdit_Text_7->setReadOnly(false);
        }
        else if (document_name == "Text_8")
        {
            unformatted("Text_8");
            formatted_8 = false;
            ui->textEdit_Text_8->setReadOnly(false);
        }
    }

    QMessageBox* messagebox2 = new QMessageBox (QMessageBox::Question,
                                               tr("Confirm"),
                                               tr("Do you want to save this file with the same name?"),
                                               QMessageBox::Yes | QMessageBox::No, this);
    messagebox2->setButtonText(QMessageBox::Yes, tr("Yes"));
    messagebox2->setButtonText(QMessageBox::No, tr("No"));
    int n = messagebox2->exec();
    delete messagebox2;

    if (n == QMessageBox::No) {
        if (document_name == "Text_1")
        {
            on_actionSave_Text_1_As_triggered();
        }
        else if (document_name == "Text_2")
        {
            on_actionSave_Text_2_As_triggered();
        }
        else if (document_name == "Text_3")
        {
            on_actionSave_Text_3_As_triggered();
        }
        else if (document_name == "Text_4")
        {
            on_actionSave_Text_4_As_triggered();
        }
        else if (document_name == "Text_5")
        {
            on_actionSave_Text_5_As_triggered();
        }
        else if (document_name == "Text_6")
        {
            on_actionSave_Text_6_As_triggered();
        }
        else if (document_name == "Text_7")
        {
            on_actionSave_Text_7_As_triggered();
        }
        else if (document_name == "Text_8")
        {
            on_actionSave_Text_8_As_triggered();
        }

    } else {
        QFile File(file);

        if(File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&File);

            out.setCodec("UTF-8");
            if (document_name == "Text_1")
            {
                out << ui->textEdit_Text_1->toPlainText();
            }
            else if (document_name == "Text_2")
            {
                out << ui->textEdit_Text_2->toPlainText();
            }
            else if (document_name == "Text_3")
            {
                out << ui->textEdit_Text_3->toPlainText();
            }
            else if (document_name == "Text_4")
            {
                out << ui->textEdit_Text_4->toPlainText();
            }
            else if (document_name == "Text_5")
            {
                out << ui->textEdit_Text_5->toPlainText();
            }
            else if (document_name == "Text_6")
            {
                out << ui->textEdit_Text_6->toPlainText();
            }
            else if (document_name == "Text_7")
            {
                out << ui->textEdit_Text_7->toPlainText();
            }
            else if (document_name == "Text_8")
            {
                out << ui->textEdit_Text_8->toPlainText();
            }

            File.flush();
            File.close();

            QMessageBox::information(this, tr("File was saved"),
                                     tr("File was saved with the same name."));

        }
    }
}

// //////////////////////////////////////////////////////////////////////////
//Option "Save Text"
// //////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionSave_Text_1_triggered()
{
    textEdit_focused("Text_1");
    save_text("Text_1");
}

void MainWindow::on_actionSave_Text_2_triggered()
{
    textEdit_focused("Text_2");
    save_text("Text_2");
}

void MainWindow::on_actionSave_Text_3_triggered()
{
    textEdit_focused("Text_3");
    save_text("Text_3");
}

void MainWindow::on_actionSave_Text_4_triggered()
{
    textEdit_focused("Text_4");
    save_text("Text_4");
}

void MainWindow::on_actionSave_Text_5_triggered()
{
    textEdit_focused("Text_5");
    save_text("Text_5");
}

void MainWindow::on_actionSave_Text_6_triggered()
{
    textEdit_focused("Text_6");
    save_text("Text_6");
}

void MainWindow::on_actionSave_Text_7_triggered()
{
    textEdit_focused("Text_7");
    save_text("Text_7");
}

void MainWindow::on_actionSave_Text_8_triggered()
{
    textEdit_focused("Text_8");
    save_text("Text_8");
}

// /////////////////////////////////////////////////////////////////////////////////////////////////
//Function for saving text with a new name
// /////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::save_text_as(QString document_name)
{
    if (document_name == "Text_1")
    {
        if (formatted_1 == true)
        {
            unformatted("Text_1");
            formatted_1 = false;
            ui->textEdit_Text_1->setReadOnly(false);
        }
        ui->textEdit_Text_1->setAcceptRichText(false);
    }
    else if (document_name == "Text_2")
    {
        if (formatted_2 == true)
        {
            unformatted("Text_2");
            formatted_2 = false;
            ui->textEdit_Text_2->setReadOnly(false);
        }
        ui->textEdit_Text_2->setAcceptRichText(false);
    }
    else if (document_name == "Text_3")
    {
        if (formatted_3 == true)
        {
            unformatted("Text_3");
            formatted_3 = false;
            ui->textEdit_Text_3->setReadOnly(false);
        }
        ui->textEdit_Text_3->setAcceptRichText(false);
    }
    if (document_name == "Text_4")
    {
        if (formatted_4 == true)
        {
            unformatted("Text_4");
            formatted_4 = false;
            ui->textEdit_Text_4->setReadOnly(false);
        }
        ui->textEdit_Text_4->setAcceptRichText(false);
    }
    if (document_name == "Text_5")
    {
        if (formatted_5 == true)
        {
            unformatted("Text_5");
            formatted_5 = false;
            ui->textEdit_Text_5->setReadOnly(false);
        }
        ui->textEdit_Text_5->setAcceptRichText(false);
    }
    if (document_name == "Text_6")
    {
        if (formatted_6 == true)
        {
            unformatted("Text_6");
            formatted_6 = false;
            ui->textEdit_Text_6->setReadOnly(false);
        }
        ui->textEdit_Text_6->setAcceptRichText(false);
    }
    if (document_name == "Text_7")
    {
        if (formatted_7 == true)
        {
            unformatted("Text_7");
            formatted_7 = false;
            ui->textEdit_Text_7->setReadOnly(false);
        }
        ui->textEdit_Text_7->setAcceptRichText(false);
    }
    if (document_name == "Text_8")
    {
        if (formatted_8 == true)
        {
            unformatted("Text_8");
            formatted_8 = false;
            ui->textEdit_Text_8->setReadOnly(false);
        }
        ui->textEdit_Text_8->setAcceptRichText(false);
    }


    QString file = "";

    file = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                        tr("USFM Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;XML Files(*.xml);;Text Files (*.txt)"));

    if(!file.isEmpty())
    {
        if ((!file.endsWith(".SFM") && (!file.endsWith(".txt")) && (!file.endsWith(".htm"))
             && (!file.endsWith(".html")) && (!file.endsWith(".xml")) && (!file.endsWith(".sfm"))))
        {
            file = file + ".SFM";
        }

        QDir direct;
        QString dir = direct.filePath(file);
        QString FileName = dir;
        QFile File(FileName);

        if(File.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&File);

            out.setCodec("UTF-8");

            if (document_name == "Text_1")
            {
                out << ui->textEdit_Text_1->toPlainText();
            }
            else if (document_name == "Text_2")
            {
                out << ui->textEdit_Text_2->toPlainText();
            }
            else if (document_name == "Text_3")
            {
                out << ui->textEdit_Text_3->toPlainText();
            }
            else if (document_name == "Text_4")
            {
                out << ui->textEdit_Text_4->toPlainText();
            }
            else if (document_name == "Text_5")
            {
                out << ui->textEdit_Text_5->toPlainText();
            }
            else if (document_name == "Text_6")
            {
                out << ui->textEdit_Text_6->toPlainText();
            }
            else if (document_name == "Text_7")
            {
                out << ui->textEdit_Text_7->toPlainText();
            }
            else if (document_name == "Text_8")
            {
                out << ui->textEdit_Text_8->toPlainText();
            }

            File.flush();
            File.close();

            QFileInfo fi(FileName);

            if (document_name == "Text_1")
            {
                ui->label_dir_1->setText(FileName);
                file_1 = FileName;
                fileName_1 = fi.fileName();
                ui->label_file_1->setText(fileName_1);
            }
            else if (document_name == "Text_2")
            {
                ui->label_dir_2->setText(FileName);
                file_2 = FileName;
                fileName_2 = fi.fileName();
                ui->label_file_2->setText(fileName_2);
            }
            else if (document_name == "Text_3")
            {
                ui->label_dir_3->setText(FileName);
                file_3 = FileName;
                fileName_3 = fi.fileName();
                ui->label_file_3->setText(fileName_3);
            }
            else if (document_name == "Text_4")
            {
                ui->label_dir_4->setText(FileName);
                file_4 = FileName;
                fileName_4 = fi.fileName();
                ui->label_file_4->setText(fileName_4);
            }
            else if (document_name == "Text_5")
            {
                ui->label_dir_5->setText(FileName);
                file_5 = FileName;
                fileName_5 = fi.fileName();
                ui->label_file_5->setText(fileName_5);
            }
            else if (document_name == "Text_6")
            {
                ui->label_dir_6->setText(FileName);
                file_6 = FileName;
                fileName_6 = fi.fileName();
                ui->label_file_6->setText(fileName_6);
            }
            else if (document_name == "Text_7")
            {
                ui->label_dir_7->setText(FileName);
                file_7 = FileName;
                fileName_7 = fi.fileName();
                ui->label_file_7->setText(fileName_7);
            }
            else if (document_name == "Text_8")
            {
                ui->label_dir_8->setText(FileName);
                file_8 = FileName;
                fileName_8 = fi.fileName();
                ui->label_file_8->setText(fileName_8);
            }

            if ((file.endsWith(".htm")) || (file.endsWith(".html")))
            {
                on_actionFormatted_Text_1_triggered();
            }

            QMessageBox::information(this, tr("File was saved"),
                                     tr("File was saved as") + " " + FileName);
        }
    }
}

// ///////////////////////////////////////////////////////////////////////////////
//Option "Save Text As"
// ///////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionSave_Text_1_As_triggered()
{
    textEdit_focused("Text_1");
    save_text_as("Text_1");
}

void MainWindow::on_actionSave_Text_2_As_triggered()
{
    textEdit_focused("Text_2");
    save_text_as("Text_2");
}

void MainWindow::on_actionSave_Text_3_As_triggered()
{
    textEdit_focused("Text_3");
    save_text_as("Text_3");
}

void MainWindow::on_actionSave_Text_4_As_triggered()
{
    textEdit_focused("Text_4");
    save_text_as("Text_4");
}

void MainWindow::on_actionSave_Text_5_As_triggered()
{
    textEdit_focused("Text_5");
    save_text_as("Text_5");
}

void MainWindow::on_actionSave_Text_6_As_triggered()
{
    textEdit_focused("Text_6");
    save_text_as("Text_6");
}

void MainWindow::on_actionSave_Text_7_As_triggered()
{
    textEdit_focused("Text_7");
    save_text_as("Text_7");
}

void MainWindow::on_actionSave_Text_8_As_triggered()
{
    textEdit_focused("Text_8");
    save_text_as("Text_8");
}



// /////////////////////////////////////////////////////////////////////
//Menu "Edit"
// /////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////
//Option "Undo"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionUndo_in_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->undo();
}

void MainWindow::on_actionUndo_in_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->undo();
}

void MainWindow::on_actionUndo_in_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->undo();
}

void MainWindow::on_actionUndo_in_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->undo();
}

void MainWindow::on_actionUndo_in_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->undo();
}

void MainWindow::on_actionUndo_in_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->undo();
}

void MainWindow::on_actionUndo_in_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->undo();
}

void MainWindow::on_actionUndo_in_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->undo();
}

// /////////////////////////////////////////////////////////////////////
//Option "Redo"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionRedo_in_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->redo();
}

void MainWindow::on_actionRedo_in_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->redo();
}

void MainWindow::on_actionRedo_in_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->redo();
}

void MainWindow::on_actionRedo_in_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->redo();
}

void MainWindow::on_actionRedo_in_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->redo();
}

void MainWindow::on_actionRedo_in_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->redo();
}

void MainWindow::on_actionRedo_in_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->redo();
}

void MainWindow::on_actionRedo_in_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->redo();
}

// /////////////////////////////////////////////////////////////////////
//Option "Cut"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionCut_from_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->cut();
}

void MainWindow::on_actionCut_from_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->cut();
}

void MainWindow::on_actionCut_from_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->cut();
}

void MainWindow::on_actionCut_from_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->cut();
}

void MainWindow::on_actionCut_from_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->cut();
}

void MainWindow::on_actionCut_from_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->cut();
}

void MainWindow::on_actionCut_from_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->cut();
}

void MainWindow::on_actionCut_from_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->cut();
}

// /////////////////////////////////////////////////////////////////////
//Option "Copy"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionCopy_from_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->copy();
}

void MainWindow::on_actionCopy_from_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->copy();
}

void MainWindow::on_actionCopy_from_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->copy();
}

void MainWindow::on_actionCopy_from_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->copy();
}

void MainWindow::on_actionCopy_from_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->copy();
}

void MainWindow::on_actionCopy_from_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->copy();
}

void MainWindow::on_actionCopy_from_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->copy();
}

void MainWindow::on_actionCopy_from_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->copy();
}

// /////////////////////////////////////////////////////////////////////
//Option "Paste"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionPaste_into_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->paste();
}

void MainWindow::on_actionPaste_into_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->paste();
}

void MainWindow::on_actionPaste_into_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->paste();
}

void MainWindow::on_actionPaste_into_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->paste();
}

void MainWindow::on_actionPaste_into_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->paste();
}

void MainWindow::on_actionPaste_into_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->paste();
}

void MainWindow::on_actionPaste_into_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->paste();
}

void MainWindow::on_actionPaste_into_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->paste();
}

// /////////////////////////////////////////////////////////////////////
//Option "Paste"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionSelect_All_in_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->selectAll();
}

void MainWindow::on_actionSelect_All_in_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->selectAll();
}

// /////////////////////////////////////////////////////////////////////////////////////////
//Funtion for searching in text
// /////////////////////////////////////////////////////////////////////////////////////////

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

    if (document_name == "Text_1") {
        Found = ui->textEdit_Text_1->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text_2") {
        Found = ui->textEdit_Text_2->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text_3") {
        Found = ui->textEdit_Text_3->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text_4") {
        Found = ui->textEdit_Text_4->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text_5") {
        Found = ui->textEdit_Text_5->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text_6") {
        Found = ui->textEdit_Text_6->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text_7") {
        Found = ui->textEdit_Text_7->find(dialogfindDocument.search, searchOptions);
    }
    else if (document_name == "Text_8") {
        Found = ui->textEdit_Text_8->find(dialogfindDocument.search, searchOptions);
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
                if (document_name == "Text_1") {
                    foundNew = ui->textEdit_Text_1->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text_2") {
                    foundNew = ui->textEdit_Text_2->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text_3") {
                    foundNew = ui->textEdit_Text_3->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text_4") {
                    foundNew = ui->textEdit_Text_4->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text_5") {
                    foundNew = ui->textEdit_Text_5->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text_6") {
                    foundNew = ui->textEdit_Text_6->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text_7") {
                    foundNew = ui->textEdit_Text_7->find(dialogfindDocument.search, searchOptions);
                }
                else if (document_name == "Text_8") {
                    foundNew = ui->textEdit_Text_8->find(dialogfindDocument.search, searchOptions);
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

// /////////////////////////////////////////////////////////////////////////////////////////
//Option "Find"
// /////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionFind_in_Text_1_triggered()
{
    textEdit_focused("Text_1");

    QString str = ui->textEdit_Text_1->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_1");
}

void MainWindow::on_actionFind_in_Text_2_triggered()
{
    textEdit_focused("Text_2");

    QString str = ui->textEdit_Text_2->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_2");
}

void MainWindow::on_actionFind_in_Text_3_triggered()
{
    textEdit_focused("Text_3");

    QString str = ui->textEdit_Text_3->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_3");
}

void MainWindow::on_actionFind_in_Text_4_triggered()
{
    textEdit_focused("Text_4");

    QString str = ui->textEdit_Text_4->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_4");
}

void MainWindow::on_actionFind_in_Text_5_triggered()
{
    textEdit_focused("Text_5");

    QString str = ui->textEdit_Text_5->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_5");
}

void MainWindow::on_actionFind_in_Text_6_triggered()
{
    textEdit_focused("Text_6");

    QString str = ui->textEdit_Text_6->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_6");
}

void MainWindow::on_actionFind_in_Text_7_triggered()
{
    textEdit_focused("Text_7");

    QString str = ui->textEdit_Text_7->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_7");
}

void MainWindow::on_actionFind_in_Text_8_triggered()
{
    textEdit_focused("Text_8");

    QString str = ui->textEdit_Text_8->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    search_word("Text_8");
}

// ////////////////////////////////////////////////////////////////////////////////////////
//Funtion for finding and replacing
// ////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::find_and_replace(QString document_name)
{
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

    if (document_name == "Text_1")
    {
        Found = ui->textEdit_Text_1->find(dialogreplace.search, searchOptions);
    }
    else if (document_name == "Text_2")
    {
        Found = ui->textEdit_Text_2->find(dialogreplace.search, searchOptions);
    }
    else if (document_name == "Text_3")
    {
        Found = ui->textEdit_Text_3->find(dialogreplace.search, searchOptions);
    }
    else if (document_name == "Text_4")
    {
        Found = ui->textEdit_Text_4->find(dialogreplace.search, searchOptions);
    }
    else if (document_name == "Text_5")
    {
        Found = ui->textEdit_Text_5->find(dialogreplace.search, searchOptions);
    }
    else if (document_name == "Text_6")
    {
        Found = ui->textEdit_Text_6->find(dialogreplace.search, searchOptions);
    }
    else if (document_name == "Text_7")
    {
        Found = ui->textEdit_Text_7->find(dialogreplace.search, searchOptions);
    }
    else if (document_name == "Text_8")
    {
        Found = ui->textEdit_Text_8->find(dialogreplace.search, searchOptions);
    }

    if ((!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) & !Found) {
        QMessageBox* notFound = new QMessageBox(QMessageBox::Warning, tr("Not found"),
                                                tr("The word was not found"));
        notFound->exec();
        delete notFound;
    }

    else if (!(dialogreplace.search.isEmpty() || dialogreplace.search.isNull())) {
        if (document_name == "Text_1")
        {
            ui->textEdit_Text_1->cut();
            ui->textEdit_Text_1->insertPlainText(dialogreplace.replace);
        }
        else if (document_name == "Text_2")
        {
            ui->textEdit_Text_2->cut();
            ui->textEdit_Text_2->insertPlainText(dialogreplace.replace);
        }
        else if (document_name == "Text_3")
        {
            ui->textEdit_Text_3->cut();
            ui->textEdit_Text_3->insertPlainText(dialogreplace.replace);
        }
        else if (document_name == "Text_4")
        {
            ui->textEdit_Text_4->cut();
            ui->textEdit_Text_4->insertPlainText(dialogreplace.replace);
        }
        else if (document_name == "Text_5")
        {
            ui->textEdit_Text_5->cut();
            ui->textEdit_Text_5->insertPlainText(dialogreplace.replace);
        }
        else if (document_name == "Text_6")
        {
            ui->textEdit_Text_6->cut();
            ui->textEdit_Text_6->insertPlainText(dialogreplace.replace);
        }
        else if (document_name == "Text_7")
        {
            ui->textEdit_Text_7->cut();
            ui->textEdit_Text_7->insertPlainText(dialogreplace.replace);
        }
        else if (document_name == "Text_8")
        {
            ui->textEdit_Text_8->cut();
            ui->textEdit_Text_8->insertPlainText(dialogreplace.replace);
        }

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
                if (document_name == "Text_1")
                {
                    foundNew = ui->textEdit_Text_1->find(dialogreplace.search, searchOptions);
                }
                else if (document_name == "Text_2")
                {
                    foundNew = ui->textEdit_Text_2->find(dialogreplace.search, searchOptions);
                }
                else if (document_name == "Text_3")
                {
                    foundNew = ui->textEdit_Text_3->find(dialogreplace.search, searchOptions);
                }
                else if (document_name == "Text_4")
                {
                    foundNew = ui->textEdit_Text_4->find(dialogreplace.search, searchOptions);
                }
                else if (document_name == "Text_5")
                {
                    foundNew = ui->textEdit_Text_5->find(dialogreplace.search, searchOptions);
                }
                else if (document_name == "Text_6")
                {
                    foundNew = ui->textEdit_Text_6->find(dialogreplace.search, searchOptions);
                }
                else if (document_name == "Text_7")
                {
                    foundNew = ui->textEdit_Text_7->find(dialogreplace.search, searchOptions);
                }
                else if (document_name == "Text_8")
                {
                    foundNew = ui->textEdit_Text_8->find(dialogreplace.search, searchOptions);
                }

                if (foundNew) {
                    if (document_name == "Text_1")
                    {
                        ui->textEdit_Text_1->cut();
                        ui->textEdit_Text_1->insertPlainText(dialogreplace.replace);
                    }
                    else if (document_name == "Text_2")
                    {
                        ui->textEdit_Text_2->cut();
                        ui->textEdit_Text_2->insertPlainText(dialogreplace.replace);
                    }
                    else if (document_name == "Text_3")
                    {
                        ui->textEdit_Text_3->cut();
                        ui->textEdit_Text_3->insertPlainText(dialogreplace.replace);
                    }
                    else if (document_name == "Text_4")
                    {
                        ui->textEdit_Text_4->cut();
                        ui->textEdit_Text_4->insertPlainText(dialogreplace.replace);
                    }
                    else if (document_name == "Text_5")
                    {
                        ui->textEdit_Text_5->cut();
                        ui->textEdit_Text_5->insertPlainText(dialogreplace.replace);
                    }
                    else if (document_name == "Text_6")
                    {
                        ui->textEdit_Text_6->cut();
                        ui->textEdit_Text_6->insertPlainText(dialogreplace.replace);
                    }
                    else if (document_name == "Text_7")
                    {
                        ui->textEdit_Text_7->cut();
                        ui->textEdit_Text_7->insertPlainText(dialogreplace.replace);
                    }
                    else if (document_name == "Text_8")
                    {
                        ui->textEdit_Text_8->cut();
                        ui->textEdit_Text_8->insertPlainText(dialogreplace.replace);
                    }

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

// ///////////////////////////////////////////////////////////////////
//Option "Find and Replace"
// ///////////////////////////////////////////////////////////////////

void MainWindow::on_actionFind_and_Replace_in_Text_1_triggered()
{
    textEdit_focused("Text_1");

    QString str = ui->textEdit_Text_1->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_1");
}

void MainWindow::on_actionFind_and_Replace_in_Text_2_triggered()
{
    textEdit_focused("Text_2");

    QString str = ui->textEdit_Text_2->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_2");
}

void MainWindow::on_actionFind_and_Replace_in_Text_3_triggered()
{
    textEdit_focused("Text_3");

    QString str = ui->textEdit_Text_3->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_3");
}

void MainWindow::on_actionFind_and_Replace_in_Text_4_triggered()
{
    textEdit_focused("Text_4");

    QString str = ui->textEdit_Text_4->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_4");
}

void MainWindow::on_actionFind_and_Replace_in_Text_5_triggered()
{
    textEdit_focused("Text_5");

    QString str = ui->textEdit_Text_5->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_5");
}

void MainWindow::on_actionFind_and_Replace_in_Text_6_triggered()
{
    textEdit_focused("Text_6");

    QString str = ui->textEdit_Text_6->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_6");
}

void MainWindow::on_actionFind_and_Replace_in_Text_7_triggered()
{
    textEdit_focused("Text_7");

    QString str = ui->textEdit_Text_7->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_7");
}

void MainWindow::on_actionFind_and_Replace_in_Text_8_triggered()
{
    textEdit_focused("Text_8");

    QString str = ui->textEdit_Text_8->toPlainText();
    if (str.isEmpty() || str.isNull()) {
        QMessageBox* warning = new QMessageBox(QMessageBox::Warning, tr("Warning"), tr("File is not open"));
        warning->exec();
        delete warning;
        return;
    }
    find_and_replace("Text_8");
}

// ////////////////////////////////////////////////////////////////////////////////
//Option "Find and Replace All
// ////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionFind_and_Replace_All_in_Text_1_triggered()
{
    textEdit_focused("Text_1");

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
    textEdit_focused("Text_2");

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
    textEdit_focused("Text_3");

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

void MainWindow::on_actionFind_and_Replace_All_in_Text_4_triggered()
{
    textEdit_focused("Text_4");

    QString str = ui->textEdit_Text_4->toPlainText();
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
        QString text = ui->textEdit_Text_4->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_4->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

void MainWindow::on_actionFind_and_Replace_All_in_Text_5_triggered()
{
    textEdit_focused("Text_5");

    QString str = ui->textEdit_Text_5->toPlainText();
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
        QString text = ui->textEdit_Text_5->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_5->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

void MainWindow::on_actionFind_and_Replace_All_in_Text_6_triggered()
{
    textEdit_focused("Text_6");

    QString str = ui->textEdit_Text_6->toPlainText();
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
        QString text = ui->textEdit_Text_6->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_6->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

void MainWindow::on_actionFind_and_Replace_All_in_Text_7_triggered()
{
    textEdit_focused("Text_7");

    QString str = ui->textEdit_Text_7->toPlainText();
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
        QString text = ui->textEdit_Text_7->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_7->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

void MainWindow::on_actionFind_and_Replace_All_in_Text_8_triggered()
{
    textEdit_focused("Text_8");

    QString str = ui->textEdit_Text_8->toPlainText();
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
        QString text = ui->textEdit_Text_8->toPlainText();
        text.replace(dialogreplaceall.search, dialogreplaceall.replace);
        ui->textEdit_Text_8->setText(text);
        QMessageBox::information(this, tr("Found and replaced"), tr("Find and replace all are done"));
    }
}

// ////////////////////////////////////////////////////////////////////////////////////////////////
//Menu "View"
// ////////////////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////////////////////////////////
//Option "Zoom In"
// /////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionZoom_In_all_windows_triggered()
{
    ui->textEdit_Text_1->zoomIn();
    ui->textEdit_Text_2->zoomIn();
    ui->textEdit_Text_3->zoomIn();
    ui->textEdit_Text_4->zoomIn();
    ui->textEdit_Text_5->zoomIn();
    ui->textEdit_Text_6->zoomIn();
    ui->textEdit_Text_7->zoomIn();
    ui->textEdit_Text_8->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->zoomIn();
}

void MainWindow::on_actionZoom_In_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->zoomIn();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////
//Option "Zoom Out"
// /////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionZoom_Out_all_windows_triggered()
{
    ui->textEdit_Text_1->zoomOut();
    ui->textEdit_Text_2->zoomOut();
    ui->textEdit_Text_3->zoomOut();
    ui->textEdit_Text_4->zoomOut();
    ui->textEdit_Text_5->zoomOut();
    ui->textEdit_Text_6->zoomOut();
    ui->textEdit_Text_7->zoomOut();
    ui->textEdit_Text_8->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_1_triggered()
{
    textEdit_focused("Text_1");
    ui->textEdit_Text_1->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_2_triggered()
{
    textEdit_focused("Text_2");
    ui->textEdit_Text_2->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_3_triggered()
{
    textEdit_focused("Text_3");
    ui->textEdit_Text_3->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_4_triggered()
{
    textEdit_focused("Text_4");
    ui->textEdit_Text_4->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_5_triggered()
{
    textEdit_focused("Text_5");
    ui->textEdit_Text_5->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_6_triggered()
{
    textEdit_focused("Text_6");
    ui->textEdit_Text_6->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_7_triggered()
{
    textEdit_focused("Text_7");
    ui->textEdit_Text_7->zoomOut();
}

void MainWindow::on_actionZoom_Out_Text_8_triggered()
{
    textEdit_focused("Text_8");
    ui->textEdit_Text_8->zoomOut();
}

// //////////////////////////////////////////////////////////////////////
//Function for formatting text
// //////////////////////////////////////////////////////////////////////

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
    else if (document_name == "Text_4") {
        file = file_4;
    }
    else if (document_name == "Text_5") {
        file = file_5;
    }
    else if (document_name == "Text_6") {
        file = file_6;
    }
    else if (document_name == "Text_7") {
        file = file_7;
    }
    else if (document_name == "Text_8") {
        file = file_8;
    }
    else return;

    if (file.isEmpty() || file.isNull()) {
        file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                             tr("USFM Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;XML Files (*.xml);;Text Files (*.txt)"));
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

            QString text_converted;

            if (file.endsWith(".htm") || file.endsWith(".html"))
            {
                text_converted = text;
            }
            else
            {
                text_converted = converter_to_html(text);
            }

            QFileInfo fi(file);
            if (document_name == "Text_1") {
                ui->textEdit_Text_1->setHtml(text_converted);
                file_1 = file;
                ui->label_dir_1->setText(file_1);
                fileName_1 = fi.fileName();
                ui->label_file_1->setText(fileName_1);
            }
            else if (document_name == "Text_2") {
                ui->textEdit_Text_2->setHtml(text_converted);
                file_2 = file;
                ui->label_dir_2->setText(file_2);
                fileName_2 = fi.fileName();
                ui->label_file_2->setText(fileName_2);
            }
            else if (document_name == "Text_3") {
                ui->textEdit_Text_3->setHtml(text_converted);
                file_3 = file;
                ui->label_dir_3->setText(file_3);
                fileName_3 = fi.fileName();
                ui->label_file_3->setText(fileName_3);
            }
            else if (document_name == "Text_4") {
                ui->textEdit_Text_4->setHtml(text_converted);
                file_4 = file;
                ui->label_dir_4->setText(file_4);
                fileName_4 = fi.fileName();
                ui->label_file_4->setText(fileName_4);
            }
            else if (document_name == "Text_5") {
                ui->textEdit_Text_5->setHtml(text_converted);
                file_5 = file;
                ui->label_dir_5->setText(file_5);
                fileName_5 = fi.fileName();
                ui->label_file_5->setText(fileName_5);
            }
            else if (document_name == "Text_6") {
                ui->textEdit_Text_6->setHtml(text_converted);
                file_6 = file;
                ui->label_dir_6->setText(file_6);
                fileName_6 = fi.fileName();
                ui->label_file_6->setText(fileName_6);
            }
            else if (document_name == "Text_7") {
                ui->textEdit_Text_7->setHtml(text_converted);
                file_7 = file;
                ui->label_dir_7->setText(file_7);
                fileName_7 = fi.fileName();
                ui->label_file_7->setText(fileName_7);
            }
            else if (document_name == "Text_8") {
                ui->textEdit_Text_8->setHtml(text_converted);
                file_8 = file;
                ui->label_dir_8->setText(file_8);
                fileName_8 = fi.fileName();
                ui->label_file_8->setText(fileName_8);
            }
        }
    }
}

// /////////////////////////////////////////////////////////////
//Option "Formatted USFM"
// /////////////////////////////////////////////////////////////

void MainWindow::on_actionFormatted_Text_1_triggered()
{
    textEdit_focused("Text_1");

    formatted("Text_1");
    formatted_1 = true;
    ui->textEdit_Text_1->setReadOnly(true);
}


void MainWindow::on_actionFormatted_Text_2_triggered()
{
    textEdit_focused("Text_2");

    formatted("Text_2");
    formatted_2 = true;
    ui->textEdit_Text_2->setReadOnly(true);
}


void MainWindow::on_actionFormatted_Text_3_triggered()
{
    textEdit_focused("Text_3");

    formatted("Text_3");
    formatted_3 = true;
    ui->textEdit_Text_3->setReadOnly(true);
}

void MainWindow::on_actionFormatted_Text_4_triggered()
{
    textEdit_focused("Text_4");

    formatted("Text_4");
    formatted_4 = true;
    ui->textEdit_Text_4->setReadOnly(true);
}

void MainWindow::on_actionFormatted_Text_5_triggered()
{
    textEdit_focused("Text_5");

    formatted("Text_5");
    formatted_5 = true;
    ui->textEdit_Text_5->setReadOnly(true);
}

void MainWindow::on_actionFormatted_Text_6_triggered()
{
    textEdit_focused("Text_6");

    formatted("Text_6");
    formatted_6 = true;
    ui->textEdit_Text_6->setReadOnly(true);
}

void MainWindow::on_actionFormatted_Text_7_triggered()
{
    textEdit_focused("Text_7");

    formatted("Text_7");
    formatted_7 = true;
    ui->textEdit_Text_7->setReadOnly(true);
}

void MainWindow::on_actionFormatted_Text_8_triggered()
{
    textEdit_focused("Text_8");

    formatted("Text_8");
    formatted_8 = true;
    ui->textEdit_Text_8->setReadOnly(true);
}

// ///////////////////////////////////////////////////////////////////////////
//function for unformatting text
// ///////////////////////////////////////////////////////////////////////////

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
    else if (document_name == "Text_4") {
        file = file_4;
    }
    else if (document_name == "Text_5") {
        file = file_5;
    }
    else if (document_name == "Text_6") {
        file = file_6;
    }
    else if (document_name == "Text_7") {
        file = file_7;
    }
    else if (document_name == "Text_8") {
        file = file_8;
    }
    else return;

    if (file.isEmpty() || file.isNull()) {
        file = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                             tr("USFM Files (*.SFM *.sfm);;HTML Files (*.html *.htm);;XML Files (*.xml);;Text Files (*.txt)"));
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

            QFileInfo fi(file);

            if (document_name == "Text_1") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_1->setAcceptRichText(false);
                    ui->textEdit_Text_1->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_1->setText(text);
                }
                file_1 = file;
                ui->label_dir_1->setText(file_1);
                fileName_1 = fi.fileName();
                ui->label_file_1->setText(fileName_1);
            }
            else if (document_name == "Text_2") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_2->setAcceptRichText(false);
                    ui->textEdit_Text_2->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_2->setText(text);
                }
                file_2 = file;
                ui->label_dir_2->setText(file_2);
                fileName_2 = fi.fileName();
                ui->label_file_2->setText(fileName_2);
            }
            else if (document_name == "Text_3") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_3->setAcceptRichText(false);
                    ui->textEdit_Text_3->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_3->setText(text);
                }
                file_3 = file;
                ui->label_dir_3->setText(file_3);
                fileName_3 = fi.fileName();
                ui->label_file_3->setText(fileName_3);
            }
            else if (document_name == "Text_4") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_4->setAcceptRichText(false);
                    ui->textEdit_Text_4->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_4->setText(text);
                }
                file_4 = file;
                ui->label_dir_4->setText(file_4);
                fileName_4 = fi.fileName();
                ui->label_file_4->setText(fileName_4);
            }
            else if (document_name == "Text_5") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_5->setAcceptRichText(false);
                    ui->textEdit_Text_5->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_5->setText(text);
                }
                file_5 = file;
                ui->label_dir_5->setText(file_5);
                fileName_5 = fi.fileName();
                ui->label_file_5->setText(fileName_5);
            }
            else if (document_name == "Text_6") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_6->setAcceptRichText(false);
                    ui->textEdit_Text_6->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_6->setText(text);
                }
                file_6 = file;
                ui->label_dir_6->setText(file_6);
                fileName_6 = fi.fileName();
                ui->label_file_6->setText(fileName_6);
            }
            else if (document_name == "Text_7") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_7->setAcceptRichText(false);
                    ui->textEdit_Text_7->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_7->setText(text);
                }
                file_7 = file;
                ui->label_dir_7->setText(file_7);
                fileName_7 = fi.fileName();
                ui->label_file_7->setText(fileName_7);
            }
            else if (document_name == "Text_8") {
                if (file.endsWith(".htm") || file.endsWith(".html")) {
                    ui->textEdit_Text_8->setAcceptRichText(false);
                    ui->textEdit_Text_8->setPlainText(text);
                }
                else
                {
                    ui->textEdit_Text_8->setText(text);
                }
                file_8 = file;
                ui->label_dir_8->setText(file_8);
                fileName_8 = fi.fileName();
                ui->label_file_8->setText(fileName_8);
            }
        }
    }
}

// ///////////////////////////////////////////////////////////////////////
//Option "Unformatted USFM"
// ///////////////////////////////////////////////////////////////////////

void MainWindow::on_actionUnformatted_Text_1_triggered()
{
    textEdit_focused("Text_1");

    unformatted("Text_1");
    formatted_1 = false;
    ui->textEdit_Text_1->setReadOnly(false);
}

void MainWindow::on_actionUnformatted_Text_2_triggered()
{
    textEdit_focused("Text_2");

    unformatted("Text_2");
    formatted_2 = false;
    ui->textEdit_Text_2->setReadOnly(false);
}

void MainWindow::on_actionUnformatted_Text_3_triggered()
{
    textEdit_focused("Text_3");

    unformatted("Text_3");
    formatted_3 = false;
    ui->textEdit_Text_3->setReadOnly(false);
}

void MainWindow::on_actionUnformatted_Text_4_triggered()
{
    textEdit_focused("Text_4");

    unformatted("Text_4");
    formatted_4 = false;
    ui->textEdit_Text_4->setReadOnly(false);
}

void MainWindow::on_actionUnformatted_Text_5_triggered()
{
    textEdit_focused("Text_5");

    unformatted("Text_5");
    formatted_5 = false;
    ui->textEdit_Text_5->setReadOnly(false);
}

void MainWindow::on_actionUnformatted_Text_6_triggered()
{
    textEdit_focused("Text_6");

    unformatted("Text_6");
    formatted_6 = false;
    ui->textEdit_Text_6->setReadOnly(false);
}

void MainWindow::on_actionUnformatted_Text_7_triggered()
{
    textEdit_focused("Text_7");

    unformatted("Text_7");
    formatted_7 = false;
    ui->textEdit_Text_7->setReadOnly(false);
}

void MainWindow::on_actionUnformatted_Text_8_triggered()
{
    textEdit_focused("Text_8");

    unformatted("Text_8");
    formatted_8 = false;
    ui->textEdit_Text_8->setReadOnly(false);
}

// /////////////////////////////////////////////////////////////////////
//Menu "Tools"
// /////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////
//Option "Font"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionFont_of_Text_1_triggered()
{
    textEdit_focused("Text_1");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_1->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_2_triggered()
{
    textEdit_focused("Text_2");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_2->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_3_triggered()
{
    textEdit_focused("Text_3");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_3->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_4_triggered()
{
    textEdit_focused("Text_4");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_4->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_5_triggered()
{
    textEdit_focused("Text_5");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_5->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_6_triggered()
{
    textEdit_focused("Text_6");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_6->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_7_triggered()
{
    textEdit_focused("Text_7");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_7->setFont(font);
    } else return;
}

void MainWindow::on_actionFont_of_Text_8_triggered()
{
    textEdit_focused("Text_8");

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->textEdit_Text_8->setFont(font);
    } else return;
}

// ////////////////////////////////////////////////////////////
//Option "Color"
// ////////////////////////////////////////////////////////////

void MainWindow::on_actionColor_of_Text_1_triggered()
{
    textEdit_focused("Text_1");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_1->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_2_triggered()
{
    textEdit_focused("Text_2");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_2->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_3_triggered()
{
    textEdit_focused("Text_3");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_3->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_4_triggered()
{
   textEdit_focused("Text_4");

   QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
   if(color.isValid()) {
       ui->textEdit_Text_4->setTextColor(color);
   }
}

void MainWindow::on_actionColor_of_Text_5_triggered()
{
    textEdit_focused("Text_5");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_5->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_6_triggered()
{
    textEdit_focused("Text_6");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_6->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_7_triggered()
{
    textEdit_focused("Text_7");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_7->setTextColor(color);
    }
}

void MainWindow::on_actionColor_of_Text_8_triggered()
{
    textEdit_focused("Text_8");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_8->setTextColor(color);
    }
}

// ////////////////////////////////////////////////////////////////////////////
//Option "Highlight"
// ////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionHighlight_in_Text_1_triggered()
{
    textEdit_focused("Text_1");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_1->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_2_triggered()
{
    textEdit_focused("Text_2");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_2->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_3_triggered()
{
    textEdit_focused("Text_3");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_3->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_4_triggered()
{
    textEdit_focused("Text_4");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_4->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_5_triggered()
{
    textEdit_focused("Text_5");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_5->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_6_triggered()
{
    textEdit_focused("Text_6");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_6->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_7_triggered()
{
    textEdit_focused("Text_7");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_7->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionHighlight_in_Text_8_triggered()
{
    textEdit_focused("Text_8");

    QColor color = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));
    if(color.isValid()) {
        ui->textEdit_Text_8->setTextBackgroundColor(color);
    }
}

// ///////////////////////////////////////////////////////////////////////////////
//Option "Interface language"
// ///////////////////////////////////////////////////////////////////////////////

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

// ///////////////////////////////////////////////////////////////////////////////////////////////
//Option "Show file paths and names"
// ///////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionShow_file_paths_in_all_windows_triggered()
{
    ui->label_file_1->hide();
    ui->label_file_2->hide();
    ui->label_file_3->hide();
    ui->label_file_4->hide();
    ui->label_file_5->hide();
    ui->label_file_6->hide();
    ui->label_file_7->hide();
    ui->label_file_8->hide();

    if (text_1_visible == true)
    {
        ui->label_dir_1->show();
    }
    if (text_2_visible == true)
    {
        ui->label_dir_2->show();
    }
    if (text_3_visible == true)
    {
        ui->label_dir_3->show();
    }
    if (text_4_visible == true)
    {
        ui->label_dir_4->show();
    }
    if (text_5_visible == true)
    {
        ui->label_dir_5->show();
    }
    if (text_6_visible == true)
    {
        ui->label_dir_6->show();
    }
    if (text_7_visible == true)
    {
        ui->label_dir_7->show();
    }
    if (text_8_visible == true)
    {
        ui->label_dir_8->show();
    }
}

void MainWindow::show_file_path(QString document_name)
{
    ui->label_file_1->hide();
    ui->label_file_2->hide();
    ui->label_file_3->hide();
    ui->label_file_4->hide();
    ui->label_file_5->hide();
    ui->label_file_6->hide();
    ui->label_file_7->hide();
    ui->label_file_8->hide();

    if ((document_name == "Text_1") && (text_1_visible == true))
    {
        ui->label_dir_1->show();
    }
    else if ((document_name == "Text_2") && (text_2_visible == true))
    {
        ui->label_dir_2->show();
    }
    else if ((document_name == "Text_3") && (text_3_visible == true))
    {
        ui->label_dir_3->show();
    }
    else if ((document_name == "Text_4") && (text_4_visible == true))
    {
        ui->label_dir_4->show();
    }
    else if ((document_name == "Text_5") && (text_5_visible == true))
    {
        ui->label_dir_5->show();
    }
    else if ((document_name == "Text_6") && (text_6_visible == true))
    {
        ui->label_dir_6->show();
    }
    else if ((document_name == "Text_7") && (text_7_visible == true))
    {
        ui->label_dir_7->show();
    }
    else if ((document_name == "Text_8") && (text_8_visible == true))
    {
        ui->label_dir_8->show();
    }

    if ((document_name != "Text_1") || (text_1_visible == false))
    {
        ui->label_dir_1->hide();
    }
    if ((document_name != "Text_2") || (text_2_visible == false))
    {
        ui->label_dir_2->hide();
    }
    if ((document_name != "Text_3") || (text_3_visible == false))
    {
        ui->label_dir_3->hide();
    }
    if ((document_name != "Text_4") || (text_4_visible == false))
    {
        ui->label_dir_4->hide();
    }
    if ((document_name != "Text_5") || (text_5_visible == false))
    {
        ui->label_dir_5->hide();
    }
    if ((document_name != "Text_6") || (text_6_visible == false))
    {
        ui->label_dir_6->hide();
    }
    if ((document_name != "Text_7") || (text_7_visible == false))
    {
        ui->label_dir_7->hide();
    }
    if ((document_name != "Text_8") || (text_8_visible == false))
    {
        ui->label_dir_8->hide();
    }
}

void MainWindow::on_actionShow_file_path_of_Text_1_triggered()
{
    textEdit_focused("Text_1");
    show_file_path("Text_1");
}

void MainWindow::on_actionShow_file_path_of_Text_2_triggered()
{
    textEdit_focused("Text_2");
    show_file_path("Text_2");
}

void MainWindow::on_actionShow_file_path_of_Text_3_triggered()
{
    textEdit_focused("Text_3");
    show_file_path("Text_3");
}

void MainWindow::on_actionShow_file_path_of_Text_4_triggered()
{
    textEdit_focused("Text_4");
    show_file_path("Text_4");
}

void MainWindow::on_actionShow_file_path_of_Text_5_triggered()
{
    textEdit_focused("Text_5");
    show_file_path("Text_5");
}

void MainWindow::on_actionShow_file_path_of_Text_6_triggered()
{
    textEdit_focused("Text_6");
    show_file_path("Text_6");
}

void MainWindow::on_actionShow_file_path_of_Text_7_triggered()
{
    textEdit_focused("Text_7");
    show_file_path("Text_7");
}

void MainWindow::on_actionShow_file_path_of_Text_8_triggered()
{
    textEdit_focused("Text_8");
    show_file_path("Text_8");
}


// /////////////////////////////////////////////////////////////////////
//Option "Show only file names"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionShow_file_names_in_all_windows_triggered()
{
    ui->label_dir_1->hide();
    ui->label_dir_2->hide();
    ui->label_dir_3->hide();
    ui->label_dir_4->hide();
    ui->label_dir_5->hide();
    ui->label_dir_6->hide();
    ui->label_dir_7->hide();
    ui->label_dir_8->hide();

    if (text_1_visible == true)
    {
        ui->label_file_1->show();
    }
    if (text_2_visible == true)
    {
        ui->label_file_2->show();
    }
    if (text_3_visible == true)
    {
        ui->label_file_3->show();
    }
    if (text_4_visible == true)
    {
        ui->label_file_4->show();
    }
    if (text_5_visible == true)
    {
        ui->label_file_5->show();
    }
    if (text_6_visible == true)
    {
        ui->label_file_6->show();
    }
    if (text_7_visible == true)
    {
        ui->label_file_7->show();
    }
    if (text_8_visible == true)
    {
        ui->label_file_8->show();
    }
}

void MainWindow::show_file_name(QString document_name)
{
    ui->label_dir_1->hide();
    ui->label_dir_2->hide();
    ui->label_dir_3->hide();
    ui->label_dir_4->hide();
    ui->label_dir_5->hide();
    ui->label_dir_6->hide();
    ui->label_dir_7->hide();
    ui->label_dir_8->hide();

    if ((document_name == "Text_1") && (text_1_visible == true))
    {
        ui->label_file_1->show();
    }
    else if ((document_name == "Text_2") && (text_2_visible == true))
    {
        ui->label_file_2->show();
    }
    else if ((document_name == "Text_3") && (text_3_visible == true))
    {
        ui->label_file_3->show();
    }
    else if ((document_name == "Text_4") && (text_4_visible == true))
    {
        ui->label_file_4->show();
    }
    else if ((document_name == "Text_5") && (text_5_visible == true))
    {
        ui->label_file_5->show();
    }
    else if ((document_name == "Text_6") && (text_6_visible == true))
    {
        ui->label_file_6->show();
    }
    else if ((document_name == "Text_7") && (text_7_visible == true))
    {
        ui->label_file_7->show();
    }
    else if ((document_name == "Text_8") && (text_8_visible == true))
    {
        ui->label_file_8->show();
    }

    if ((document_name != "Text_1") || (text_1_visible == false))
    {
        ui->label_file_1->hide();
    }
    if ((document_name != "Text_2") || (text_2_visible == false))
    {
        ui->label_file_2->hide();
    }
    if ((document_name != "Text_3") || (text_3_visible == false))
    {
        ui->label_file_3->hide();
    }
    if ((document_name != "Text_4") || (text_4_visible == false))
    {
        ui->label_file_4->hide();
    }
    if ((document_name != "Text_5") || (text_5_visible == false))
    {
        ui->label_file_5->hide();
    }
    if ((document_name != "Text_6") || (text_6_visible == false))
    {
        ui->label_file_6->hide();
    }
    if ((document_name != "Text_7") || (text_7_visible == false))
    {
        ui->label_file_7->hide();
    }
    if ((document_name != "Text_8") || (text_8_visible == false))
    {
        ui->label_file_8->hide();
    }
}

void MainWindow::on_actionShow_file_name_of_Text_1_triggered()
{
    textEdit_focused("Text_1");
    show_file_name("Text_1");
}

void MainWindow::on_actionShow_file_name_of_Text_2_triggered()
{
    textEdit_focused("Text_2");
    show_file_name("Text_2");
}

void MainWindow::on_actionShow_file_name_of_Text_3_triggered()
{
    textEdit_focused("Text_3");
    show_file_name("Text_3");
}

void MainWindow::on_actionShow_file_name_of_Text_4_triggered()
{
    textEdit_focused("Text_4");
    show_file_name("Text_4");
}

void MainWindow::on_actionShow_file_name_of_Text_5_triggered()
{
    textEdit_focused("Text_5");
    show_file_name("Text_5");
}

void MainWindow::on_actionShow_file_name_of_Text_6_triggered()
{
    textEdit_focused("Text_6");
    show_file_name("Text_6");
}

void MainWindow::on_actionShow_file_name_of_Text_7_triggered()
{
    textEdit_focused("Text_7");
    show_file_name("Text_7");
}

void MainWindow::on_actionShow_file_name_of_Text_8_triggered()
{
    textEdit_focused("Text_8");
    show_file_name("Text_8");
}

// //////////////////////////////////////////////////////////////////////
//Option "Hide file names and paths"
// /////////////////////////////////////////////////////////////////////

void MainWindow::on_actionHide_file_paths_and_names_triggered()
{
    ui->label_dir_1->hide();
    ui->label_dir_2->hide();
    ui->label_dir_3->hide();
    ui->label_dir_4->hide();
    ui->label_dir_5->hide();
    ui->label_dir_6->hide();
    ui->label_dir_7->hide();
    ui->label_dir_8->hide();

    ui->label_file_1->hide();
    ui->label_file_2->hide();
    ui->label_file_3->hide();
    ui->label_file_4->hide();
    ui->label_file_5->hide();
    ui->label_file_6->hide();
    ui->label_file_7->hide();
    ui->label_file_8->hide();
}

void MainWindow::on_actionReset_screen_size_triggered()
{
    resize(800, 600);
}


// ////////////////////////////////////////////////////////////////////////////////////////
//Menu "Windows"
// ////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionShow_Text_1_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->hide();
    ui->textEdit_Text_3->hide();
    ui->textEdit_Text_4->hide();
    ui->textEdit_Text_5->hide();
    ui->textEdit_Text_6->hide();
    ui->textEdit_Text_7->hide();
    ui->textEdit_Text_8->hide();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->hide();
    ui->label_Text_3->hide();
    ui->label_Text_4->hide();
    ui->label_Text_5->hide();
    ui->label_Text_6->hide();
    ui->label_Text_7->hide();
    ui->label_Text_8->hide();

    text_1_visible = true;
    text_2_visible = false;
    text_3_visible = false;
    text_4_visible = false;
    text_5_visible = false;
    text_6_visible = false;
    text_7_visible = false;
    text_8_visible = false;
}

void MainWindow::on_actionShow_Texts_1_2_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->show();
    ui->textEdit_Text_3->hide();
    ui->textEdit_Text_4->hide();
    ui->textEdit_Text_5->hide();
    ui->textEdit_Text_6->hide();
    ui->textEdit_Text_7->hide();
    ui->textEdit_Text_8->hide();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->show();
    ui->label_Text_3->hide();
    ui->label_Text_4->hide();
    ui->label_Text_5->hide();
    ui->label_Text_6->hide();
    ui->label_Text_7->hide();
    ui->label_Text_8->hide();

    text_1_visible = true;
    text_2_visible = true;
    text_3_visible = false;
    text_4_visible = false;
    text_5_visible = false;
    text_6_visible = false;
    text_7_visible = false;
    text_8_visible = false;
}

void MainWindow::on_actionShow_Texts_1_3_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->show();
    ui->textEdit_Text_3->show();
    ui->textEdit_Text_4->hide();
    ui->textEdit_Text_5->hide();
    ui->textEdit_Text_6->hide();
    ui->textEdit_Text_7->hide();
    ui->textEdit_Text_8->hide();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->show();
    ui->label_Text_3->show();
    ui->label_Text_4->hide();
    ui->label_Text_5->hide();
    ui->label_Text_6->hide();
    ui->label_Text_7->hide();
    ui->label_Text_8->hide();

    text_1_visible = true;
    text_2_visible = true;
    text_3_visible = true;
    text_4_visible = false;
    text_5_visible = false;
    text_6_visible = false;
    text_7_visible = false;
    text_8_visible = false;
}

void MainWindow::on_actionShow_Texts_1_4_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->show();
    ui->textEdit_Text_3->show();
    ui->textEdit_Text_4->show();
    ui->textEdit_Text_5->hide();
    ui->textEdit_Text_6->hide();
    ui->textEdit_Text_7->hide();
    ui->textEdit_Text_8->hide();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->show();
    ui->label_Text_3->show();
    ui->label_Text_4->show();
    ui->label_Text_5->hide();
    ui->label_Text_6->hide();
    ui->label_Text_7->hide();
    ui->label_Text_8->hide();

    text_1_visible = true;
    text_2_visible = true;
    text_3_visible = true;
    text_4_visible = true;
    text_5_visible = false;
    text_6_visible = false;
    text_7_visible = false;
    text_8_visible = false;
}

void MainWindow::on_actionShow_Texts_1_5_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->hide();
    ui->textEdit_Text_3->hide();
    ui->textEdit_Text_4->hide();
    ui->textEdit_Text_5->show();
    ui->textEdit_Text_6->hide();
    ui->textEdit_Text_7->hide();
    ui->textEdit_Text_8->hide();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->hide();
    ui->label_Text_3->hide();
    ui->label_Text_4->hide();
    ui->label_Text_5->show();
    ui->label_Text_6->hide();
    ui->label_Text_7->hide();
    ui->label_Text_8->hide();

    text_1_visible = true;
    text_2_visible = false;
    text_3_visible = false;
    text_4_visible = false;
    text_5_visible = true;
    text_6_visible = false;
    text_7_visible = false;
    text_8_visible = false;
}

void MainWindow::on_actionShow_Texts_1_2_5_6_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->show();
    ui->textEdit_Text_3->hide();
    ui->textEdit_Text_4->hide();
    ui->textEdit_Text_5->show();
    ui->textEdit_Text_6->show();
    ui->textEdit_Text_7->hide();
    ui->textEdit_Text_8->hide();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->show();
    ui->label_Text_3->hide();
    ui->label_Text_4->hide();
    ui->label_Text_5->show();
    ui->label_Text_6->show();
    ui->label_Text_7->hide();
    ui->label_Text_8->hide();

    text_1_visible = true;
    text_2_visible = true;
    text_3_visible = false;
    text_4_visible = false;
    text_5_visible = true;
    text_6_visible = true;
    text_7_visible = false;
    text_8_visible = false;
}

void MainWindow::on_actionShow_Texts_1_3_5_7_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->show();
    ui->textEdit_Text_3->show();
    ui->textEdit_Text_4->hide();
    ui->textEdit_Text_5->show();
    ui->textEdit_Text_6->show();
    ui->textEdit_Text_7->show();
    ui->textEdit_Text_8->hide();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->show();
    ui->label_Text_3->show();
    ui->label_Text_4->hide();
    ui->label_Text_5->show();
    ui->label_Text_6->show();
    ui->label_Text_7->show();
    ui->label_Text_8->hide();

    text_1_visible = true;
    text_2_visible = true;
    text_3_visible = true;
    text_4_visible = false;
    text_5_visible = true;
    text_6_visible = true;
    text_7_visible = true;
    text_8_visible = false;
}

void MainWindow::on_actionShow_Texts_1_8_triggered()
{
    ui->textEdit_Text_1->show();
    ui->textEdit_Text_2->show();
    ui->textEdit_Text_3->show();
    ui->textEdit_Text_4->show();
    ui->textEdit_Text_5->show();
    ui->textEdit_Text_6->show();
    ui->textEdit_Text_7->show();
    ui->textEdit_Text_8->show();

    on_actionHide_file_paths_and_names_triggered();

    ui->label_Text_1->show();
    ui->label_Text_2->show();
    ui->label_Text_3->show();
    ui->label_Text_4->show();
    ui->label_Text_5->show();
    ui->label_Text_6->show();
    ui->label_Text_7->show();
    ui->label_Text_8->show();

    text_1_visible = true;
    text_2_visible = true;
    text_3_visible = true;
    text_4_visible = true;
    text_5_visible = true;
    text_6_visible = true;
    text_7_visible = true;
    text_8_visible = true;
}



// ////////////////////////////////////////////////////////////////////////////////////////
//Menu "Help"
// ////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionAbout_triggered()
{
    QString about_text;
    about_text  = tr("Program for editing Bible texts in USFM format") + "\n\n";

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



// //////////////////////////////////////////////////////////////////////////////////
//Contextual menus
// /////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_textEdit_Text_1_customContextMenuRequested()
{
    textEdit_focused("Text_1");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_1_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_1_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_1_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_1_As_triggered()));

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

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_1_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_1_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_2_customContextMenuRequested()
{
    textEdit_focused("Text_2");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_2_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_2_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_2_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_2_As_triggered()));

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

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_2_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_2_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_3_customContextMenuRequested()
{
    textEdit_focused("Text_3");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_3_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_3_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_3_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_3_As_triggered()));

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

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_3_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_3_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_4_customContextMenuRequested()
{
    textEdit_focused("Text_4");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_4_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_4_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_4_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_4_As_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_4_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_4_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_4_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_4_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_4_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_4_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_4_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_4_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_4_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_4_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_4_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_4_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_4_triggered()));

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_4_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_4_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_5_customContextMenuRequested()
{
    textEdit_focused("Text_5");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_5_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_5_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_5_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_5_As_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_5_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_5_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_5_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_5_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_5_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_5_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_5_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_5_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_5_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_5_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_5_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_5_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_5_triggered()));

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_5_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_5_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_6_customContextMenuRequested()
{
    textEdit_focused("Text_6");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_6_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_6_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_6_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_6_As_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_6_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_6_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_6_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_6_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_6_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_6_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_6_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_6_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_6_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_6_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_6_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_6_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_6_triggered()));

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_6_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_6_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_7_customContextMenuRequested()
{
    textEdit_focused("Text_7");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_7_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_7_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_7_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_7_As_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_7_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_7_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_7_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_7_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_7_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_7_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_7_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_7_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_7_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_7_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_7_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_7_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_7_triggered()));

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_7_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_7_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}

void MainWindow::on_textEdit_Text_8_customContextMenuRequested()
{
    textEdit_focused("Text_8");

    QAction *actionNew = new QAction(tr("New"), this);
    connect(actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_Text_8_triggered()));

    QAction *actionOpen = new QAction(tr("Open"), this);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(on_actionOpen_Text_8_triggered()));

    QAction *actionSave = new QAction(tr("Save"), this);
    connect(actionSave, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_8_triggered()));

    QAction *actionSaveAs = new QAction(tr("Save As"), this);
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(on_actionSave_Text_8_As_triggered()));

    QAction *actionUndo = new QAction(tr("Undo"), this);
    connect(actionUndo, SIGNAL(triggered()), this, SLOT(on_actionUndo_in_Text_8_triggered()));

    QAction *actionRedo = new QAction(tr("Redo"), this);
    connect(actionRedo, SIGNAL(triggered()), this, SLOT(on_actionRedo_in_Text_8_triggered()));

    QAction *actionCut = new QAction(tr("Cut"), this);
    connect(actionCut, SIGNAL(triggered()), this, SLOT(on_actionCut_from_Text_8_triggered()));

    QAction *actionCopy = new QAction(tr("Copy"), this);
    connect(actionCopy, SIGNAL(triggered()), this, SLOT(on_actionCopy_from_Text_8_triggered()));

    QAction *actionPaste = new QAction(tr("Paste"), this);
    connect(actionPaste, SIGNAL(triggered()), this, SLOT(on_actionPaste_into_Text_8_triggered()));

    QAction *actionSelectAll = new QAction(tr("Select All"), this);
    connect(actionSelectAll, SIGNAL(triggered()), this, SLOT(on_actionSelect_All_in_Text_8_triggered()));

    QAction *actionZoomIn = new QAction(tr("Zoom In"), this);
    connect(actionZoomIn, SIGNAL(triggered()), this, SLOT(on_actionZoom_In_Text_8_triggered()));

    QAction *actionZoomOut = new QAction(tr("Zoom Out"), this);
    connect(actionZoomOut, SIGNAL(triggered()), this, SLOT(on_actionZoom_Out_Text_8_triggered()));

    QAction *actionFormatted = new QAction(tr("Formatted USFM"), this);
    connect(actionFormatted, SIGNAL(triggered()), this, SLOT(on_actionFormatted_Text_8_triggered()));

    QAction *actionUnformatted = new QAction(tr("Unformatted USFM"), this);
    connect(actionUnformatted, SIGNAL(triggered()), this, SLOT(on_actionUnformatted_Text_8_triggered()));

    QAction *actionFind = new QAction(tr("Find"), this);
    connect(actionFind, SIGNAL(triggered()), this, SLOT(on_actionFind_in_Text_8_triggered()));

    QAction *actionReplace = new QAction(tr("Find and Replace"), this);
    connect(actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_in_Text_8_triggered()));

    QAction *actionReplaceAll = new QAction(tr("Find and Replace All"), this);
    connect(actionReplaceAll, SIGNAL(triggered()), this, SLOT(on_actionFind_and_Replace_All_in_Text_8_triggered()));

    QAction *actionShowFilePath = new QAction(tr("Show File Path"), this);
    connect(actionShowFilePath, SIGNAL(triggered()), this, SLOT(on_actionShow_file_path_of_Text_8_triggered()));

    QAction *actionShowFileName = new QAction(tr("Show File Name"), this);
    connect(actionShowFileName, SIGNAL(triggered()), this, SLOT(on_actionShow_file_name_of_Text_8_triggered()));

    QAction *actionHideFilePathName = new QAction(tr("Hide File Path and Name"), this);
    connect(actionHideFilePathName, SIGNAL(triggered()), this, SLOT(on_actionHide_file_paths_and_names_triggered()));

    QMenu *contextMenu = new QMenu(this);
    contextMenu->addAction(actionNew);
    contextMenu->addAction(actionOpen);
    contextMenu->addAction(actionSave);
    contextMenu->addAction(actionSaveAs);
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
    contextMenu->insertSeparator(0);
    contextMenu->addAction(actionShowFilePath);
    contextMenu->addAction(actionShowFileName);
    contextMenu->addAction(actionHideFilePathName);
    contextMenu->exec(QCursor::pos());
}


// /////////////////////////////////////////////////////////////////////////////////////////////////
//Other functions
// /////////////////////////////////////////////////////////////////////////////////////////////////

//setting highlighted textEdit
//all the methods that affect textEdits will call this method in the beginning
void MainWindow::textEdit_focused(QString textEditName) {
    //setting the chosen textEdit and corresponding label as highlighted
    if (textEditName == "Text_1") {
        ui->textEdit_Text_1->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_1->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text_2") {
        ui->textEdit_Text_2->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_2->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text_3") {
        ui->textEdit_Text_3->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_3->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text_4") {
        ui->textEdit_Text_4->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_4->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text_5") {
        ui->textEdit_Text_5->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_5->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text_6") {
        ui->textEdit_Text_6->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_6->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text_7") {
        ui->textEdit_Text_7->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_7->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }
    else if (textEditName == "Text_8") {
        ui->textEdit_Text_8->setFrameStyle(QFrame::WinPanel | QFrame::Plain);
        ui->label_Text_8->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 0, 255);");
    }

    //unsetting highlightening of others
    if (textEditName != "Text_1") {
        ui->textEdit_Text_1->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_1->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text_2") {
        ui->textEdit_Text_2->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_2->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text_3") {
        ui->textEdit_Text_3->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_3->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text_4") {
        ui->textEdit_Text_4->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_4->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text_5") {
        ui->textEdit_Text_5->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_5->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text_6") {
        ui->textEdit_Text_6->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_6->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text_7") {
        ui->textEdit_Text_7->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_7->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
    if (textEditName != "Text_8") {
        ui->textEdit_Text_8->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
        ui->label_Text_8->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(240, 240, 240);");
    }
}

void MainWindow::on_textEdit_Text_1_selectionChanged()
{
    textEdit_focused("Text_1");
}

void MainWindow::on_textEdit_Text_2_selectionChanged()
{
    textEdit_focused("Text_2");
}

void MainWindow::on_textEdit_Text_3_selectionChanged()
{
    textEdit_focused("Text_3");
}

void MainWindow::on_textEdit_Text_4_selectionChanged()
{
    textEdit_focused("Text_4");
}

void MainWindow::on_textEdit_Text_5_selectionChanged()
{
    textEdit_focused("Text_5");
}

void MainWindow::on_textEdit_Text_6_selectionChanged()
{
    textEdit_focused("Text_6");
}

void MainWindow::on_textEdit_Text_7_selectionChanged()
{
    textEdit_focused("Text_7");
}

void MainWindow::on_textEdit_Text_8_selectionChanged()
{
    textEdit_focused("Text_8");
}


