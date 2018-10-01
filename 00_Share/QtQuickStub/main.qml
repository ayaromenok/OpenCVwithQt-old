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
    width: 800
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
            implicitWidth: 200
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
                    implicitWidth: 200
                    implicitHeight: 200
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
                                console.log(mmCamera.imageCapture.capturedImagePath);
                                mmImageIn.source = ""
                                //tested and OK on OSX, Windows, Linux, Android
                                mmImageIn.source = "file:"+mmCamera.imageCapture.capturedImagePath;
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
                    sourceSize.width: 200
                    sourceSize.height: 200
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
            implicitWidth: 200
            QQL.ColumnLayout{
                QQC.Button{
                    text: "Blur Gaussian"
                    onPressed: { cvo.blurGaussian()
                        imgBlurGaussian.source = ""
                        imgBlurGaussian.source = "file:./blurGaussian.jpg"
                        }
                }
                QQ.Image{
                    id: imgBlurGaussian
                    sourceSize.width: 200
                    sourceSize.height: 200
                    fillMode: QQ.Image.PreserveAspectFit
                    source: "file:./imageRgb.png"
                }
            }
        }
        QQ.Rectangle{
            color: "lightgrey"
            implicitHeight: 480
            implicitWidth: 200
            QQL.ColumnLayout{
                QQC.Button{
                    text: "Checked Board detect"
                    onPressed: { cvo.checkedBoardDetect()
                        imgCheckedBoardDetect.source = ""
                        imgCheckedBoardDetect.source = "file:./checkedBoardDetect.jpg"
                        }
                }
                QQ.Image{
                    id: imgCheckedBoardDetect
                    sourceSize.width: 200
                    sourceSize.height: 200
                    fillMode: QQ.Image.PreserveAspectFit
                    source: "file:./imageRgbPart.png"
                    transform: QQ.Rotation{origin.x: 100; origin.y:100; angle:90}
                }
            }
        }
        QQ.Rectangle{
            color: "grey"
            implicitHeight: 480
            implicitWidth: 200
            QQL.ColumnLayout{
                QQC.Button{
                    text: "Edge Detect canny"
                    onPressed: { cvo.edgeDetectCanny()
                                imgEgdeDetectCanny.source = ""
                                imgEgdeDetectCanny.source = "file:./edgeDetectCanny.jpg"
                                }
                }
                QQ.Image{
                    id: imgEgdeDetectCanny
                    sourceSize.width: 200
                    sourceSize.height: 200
                    fillMode: QQ.Image.PreserveAspectFit
                    source: "file:./imageRgb.png"
                }
            }
        }
    }
}
