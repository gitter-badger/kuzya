QT   += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++14

unix:QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

TEMPLATE = app

FORMS += kuzya.ui \
    gotolinedialog.ui \
    optionsdialog.ui \
    finddialog.ui \
    replacedialog.ui

HEADERS += kuzya.h \
    gotolinedialog.h \
    compiler.h \
    optionsdialog.h \
    finddialog.h \
    replacedialog.h \
    helpbrowser.h \
    translator.h \
    version.h

SOURCES += kuzya.cpp \
    main.cpp \
    gotolinedialog.cpp \
    compiler.cpp \
    optionsdialog.cpp \
    finddialog.cpp \
    replacedialog.cpp \
    translator.cpp

RESOURCES = images.qrc

TRANSLATIONS = ../resources/translations/Ukrainian.ts \
    ../resources/translations/English.ts \
    ../resources/translations/Byelorussian.ts \
    ../resources/translations/French.ts \
    ../resources/translations/Serbian.ts \
    ../resources/translations/Arabic.ts


unix {
    TARGET = ../bin/kuzya
    target.path = /usr/bin
    translations.path = /usr/share/kuzya/translations
    translations.files = ../resources/translations/*.qm
    kuzya_profiles.path = /usr/share/kuzya/profiles
    kuzya_profiles.files = ../profiles/*
    kuzya_doc.path = /usr/share/kuzya/doc
    kuzya_doc.files = ../doc/Kuzya_Help/*
    kuzya_resources.path = /usr/share/kuzya/resources
    kuzya_resources.files = ../resources/*
    kuzya_icon.path = /usr/share/icons
    kuzya_icon.files = ../resources/icon/*
    kuzya_app_desktop.path = /usr/share/applications
    kuzya_app_desktop.files = ../resources/linux/*

    INSTALLS += target \
        translations \
        kuzya_profiles \
        kuzya_doc \
        kuzya_resources\
    kuzya_icon\
    kuzya_app_desktop
}

CONFIG += qscintilla2

win32 {
    TARGET = ../../bin/kuzya
    LIBS += -L../../3rdparty/QScintilla/2.9.4
    INCLUDEPATH = ../../3rdparty/QScintilla/2.9.4
    LIBS += -lqscintilla2
}

mac {
    CONFIG-=app_bundle
    DESTDIR +=../kuzya
    TARGET +=kuzya
}
