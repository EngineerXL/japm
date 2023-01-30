QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    aes/aes.c \
    data/data.cpp \
    encrypter/encrypter_aes256.cpp \
    main.cpp \
    japm.cpp \
    sha3/sha3.cpp \
    substr/pattern_text_search.cpp

HEADERS += \
    aes/aes.h \
    aes/aes.hpp \
    data/data.h \
    encrypter/encrypter_aes256.h \
    japm.h \
    sha3/sha3.h \
    substr/pattern_text_search.h

FORMS += \
    japm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
