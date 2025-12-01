#include "stacklist.h"


StackList::StackList(QWidget *parent) : QListWidget(parent)
{

}

void StackList::push(QString item)
{
    this->insertItem(0,item);
}

QListWidgetItem* StackList::pop_back()
{
    return this->takeItem(0);
}

QListWidgetItem *StackList::pop_front()
{
    return this->takeItem(this->count()-1);
}
