// Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

import QtQuick 2.9 as QQ
import QtQuick.Window 2.9
import QtQuick.Layouts 1.1 as QQL
import QtQuick.Controls 2.2 as QQC
import QtMultimedia 5.9 as QMM

import CvObject 1.0

Window {
    visible: true
    width: 1024
    height: 480
    title: qsTr("Qt Quick for OpenCV")

    CvObject{
        id:cvo
    }

    QQL.GridLayout {
        anchors.fill: parent
        rows:1
        columns:4
        QQ.Rectangle{
            color: "darkgrey"
            implicitHeight: 480
            implicitWidth: 256
            QQL.ColumnLayout{
                QQC.Button{
                    text: "Button #0"
                    onPressed: {
                        //! \todo - need to be ready
                        mmCamera.searchAndLock();
                        mmCamera.imageCapture.captureToLocation("./imgCap.jpg");

                    }
                }
                QQ.Rectangle{
                    color: "blue"
                    implicitWidth: 256
                    implicitHeight: 172
                    QMM.Camera {
                        id: mmCamera
                        captureMode: QMM.Camera.CaptureStillImage
                        imageCapture{
                            onImageCaptured: {
                                console.log("onImageCaptured")
                                console.log(mmCamera.imageCapture.capturedImagePath)
                            }
                            onImageSaved:{
                                console.log("onImageSaved")
                                mmImageIn.source = ""
                                mmImageIn.source = "file:///"+mmCamera.imageCapture.capturedImagePath;
                            }
                        }
                    }
                    QMM.VideoOutput {
                        id: videoOutput
                        source: mmCamera
                        anchors.fill: parent
                    }
                }
                QQ.Image{
                    id: mmImageIn
                    cache: false
                    sourceSize.width: 256
                    sourceSize.height: 256
                    fillMode: QQ.Image.PreserveAspectFit
                    source: "file:./imageRgbPart.png"
                    onStatusChanged: if (mmImageIn.status == QQ.Image.Ready)
                                         console.log('Image#0 Loaded')

                }
            }
        }
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
