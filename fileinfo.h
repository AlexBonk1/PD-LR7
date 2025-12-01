#pragma once

#include <QString>
#include<QDir>


class FileInfo
{
private:
    QDir dir;
    QString filename;
public:
    FileInfo(QDir dir,QString filename):dir(dir),filename(filename) {}
    QDir getDir() const;
    void setDir(const QDir &newDir);
    QString getFilename() const;
    void setFilename(const QString &newFilename);
    QString getCurrentFilePath();
};
