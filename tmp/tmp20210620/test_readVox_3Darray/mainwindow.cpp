#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_select_clicked()
{
    QString loadfileName  = "";
    QString tmpDirPath = "Desktop";
    loadfileName = QFileDialog::getOpenFileName(this, "select_file", tmpDirPath);
    if(loadfileName.isEmpty() == 1 ){return;} // ファイル選択でキャンセルボタンが押されたら, そのまま終了。


    ui->lineEdit_voxpath->setText(loadfileName);
}



void MainWindow::on_pushButton_load_clicked()
{
   //QFile voxinfile("C:/kuroda/work/00_Data_vox/test_mini_4x3x2.vox.txt");
   QFile voxinfile(ui->lineEdit_voxpath->text());
   if(! voxinfile.open(QIODevice::ReadOnly)){
       //Error
       return;
   }

   int VoxUnitlength =20;
   QTextStream in(&voxinfile);
   QString VoxfileLine;
   QStringList VoxfileLineList;
   QString nxstr, nystr, nzstr;
   int nx, ny, nz;
   while(!in.atEnd()){
       VoxfileLine = in.readLine(0);
       if(VoxfileLine.indexOf(" x ") > 0){
           VoxfileLineList = VoxfileLine.split(" x ");
           nxstr = VoxfileLineList.at(0);
           nystr = VoxfileLineList.at(1);
           nzstr = VoxfileLineList.at(2);
           nx = nxstr.toInt();
           ny = nystr.toInt();
           nz = nzstr.toInt();
           break;
       }

       if(VoxfileLine.indexOf("unitlength")>0){
           VoxfileLineList = VoxfileLine.split("\t");
           QString tmpString = VoxfileLineList.at(0);
           float tmpFloat = tmpString.toFloat();
           VoxUnitlength = int(tmpFloat * 1000);
       }
   }

   //初期化
   int ***g_voxDomain = new int**[nx];
   for(int x=0; x< nx; x++){
       g_voxDomain[x] = new int*[ny];
       for(int y=0; y< ny; y++){
           g_voxDomain[x][y] = new int[nz](); //初期化　全部ゼロを入れる
       }
   }

   //[DEBUG]内容表示
   for(int  z=0; z < nz; z++){
       for(int  y=0; y < ny; y++){
           VoxfileLine = in.readLine(0);
           VoxfileLine = VoxfileLine.trimmed(); //末尾の空白を削除する

           VoxfileLineList = VoxfileLine.split(" ");
           int countx = 0;
           int tmpint = VoxfileLine.size()/2;
           for(int x=0; x < (VoxfileLineList.size()/2); x++){
               QString tmpnumstr1 = VoxfileLineList.at(2*x); //material-ID
               int tmpnum1 = tmpnumstr1.toInt();
               QString tmpnumstr2 = VoxfileLineList.at(2*x+1); //繰り返し数
               int tmpnum2 = tmpnumstr2.toInt();
               for(int n=0; n< tmpnum2; n++){
                   g_voxDomain[countx + n][y][z] = tmpnum1;
               }
               countx += tmpnum2;
           }
       }
       //-end- for(int  y=0; y< ny; y++)
   }

//   //[DEBUG]内容表示
   for(int  z=0; z < nz; z++){
       QString tmpstr;
       qDebug() << "\n[DEBUG]z=" << QString::number(z) << "bottom-left (0,0) top-right=(xmax, ymax)";
       for(int  y=ny-1; y >=0 ; y--){ //確認用に Y座標　左下(0,0) 右上(xmax, ymax)で表示する
           QString tmpstr="";
           for(int x=0; x< nx; x++){
               tmpstr = tmpstr + " " + QString::number(g_voxDomain[x][y][z]);
           }
           qDebug() << "[DEBUG] " << tmpstr;
       }
   }

   //終了　3次元配列解放
   for(int x=0; x<nx; x++){
       for(int y=0; y<ny; y++){
           delete[] g_voxDomain[x][y];
       }
       delete[] g_voxDomain[x];
   }
   delete[] g_voxDomain;



}

