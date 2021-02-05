QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    addtocart.cpp \
    book.cpp \
    cart.cpp \
    checkout.cpp \
    createaccount.cpp \
    database.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    managebooks.cpp

HEADERS += \
    account.h \
    addbook.h \
    addtocart.h \
    book.h \
    cart.h \
    checkout.h \
    createaccount.h \
    database.h \
    login.h \
    mainwindow.h \
    managebooks.h

FORMS += \
    addbook.ui \
    addtocart.ui \
    checkout.ui \
    createaccount.ui \
    login.ui \
    mainwindow.ui \
    managebooks.ui

win32:RC_ICONS += bsu.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += "C:\Program Files\MySQL\Connector C++ 8.0\include"
INCLUDEPATH += "C:\Program Files\MySQL\MySQL Server 8.0\include"

win32: LIBS += -L$$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14/' -lmysqlcppconn8-static

INCLUDEPATH += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14'
DEPENDPATH += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14'

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14/mysqlcppconn8-static.lib'
else:win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14/libmysqlcppconn8-static.a'

win32: LIBS += -L$$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14/' -lmysqlcppconn-static

INCLUDEPATH += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14'
DEPENDPATH += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14'

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14/mysqlcppconn-static.lib'
else:win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/MySQL/Connector C++ 8.0/lib64/vs14/libmysqlcppconn-static.a'

win32: LIBS += -L$$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/lib/' -llibmysql

INCLUDEPATH += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/include'
DEPENDPATH += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/include'

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib'
else:win32-g++: PRE_TARGETDEPS += $$PWD/'../../../../../Program Files/MySQL/MySQL Server 8.0/lib/liblibmysql.a'
