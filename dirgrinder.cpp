#include <QCoreApplication>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "dirgrinder.h"
#include "sqlgrinder.h"
#include <QCoreApplication>
#include <QStringList>
#include <iostream>
#include <QTextStream>
#include <QDebug>
#include <QDate>
#include <QtSql>




QMultiMap<QString,FileAttributes> ListFilesInDirectoryTest(QDir dir, bool Hash)
{
    extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;
    qt_ntfs_permission_lookup++; // turn checking on
    QMultiMap<QString, FileAttributes> fileAttHashTable; //making hash table to store file attributes
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
       QFileInfo fileInfo = list.at(i);
       if (fileInfo.isFile())
       {
           FileAttributes tempFileAttributes;
           QDateTime date = fileInfo.lastModified();
           QString lastModified = date.toString();

            tempFileAttributes.absoluteFilePath = fileInfo.absoluteFilePath();
            tempFileAttributes.fileName = fileInfo.fileName();
            tempFileAttributes.filePath= fileInfo.path();
            if (Hash) tempFileAttributes.md5Hash = GetFileMd5hash(fileInfo.absoluteFilePath());
            tempFileAttributes.lastModified  = fileInfo.lastModified();
            tempFileAttributes.lastRead = fileInfo.lastRead();
            tempFileAttributes.created = fileInfo.created();
            tempFileAttributes.isHidden =  fileInfo.isHidden();
            tempFileAttributes.size = fileInfo.size();
            tempFileAttributes.owner = fileInfo.owner();
            fileAttHashTable.insert(fileInfo.absoluteFilePath(),tempFileAttributes);
       }

    }
return fileAttHashTable;
}



QString GetFileMd5hash(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        //reading hash file is limited to 20MB = 2621440 bytes
        QString hash = QCryptographicHash::hash(file.read(2621440), QCryptographicHash::Md5).toHex().constData();
        file.close();
        //std::cout <<  hash.toStdString() << "\n";
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
       ListFilesInDirectory(dir,Hash);
       QDir NextDir(fileInfo.absoluteFilePath());
       if (Recurse)
           {
              ListContentOfDirectory(NextDir,Recurse,Hash);
              ListFilesInDirectory(dir,Hash);
           }
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
              QDateTime date = fileInfo.lastModified();
              QString lastModified = date.toString();
              std::cout << qPrintable(QString("%1 lastModified=%2 ").arg(fileInfo.absoluteFilePath()).arg(lastModified)) << std::endl;
              if (Hash) GetFileMd5hash(fileInfo.absoluteFilePath());
          }

       }
}



void scanDir(QDir dir,   QSqlDatabase db, QDateTime currentDateTime )
{
   // dir.setNameFilters(QStringList("*.nut"));
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks| QDir::Hidden );

    QStringList fileList = dir.entryList();
    QMultiMap<QString,FileAttributes> temp =  ListFilesInDirectoryTest(dir.path(),0);
    copyFilesAttHashTableToSqlLite(temp,db,currentDateTime);

    dir.setFilter(QDir::AllDirs | QDir::Hidden | QDir::NoDotAndDotDot| QDir::NoSymLinks);
    QStringList dirList = dir.entryList();

    for (int i=0; i<dirList.size(); ++i)
    {
        QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(dirList.at(i));
        scanDir(QDir(newPath),db,currentDateTime);
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
