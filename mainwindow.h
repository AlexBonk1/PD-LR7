#pragma once

#include<QWidget>
#include "actionmanager.h"
#include "imageeffectscontroller.h"
#include"menubar.h"
#include"contentwidget.h"
#include"scrollerswidget.h"
#include<QMouseEvent>



class MainWindow : public QWidget
{
    Q_OBJECT
/// UI
private:
    void setupUi();
    MenuBar*menubar;
    QToolBar*toolBar;
    QVBoxLayout*layout;
    ContentWidget*contentWidget;
    ScrollersWidget*scrollersWidget;
    QHBoxLayout*secLayout;
private:
    ImageEffectsController* ifc;
    IActionManager*actionManager;
    QString curFileName;
    void setupConnectors();
protected:
    void mouseDoubleClickEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
public:
    void loadImage();
    MainWindow(IActionManager*actionManager,QWidget *parent = nullptr);
    QString getDir();
    // ~MainWindow();

private:
    void setupMenu();
    void setupToolBar();
    void setupSubscribers();
};
