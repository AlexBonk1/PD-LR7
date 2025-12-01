#include "contentwidget.h"
#include<QPushButton>
#include<QSpacerItem>

static int brightnessStep = 2;

//так как ContentWidget = image view, то он будет отвечать за функцию scale
ContentWidget::ContentWidget(IActionManager *actionManager, QWidget *parent)
    :QWidget{parent},actionManager{actionManager}
{
    setupUi();
    setupConnections();
}



void ContentWidget::setupUi()
{
    scaleF = 1;
    QWidget* header = new QWidget(this);
    header->setLayout(new QHBoxLayout(header));
    QPushButton* scalePlusBut = new QPushButton("+",this);
    connect(scalePlusBut, &QPushButton::clicked, actionManager->scalePlusAction(), &QAction::trigger);
    percentages = new QLineEdit("100%", this);
    percentages->setReadOnly(true);
    QPushButton* scaleMinusBut = new QPushButton("-",this);
    connect(scaleMinusBut, &QPushButton::clicked, actionManager->scaleMinusAction(), &QAction::trigger);
    QSpacerItem* spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QPushButton* rotateLeftButton = new QPushButton("rL",this);
    connect(rotateLeftButton, &QPushButton::clicked, actionManager->rotateLeftAction(), &QAction::trigger);
    QPushButton* rotateRightButton = new QPushButton("rR",this);
    connect(rotateRightButton, &QPushButton::clicked, actionManager->rotateRightAction(), &QAction::trigger);

    header->layout()->addWidget(scalePlusBut);
    header->layout()->addWidget(percentages);
    header->layout()->addWidget(scaleMinusBut);
    header->layout()->addItem(spacer);
    header->layout()->addWidget(rotateRightButton);
    header->layout()->addWidget(rotateLeftButton);

    label = new QLabel(this);
    scrollArea = new QScrollArea(this);
    scrollArea->setMinimumSize(600,450);
    label->setPixmap(pixmap);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(label);
    layout = new QVBoxLayout(this);
    setLayout(layout);

    layout->addWidget(header);
    layout->addWidget(scrollArea);
}

void ContentWidget::setupConnections()
{
    connect(actionManager->scaleModeAction(),&QAction::triggered,this,[this](){
        qDebug()<<"scale+";
        editMode = EditMode::Scale;
    });
    connect(actionManager->scalePlusAction(),&QAction::triggered,this,[this](){
        qDebug()<<"scale+";
        scalePositive();
    });
    connect(actionManager->scaleMinusAction(),&QAction::triggered,this,[this](){
        qDebug()<<"scale-";
        scaleNegative();
    });

}


void ContentWidget::imageToPixmap()
{
    pixmap = QPixmap::fromImage(image);
    scaleImage(scaleF);
    if(pixmap.isNull()){
        qDebug()<<"Cannot load image! Try Again";
        return;
    }
    label->setPixmap(pixmap);
    label->adjustSize();
}


bool ContentWidget::loadImage(const QImage &image)
{
    this->image = image;

    scaleF = 1;
    if(image.isNull()){
        qDebug()<<"Bad image!";
        return false;
    }
    imageToPixmap();
    return true;
}

bool ContentWidget::updateImage(const QImage &image)
{
    this->image = image;
    if(image.isNull()) return false;
    imageToPixmap();
    return true;
}

void ContentWidget::scaleImage(double ratio)
{
    pixmap = QPixmap::fromImage(image);
    if(ratio != 1){
    pixmap = pixmap.scaled(
        image.width()*ratio,
        image.height()*ratio,
        Qt::KeepAspectRatio,            // KEY: Preserve the width/height ratio
        Qt::SmoothTransformation        // KEY: Use the best quality algorithm
        );
    }
    qDebug()<<pixmap.size();
    label->setPixmap(pixmap);
    label->adjustSize();
    percentages->setText(QString("%0 %").arg((int)(ratio*100)));
}

void ContentWidget::setScale()
{
    isScaling = true;
    qDebug()<<"scaling setted";
}

void ContentWidget::scalePositive()
{
    if(scaleF - 0.5*sizeAdjustment < 1e-5){
        scaleF = sizeAdjustment;
    }
    else{
        scaleF+=sizeAdjustment;
    }
    scaleImage(scaleF);
}

void ContentWidget::scaleNegative()
{
    qDebug()<<"RMB scale!";
    if(scaleF - sizeAdjustment < 1e-5){
        scaleF/=2;
    }
    else{
        scaleF-=sizeAdjustment;
    }
    scaleImage(scaleF);
}


void ContentWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(editMode == EditMode::Scale){
        scalePositive();
    }
    // QWidget::mouseDoubleClickEvent(event);
}

void ContentWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<image.format();
    if(event->button() == Qt::RightButton && editMode == EditMode::Scale){
        qDebug()<<"scale negative";
        scaleNegative();
    }
    QWidget::mousePressEvent(event);
}

void ContentWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    if(editMode == EditMode::Scale && event->key() == Qt::Key_Control){
        qDebug()<<"Ctrl pressed";
        isscrollScaling = true;
    }
    QWidget::keyPressEvent(event);
}

void ContentWidget::keyReleaseEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    if(event->key() == Qt::Key_Control){
        qDebug()<<"Ctrl released";
    }
    QWidget::keyReleaseEvent(event);
}
