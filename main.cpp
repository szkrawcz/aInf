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

   QDir dir("C:/windows");
   //QMultiMap<QString,FileAttributes> temp =  ListFilesInDirectoryTest(dir,1);
   //qDebug() <<  copyFilesAttHashTableToSqlLite(temp);
   //ListContentOfDirectory(dir, 1,1);


   scanDir(dir,db );





  /*  QString FileName = "C:/test/MaintenanceTool.exe";
   GetFileMd5hash(FileName); */
   qDebug() << "\n";
   qDebug() << "execution time = " << timer.elapsed();
   return 0;
   //return a.exec();
}
