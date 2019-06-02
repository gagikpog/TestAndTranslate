#ifndef HEADER_H
#define HEADER_H

#include <QSqlError>

#ifdef _WIN32
    #define QODBC_DATABASE
#endif
#define __MONTH__ (\
  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? "01" : "06") \
: __DATE__ [2] == 'b' ? "02" \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? "03" : "04") \
: __DATE__ [2] == 'y' ? "05" \
: __DATE__ [2] == 'l' ? "07" \
: __DATE__ [2] == 'g' ? "08" \
: __DATE__ [2] == 'p' ? "09" \
: __DATE__ [2] == 't' ? "10" \
: __DATE__ [2] == 'v' ? "11" \
: "12")

const char _BUILD_ []{__DATE__[ 9],
    __DATE__[ 10], __MONTH__[0], __MONTH__[1],
    __DATE__[4] == ' ' ? '0' : __DATE__[4],
    __DATE__[5], '\0'};

const QString BUILD_TIME = __TIME__;
const QString BUILD_DATE = __DATE__;
const QString VERSION = "1.0.0";
const QString BUILD = _BUILD_;

#endif // HEADER_H
