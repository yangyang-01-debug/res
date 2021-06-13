QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basicmovie.cpp \
    basicpbs.cpp \
    basicplants.cpp \
    basicplantsBtn.cpp \
    basicwindow.cpp \
    basiczombies.cpp \
    button.cpp \
    chooselevelwidget.cpp \
    chooseplantstitllbar.cpp \
    firstscreen.cpp \
    form.cpp \
    label.cpp \
    logindialog.cpp \
    main.cpp \
    mediaplayer.cpp \
    messagebox.cpp \
    moveplantbtn.cpp \
    mybtn.cpp \
    mytimer.cpp \
    screencontroler.cpp \
    setbtndialog.cpp \
    shooters.cpp \
    sunflower.cpp \
    sunlabel.cpp \
    titlebar.cpp \
    wallnut.cpp \
    widget.cpp \
    zombies.cpp

HEADERS += \
    basicmovie.h \
    basicpbs.h \
    basicplants.h \
    basicplantsBtn.h \
    basicwindow.h \
    basiczombies.h \
    button.h \
    chooselevelwidget.h \
    chooseplantstitllbar.h \
    config.h \
    firstscreen.h \
    form.h \
    label.h \
    logindialog.h \
    mediaplayer.h \
    messagebox.h \
    moveplantbtn.h \
    mybtn.h \
    mytimer.h \
    screencontroler.h \
    setbtndialog.h \
    shooters.h \
    sunflower.h \
    sunlabel.h \
    titlebar.h \
    wallnut.h \
    widget.h \
    zombies.h

FORMS += \
    chooselevelwidget.ui \
    form.ui \
    logindialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

