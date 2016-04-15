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
#include <QtSql>


bool copyFilesAttHashTableToSqlLite(QMultiMap<QString,FileAttributes> fileAttHashTable)
{

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    try{
    db.setDatabaseName( "./datagrinder.db" );
    if(! db.open() )
            {
             db.close();
             return 0; //something wrong false
            }

    } catch (...)
    {

    }

    qDebug( "Connected to SqlLite DB" );
    QSqlQuery qry;
    QString sqlCmd;
    qry.prepare( QString("CREATE TABLE IF NOT EXISTS filesScannedTemp ( absoluteFilePath VARCHAR(65536),  ")
                 + "fileName VARCHAR(255),"
                 + "filePath VARCHAR(255),"
                 + "md5Hash  VARCHAR(500),"
                 + "lastModified VARCHAR(50),"
                 + "lastRead VARCHAR(50),"
                 + "created VARCHAR(50),"
                 + "isHidden VARCHAR(50),"
                 + "size VARCHAR(50),"
                 + "owner VARCHAR(50))");
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug() << "Table created!";



    //list all files from hash table
    QSet<QString> keys = QSet<QString> :: fromList(fileAttHashTable.keys());
    foreach (const QString keyvalue, keys)
    {   //list all keys  . In this case list all files.
        FileAttributes tempAttributes ;
        tempAttributes = fileAttHashTable.value(keyvalue);

        //qDebug() << "keyvalue " << keyvalue << "attr" << tempAttributes.fileName;
     //   qDebug() << tempAttributes.absoluteFilePath;

    //  sqlCmd = "INSERT INTO filesScannedTemp ( absoluteFilePath, fileName) VALUES ('"  + tempAttributes.absoluteFilePath + "', 'file.txt')" );
        sqlCmd = "INSERT INTO filesScannedTemp ( absoluteFilePath,fileName,filePath,md5Hash,lastModified,lastRead,created,isHidden,size,owner) VALUES ('"
                  + QString(tempAttributes.absoluteFilePath) + "',"
                  + "'" + QString(tempAttributes.fileName) + "',"
                  + "'" + QString(tempAttributes.filePath) + "',"
                  + "'" + QString(tempAttributes.md5Hash) + "',"
                  + "'" + QString(tempAttributes.lastModified.toString()) + "',"
                  + "'" + QString(tempAttributes.lastRead.toString()) + "',"
                  + "'" + QString(tempAttributes.created.toString()) + "',"
                  + "'" + QString::number(tempAttributes.isHidden) + "',"
                  + "'" + QString::number(tempAttributes.size) + "',"
                  + "'" + QString(tempAttributes.owner) +  "')" ;
      //  qDebug() << sqlCmd;
         qry.prepare( sqlCmd );

         if( !qry.exec() )
      qDebug() << qry.lastError();
    //else
     // qDebug( "Inserted!" );
    } //end foreach

    db.close();
    return 1; //all ok true
}
