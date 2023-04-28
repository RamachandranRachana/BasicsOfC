import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls
import Qt.labs.platform as Platform

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Image Viewer")

    background: Rectangle {
        color: "darkGray"
    }

    Image {
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        asynchronous: true
        property bool counter: false
        source: "image://live/image?id=false"
        function reload()
        {
             console.log("reload")
             counter = !counter
             source = "image://live/image?id=" + counter
        }
        function getScaleX()
        {
            return image.paintedWidth / image.sourceSize.width
        }
        function getScaleY()
        {
            return image.paintedHeight / image.sourceSize.height
        }

        function getXPosition()
        {
            switch (image.horizontalAlignment) 
            {
                case Image.AlignLeft:
                    return 0
                case Image.AlignRight:
                    return image.width - image.paintedWidth
                case Image.AlignHCenter:
                default:
                    return (image.width - image.paintedWidth) * 0.5
            }
        }
        function getYPosition()
        {
            switch (image.verticalAlignment) 
            {
                case Image.AlignTop:
                    return 0
                case Image.AlignBottom:
                    return image.height - image.paintedHeight
                case Image.AlignVCenter:
                default:
                    return (image.height - image.paintedHeight) * 0.5
            }
        }  
        Canvas{
            id: canvasArea
            anchors.fill:parent
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                property real originX: 0
                property real originY: 0
                property real wx: 0
                property real hy: 0
                onClicked: {
                    originX = Math.floor((mouseArea.mouseX - image.getXPosition()) / image.getScaleX())
                    originY = Math.floor((mouseArea.mouseY - image.getYPosition()) / image.getScaleY())

                    ImageProcessor.AnnotTextAt(originX,originY,"AAA")
                }
                onPressed:
                {
                    originX = Math.floor((mouseArea.mouseX - image.getXPosition()) / image.getScaleX())
                    originY = Math.floor((mouseArea.mouseY - image.getYPosition()) / image.getScaleY())
                }
                onPositionChanged: 
                {
                    var curX=Math.floor((mouseArea.mouseX - image.getXPosition()) / image.getScaleX())
                    var curY=Math.floor((mouseArea.mouseX - image.getXPosition()) / image.getScaleX())
                    wx = Math.abs(curX - originX)
                    hy = Math.abs(curY - originY)
                }
                onReleased: 
                {
                    ImageProcessor.AnnotTextWithBoxSelect(originX,originY,wx,hy,"HHH")
                }
            }
        }        
    }

    header: ToolBar {
        Flow {
            anchors.fill: parent
            ToolButton {
                text: qsTr("Open")
                icon.name: "document-open"
                onClicked: fileOpenDialog.open()
            }
        }
    } 

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open...")
                icon.name: "document-open"
                onTriggered: fileOpenDialog.open()
            }
        }

        Menu {
            title: qsTr("&Help")
            MenuItem {
                text: qsTr("&About...")
                onTriggered: aboutDialog.open()
            }
        }
    }
    
    Platform.FileDialog {
        id: fileOpenDialog
        title: "Select an image file"
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: [
            "Image files (*.png *.jpeg *.jpg)",
        ]
        onAccepted: {
            var path = fileOpenDialog.currentFile.toString();
            path = path.replace(/^(file:\/{3})/,"");
            ImageProcessor.loadInitial(decodeURIComponent(path))
        }
    }

     Dialog {
        id: aboutDialog
        title: qsTr("About")
        Label {
            anchors.fill: parent
            text: qsTr("QML Image Viewer\nA part of the QmlBook\nhttp://qmlbook.org")
            horizontalAlignment: Text.AlignHCenter
        }

        standardButtons: StandardButton.Ok
    }

    Connections{
        target: liveImageProvider

        function onImageChanged()
        {
            image.reload()
        }
        }
}
