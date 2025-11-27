#pragma once

#include <QToolBar>
#include<QMenu>
#include<QMenuBar>

class MenuBar : public QMenuBar
{
public:
    MenuBar(QWidget*parent = nullptr);
    QMenu*file;
    QMenu*editor;
    QMenu*effects;
private:
    void setupUi();
};
