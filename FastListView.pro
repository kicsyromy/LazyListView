#
# LazyListView
# Copyright (C) 2015 Romeo Calota <kicsyromy@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

TEMPLATE = app

QT += qml quick quick_private core_private

TARGET = FastListView

macx:QMAKE_CXXFLAGS += -std=c++11

#INCLUDEPATH += /usr/include/qt/QtQuick/5.4.0/QtQuick/private

QMAKE_CXXFLAGS += -fpermissive

SOURCES += main.cpp \
    lazylistview.cpp \
    itempool.cpp

OTHER_FILES += qml/*.qml

HEADERS += \
    lazylistview.h \
    itempool.h

macx:QMAKE_POST_LINK += cp -rvf $$quote($$_PRO_FILE_PWD_/qml) $$quote($$OUT_PWD/FastListView.app/Contents/MacOS/)
