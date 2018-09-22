HEADERS += \
    $$PWD/share/cvres.h
SOURCES += \
    $$PWD/share/cvres.cpp

linux:!android {
    message("* Using settings for Unix/Linux.")
    contains(QMAKE_HOST.arch, x86_64){
        message("        arch: amd64")
    }
    contains(QMAKE_HOST.arch, x86){
        message("        arch: i386")
    }
}
macx{
    message("* Using settings for Mac OS X.")
    contains(QMAKE_HOST.arch, x86_64){
        message("        arch: amd64")
    }
    contains(QMAKE_HOST.arch, x86){
        message("        arch: i386")
    }
    DEFINES += CAMERA_CAPTURE_VIA_FILE
 }
