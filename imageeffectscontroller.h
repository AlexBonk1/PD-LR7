#pragma once

#include <QDir>
#include <QImage>
#include <QObject>
#include<QTimer>
#include <QElapsedTimer>
#include<QMessageBox>
#include <QDebug>

#include"fileinfo.h"
#include "Effects/abstracteffect.h"

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
    std::unique_ptr<FileInfo> fileinfo;
    RGBA rgba;
    bool isEditColors = false;
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
    void undo();
    void setupEffects();
    void setRed(int value);
    void setBlue(int value);
    void setGreen(int value);
    void setOpacity(int value);
    ImageEffectsController(QObject*obj = nullptr);
    void triggerEffect(Effect*effect);
    void editColors();
    bool loadImage(QString filename);
    bool saveImage(QString filepath = "");
    void reset();
    void rotateLeft();
    void rotateRight();
    QImage getImage() const;
    void setDir(const QDir &newDir);
    QString getCurrentPath();
    ~ImageEffectsController();
signals:
    void imageChanged();//subscriper signal when image changed we renew it in the all needed widgets
    void addAction(QAction*action);
    void addEffect(QString name);
    void popEffect();
    void zeroScrollers();
    void deleteFirstInChain();
    void deleteAllInChain();
};
