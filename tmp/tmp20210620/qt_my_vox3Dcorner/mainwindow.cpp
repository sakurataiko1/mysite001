#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

#include <QMessageBox>

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
    QString loadfilepath = "";
    QString tmpDirpath = "Desktop";
    loadfilepath = QFileDialog::getOpenFileName(this, "select file", tmpDirpath);
    if(loadfilepath.isEmpty()==1){ return; } //ファイル選択でキャンセルボタンが押されたら、そのまま終了。

    ui->lineEdit_voxpath->setText(loadfilepath);
}


void MainWindow::on_pushButton_load_clicked()
{
    func_vox_readHeader(); //voxヘッダー部分　マテリアルID, マテリアル名読み込み
    qDebug() << "\n[DEBUG]Main.cpp-on_pushButton_load_clicked materialName=" << g_matNameList;
    qDebug() << "\n[DEBUG]Main.cpp-on_pushButton_load_clicked materialID=" << g_matNoList;

    func_vox_read3Darray(); //voxデータ部分読み込み
    //-start- [DEBUG]
    //qDebug() << "\n[DEBUG]Main.cpp-on_pushButton_load_clicked vox-data=";
    //for(int z=0; z<nz; z++){
    //    for(int y=0; y<ny; y++){
    //        QString tmpstr = "";
    //        for(int x=0; x<nx; x++){
    //            tmpstr += QString::number(g_voxDomain[x][y][z]) + " ";
    //        }
    //        qDebug() << tmpstr;
    //    }
    //}
    //-end- [DEBUG]

    //描画するメッシュの面情報を取得
    func_checkMateNumOfAdjoinMesh();
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawMesh=" << DrawMesh;
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_voxGraffic DrawSurface=" << DrawSurface;
    //-start- [DEBUG]
    for(int i=0; i< g_matNoList.size(); i++){
        QList<QString> tmp_drawMeshList =  g_drawMeshHash.values(g_matNoList.at(i));
        for(int j=0; j < tmp_drawMeshList.size(); j++ ){
            qDebug() << "[DEBUG]Main.cpp-on_pushButton_load_clicked tmp_drawMeshList =" << tmp_drawMeshList.at(j);
        }
    }
    //-end- [DEBUG]
    QMessageBox::information(this, "notice", "end.");
}

//ファイル書き込み(windowsで使うファイル用)
void MainWindow::fileWrteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList)
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

QStringList MainWindow::readTextFileAll(QString fileName) //ファイル読み込みして、1行ごとにリストに格納する
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



void MainWindow::func_vox_readHeader()
{
   //QFile voxinfile("C:/kuroda/work/00_Data_vox/test_mini_4x3x2.vox.txt");
   QFile voxinfile(ui->lineEdit_voxpath->text());
   if(! voxinfile.open(QIODevice::ReadOnly)){
       //Error
       return;
   }

   g_matNoList.clear();
   g_matNameList.clear();

   int VoxUnitlength =20;
   QTextStream in(&voxinfile);
   QString VoxfileLine;
   QStringList VoxfileLineList;
   QString nxstr, nystr, nzstr;

   while(!in.atEnd()){
       VoxfileLine = in.readLine(0);
       if(VoxfileLine.indexOf("unitlength")>0){
           VoxfileLineList = VoxfileLine.split("\t");
           QString tmpString = VoxfileLineList.at(0);
           float tmpFloat = tmpString.toFloat();
           g_meshsize = int(tmpFloat * 1000);
           g_meshsize_x = g_meshsize;
           g_meshsize_y = g_meshsize;
           g_meshsize_z = g_meshsize;
           break;
       }
   }

   while(!in.atEnd()){
       //マテリアル定義箇所　unitlength以後、 CellData まで
       VoxfileLine = in.readLine(0);
       if(VoxfileLine.startsWith("CellData")>0){ break; }
       QStringList tmpstrList = VoxfileLine.split("\t");
       if( tmpstrList.size() >= 2){
           g_matNoList << tmpstrList.at(0).toInt();
           g_matNameList << tmpstrList.at(1);
       }
   }

   while(!in.atEnd()){
       //メッシュ最大数　取得
       VoxfileLine = in.readLine(0);
       if(VoxfileLine.indexOf(" x ") > 0){
           VoxfileLineList = VoxfileLine.split(" x ");
           nxstr = VoxfileLineList.at(0);
           nystr = VoxfileLineList.at(1);
           nzstr = VoxfileLineList.at(2);
           nx = nxstr.toInt();
           ny = nystr.toInt();
           nz = nzstr.toInt();
           g_nx = nx;
           g_ny = ny;
           g_nz = nz;
           break;
       }
   }

}


void MainWindow::func_vox_read3Darray() //voxファイル読み出し 3次元配列への格納
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
   //int ***g_voxDomain = new int**[nx];
   g_voxDomain = new int**[nx];
   for(int x=0; x< nx; x++){
       g_voxDomain[x] = new int*[ny];
       for(int y=0; y< ny; y++){
           g_voxDomain[x][y] = new int[nz](); //初期化　全部ゼロを入れる
       }
   }

   //データ格納
   for(int  z=0; z < nz; z++){
       for(int  y=0; y < ny; y++){
           VoxfileLine = in.readLine(0);
           VoxfileLine = VoxfileLine.trimmed(); //末尾の空白を削除する
           qDebug() << "[DEBUG]Main.cpp-func_vox_read3Darray() "  << VoxfileLine;
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

   //[DEBUG]内容表示
//   for(int  z=0; z < nz; z++){
//       QString tmpstr;
//       qDebug() << "\n[DEBUG]z=" << QString::number(z) << "bottom-left (0,0) top-right=(xmax, ymax)";
//       for(int  y=ny-1; y >=0 ; y--){ //確認用に Y座標　左下(0,0) 右上(xmax, ymax)で表示する
//           QString tmpstr="";
//           for(int x=0; x< nx; x++){
//               tmpstr = tmpstr + " " + QString::number(g_voxDomain[x][y][z]);
//           }
//           qDebug() << "[DEBUG]Main.cpp-func_vox_read3Darray() " << tmpstr;
//       }
//   }

//   //終了　3次元配列解放
//   for(int x=0; x<nx; x++){
//       for(int y=0; y<ny; y++){
//           delete[] g_voxDomain[x][y];
//       }
//       delete[] g_voxDomain[x];
//   }
//   delete[] g_voxDomain;



}



void MainWindow::func_checkMateNumOfAdjoinMesh() //描画するメッシュの面情報を取得
{
//    int i,j,k;
//    meshAll = nx*ny*nz;
//    unsigned int nowMeshNo = 0;
//    unsigned int chkMeshNo = 0;
    //int nowMeshNo = 0;
    //int chkMeshNo = 0;
    int drawMeshFlag;

    //-start- kuroda commentout
    //QProgressDialog pd(this);
    //pd.setRange(0, meshAll/1000);
    //pd.setWindowModality(Qt::WindowModal);
    //pd.setLabelText(TR("Selecting Drawing Mesh"));
    //qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    //if(pd.wasCanceled()){
    //    exit(false);
    //}
    //-end- kuroda commentout

    for(int z=0; z<g_nz; z++){
        for(int y=0; y<g_ny; y++){
            for(int x=0; x<g_nx; x++){
                drawMeshFlag = 0;
                QString drawSurfaceStr = "";

                //front
                //chkMeshNo = nowMeshNo - nx * ny;
                if(y == 0 || ((y > 0) && g_voxDomain[x][y][z] != g_voxDomain[x][y-1][z])){
                    drawMeshFlag = 1;
                    drawSurfaceStr += "1-";
                }


                //back
                //chkMeshNo = nowMeshNo + nx * ny;
                if(y == ny-1 || ((y < ny-1) && g_voxDomain[x][y][z] != g_voxDomain[x][y+1][z])){
                    drawMeshFlag = 1;
                    drawSurfaceStr += "2-";
                }

                //right
                //chkMeshNo = nowMeshNo + 1;
                if(x ==nx-1 || ((x < nx-1) && g_voxDomain[x][y][z] != g_voxDomain[x+1][y][z])){
                    drawMeshFlag = 1;
                    drawSurfaceStr += "2-";
                }

                //left
                //chkMeshNo = nowMeshNo - 1;
                if(x ==0 || ((x > 0) && g_voxDomain[x][y][z] != g_voxDomain[x-1][y][z])){
                    drawMeshFlag = 1;
                    drawSurfaceStr += "4-";
                }

                //top
                //chkMeshNo = nowMeshNo + nx;
                if(z == nz-1 || ((z < nz-1) && g_voxDomain[x][y][z] != g_voxDomain[x][y][z+1])){
                    drawMeshFlag = 1;
                    drawSurfaceStr += "5-";
                }

                //bottom
                //chkMeshNo = nowMeshNo - nx;
                if(y== 0 || ((y > 0) && g_voxDomain[x][y][z] != g_voxDomain[x][y][z-1])){
                    drawMeshFlag = 1;
                    drawSurfaceStr += "6-";
                }

                if(drawSurfaceStr != ""){
                    drawSurfaceStr.chop(1); //最後の余分な '-' を削除
                }

                if(drawMeshFlag == 1 ){ //1列分まとめて描くための始点判定：　x=0 または　0以上　直方体として6面いずれかが空いている。
                    int mateID = g_voxDomain[x][y][z];
                    int tmpcnt = 0;
                    for(int n=x; n < nx; n++){
                        //1列分まとめて描くための終点判定。右隣が同じでない or 1列分の終端の場合。
                        if(n == nx-1){ break; }
                        int tmpint1 = g_voxDomain[n][y][z];
                        int tmpint2 = g_voxDomain[n+1][y][z];
                        if(g_voxDomain[n][y][z] != g_voxDomain[n+1][y][z]) { break; }
                        tmpcnt = tmpcnt + 1;
                    }
                    int Xend = x;
                    if(tmpcnt > 0 ){ Xend = x + tmpcnt ; }
                    QString tmpstr = QString::number(mateID) + "," +
                            QString::number(x) + "," + QString::number(y) + "," + QString::number(z) + "," +
                            QString::number(Xend) + "," + QString::number(y) + "," + QString::number(z) + "," +
                            drawSurfaceStr;
                    //qDebug() << "[DEBUG]Main.cpp-func_checkMateNumOfAdjoinMesh tmpstr=" << tmpstr;
                    g_drawMeshHash.insert(mateID, tmpstr);
                    if(tmpcnt > 0 ){ x = Xend ; } //連続箇所をスキップ
                 }
                //nowMeshNo++;

            }//-end- for x
        }//-end- for y
    }//-end- for j

}
