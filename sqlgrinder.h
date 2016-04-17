#ifndef SQLGRINDER_H
#define SQLGRINDER_H

#endif // SQLGRINDER_H
#include <QtSql>
bool copyFilesAttHashTableToSqlLite(QMultiMap<QString,FileAttributes> fileAttHashTable,QSqlDatabase db, QDateTime currentDateTime );
QString sqlEscape(QString boundValue);
