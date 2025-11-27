#pragma once

#include "iactionmanager.h"

#include <QObject>
#include<QAction>
#include <qmenubar.h>
#include <qtoolbar.h>

class ActionManager : public QObject,public IActionManager
{
    Q_OBJECT
//some setup functions
private:
    void setupActions();
private:
    QAction*scaleMode;
    QAction*undo;
    QAction*redo;
    QAction *open;
    QAction *save;
    QAction *saveAs;
    QAction *scalePlus;
    QAction *scaleMinus;
    QAction *blur;
    QAction *grayscale;
    QAction*rotateMode;
    QAction *rotateLeft;
    QAction *rotateRight;
    QAction*timer = nullptr;
    QActionGroup*editorModes;
public:
    explicit ActionManager(QObject *parent = nullptr);

signals:
    // IActionManager interface
public:
    QAction *scaleModeAction() const override{return scaleMode;}
    QAction *undoAction() const override{return undo;}
    QAction *redoAction() const override{return redo;}
    QAction *openfileAction() const override {return open;}
    QAction *saveAction() const override{return save;}
    QAction *saveAsAction() const override{return saveAs;}
    QAction *scalePlusAction() const override{return scalePlus;}
    QAction *scaleMinusAction() const override{return scaleMinus;}
    QAction *blurAction() const override{return blur;}
    QAction *grayscaleAction() const override{return grayscale;}
    QAction *rotateLeftAction() const override{return rotateLeft;}
    QAction *rotateRightAction() const override{return rotateRight;}
    QAction *timerAction() const override{return timer;}

    // IActionManager interface
public:
    //пока что лень делать
    QAction *rotateModeAction() const override{return rotateMode;}
};
