#pragma once
#include "Effects/abstracteffect.h"
#include <QDir>
#include <QImage>
#include <QObject>
#include<QTimer>
#include <QElapsedTimer>
#include<QMessageBox>
#include <QDebug>


class BadImageException
{
public:
    BadImageException() {}
};



//ImageFileController stores image and stack that we need to implement undo/redo operations
struct RGBA{
  RGBA(int red, int green, int blue, int opacity)
      : red(red), green(green), blue(blue), opacity(opacity) {}
  int red;
  int green;
  int blue;
  int opacity;
};


class FileInfo
{
private:
    QDir dir;
    QString filename;
public:
    FileInfo(QDir dir,QString filename):dir(dir),filename(filename) {}
};


//empty classes may be needed in refactoring to prent GOD class anti-pattern
class ImageInfo
{
public:
    ImageInfo() {}
};

class ImageEffectsController: public  QObject
{
    Q_OBJECT
private:
    bool isEditColors = false;
    RGBA rgba;
    // QImage originalImage;
    QImage image;
    QDir dir;
    QString fileName;
    QVector<QImage> states;
    QVector<Effect*>effects;
    int row;
    int col;
    QTimer*passed;
    bool isImageDirty;
    void setupEffect(QString name,QString description,_Func func =0 ,QKeySequence key = 0);
public:
    void setupEffects();
    void setRed(int value);
    void setBlue(int value);
    void setGreen(int value);
    void setOpacity(int value);
    ImageEffectsController(QObject*obj = nullptr);
    void triggerEffect(Effect*effect);
    void editColors();
    void applyEffect();
    void undo();
    bool loadImage(QString filename);
    bool saveImage(QString filepath = "");
    void reset();
    void rotateLeft();
    void rotateRight();
    QImage getImage() const;

    QString getLastDir() const;
    ~ImageEffectsController();
    void setDir(const QDir &newDir);

    QString getFileName() const;

signals:
    void imageChanged();//subscriper signal when image changed we renew it in the all needed widgets
    void addAction(QAction*action);
    void addEffect(QString name);
    void popEffect();
    void zeroScrollers();
};
