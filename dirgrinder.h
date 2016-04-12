#include <QCoreApplication>
void ListFilesInDirectory(QDir dir, bool Hash);
void ListDirectory(QDir dir, bool Recurse);
void ListContentOfDirectory(QDir dir, bool Recurse, bool Hash);
QString HashFile(QString path);
