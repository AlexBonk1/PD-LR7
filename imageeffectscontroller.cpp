#include "imageeffectscontroller.h"
#include "Effects/EffectsBuilder.h"
#include<memory>


extern "C" void AdjustColors(uchar* array, RGBA*rgba, int size);

extern "C" void GrayScale(uchar*oldArray,uchar*copyArray,int row,int col);
extern "C" void Blur(uchar*oldArray,uchar*copyArray,int row,int col);
extern "C" void Inversion(uchar*oldArray,uchar*copyArray,int row,int col);

extern "C" void RotateLeft(uchar*picture,uchar*copyArray,int row, int col);
extern "C" void RotateRight(uchar*picture,uchar*copyArray,int row, int col);


const long long tickValue = 50;
const long long maxbackups = 10;

QImage ImageEffectsController::getImage() const
{
    return image;
}

void ImageEffectsController::setDir(const QDir &newDir)
{
    fileinfo->setDir(newDir);
}

QString ImageEffectsController::getCurrentPath()
{
    if(fileinfo == nullptr){
        return QDir::homePath();
    }
    return fileinfo->getCurrentFilePath();
}

void ImageEffectsController::setupEffect(QString name,QString description,_Func func,QKeySequence key)
{
    auto popaBuilder = new EffectsBuilder(this);
    popaBuilder->applyDescription(description)->applyName(name);
    if(func != 0){
        popaBuilder->applyFunc(func);
    }
    if(key != 0){
        popaBuilder->applyShortCut(key);
    }
    Effect* effect = popaBuilder->build();
    emit addAction(effect->action);//in MainWindow
    connect(effect->action,&QAction::triggered,this,[this,effect](){

        if(states.size()>=maxbackups){
            states.pop_front();
            emit deleteFirstInChain();
        }
        states.push_back(image.copy());

        col = image.bytesPerLine();
        row = image.sizeInBytes()/col;
        effect->func(image.bits(),states.last().bits(),row,col);
        emit addEffect(effect->description);
        qDebug()<<states.size();
        emit imageChanged();
        if(isEditColors == true){
            emit zeroScrollers();
            isEditColors = false;
            rgba = RGBA(0,0,0,0);
        }
    });
    effects.push_back(effect);
}

void ImageEffectsController::setupEffects()
{
    setupEffect("Blur x1","picture blur x1",Blur,QKeySequence(Qt::CTRL|Qt::SHIFT | Qt::Key_B));
    setupEffect("GrayScale","Simple Grayscale",GrayScale,QKeySequence(Qt::CTRL |Qt::SHIFT | Qt::Key_G));
    setupEffect("Inversion","Inversion",Inversion,QKeySequence(Qt::CTRL|Qt::SHIFT | Qt::Key_I));
    // setupEffect("")
}

ImageEffectsController::ImageEffectsController(QObject *parent)
    :QObject(parent), rgba(0,0,0,0)
{
    dir = QDir::home();
    isImageDirty = false;
    passed = new QTimer(this);
    connect(passed, &QTimer::timeout, this,&ImageEffectsController::editColors);
    passed->start(tickValue);
}

void ImageEffectsController::setRed(int value)
{
    rgba.red = value;
    isImageDirty = true;
}

void ImageEffectsController::editColors(){
    if(isImageDirty){
        int size = image.sizeInBytes();
        //FirstEditColors
        if(isEditColors == false){
            states.push_back(image);
            isEditColors = true;
            emit addEffect("Edit colors");
        }
        image = states.last().copy();
        AdjustColors(image.bits(),&rgba,size);
        emit imageChanged();
        isImageDirty = false;
    }
}


void ImageEffectsController::undo()
{
    if(states.size() == 0){
        return;
    }
    if(isEditColors == true){
        isEditColors = false;
        emit zeroScrollers();
    }
    image = states.last();
    states.pop_back();
    emit imageChanged();
    emit popEffect();
}


void ImageEffectsController::setBlue(int value)
{
    rgba.blue = value;
    isImageDirty = true;
}

void ImageEffectsController::setGreen(int value)
{
    rgba.green = value;
    isImageDirty = true;
}

void ImageEffectsController::setOpacity(int value)
{
    rgba.opacity = value;
    isImageDirty = true;
}

bool ImageEffectsController::loadImage(QString filename)
{
    reset();
    QFileInfo fileInfo(filename);

    this->dir = QDir(fileInfo.absoluteDir());
    fileName = fileInfo.fileName();
    qDebug()<<"dir: "<<dir;
    qDebug()<<"file: "<<fileName;
    fileinfo = std::make_unique<FileInfo>(dir,filename);
    image.load(filename);
    image.convertTo(QImage::Format_ARGB32);//A R G B


    if(image.isNull()){
        qDebug()<<"Bad image!";
        throw BadImageException();
        return false;
    }
    qDebug()<<"Image loaded succesful!";
    row = image.bytesPerLine();
    col = image.sizeInBytes()/row;
    qDebug()<<"Image size: "<<row<<"x"<<col;
    return true;
}

///Some sort of image saving
bool ImageEffectsController::saveImage(QString filepath)
{
    if(filepath.isEmpty()){
        filepath = dir.absolutePath()+"/"+fileName;
    }
    qDebug()<<filepath;
    bool usp = image.save(filepath);
    qDebug()<<usp;
    return usp;
}

void ImageEffectsController::reset()
{
    states.clear();
    emit deleteAllInChain();
}

void ImageEffectsController::rotateLeft()
{
    if(states.size()>=maxbackups){
        states.pop_front();
        emit deleteFirstInChain();
    }
    states.push_back(image.copy());
    col = image.width();
    row = image.height();
    image = QImage(image.height(),image.width(),QImage::Format_ARGB32);

    qDebug() << row<<col;
    RotateLeft(image.bits(),states.last().bits(),image.width(),image.height());
    emit addEffect("Rotated 90 left");
    qDebug()<<image.format();
    emit imageChanged();
    if(isEditColors == true){
        emit zeroScrollers();
        isEditColors = false;
        rgba = RGBA(0,0,0,0);
    }
}

void ImageEffectsController::rotateRight()
{
    if(states.size()>=maxbackups){
        states.pop_front();
        emit deleteFirstInChain();
    }
    states.push_back(image.copy());
    col = image.height()*4;
    row = image.width()*4;
    image = QImage(image.height(),image.width(),QImage::Format_ARGB32);

    RotateRight(image.bits(),states.last().bits(),image.width(),image.height());
    emit addEffect("Rotated 90 right");
    emit imageChanged();
    if(isEditColors == true){
        emit zeroScrollers();
        isEditColors = false;
        rgba = RGBA(0,0,0,0);
    }
}
ImageEffectsController::~ImageEffectsController() {
    for (auto i : effects) {
        delete i;
    }
}
