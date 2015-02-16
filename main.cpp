/*
 * LazyListView
 * Copyright (C) 2015 Romeo Calota <kicsyromy@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QGuiApplication>
#include <QQuickView>

#include "lazylistview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView viewer;

    qmlRegisterType<LazyListView>("LazyViews", 1, 0, "LazyListView");

    viewer.setSource(QUrl("qml/main.qml"));
    viewer.show();

    return app.exec();
}
