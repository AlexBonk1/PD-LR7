#include "stacklist.h"


StackList::StackList(QWidget *parent) : QListWidget(parent)
{

}

void StackList::push(QString item)
{
    this->insertItem(0,item);
}

QListWidgetItem* StackList::pop()
{
   return this->takeItem(0);
}
