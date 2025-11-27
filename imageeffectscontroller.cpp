#include "imageeffectscontroller.h"
#include "Effects/EffectsBuilder.h"


///ЧТО НУЖНО СДЕЛАТЬ
/// 2) ГРАДАЦИЯ СЕРОГО - ГРАДАЦИЯ СЕРОГО ОТКЛЮЧАЕТ КАНАЛЫ
/// 3) БЛЮР
/// СОХРАНЕНИЕ КАРТИНКИ
/// СОХРАНИТЬ КАРТИНКУ КАК

extern "C" void AdjustColors(uchar* array, RGBA*rgba, int size);
// extern "C" void Blur(uchar*oldArray,uchar*copyArray,int row,int col);

extern "C" void GrayScale(uchar*oldArray,uchar*copyArray,int row,int col);
extern "C" void Blur(uchar*oldArray,uchar*copyArray,int row,int col);
extern "C" void Inversion(uchar*oldArray,uchar*copyArray,int row,int col);

void Aboba(uchar*a = nullptr,uchar*b =nullptr,int ai=0,int bi =0){
    qDebug()<<"Aboba";
}


const long long tickValue = 50;
const long long maxbackups = 10;

QImage ImageEffectsController::getImage() const
{
    return image;
}

QString ImageEffectsController::getLastDir() const
{
    qDebug() << dir.path();
    return dir.path();
}


void ImageEffectsController::setDir(const QDir &newDir)
{
    dir = newDir;
}

QString ImageEffectsController::getFileName() const
{
    return fileName;
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
    // setupEffects();
    connect(passed, &QTimer::timeout, this,&ImageEffectsController::editColors);
    // Запускаем таймер (1000 мс = 1 сек)
    passed->start(tickValue);
}

void ImageEffectsController::setRed(int value)
{
    rgba.red = value;
    isImageDirty = true;
}

void ImageEffectsController::editColors(){
    if(isImageDirty){
        int size = row*col;
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

void ImageEffectsController::applyEffect()
{

}

void ImageEffectsController::undo()
{
    if(states.size() == 0){
        return;
    }
    if(isEditColors == true){
        isEditColors = false;
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

    QFileInfo fileInfo(filename);

    this->dir = QDir(fileInfo.absoluteDir());
    fileName = fileInfo.fileName();
    qDebug()<<"dir: "<<dir;
    qDebug()<<"file: "<<fileName;
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
ImageEffectsController::~ImageEffectsController() {
    for (auto i : effects) {
        delete i;
    }
}
