#pragma once
#include<QWidget>
#include<QSlider>
#include<QLabel>
#include<QBoxLayout>

class SliderBox : public QWidget
{
    Q_OBJECT
private:
    QBoxLayout*layout;
    QSlider*slider;
    QLabel*label;
    QHBoxLayout *sliderLayout;
public:
    explicit SliderBox(QString sliderName,QWidget *parent = nullptr);
    void zeroSlider();
signals:
    void valueChanged(int value);
};
