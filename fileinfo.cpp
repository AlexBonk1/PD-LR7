#include "fileinfo.h"

QString FileInfo::getFilename() const
{
    return filename;
}

void FileInfo::setFilename(const QString &newFilename)
{
    filename = newFilename;
}

QString FileInfo::getCurrentFilePath()
{
    return dir.path()+"/"+filename;
}

QDir FileInfo::getDir() const
{
    return dir;
}

void FileInfo::setDir(const QDir &newDir)
{
    dir = newDir;
}
