# Copyright(C) 2018 Andrey Yaromenok, ayaromenok@gmail.com
# MIT License - https://github.com/ayaromenok/OpenCVwithQt/blob/master/LICENSE

#OpenCV SDK places on different platforms
CVLINUX = /usr/local
CVANDROID = /opt/cvAndroid/3/sdk/native
#OpenCV platform dependend settings
linux:!android {
    message("* OpenCV settings for Unix/Linux.")
    INCLUDEPATH += -L$${CVLINUX}/include
    LIBS += -L$${CVLINUX}/lib
    LIBS += -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
    LIBS += -lopencv_highgui
    contains(QMAKE_HOST.arch, x86_64){
        message("        arch: amd64")
        #LIB += -L$${CVLINUX}/lib64
    }
    contains(QMAKE_HOST.arch, x86){
        message("        arch: i386")
        #LIB += -L$${CVLINUX}/lib32
    }
}

android {
    INCLUDEPATH += "$${CVANDROID}/jni/include"
    message("* OpenCV settings for Android.")
    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
        message("        arch: armeabi-v7a")
        LIBS += -L$${CVANDROID}/libs/armeabi-v7a
        LIBS += -lopencv_java3

       ANDROID_EXTRA_LIBS = \
           $${CVANDROID}/libs/armeabi-v7a/libopencv_java3.so
    }
}
