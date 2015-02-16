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

import QtQuick 2.0
import LazyViews 1.0

Item {
    visible: true
    anchors.fill: parent

    LazyListView {
        id: view
        anchors.fill: parent

        orientation: Qt.Vertical

        model: TestModel {}

        delegate: Component {
            Image {
                width: 100
                height: 100
                source: "/Users/kicsyromy/Downloads/Qt_master_logo_CMYK_300dpi.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Component.onCompleted: {
            console.log("DONE!!!!")
        }
    }

//    Item {
//        anchors.fill: parent

//        Flickable {
//            anchors.fill: parent
//            contentWidth: image.width
//            contentHeight: image.height

//            Image {
//                id: image
//                source: "/home/kicsyromy/Downloads/Qt_master_logo_CMYK_300dpi.png"
//            }

//            Component.onCompleted: {
//                console.log("CONTENT ITEM = " + contentItem)
//                console.log("CONTENT ITEM CHILDREN = " + contentItem.children)
//                console.log("CONTENT ITEM PARENT = " + contentItem.parent)
//            }
//        }
//    }
}
