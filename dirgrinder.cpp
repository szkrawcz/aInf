#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "dirgrinder.h"



void FileHash(QString FileName )
{
    QFile file(FileName);
    QCryptographicHash crypto(QCryptographicHash::Sha1);

    if (file.open(QFile::ReadOnly))
    {
        while(!file.atEnd())
        {
          crypto.addData(file.read(8192));
         QByteArray hash = crypto.result();
        std::cout<< QString(hash.toHex()).toStdString() <<std::endl;
       }
     } else
    {
         std::cout << "file coulnt be open" << "\n";
    }
}



void ListContentOfDirectory(QDir dir, bool Recurse)
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

       std::cout << qPrintable(QString("%1").arg(fileInfo.absoluteFilePath()));
       std::cout << std::endl;
       ListFilesInDirectory(fileInfo.absoluteFilePath());
       QDir NextDir(fileInfo.absoluteFilePath());
       if (Recurse) ListContentOfDirectory(NextDir,Recurse);
       }
    }

}

void ListFilesInDirectory(QDir dir)
{
       dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
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
          std::cout << qPrintable(QString("%1").arg(fileInfo.absoluteFilePath()));
          std::cout << std::endl;
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
       QString str1 = fileInfo.fileName();
       QString str2 = ".";
       QString str3 = "..";
       if (!str1.compare(str2) || !str1.compare(str3) )
       {
           // std::cout <<  " found . or .. ";
       }
       else
       {
       std::cout << qPrintable(QString("%1").arg(fileInfo.absoluteFilePath()));
       std::cout << std::endl;
       QDir NextDir(fileInfo.absoluteFilePath());
       if (Recurse) ListDirectory(NextDir,1);
       }
    }


}
