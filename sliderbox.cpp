#include "sliderbox.h"

const int SliderMin = -255;
const int SliderMax = 255;


SliderBox::SliderBox(QString sliderName,QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout(this);
    setLayout(layout);
    label = new QLabel(sliderName,this);
    slider = new QSlider(Qt::Orientation::Horizontal,this);
    slider->setValue(0);
    slider->setRange(SliderMin,SliderMax);
    slider->setTickPosition(QSlider::TicksBelow);
    layout->addWidget(label);
    sliderLayout = new QHBoxLayout(this);
    sliderLayout->addWidget(new QLabel(QString("%1").arg(SliderMin)));
    sliderLayout->addWidget(slider);
    sliderLayout->addWidget(new QLabel(QString("%1").arg(SliderMax)));
    layout->addLayout(sliderLayout);
    // layout->addWidget(slider);

    connect(slider,&QSlider::valueChanged,this,[this](int value){
        emit valueChanged(value);
    });
}

void SliderBox::zeroSlider()
{
    slider->blockSignals(true);
    slider->setValue(0);
    slider->blockSignals(false);
}
