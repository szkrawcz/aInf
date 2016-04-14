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
            tempFileAttributes.md5Hash = GetFileMd5hash(fileInfo.absoluteFilePath());
            tempFileAttributes.lastModified  = fileInfo.lastModified();
            tempFileAttributes.lastRead = fileInfo.lastRead();
            tempFileAttributes.created = fileInfo.created();
            tempFileAttributes.isHidden =  fileInfo.isHidden();
            tempFileAttributes.size = fileInfo.size();
            tempFileAttributes.owner = fileInfo.owner();
           fileAttHashTable.insert(fileInfo.absoluteFilePath(),tempFileAttributes);
         //  std::cout << qPrintable(QString("lastModified=%1|").arg(fileInfo.absoluteFilePath()).arg(lastModified));// << std::endl;;
           std::cout <<  qPrintable(QString("lastModified=%1|").arg(lastModified));
           std::cout <<  qPrintable(QString("md5Hash=%1|").arg(tempFileAttributes.md5Hash));
           std::cout <<  qPrintable(QString("owner=%1|").arg(tempFileAttributes.owner));
           std::cout <<  qPrintable(QString("absoluteFilePath=%1\n").arg(tempFileAttributes.absoluteFilePath));

          // if (Hash) GetFileMd5hash(fileInfo.absoluteFilePath());
           //tempFileAttributes = null;
       }

    }







FileAttributes file1Attr;
file1Attr.fileName = "file name example";
//inserting valuse to hash table
//fileAttHashTable.insert("c:/file1",file1Attr);
//fileAttHashTable.insert("c:/file2",file1Attr);


//list all files hash
QSet<QString> keys = QSet<QString> :: fromList(fileAttHashTable.keys());
foreach (const QString keyvalue, keys)
{   //list all keys  . In this case list all files.
    FileAttributes tempAttributes ;
    tempAttributes = fileAttHashTable.value(keyvalue);
    //qDebug() << "keyvalue " << keyvalue << "attr" << tempAttributes.fileName;


}


return fileAttHashTable;


}


 QMultiMap<QString,FileAttributes>   test2(void)
 {
 QMultiMap<QString, FileAttributes> fileAttHashTable;
 FileAttributes file1Attr;
 file1Attr.fileName = "file name example";
 //inserting valuse to hash table
 fileAttHashTable.insert("c:/file1",file1Attr);
 fileAttHashTable.insert("c:/file2",file1Attr);


 //list all files hash
 QSet<QString> keys = QSet<QString> :: fromList(fileAttHashTable.keys());
 foreach (const QString keyvalue, keys)
 {   //list all keys  . In this case list all files.
     FileAttributes tempAttributes ;
     tempAttributes = fileAttHashTable.value(keyvalue);
     qDebug() << "keyvalue " << keyvalue << "attr" << tempAttributes.fileName;

   /*< QList<QString> values2 = FileHash1.values(keyvalue);
    for (int i = 0; i < values2.size(); ++i)
        cout << values2.at(i) << endl;
   */
}


 return fileAttHashTable;

 }


void test(void) //play around with QMultiMap

{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QMultiMap<QString, QString > FileHash1, FileDate;
    FileHash1.insert("c:\file.txt", "hash1 of file.txt");
    FileDate.insert("c:\file.txt","10/11/2015");

    FileHash1.insert("c:\file1.txt", "hash2");
    FileHash1.insert("c:\file2.txt", "hash3");


     //list all files hash
     QSet<QString> keys = QSet<QString> :: fromList(FileHash1.keys());
     foreach (const QString &keyvalue, keys)
     {   //list all keys  . In this case list all files.
         qDebug() << keyvalue;
        QList<QString> values2 = FileHash1.values(keyvalue);
        for (int i = 0; i < values2.size(); ++i)
            cout << values2.at(i) << endl;
     }
}


QString GetFileMd5hash(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QString hash = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex().constData();
        file.close();
      //  std::cout <<  hash.toStdString() << "\n";
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
       ListFilesInDirectoryTest(fileInfo.absoluteFilePath(),Hash);
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
              QDateTime date = fileInfo.lastModified();
              QString lastModified = date.toString();
              std::cout << qPrintable(QString("%1 lastModified=%2 ").arg(fileInfo.absoluteFilePath()).arg(lastModified));// << std::endl;;
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
