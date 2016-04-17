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



bool copyFilesAttHashTableToSqlLite(QMultiMap<QString,FileAttributes> fileAttHashTable,QSqlDatabase db )
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
                 + "owner VARCHAR(50))");

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

        //qDebug() << "keyvalue " << keyvalue << "attr" << tempAttributes.fileName;
     //   qDebug() << tempAttributes.absoluteFilePath;
  //    qDebug() << "recived file info  " << QString(tempAttributes.absoluteFilePath);
    //  sqlCmd = "INSERT INTO filesScannedTemp ( absoluteFilePath, fileName) VALUES ('"  + tempAttributes.absoluteFilePath + "', 'file.txt')" );
        sqlCmd = "INSERT INTO filesScannedTemp ( absoluteFilePath,fileName,filePath,md5Hash,lastModified,lastRead,created,isHidden,size,owner) "
                 "VALUES (:absoluteFilePath,:fileName,:filePath,:md5Hash,:lastModified,:lastRead,:created,:isHidden,:size,:owner)";
        qry.bindValue(":absoluteFilePath", QString(tempAttributes.absoluteFilePath));
        qry.bindValue(":fileName", QString(tempAttributes.fileName));


        /*          + QString(tempAttributes.absoluteFilePath) + "',"
                  + "'" + QString(tempAttributes.fileName) + "',"
                  + "'" + QString(tempAttributes.filePath) + "',"
                  + "'" + QString(tempAttributes.md5Hash) + "',"
                  + "'" + QString(tempAttributes.lastModified.toString(dateFormat)) + "',"
                  + "'" + QString(tempAttributes.lastRead.toString(dateFormat)) + "',"
                  + "'" + QString(tempAttributes.created.toString(dateFormat)) + "',"
                  + "'" + QString::number(tempAttributes.isHidden) + "',"
                  + "'" + QString::number(tempAttributes.size) + "',"
                  + "'" + QString(tempAttributes.owner) +  "')" ;*/

       /* QSqlQuery query;
        query.prepare("INSERT INTO contacts (id, first_name, last_name) "
                      "VALUES (:id, :first_name, :last_name)");
        query.bindValue(":id", 1001);
        query.bindValue(":first_name", first_name);
        query.bindValue(":last_name", last_name);
        query.exec();
        */



        //  qDebug() << sqlCmd;
         qry.prepare( sqlCmd );
       //tracing insert time
         QElapsedTimer timer;
         timer.start();
        if( !qry.exec() )
        {
      qDebug() << qry.lastError();
         qDebug() << sqlCmd;
        }
      //  qDebug() << "insert  time ms = " << timer.elapsed();

        //else
    // qDebug( "Inserted!" );

    } //end foreach

   // db.close();

    return 0; //all ok true
}
