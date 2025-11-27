#include "menubar.h"


MenuBar::MenuBar(QWidget *parent): QMenuBar(parent)
{
    setupUi();
}

void MenuBar::setupUi()
{
    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    file = new QMenu("file",this);
    editor = new QMenu("Editor",this);
    effects = new QMenu("Effects",this);
    addMenu(file);
    addMenu(editor);
    addMenu(effects);
    // this->addWidget(spacer);
    // this->addAction(new QAction("open new",this));
    // this->addAction(new QAction("save",this));
    // this->addAction(new QAction("delete",this));
}

