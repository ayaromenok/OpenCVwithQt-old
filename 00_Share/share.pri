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

win32{
    message("* Using settings for Windows.")
    contains(QMAKE_TARGET.arch, x86_64){
        message("        arch: amd64")
        win32-msvc* {
            message("               compiler: msvc")
        }
    }
    contains(QMAKE_TARGET.arch, x86){
        message("        arch: i386")
        win32-g++ {
            message("               compiler: mingw-32")
            #mingw-32 required capture via file, while MSVC works well via buffer
            DEFINES += CAMERA_CAPTURE_VIA_FILE
        }
        win32-msvc* {
            message("               compiler: msvc")
        }
    }

}
