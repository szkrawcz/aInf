#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "dirgrinder.h"
#include <QDebug>
#include <QElapsedTimer>


void ListFilesInDirectory(QDir dir);
void ListDirectory(QDir dir, bool Recurse);





int main(int argc, char *argv[])
{
   QElapsedTimer timer;
   timer.start();

   QCoreApplication a(argc, argv);
   QDir dir("C:/");
  //ListDirectory(dir, true);
   //ListFilesInDirectory(dir);
   ListFilesInDirectory(dir,1);
   ListContentOfDirectory(dir, 1,1);
  //  QFile plik("/home/szymon/c/main");


   QString FileName = "C:/test/MaintenanceTool.exe";
 //  FileHash(FileName);
 //  HashFile(FileName);

   qDebug() << timer.elapsed();
   return 0;
   //return a.exec();
}
