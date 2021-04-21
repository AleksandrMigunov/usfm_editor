
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

#-------------------------------------------------
#
# Project created by QtCreator 2021-04-10T00:39:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USFM_editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    converter.cpp \
    dialogfind.cpp \
    dialogreplace.cpp \
    dialogreplaceall.cpp

HEADERS  += mainwindow.h \
    converter.h \
    dialogfind.h \
    dialogreplace.h \
    dialogreplaceall.h

FORMS    += mainwindow.ui \
    dialogfind.ui \
    dialogreplace.ui \
    dialogreplaceall.ui

TRANSLATIONS = main_ru.ts
