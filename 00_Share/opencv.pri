# Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
# MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#OpenCV pratform dependend settings
linux:!android {
    message("* OpenCV Using settings for Unix/Linux.")
    INCLUDEPATH += /usr/local/include
    LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
    LIBS += -lopencv_highgui
    contains(QMAKE_HOST.arch, x86_64){
        message("        arch: amd64")
        #LIB += /usr/local/lib64
    }
    contains(QMAKE_HOST.arch, x86){
        message("        arch: i386")
        #LIB += /usr/local/lib32
    }
}
