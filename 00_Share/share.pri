HEADERS += \
    $$PWD/share/cvres.h \
    $$PWD/share/share.h
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
            MSVC_VER = $$(VisualStudioVersion)
            equals(MSVC_VER, 12.0){
                message("           msvc12 - 2013")
                # MSVC2013 build required camera capture via file
                DEFINES += CAMERA_CAPTURE_VIA_FILE
            }
            equals(MSVC_VER, 13.0){
                # camera capture via buffer NOT tested
                message("           msvc13 - 2014")
            }
            equals(MSVC_VER, 14.0){
                # camera capture via buffer NOT tested
                message("           msvc14 - 2015")
            }
            equals(MSVC_VER, 15.0){
                # camera capture via buffer is OK
                message("           msvc15 - 2017")
            }
        }
    }
    contains(QMAKE_TARGET.arch, x86){
        message("        arch: i386")
        win32-g++ {
            message("               compiler: mingw-32")
            # mingw-32 required camera capture via file
            DEFINES += CAMERA_CAPTURE_VIA_FILE
        }
        win32-msvc* {
            message("               compiler: msvc")
        }
    }

}
