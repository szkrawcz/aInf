#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "dirgrinder.h"

void ListFilesInDirectory(QDir dir);
void ListDirectory(QDir dir, bool Recurse);





int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
   QDir dir("C:/Users/Administrator/Downloads");
  //ListDirectory(dir, true);
   //ListFilesInDirectory(dir);
   ListFilesInDirectory(dir);
   ListContentOfDirectory(dir, 1);
  //  QFile plik("/home/szymon/c/main");


   QString FileName = "/home/szymon/c/main";
   FileHash(FileName);


   return 0;
   //return a.exec();
}
