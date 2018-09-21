// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

import QtQuick 2.11 as QQ
import QtQuick.Window 2.11
import QtQuick.Layouts 1.1 as QQL
import QtQuick.Controls 2.2 as QQC

import CvObject 1.0

Window {
    visible: true
    width: 800
    height: 480
    title: qsTr("Qt Quick for OpenCV")

    CvObject{
        id:cvo
    }

    QQL.GridLayout {
        anchors.fill: parent
        rows:1
        columns:3
        QQ.Rectangle{
            color: "grey"
            implicitHeight: 480
            implicitWidth: 256
            QQL.ColumnLayout{
                QQC.Button{
                    text: "Button #1"
                    onPressed: cvo.setIntVal(1)
                }
                QQ.Image{
                    sourceSize.width: 256
                    sourceSize.height: 256
                    fillMode: QQ.Image.PreserveAspectFit
                    source: "file:./imageRgb.png"
                }
            }
        }
        QQ.Rectangle{
            color: "lightgrey"
            implicitHeight: 480
            implicitWidth: 256
            QQL.ColumnLayout{
                QQC.Button{
                    text: "Button #2"
                    onPressed: cvo.setIntVal(2)
                }
                QQ.Image{
                    sourceSize.width: 256
                    sourceSize.height: 256
                    fillMode: QQ.Image.PreserveAspectFit
                    source: "file:./imageRgbPart.png"
                }
            }
        }
        QQ.Rectangle{
            color: "grey"
            implicitHeight: 480
            implicitWidth: 256
            QQL.ColumnLayout{
                QQC.Button{
                    text: "Button #3"
                    onPressed: cvo.setIntVal(3)
                }
                QQ.Image{
                    sourceSize.width: 256
                    sourceSize.height: 256
                    fillMode: QQ.Image.PreserveAspectFit
                    source: "file:./imageRgb.png"
                }
            }
        }
    }
}
