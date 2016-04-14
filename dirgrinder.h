#include <QCoreApplication>
#include <Qdate>

struct FileAttributes;
void ListFilesInDirectory(QDir dir, bool Hash);
QMultiMap<QString,FileAttributes> ListFilesInDirectoryTest(QDir dir, bool Hash);
void ListDirectory(QDir dir, bool Recurse);
void ListContentOfDirectory(QDir dir, bool Recurse, bool Hash);
QString GetFileMd5hash(QString path);
QString HashFile(QString path);
void test(void);

QMultiMap<QString,FileAttributes>   test2(void);

struct FileAttributes
{
    QString absoluteFilePath;
    QString fileName;
    QString filePath;
    QString md5Hash;
    QDateTime lastModified;
    QDateTime lastRead;
    QDateTime created;
    bool isHidden;
    qint64 size;
    QString owner;
};
