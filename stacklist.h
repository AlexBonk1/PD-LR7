#pragma once

#include <qlistwidget.h>

class StackList: public QListWidget
{
private:
    QVector<QString> effects;
public:
    StackList(QWidget*parent = nullptr);
    void push(QString item);
    QListWidgetItem* pop();
};
