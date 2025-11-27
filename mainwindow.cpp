#include "mainwindow.h"
#include "imageeffectscontroller.h"
#include<QToolBar>
#include<QBoxLayout>
#include<QFileDialog>
#include<QActionGroup>
#include<QDir>
#include<QSpacerItem>
#include<QMessageBox>

void MainWindow::setupUi()
{
    resize(800,600);
    layout = new QVBoxLayout(this);
    setLayout(layout);
    menubar = new MenuBar(this);
    toolBar = new QToolBar(this);
    layout->addWidget(menubar);
    layout->addWidget(toolBar);
    //need to test this thing
    contentWidget= new ContentWidget(actionManager,this);
    secLayout = new QHBoxLayout(this);
    layout->addLayout(secLayout);
    scrollersWidget = new ScrollersWidget(this);
    secLayout->addWidget(contentWidget,3);
    secLayout->addWidget(scrollersWidget,3);
}


void MainWindow::setupConnectors()
{

    connect(actionManager->openfileAction(),&QAction::triggered,this,&MainWindow::loadImage);
    connect(actionManager->saveAction(),&QAction::triggered,this,[this](){
        int ret = QMessageBox::warning(this, tr("Image saving"),
                                       tr("Save changes?"),
                                       QMessageBox::Save | QMessageBox::Cancel);
        bool isSaved;
        switch(ret){
        case QMessageBox::Save:
            isSaved = ifc->saveImage();
            if(isSaved){
                setWindowTitle("LR7 File saved:"+curFileName);
            }
            break;
        case QMessageBox::Cancel:
            break;
        }
    });
    connect(actionManager->saveAsAction(),&QAction::triggered,this,[this](){
        QString filePath = QFileDialog::getSaveFileName(
            this,
            tr("Save picture as"),
            QString(ifc->getLastDir()+ "/" + ifc->getFileName()),
            tr("Images (*.png *.jpg,*.bmp,*.gif)")
        );
        qDebug()<<filePath;
        ifc->saveImage(filePath);
        qDebug()<<QFileInfo(filePath).absoluteDir();
        ifc->setDir(QFileInfo(filePath).absoluteDir());


    });

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void MainWindow::loadImage()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        ifc->getLastDir(),
        tr("Images (*.png *.jpg,*.bmp,*.gif)")
    );
    if(filePath == ""){
        qDebug()<<"Image not loaded: Escape Key pressed!";
        return;
    }
    qDebug()<<filePath;
    curFileName = filePath;
    setWindowTitle("LR7: File opened "+filePath);
    if(ifc->loadImage(filePath) == true){//in ifc we are storing image
        contentWidget->loadImage(ifc->getImage());
        scrollersWidget->loadImage(ifc->getImage());
        return;
    }
    curFileName = filePath;

}

MainWindow::MainWindow(IActionManager *actionManager, QWidget *parent): QWidget(parent)
    ,actionManager(actionManager)
{
    setupUi();
    ifc = new ImageEffectsController(this);
    qDebug()<<"Ui loaded succesful";
    setupMenu();
    setupToolBar();
    qDebug()<<"Menus loaded succesful";
    setupConnectors();
    loadImage();
    setupSubscribers();
    ifc->setupEffects();
}


void MainWindow::setupMenu()
{
    menubar->file->addAction(actionManager->openfileAction());
    menubar->file->addAction(actionManager->saveAction());
    menubar->file->addAction(actionManager->saveAsAction());

    // menubar->effects->addAction(actionManager->blurAction());
    // menubar->effects->addAction(actionManager->grayscaleAction());

}

void MainWindow::setupToolBar()
{
    toolBar->addAction(actionManager->undoAction());
    toolBar->addAction(actionManager->redoAction());

    toolBar->addAction(actionManager->scaleModeAction());
    toolBar->addAction(actionManager->rotateModeAction());

    QWidget* emptySpacer = new QWidget(this);
    emptySpacer->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
    toolBar->addWidget(emptySpacer);
    toolBar->addAction(actionManager->timerAction());
}

void MainWindow::setupSubscribers()
{
    connect(ifc,&ImageEffectsController::imageChanged,[this](){
        contentWidget->updateImage(ifc->getImage());
        scrollersWidget->updateImage(ifc->getImage());
    });
    connect(scrollersWidget,&ScrollersWidget::brightnessChanged,ifc,&ImageEffectsController::setOpacity);
    connect(scrollersWidget,&ScrollersWidget::redChanged,ifc,&ImageEffectsController::setRed);
    connect(scrollersWidget,&ScrollersWidget::greenChanged,ifc,&ImageEffectsController::setGreen);
    connect(scrollersWidget,&ScrollersWidget::blueChanged,ifc,&ImageEffectsController::setBlue);

    connect(ifc,&ImageEffectsController::addEffect,scrollersWidget,&ScrollersWidget::addEffect);
    connect(ifc,&ImageEffectsController::popEffect,scrollersWidget,&ScrollersWidget::removeEffect);

    connect(actionManager->undoAction(),&QAction::triggered,ifc,&ImageEffectsController::undo);

    connect(ifc,&ImageEffectsController::addAction,this,[this](QAction*action){
        menubar->effects->addAction(action);
    });

    connect(ifc,&ImageEffectsController::zeroScrollers,scrollersWidget,&ScrollersWidget::zeroScrollers);

}


