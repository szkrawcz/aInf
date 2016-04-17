#include <QtSql>
#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "dirgrinder.h"
#include <QCoreApplication>
#include <QStringList>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QDate>



QString sqlEscape(QString boundValue)
{
    boundValue.replace('@', "@@");
    boundValue.replace('_', "@_");
    boundValue.replace('%', "@%");
    boundValue.replace("'", "''");
    return boundValue;
}


bool copyFilesAttHashTableToSqlLite(QMultiMap<QString,FileAttributes> fileAttHashTable,QSqlDatabase db, QDateTime currentDateTime )
{
   QString dateFormat = "yyyy-MM-dd hh:mm:ss";


   // qDebug( "Connected to SqlLite DB" );
    QSqlQuery qry;
    QString sqlCmd;
    qry.prepare( QString("CREATE TABLE IF NOT EXISTS filesScannedTemp ( absoluteFilePath VARCHAR(65536),  ")
                 + "fileName VARCHAR(65536),"
                 + "filePath VARCHAR(65536),"
                 + "md5Hash  VARCHAR(500),"
                 + "lastModified VARCHAR(50),"
                 + "lastRead VARCHAR(50),"
                 + "created VARCHAR(50),"
                 + "isHidden VARCHAR(50),"
                 + "size VARCHAR(50),"
                 + "owner VARCHAR(50),"
                 + "reportCreated VARCHAR(50))");

    if( !qry.exec() )
      qDebug() << qry.lastError();

      // else
   //   qDebug() << "Table created!";



    //list all files from hash table
    QSet<QString> keys = QSet<QString> :: fromList(fileAttHashTable.keys());
    foreach (const QString keyvalue, keys)
    {   //list all keys  . In this case list all files.
        FileAttributes tempAttributes ;
        tempAttributes = fileAttHashTable.value(keyvalue);

        qry.prepare ( "INSERT INTO filesScannedTemp ( absoluteFilePath,fileName,filePath,md5Hash,lastModified,lastRead,created,isHidden,size,owner,reportCreated) "
                 "VALUES (:absoluteFilePath,:fileName,:filePath,:md5Hash,:lastModified,:lastRead,:created,:isHidden,:size,:owner,:reportCreated)");

        qry.bindValue(":absoluteFilePath", QString(sqlEscape(tempAttributes.absoluteFilePath)));
        qry.bindValue(":fileName", QString(sqlEscape(tempAttributes.fileName)));
        qry.bindValue(":filePath", QString(sqlEscape(tempAttributes.filePath)));
        qry.bindValue(":md5Hash",QString(tempAttributes.md5Hash));
        qry.bindValue(":lastModified",QString(tempAttributes.lastModified.toString(dateFormat)));
        qry.bindValue(":lastRead",QString(tempAttributes.lastRead.toString(dateFormat)));
        qry.bindValue(":created",QString(tempAttributes.created.toString(dateFormat)));
        qry.bindValue(":isHidden",QString::number(tempAttributes.isHidden));
        qry.bindValue(":size",QString::number(tempAttributes.size));
        qry.bindValue(":owner",QString(tempAttributes.owner));
        qry.bindValue(":reportCreated",QString(currentDateTime.toString(dateFormat)));

        if( !qry.exec() )
        {
      qDebug() << qry.lastError();
         qDebug() << sqlCmd;
        }
      //  qDebug() << "insert  time ms = " << timer.elapsed();

    } //end foreach


    return 0; //all ok true
}
