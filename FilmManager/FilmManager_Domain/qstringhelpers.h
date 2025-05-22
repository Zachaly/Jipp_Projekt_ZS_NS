#include <QString>

#ifndef QSTRINGHELPERS_H
#define QSTRINGHELPERS_H

inline QString toQString(const std::string& str) {
    return QString::fromStdString(str);
}

inline std::string fromQString(const QString& qstr) {
    return qstr.toStdString();
}


#endif // QSTRINGHELPERS_H
