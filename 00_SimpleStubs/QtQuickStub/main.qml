// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

import QtQml 2.9 as QML
import QtQuick 2.9 as QQ
import QtQuick.Window 2.9
import QtQuick.Layouts 1.1 as QQL
import QtQuick.Controls 2.2 as QQC
import QtMultimedia 5.9 as QMM

import CvObject 1.0

Window {
    visible: true
    width: 360
    height: 360
    title: qsTr("Qt Quick for OpenCV")

    CvObject{
        id:cvo
    }
    QML.Connections{
        target:cvo
        onIntValChanged:{
            console.log("onIntValChanged()")
            lbResult.text = value;
        }
    }

    QQL.GridLayout {
        anchors.fill: parent
        rows:1
        columns:4
        QQ.Rectangle{
            color: "darkgrey"
            implicitHeight: 360
            implicitWidth: 360
            QQL.ColumnLayout{
                QQC.Button{
                    text: "set value via Property: 5"
                    onPressed: {                        
                        console.log("set value 5")
                        cvo.setIntVal(5);
                    }
                }

                QQC.Button{
                    text: "set value via Invokable: 7"
                    onPressed: {
                        console.log("set value 7")
                        cvo.setIntVal(7);
                    }
                }
                QQL.RowLayout{
                    QQC.Label{
                        id: lbName
                        text: "value is:"
                    }
                    QQC.Label{
                        id: lbResult
                        text: cvo.intVal
                    }
                }

            }
        }

    }
}
