#pragma once
#include<QString>
#include <qaction.h>


using _Func = std::function<void(uchar* newArr,uchar* oldArray,
                                 int row,int col)>;



class Effect
{
private:
    static void boilerPlate(uchar*array,uchar*oldarr,int row,int col){
        qDebug()<<"function not implemented!";
    }
public:
    QString name = "NOT IMPLEMENTED";
    QString description;
    QAction *action = nullptr;
    _Func func = boilerPlate;
public:
    Effect(){}
    void apply();
};
