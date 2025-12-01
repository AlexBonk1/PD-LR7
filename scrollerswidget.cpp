#include "scrollerswidget.h"
#include "sliderbox.h"
#include<QBoxLayout>
#include<QListWidget>
#include<QStackedWidget>

ScrollersWidget::ScrollersWidget(
    QWidget *parent)
    : QWidget{parent}
{
    setupUi();
    setupConnect();
}

void ScrollersWidget::setupUi()
{
    setMinimumSize(400,450);
    layout = new QVBoxLayout(this);
    setLayout(layout);
    redScaleBox = new SliderBox("Red scale",this);
    greenScaleBox = new SliderBox("Green scale",this);
    blueScaleBox = new SliderBox("Blue scale",this);
    brightnessBox = new SliderBox("Opacity",this);
    QLabel*effectChain = new QLabel("Effect chain",this);
    listWidget = new StackList(this);
    // listWidget->set


    layout->addWidget(redScaleBox);
    layout->addWidget(greenScaleBox);
    layout->addWidget(blueScaleBox);
    layout->addWidget(brightnessBox);
    layout->addWidget(effectChain);
    layout->addWidget(listWidget);
    // layout->addWidget(listWidget);
    // layout->addWidget(opacityBox);
}

//проброска событий
void ScrollersWidget::setupConnect()
{
    //если больше то +яркость, если меньше - то
    connect(brightnessBox,&SliderBox::valueChanged,this,[this](int value){
        emit brightnessChanged(value);
    });
    connect(redScaleBox,&SliderBox::valueChanged,this,[this](int value){
        emit redChanged(value);
    });
    connect(greenScaleBox,&SliderBox::valueChanged,this,[this](int value){
        emit greenChanged(value);
    });
    connect(blueScaleBox,&SliderBox::valueChanged,this,[this](int value){
        emit blueChanged(value);
    });
    connect(redScaleBox,&SliderBox::valueChanged,this,[this](int value){
        emit redChanged(value);
    });
}

QImage ScrollersWidget::getImage() const
{
    return image;
}

void ScrollersWidget::loadImage(QImage image)
{

}

void ScrollersWidget::addEffect(QString effectName)
{
    listWidget->push(effectName);
}

void ScrollersWidget::removeEffect()
{
    listWidget->pop_back();
}

void ScrollersWidget::zeroScrollers()
{
    redScaleBox->zeroSlider();
    greenScaleBox->zeroSlider();
    blueScaleBox->zeroSlider();
    brightnessBox->zeroSlider();
}

void ScrollersWidget::deleteFirstEffect()
{
    listWidget->pop_front();
}

void ScrollersWidget::deleteAllEffects()
{
    listWidget->clear();
}
