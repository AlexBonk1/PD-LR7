#pragma once

#include "imageeffectscontroller.h"
#include "sliderbox.h"
#include "stacklist.h"
#include <QWidget>
#include <qboxlayout.h>
#include <qabstractscrollarea.h>
#include<QSlider>
#include<QLabel>
#include <qlistwidget.h>

class ScrollersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollersWidget(QWidget *parent = nullptr);
    QImage getImage() const;
    void loadImage(QImage image);
    void updateImage(QImage image) {qDebug()<<"ScrollersWidget update image not implemented";};
    void addEffect(QString effectName);
    void removeEffect();
    void zeroScrollers();
    void deleteFirstEffect();
    void deleteAllEffects();
private:
    void setupUi();
    void setupConnect();
    QVBoxLayout*layout;
    SliderBox*redScaleBox;
    SliderBox*greenScaleBox;
    SliderBox*blueScaleBox;
    SliderBox*brightnessBox;
    StackList*listWidget;
private:
    QImage image;
    int sliderValue;

signals:
    void brightnessChanged(int value);
    void redChanged(int value);
    void greenChanged(int value);
    void blueChanged(int value);
};
