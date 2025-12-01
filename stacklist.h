#pragma once

#include <qlistwidget.h>

class StackList: public QListWidget
{
public:
    StackList(QWidget*parent = nullptr);
    void push(QString item);
    QListWidgetItem* pop_back();
    QListWidgetItem* pop_front();
};
