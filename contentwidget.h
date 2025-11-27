#pragma once

#include "actionmanager.h"
#include <QWidget>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qscrollarea.h>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QScrollEvent>


enum class EditMode{
    Scale,
    Rotate,
};


const double sizeAdjustment = 0.2;


class ContentWidget : public QWidget
{
    Q_OBJECT
///UI
private:
    void setupUi();
    void setupConnections();
    QImage image;
    QPixmap pixmap;
    QScrollArea* scrollArea;
    QLabel* label;
    QVBoxLayout*layout;
    bool isScaling =false;
    bool isRotating= false;
private:
    IActionManager*actionManager;
    QString filename;
    double scaleF;
    bool isscrollScaling = false;
    void imageToPixmap();
public:
    EditMode editMode;
    ContentWidget(IActionManager*actionManager,QWidget *parent = nullptr);
    bool loadImage(const QImage &image);
    bool updateImage(const QImage &image);
    void scaleImage(double ratio);
    void setScale();
    void scalePositive();
    void scaleNegative();
    void rotatePositive();
    void rotateNegative();
    // void setRotate();
protected:
    void mouseDoubleClickEvent(QMouseEvent*event) override;
    void mousePressEvent(QMouseEvent*event) override;
    void keyPressEvent(QKeyEvent*event) override;
    void keyReleaseEvent(QKeyEvent*event) override;
    // void whellEvent(QWheelEvent*event) override;
signals:

};
