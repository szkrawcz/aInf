#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "dirgrinder.h"
#include <QDebug>
#include <QElapsedTimer>
#include <sqlgrinder.h>
#include <QtSql>

void ListFilesInDirectory(QDir dir);
void ListDirectory(QDir dir, bool Recurse);





int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   //counting time of execution
   QElapsedTimer timer;
   timer.start();


  // test2();
   QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
   //try{
   db.setDatabaseName( "./datagrinder.db" );
   /*if(! db.open() )
           {
            db.close();
            return 1; //something wrong false
           }

   } catch (...)
   {

   }*/
   db.open();
   db.transaction();
   QDir dir("C:/test");
   //QMultiMap<QString,FileAttributes> temp =  ListFilesInDirectoryTest(dir,1);
   //qDebug() <<  copyFilesAttHashTableToSqlLite(temp);
   //ListContentOfDirectory(dir, 1,1);


   scanDir(dir,db );


   db.commit();
   db.close();
   float executionTime = float(timer.elapsed()/1000);
  /*  QString FileName = "C:/test/MaintenanceTool.exe";
   GetFileMd5hash(FileName); */
   qDebug() << "\n";
   qDebug() << "execution time s = " << executionTime;
   return 0;
   //return a.exec();
}
