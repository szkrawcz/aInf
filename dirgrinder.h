#include <QCoreApplication>
#include <Qdate>
void ListFilesInDirectory(QDir dir, bool Hash);
void ListDirectory(QDir dir, bool Recurse);
void ListContentOfDirectory(QDir dir, bool Recurse, bool Hash);
QString HashFile(QString path);
void test(void);


struct FileAttributes
{
    QString absoluteFilePath;
    QString fileName;
    QString filePath;
    QString md5Hash;
    QDate lastModified;
    QDate lastRead;
    QDateTime created;
    bool isHidden;
    qint64 size;
};
