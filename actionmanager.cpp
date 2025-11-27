#include "actionmanager.h"
#include <qactiongroup.h>

void ActionManager::setupActions(){

    scaleMode = new QAction(QIcon(),tr("Scale Mode"),this);
    scaleMode->setCheckable(true);

    rotateMode = new QAction(QIcon(),tr("Rotate Mode"),this);
    rotateMode->setCheckable(true);

    editorModes = new QActionGroup(this);
    editorModes->addAction(scaleMode);
    editorModes->addAction(rotateMode);


    undo = new QAction(QIcon(), tr("Undo"), this);
    undo->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));

    redo = new QAction(QIcon(), tr("Redo"), this);
    redo->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));

    open = new QAction(QIcon(), tr("Open file"), this);
    open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    save = new QAction(QIcon(), tr("Save"), this);
    save->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    saveAs = new QAction(QIcon(), tr("Save as ..."), this);
    saveAs->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

    scalePlus = new QAction(QIcon(), tr("Scale+"), this);
    scalePlus->setShortcut(QKeySequence(Qt::Key_Plus));

    scaleMinus = new QAction(QIcon(), tr("Scale-"), this);
    scaleMinus->setShortcut(QKeySequence(Qt::Key_Plus));

    blur = new QAction(QIcon(), tr("Blur"), this);
    blur->setCheckable(true);

    grayscale = new QAction(QIcon(), tr("Gray Scale"), this);
    grayscale->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
    grayscale->setCheckable(true);

    rotateLeft = new QAction(QIcon(), tr("Rotate 90 left"), this);
    redo->setShortcut(QKeySequence(Qt::Key_A));


    rotateRight = new QAction(QIcon(), tr("Rotate 90 right"), this);\
    rotateRight->setShortcut(QKeySequence(Qt::Key_D));

    timer = new QAction(QIcon(), tr("Assembly timer"), this);
    redo->setShortcut(QKeySequence(Qt::Key_T));
    rotateLeft->setCheckable(true);

    auto childrens = this->findChildren<QAction*>();
    for(auto child : childrens){
        if(child == nullptr){
            qDebug()<<"Cannot find definition for child";
            throw std::exception();
        }
    }
}



ActionManager::ActionManager(
    QObject *parent)
    : QObject{parent}
{
    setupActions();
}




