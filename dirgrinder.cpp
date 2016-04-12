#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "dirgrinder.h"

QString GetFileMd5hash(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QString hash = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex().constData();
        file.close();
        std::cout <<  hash.toStdString() << "\n";
        return hash;
    }

    return "error geting md5 hash";
}






void ListContentOfDirectory(QDir dir, bool Recurse, bool Hash)
{
    //ListFilesInDirectory(dir);
    dir.setFilter(  QDir::Hidden | QDir::NoSymLinks |QDir::AllDirs );
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {

       QFileInfo fileInfo = list.at(i);
       QString str1 = fileInfo.fileName();
       QString str2 = ".";
       QString str3 = "..";
       if (!str1.compare(str2) || !str1.compare(str3) )
       {
           // std::cout <<  " found . or .. ";
       }
       else
       {

       std::cout << qPrintable(QString("%1  ").arg(fileInfo.absoluteFilePath()));
       std::cout << std::endl;
       ListFilesInDirectory(fileInfo.absoluteFilePath(),Hash);
       QDir NextDir(fileInfo.absoluteFilePath());
      if (Recurse) ListContentOfDirectory(NextDir,Recurse,Hash);
       }
    }

}

void ListFilesInDirectory(QDir dir, bool Hash)
{
       dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
       dir.setSorting(QDir::Size | QDir::Reversed);
       QFileInfoList list = dir.entryInfoList();
       for (int i = 0; i < list.size(); ++i)
       {
          QFileInfo fileInfo = list.at(i);
          if (fileInfo.isFile())
          {
              std::cout << qPrintable(QString("%1 ").arg(fileInfo.absoluteFilePath()));// << std::endl;;
              if (Hash) GetFileMd5hash(fileInfo.absoluteFilePath());
          }

       }
}

// ListDirectory list for given path
void ListDirectory(QDir dir, bool Recurse)
{
    dir.setFilter(  QDir::Hidden | QDir::NoSymLinks |QDir::AllDirs );
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
       QFileInfo fileInfo = list.at(i);
       if (fileInfo.isFile())
       {
       std::cout << qPrintable(QString("%1").arg(fileInfo.absoluteFilePath()))  << std::endl;
       QDir NextDir(fileInfo.absoluteFilePath());
       if (Recurse) ListDirectory(NextDir,1);
       }
    }


}
