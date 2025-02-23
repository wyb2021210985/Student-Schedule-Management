QT       += core gui axcontainer\

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=\
    AVLCourseNode.cpp \
    CourseWidget.cpp \
    Map.cpp \
    User.cpp \
    main.cpp \
    mainwindow.cpp\
    Buildings.cpp\
    node.cpp\
    Graph.cpp\
    ScheduleTable.cpp\
    Temporary.cpp\
    AfterClass.cpp\
    Course.cpp\
    ClassTable.cpp
HEADERS += \
    AVLCourseNode.h \
    CourseWidget.h \
    Map.h \
    User.h \
    mainwindow.h\
    Buildings.h\
    node.h\
    Graph.h\
    ScheduleTable.h\
    Temporary.h\
    AfterClass.h\
    Course.h\
    ClassTable.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
