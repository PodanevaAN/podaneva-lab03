QT       += core gui sql charts widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BarChart.cpp \
    JsonDataReader.cpp \
    PieChart.cpp \
    SqlDataReader.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    BarChart.h \
    IChart.h \
    IDataReader.h \
    IOCContainer.h \
    JsonDataReader.h \
    MainWindow.h \
    PieChart.h \
    SqlDataReader.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    InputData/BLOOD_SUGAR.sqlite \
    InputData/HUMIDITY_MOSCOW.sqlite \
    InputData/JSON.json \
    InputData/NORDPOOL_PRICES.sqlite \
    InputData/PRICES_NATURAL_GAS_USD.sqlite \
    InputData/TEMPERATURE_NOVOSIB.sqlite
