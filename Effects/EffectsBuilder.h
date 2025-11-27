#pragma once
#include "abstracteffect.h"
#include<QString>
#include <qaction.h>
#include <qevent.h>





class EffectsBuilder: QObject
{
    Q_OBJECT
private:
    Effect*effect;
public:
    EffectsBuilder(QObject*parent = nullptr):QObject(parent){
        effect = new Effect();
        effect->action = new QAction(effect->name,this);//я не уверен в этой строчке кода
    }
    EffectsBuilder*applyName(QString name){
        effect->name = name;
        return this;
    }
    EffectsBuilder*applyDescription(QString name){
        effect->description = name;
        return this;
    }
    EffectsBuilder* applyFunc(_Func func){
        effect->func = func;
        return this;
    }
    EffectsBuilder*applyShortCut(QKeySequence key){
        effect->action->setShortcut(key);
        return this;
    }
    //Careful - effects are not nested by QObject. The struct   storing effect need to dispose it
    Effect* build(){
        effect->action->setText(effect->name);
        return effect;
    }
};
