QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file_edit_dialogue.cpp \
    gen.cpp \
    graph_dialogue.cpp \
    list_details_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix_details_dialogue.cpp \
    runner_dialogue.cpp \
    string_details_dialogue.cpp \
    variable_details_dialog.cpp

HEADERS += \
    NumericValidator.h \
    file_edit_dialogue.h \
    gen.h \
    graph_dialogue.h \
    list_details_dialog.h \
    mainwindow.h \
    matrix_details_dialogue.h \
    runner_dialogue.h \
    string_details_dialogue.h \
    variable.h \
    variable_details_dialog.h

FORMS += \
    file_edit_dialogue.ui \
    graph_dialogue.ui \
    list_details_dialog.ui \
    mainwindow.ui \
    matrix_details_dialogue.ui \
    runner_dialogue.ui \
    string_details_dialogue.ui \
    variable_details_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
