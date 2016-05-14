#-------------------------------------------------
#
# Project created by QtCreator 2011-06-08T12:37:09
#
#-------------------------------------------------

QT       += core gui\
            network

TARGET = FS_Mobile
TEMPLATE = app

LIBS += d:\QtSDK\Symbian\tools\sbs\win32\mingw\lib\libws2_32.a

SOURCES += main.cpp\
            gsoap/soapC.cpp \
            gsoap/soapClient.cpp \
            gsoap/stdsoap2.cpp \
        mainwindow.cpp \
    loginform.cpp \
    navigatorform.cpp \
    jf_scrollarea.cpp \
    jfrb_scrollarea.cpp \
    jfyb_scrollarea.cpp \
    skcx_scrollarea.cpp \
    ydxh_scrollarea.cpp \
    skjx_scrollarea.cpp \
    kcxk_scrollarea.cpp \
    tczfcx_scrollarea.cpp \
    ywbl_scrollarea.cpp \
    ywslcx_scrollarea.cpp \
    zhye_scrollarea.cpp \
    zhcz_scrollarea.cpp \
    xkkk_scrollarea.cpp \
    xgmm_scrollarea.cpp \
    yhxxxg_scrollarea.cpp \
    gszh_scrollarea.cpp \
    jymx_scrollarea.cpp \
    gmjp_scrollarea.cpp \
    drjytj_scrollarea.cpp \
    dbfjs_scrollarea.cpp \
    singleton.cpp \
    registerbox.cpp \
    noticedialog.cpp \
    newsalertdialog.cpp \
    zxgg_scrollarea.cpp \
    config.cpp \
    kdcz_tabwidget.cpp \
    yxcz_tabwidget.cpp \
    printer.cpp \
    buynodialog.cpp \
    businessdialog.cpp \
    klxs_tabwidget.cpp

HEADERS  += mainwindow.h \
    loginform.h \
    navigatorform.h \
    jf_scrollarea.h \
    jfrb_scrollarea.h \
    jfyb_scrollarea.h \
    skcx_scrollarea.h \
    ydxh_scrollarea.h \
    skjx_scrollarea.h \
    kcxk_scrollarea.h \
    tczfcx_scrollarea.h \
    ywbl_scrollarea.h \
    ywslcx_scrollarea.h \
    zhye_scrollarea.h \
    zhcz_scrollarea.h \
    xkkk_scrollarea.h \
    xgmm_scrollarea.h \
    yhxxxg_scrollarea.h \
    gszh_scrollarea.h \
    jymx_scrollarea.h \
    gmjp_scrollarea.h \
    drjytj_scrollarea.h \
    dbfjs_scrollarea.h \
    singleton.h \
    registerbox.h \
    noticedialog.h \
    newsalertdialog.h \
    zxgg_scrollarea.h \
    EncryptUtil.h \
    config.h \
    kdcz_tabwidget.h \
    yxcz_tabwidget.h \
    printer.h \
    buynodialog.h \
    businessdialog.h \
    klxs_tabwidget.h

FORMS    += mainwindow.ui \
    loginform.ui \
    navigatorform.ui \
    jf_scrollarea.ui \
    jfrb_scrollarea.ui \
    jfyb_scrollarea.ui \
    skcx_scrollarea.ui \
    ydxh_scrollarea.ui \
    skjx_scrollarea.ui \
    kcxk_scrollarea.ui \
    tczfcx_scrollarea.ui \
    ywbl_scrollarea.ui \
    ywslcx_scrollarea.ui \
    zhye_scrollarea.ui \
    zhcz_scrollarea.ui \
    xkkk_scrollarea.ui \
    xgmm_scrollarea.ui \
    yhxxxg_scrollarea.ui \
    gszh_scrollarea.ui \
    jymx_scrollarea.ui \
    gmjp_scrollarea.ui \
    drjytj_scrollarea.ui \
    dbfjs_scrollarea.ui \
    registerbox.ui \
    noticedialog.ui \
    newsalertdialog.ui \
    zxgg_scrollarea.ui \
    kdcz_tabwidget.ui \
    yxcz_tabwidget.ui \
    buynodialog.ui \
    businessdialog.ui \
    klxs_tabwidget.ui

RESOURCES += \
    images.qrc

unix:!mac:!symbian:!vxworks:LIBS += -lm

CONFIG += precompiled_header\
            thread\
            qaxcontainer\
            openssl

PRECOMPILED_HEADER = mainwindow.h

RC_FILE = icon.rc
