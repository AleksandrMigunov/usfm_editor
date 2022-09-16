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

#include "dialogreplaceall.h"
#include "ui_dialogreplaceall.h"

DialogReplaceAll::DialogReplaceAll(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReplaceAll)
{
    ui->setupUi(this);
}

DialogReplaceAll::~DialogReplaceAll()
{
    delete ui;
}

void DialogReplaceAll::on_lineEdit_Find_editingFinished()
{
    search = ui->lineEdit_Find->text();
}

void DialogReplaceAll::on_buttonBox_accepted()
{
    BeginSearch = true;
}

void DialogReplaceAll::on_buttonBox_rejected()
{
    BeginSearch = false;
}

void DialogReplaceAll::on_lineEdit_Replace_editingFinished()
{
    replace = ui->lineEdit_Replace->text();
}
