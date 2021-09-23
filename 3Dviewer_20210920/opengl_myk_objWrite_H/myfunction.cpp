#include "myfunction.h"


myfunction::myfunction(QWidget *parent) : QWidget(parent)
{

}

myfunction::~myfunction(){

}

QVector3D myfunction::func_defineColor(int input_colornum){
     QVector3D resultColor = QVector3D(1, 0, 0);
     int tmpint_color = input_colornum % 10;

     if(tmpint_color == 0){ resultColor = QVector3D(1, 0, 0); } //赤
     if(tmpint_color == 1){ resultColor = QVector3D(0, 1, 0); } //緑
     if(tmpint_color == 2){ resultColor = QVector3D(0, 0, 1); } //青

     if(tmpint_color == 3){ resultColor = QVector3D(1, 1, 0); } //黄色
     if(tmpint_color == 4){ resultColor = QVector3D(1, 0, 1); } //マゼンタ
     if(tmpint_color == 5){ resultColor = QVector3D(0, 1, 1); } //シアン(水色)

     if(tmpint_color == 6){ resultColor = QVector3D(0.5, 0, 0); } //濃い赤
     if(tmpint_color == 7){ resultColor = QVector3D(0, 0.5, 0); } //濃い緑
     if(tmpint_color == 8){ resultColor = QVector3D(0, 0, 0.5); } //濃い青

     if(tmpint_color == 9){ resultColor  = QVector3D(0.3,  0.7, 0); }   //濃いマゼンタ
     if(tmpint_color == 10){ resultColor = QVector3D(0.3, 0,   0.7); } //
     if(tmpint_color == 11){ resultColor = QVector3D(0,   0.3, 0.7); } //

     return resultColor;

}

void myfunction::fileWriteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList)
{
     QFile file(WriteFilePath);
     if(WriteMode == "Append"){
         if(!file.open(QIODevice::Append| QIODevice::Text)){
             QMessageBox::information(this, tr("Unable to openfile"), file.errorString());
             return;
         }
     } else {
         if(!file.open(QIODevice::WriteOnly| QIODevice::Text)){
             QMessageBox::information(this, tr("Unable to openfile"), file.errorString());
             return;
         }
     }

     QTextStream out(&file);
     for (int n=0; n<msgList.size(); n++){
         out << msgList.at(n) << endl;
     }
     file.close();
}

QStringList  myfunction::readTextFileAll(QString fileName) //ファイル読み込みして、1行ごとにリストに格納する
{
    QStringList lines;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QString errStr =  "file open error:" + file.errorString();
        qDebug() << errStr;
        //return(lines);
    }
    QTextStream in(&file);
    QString inStr = in.readAll();
    file.close();

    //voxファイルのLF改行に対応
    //QStringList lines = inStr.split("\r\n");
    lines = inStr.split("\r\n"); //kuroda add
    lines = inStr.split("\n");
    return lines;

}

