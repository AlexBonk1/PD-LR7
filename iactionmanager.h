#pragma once

#include <qaction.h>
class IActionManager
{
public:
    virtual QAction*scaleModeAction() const=0;
    virtual QAction*rotateModeAction() const=0;

    virtual QAction *undoAction() const=0;
    virtual QAction *redoAction() const = 0;
    virtual QAction *openfileAction() const=0;
    virtual QAction *saveAction() const = 0;
    virtual QAction *saveAsAction() const=0;
    virtual QAction *scalePlusAction() const=0;
    virtual QAction *scaleMinusAction() const=0;
    //одноразовое действие
    virtual QAction *blurAction() const=0;
    //одноразовое действие
    virtual QAction *grayscaleAction() const=0;

    virtual QAction *rotateLeftAction() const =0;
    virtual QAction *rotateRightAction() const =0;
    //ассемблеровский таймер
    virtual QAction *timerAction() const =0;


    // virtual QActionGroup *editGroup() const =0;
    IActionManager();
};
