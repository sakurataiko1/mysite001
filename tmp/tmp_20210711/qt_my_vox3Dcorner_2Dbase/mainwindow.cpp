#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

#include <QMessageBox>
#include <QRegularExpression>

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

    //直方体　objファイル作成
    int matNum = 1; //[DEBUG]
    QString voxfilePath = ui->lineEdit_voxpath->text();
    //QString outfileDir =  QFileInfo(QFile(voxfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(voxfilePath)).baseName() ;//2021.06.xx-01 for-obj
    QString outfileDir = g_resultDirPath + "/objfile_" + QFileInfo(QFile(voxfilePath)).baseName();//2021.06.xx-01 for-obj
    QDir dir(outfileDir);
    if(! dir.exists()){ dir.mkpath(outfileDir); }
    g_obj_outfilepath = outfileDir + "/" + QFileInfo(QFile(voxfilePath)).baseName() + "_" + QString::number(matNum) + ".obj"; //
    if(QFileInfo(QFile(g_obj_outfilepath)).exists()){ QFile(g_obj_outfilepath).remove(); }

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
    func_meshSurface_get();

    //func_get_rectVertex(); //平面mesh始点・頂点(g_drawMeshHash.values)から、　3Drectangleとしての、6平面の頂点情報を取得する。

    QMessageBox::information(this, "notice", "end.\n resultDir=" + g_resultDirPath);
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
           //qDebug() << "[DEBUG]Main.cpp-func_vox_read3Darray() "  << VoxfileLine;
           VoxfileLineList = VoxfileLine.split(" ");
           int countx = 0;
           int tmpint = VoxfileLine.size()/2;
           for(int x=0; x < (VoxfileLineList.size()/2); x++){
               QString tmpnumstr1 = VoxfileLineList.at(2*x); //material-ID
               int tmpnum1 = tmpnumstr1.toInt();
               QString tmpnumstr2 = VoxfileLineList.at(2*x+1); //繰り返し数
               int tmpnum2 = tmpnumstr2.toInt();
               for(int n=0; n< tmpnum2; n++){
                   if((countx + n) < nx){
                      g_voxDomain[countx + n][y][z] = tmpnum1;
                   }
               }
               countx += tmpnum2;
           }
       }
       //-end- for(int  y=0; y< ny; y++)
   }

    //[DEBUG]内容表示
    //for(int  z=0; z < nz; z++){
    //   QString tmpstr;
    //   qDebug() << "\n[DEBUG]z=" << QString::number(z) << "bottom-left (0,0) top-right=(xmax, ymax)";
    //   for(int  y=ny-1; y >=0 ; y--){ //確認用に Y座標　左下(0,0) 右上(xmax, ymax)で表示する
    //       QString tmpstr="";
    //       for(int x=0; x< nx; x++){
    //           tmpstr = tmpstr + " " + QString::number(g_voxDomain[x][y][z]);
    //       }
    //       qDebug() << "[DEBUG]Main.cpp-func_vox_read3Darray() g_voxDomain=" << tmpstr;
    //   }
    //}

//   //終了　3次元配列解放
//   for(int x=0; x<nx; x++){
//       for(int y=0; y<ny; y++){
//           delete[] g_voxDomain[x][y];
//       }
//       delete[] g_voxDomain[x];
//   }
//   delete[] g_voxDomain;



}


void MainWindow::func_get_rectVertex(){ //平面mesh始点・頂点(g_drawMeshHash.values)から、　3Drectangleの頂点情報を取得する。(6平面-8頂点)
    float meshsize = 1; //20; //[DEBUG]
    //描画するメッシュの面情報を取得
    //func_checkMateNumOfAdjoinMesh();
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_rectVertices DrawMesh=" << DrawMesh;
    //qDebug() << "[DEBUG]01 miwidget.cpp-func_get_rectVertices DrawSurface=" << DrawSurface;
    ////-start- [DEBUG]
    for(int i=0; i< g_matNoList.size(); i++){
        QList<QString> tmp_drawMeshList =  g_drawMeshHash.values(g_matNoList.at(i));
        for(int j=0; j < tmp_drawMeshList.size(); j++ ){
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertices tmp_drawMeshList =" << tmp_drawMeshList.at(j);
            //tmpList 例： "13,2,1,0,4,1,0,2-4-5-6" [0]マテリアル番号 [1-3]始点Mesh座標　[4-6]始点Mesh座標  [7]描画が必要な面
            QStringList tmpList = tmp_drawMeshList.at(j).split(",");

            float wide = (tmpList.at(4).toFloat() +1 ) - tmpList.at(1).toFloat()  ;
            float depth = (tmpList.at(5).toFloat() +1 ) - tmpList.at(2).toFloat();
            float hight = (tmpList.at(6).toFloat() +1) - tmpList.at(3).toFloat();

            //通常座標　(openGL系座標にするときは、別関数で変更する
            //面の名前 3-left/4-right , 2-front/1-back, 5-top/6-under (bottomだとbackとかぶるので）
            // 前　　　　|　　後ろ
            //　D - C | H - G
            //　A - B | E - F
            float xA, yA, zA; //左・前・下
            float xB, yB, zB; //右・前・下
            float xC, yC, zC; //右・前・上
            float xD, yD, zD; //左・前・上
            float xE, yE, zE; //左・後・下
            float xF, yF, zF; //右・後・下
            float xG, yG, zG; //右・後・上
            float xH, yH, zH; //左・後・上

            //A 左・前・下
            xA = tmpList.at(1).toFloat();
            yA = tmpList.at(2).toFloat();
            zA = tmpList.at(3).toFloat();
            QVector3D vertexA = QVector3D(xA, yA, zA);  //通常座標敬
            QVector3D vertexglA = QVector3D(xA, zA, yA); //openGL座標系
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexA=" << vertexA;

            //B 右・前・下
            xB = xA + meshsize;
            yB = yA;
            zB = zA;
            QVector3D vertexB = QVector3D(xB, yB, zB);
            QVector3D vertexglB = QVector3D(xB, zB, yB); //openGL座標系
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexB=" << vertexB;

            //C 右・前・上
            xC = xA + meshsize;
            yC = yA;
            zC = zA + meshsize;
            QVector3D vertexC = QVector3D(xC, yC, zC);
            QVector3D vertexglC = QVector3D(xC, zC, yC); //openGL座標系
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexC=" << vertexC;

            //D 左・前・上
            xD = xA;
            yD = yA;
            zD = zA+ meshsize;
            QVector3D vertexD = QVector3D(xD, yD, zD);
            QVector3D vertexglD = QVector3D(xD, zD, yD); //openGL座標系
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexD=" << vertexD;

            //E 左・後・下
            xE = xA;
            yE = yA + meshsize * depth;
            zE = zA;
            QVector3D vertexE = QVector3D(xE, yE, zE);
            QVector3D vertexglE = QVector3D(xE, zE, yE); //openGL座標系
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexE=" << vertexE;

            //F 右・後・下
            xF = xA + meshsize * wide;
            yF = yA + meshsize * depth;
            zF = zA;
            QVector3D vertexF = QVector3D(xF, yF, zF);
            QVector3D vertexglF = QVector3D(xF, zF, yF); //openGL座標系
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexF=" << vertexF;

            //G 右・後・上
            xG = xA + meshsize * wide;
            yG = yA + meshsize * depth;
            zG = zA + meshsize * hight;
            QVector3D vertexG = QVector3D(xG, yG, zG);
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexG=" << vertexG;
            QVector3D vertexglG = QVector3D(xG, zG, yG); //openGL座標系
            //H 左・後・上
            xH = xA;
            yH = yA + meshsize * depth;
            zH = zA + meshsize * hight;
            QVector3D vertexH = QVector3D(xH, yH, zH);
            QVector3D vertexglH = QVector3D(xH, zH, yH); //openGL座標系
            qDebug() << "[DEBUG]Main.cpp-func_get_rectVertex vertexH=" << vertexH;

            //objファイル書き込み
            func_objfile_write_rectangle(vertexglA, vertexglB, vertexglC, vertexglD, vertexglE, vertexglF, vertexglG, vertexglH);//直方体 objファイルの作成

        }
    }
}

void MainWindow::func_objfile_write_plane(int input_matNum, int in_surfaceCnt, QString in_msg1,  QVector3D in_vertex1, QVector3D in_vertex2, QVector3D in_vertex3, QVector3D in_vertex4) //objファイル書き込み
{
    //-start- objファイル作成前準備
    QString voxfilePath = ui->lineEdit_voxpath->text();
    QString outfileDir =  QFileInfo(QFile(voxfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(voxfilePath)).baseName() ;//2021.06.xx-01 for-obj
    QString outfilePath = outfileDir + "/" + QFileInfo(QFile(voxfilePath)).baseName() + "_" + QString::number(input_matNum) + ".obj"; //
    QFile outfile1(outfilePath);
    if(!outfile1.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::information(this, tr("Unable to openfile"), outfile1.errorString());
        return;
    }
    QTextStream g_out_obj1(&outfile1);
    //-end- objファイル作成前準備

    //qDebug() << "[DEBUG]01miWidget.cpp-func_objfile_write()";

    //objファイル書き込み
    //例 FRONT
    //mtllib sample_plane_front_blender.mtl
    //o Plane
    //v -1.000000 1.000000 1.000000
    //v -1.000000 -1.000000 1.000000
    //v 1.000000 1.000000 1.000000
    //v 1.000000 -1.000000 1.000000
    g_out_obj1 << "# " + in_msg1 << endl;
    g_out_obj1 << "o Plane." + QString::number(in_surfaceCnt) +  "\n";
    //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
    g_out_obj1 << "v " << in_vertex1.x() << " " << in_vertex1.y() << " " << in_vertex1.z() <<endl; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
    g_out_obj1 << "v " << in_vertex2.x() << " " << in_vertex2.y() << " " << in_vertex2.z() <<endl; //頂点順番はこれから修正する
    g_out_obj1 << "v " << in_vertex3.x() << " " << in_vertex3.y() << " " << in_vertex3.z() <<endl;
    g_out_obj1 << "v " << in_vertex4.x() << " " << in_vertex4.y() << " " << in_vertex4.z() <<endl;
    //vt,vn,s行：固定
    g_out_obj1 << "vt 0.000000 0.000000" << endl;
    g_out_obj1 << "vt 1.000000 0.000000" << endl;
    g_out_obj1 << "vt 1.000000 1.000000" << endl;
    g_out_obj1 << "vt 0.000000 1.000000" << endl;
    g_out_obj1 << "vn 0.0000 1.0000 0.0000" << endl;
    g_out_obj1 << "s off"<< endl;
    //f行：可変。Planeごとにカウントアップ必要。
    //g_out_obj1 << "f 1/1/1 2/2/1 4/3/1"<< endl; //D A B
    //g_out_obj1 << "f 4/3/1 3/4/1 1/1/1"<< endl; //B C D
    QList<int> vList,vtList;
    vList << 1 << 2 << 4 << 4 << 3 << 1;
    vtList << 1 << 2 << 3 << 3 << 4 << 1;
    for(int i=0; i < vList.count(); i++ ){
        vList[i] = vList.at(i) + 4 * in_surfaceCnt;
        vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
    }
    QString tmpstr;
    g_out_obj1 << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 vList.at(0), vtList.at(0), in_surfaceCnt + 1,
                                 vList.at(1), vtList.at(1), in_surfaceCnt + 1,
                                 vList.at(2), vtList.at(2), in_surfaceCnt + 1);
    g_out_obj1 << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 vList.at(3), vtList.at(3), in_surfaceCnt + 1,
                                 vList.at(4), vtList.at(4), in_surfaceCnt + 1,
                                 vList.at(5), vtList.at(5), in_surfaceCnt + 1);

    outfile1.close(); //objファイル書き込み。
}


void MainWindow::func_objfile_write_rectangle(QVector3D vertexglA, QVector3D vertexglB, QVector3D vertexglC, QVector3D vertexglD, QVector3D vertexglE, QVector3D vertexglF, QVector3D vertexglG, QVector3D vertexglH) //直方体 objファイルの作成
{
    //-start- objファイル作成前準備
    //QString voxfilePath = ui->lineEdit_voxpath->text();
    //QString outfileDir =  QFileInfo(QFile(voxfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(voxfilePath)).baseName() ;//2021.06.xx-01 for-obj
    //QDir dir(outfileDir);
    //if(! dir.exists()){ dir.mkpath(outfileDir); }
    //QString outfilePath = outfileDir + "/" + QFileInfo(QFile(voxfilePath)).baseName() + "_" + QString::number(input_MateNo) + ".obj"; //
    QFile outfile1(g_obj_outfilepath);
    if(!outfile1.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::information(this, tr("Unable to openfile"), outfile1.errorString());
        return;
    }
    QTextStream g_out_obj1(&outfile1);
    //-end- objファイル作成前準備

    QString msg1 = "";
    g_out_obj1 << "# " + msg1 + "\n"; //ただのメッシュ情報なのでなくていいが
    g_out_obj1 << "o rectungle\n"; // + QString::number(in_surfaceCnt) +  "\n";

    //objファイルに書き込む　直方体の頂点座標
    //g_out_obj1 << "v 1.000000 2.000000 -1.000000\n"; //vertexH
    //g_out_obj1 << "v 1.000000 -2.000000 -1.000000\n"; //vertexE
    //g_out_obj1 << "v 1.000000 2.000000 1.000000\n"; //D
    //g_out_obj1 << "v 1.000000 -2.000000 1.000000\n"; //A
    //g_out_obj1 << "v -1.000000 2.000000 -1.000000\n"; //G
    //g_out_obj1 << "v -1.000000 -2.000000 -1.000000\n"; //F
    //g_out_obj1 << "v -1.000000 2.000000 1.000000\n"; //C
    //g_out_obj1 << "v -1.000000 -2.000000 1.000000\n"; //B
    //
    QString tmpstr;
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglC.x(), vertexglC.y(), vertexglC.z());
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglB.x(), vertexglB.y(), vertexglB.z());
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglG.x(), vertexglG.y(), vertexglG.z());
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglF.x(), vertexglF.y(), vertexglF.z());
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglD.x(), vertexglD.y(), vertexglD.z());
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglA.x(), vertexglA.y(), vertexglA.z());
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglH.x(), vertexglH.y(), vertexglH.z());
    g_out_obj1 << tmpstr.asprintf("v %f %f %f\n", vertexglE.x(), vertexglE.y(), vertexglE.z());


    //以下, 固定内容
    g_out_obj1 << "vt 0.625000 0.000000\n";
    g_out_obj1 << "vt 0.375000 0.250000\n";
    g_out_obj1 << "vt 0.375000 0.000000\n";
    g_out_obj1 << "vt 0.625000 0.250000\n";
    g_out_obj1 << "vt 0.375000 0.500000\n";
    g_out_obj1 << "vt 0.375000 0.250000\n";
    g_out_obj1 << "vt 0.625000 0.500000\n";
    g_out_obj1 << "vt 0.375000 0.750000\n";
    g_out_obj1 << "vt 0.625000 0.750000\n";
    g_out_obj1 << "vt 0.375000 1.000000\n";
    g_out_obj1 << "vt 0.375000 0.500000\n";
    g_out_obj1 << "vt 0.125000 0.750000\n";
    g_out_obj1 << "vt 0.125000 0.500000\n";
    g_out_obj1 << "vt 0.875000 0.500000\n";
    g_out_obj1 << "vt 0.625000 0.500000\n";
    g_out_obj1 << "vt 0.625000 0.250000\n";
    g_out_obj1 << "vt 0.625000 0.750000\n";
    g_out_obj1 << "vt 0.625000 1.000000\n";
    g_out_obj1 << "vt 0.375000 0.750000\n";
    g_out_obj1 << "vt 0.875000 0.750000\n";
    g_out_obj1 << "vn 0.0000 1.0000 0.0000\n";
    g_out_obj1 << "vn 0.0000 0.0000 1.0000\n";
    g_out_obj1 << "vn -1.0000 0.0000 0.000\n";
    g_out_obj1 << "vn 0.0000 -1.0000 0.0000\n";
    g_out_obj1 << "vn 1.0000 0.0000 0.0000\n";
    g_out_obj1 << "vn 0.0000 0.0000 -1.0000\n";
    g_out_obj1 << "s off\n";
    //1つのobjに、複数の3D図形登録するので、f行は変更が必要。
    g_out_obj1 << "f 5/1/1 3/2/1 1/3/1\n";
    g_out_obj1 << "f 3/4/2 8/5/2 4/6/2\n";
    g_out_obj1 << "f 7/7/3 6/8/3 8/5/3\n";
    g_out_obj1 << "f 2/9/4 8/10/4 6/8/4\n";
    g_out_obj1 << "f 1/11/5 4/12/5 2/13/5\n";
    g_out_obj1 << "f 5/14/6 2/9/6 6/15/6\n";
    g_out_obj1 << "f 5/1/1 7/16/1 3/2/1\n";
    g_out_obj1 << "f 3/4/2 7/7/2 8/5/2\n";
    g_out_obj1 << "f 7/7/3 5/17/3 6/8/3\n";
    g_out_obj1 << "f 2/9/4 4/18/4 8/10/4\n";
    g_out_obj1 << "f 1/11/5 3/19/5 4/12/5\n";
    g_out_obj1 << "f 5/14/6 1/20/6 2/9/6\n";

    outfile1.close(); //objファイル書き込み。

}


void MainWindow::func_meshSurface_get(){ //描くMeshを0 , 描かないMeshを1にする
    //初期化
    //int ***g_voxSurface = new int**[nx];
    g_voxSurface = new int**[nx];
    for(int x=0; x< nx; x++){
        g_voxSurface[x] = new int*[ny];
        for(int y=0; y< ny; y++){
            g_voxSurface[x][y] = new int[nz](); //初期化　全部ゼロを入れる
        }
    }

    //surface-XZ面(前後)　描くMeshを0 , 描かないMeshを1にする
    for(int z=0; z<g_nz; z++){
        for(int y=0; y<g_ny; y++){
            for(int x=0; x<g_nx; x++){
                g_voxSurface[x][y][z] = 0; //初期値　今回は、 描くMesh=0;
                int judge_corner = 0;

                //始点判定 左・下・左斜め下が違うマテリアル かつ　前後いずれかが違うマテリアル
                if(x == 0){
                    judge_corner= judge_corner + 1;
                } else if(x > 0){ //左
                    if( g_voxDomain[x][y][z] != g_voxDomain[x-1][y][z]){ judge_corner= judge_corner + 1; }
                }

                if(y == 0){
                    judge_corner= judge_corner + 1;
                } else if(y > 0){ //前
                    if( g_voxDomain[x][y][z] != g_voxDomain[x][y-1][z]){ judge_corner= judge_corner + 1; }
                }

                if(z == 0){
                    judge_corner= judge_corner + 1;
                } else if(z > 0){ //下
                    if( g_voxDomain[x][y][z] != g_voxDomain[x][y][z-1]){ judge_corner= judge_corner + 1; }
                }

                //if(judge_corner == 3 ){
                    g_voxSurface[x][y][z] = judge_corner ;
                //}

            }
            //-end- for x
        }
    }

    //[DEBUG]内容表示
    for(int  z=0; z < nz; z++){
       QString tmpstr;
       qDebug() << "\n[DEBUG]func_meshSurface_getz=" << QString::number(z) << "bottom-left (0,0) top-right=(xmax, ymax)";
       for(int  y=ny-1; y >=0 ; y--){ //確認用に Y座標　左下(0,0) 右上(xmax, ymax)で表示する
           QString tmpstr="";
           for(int x=0; x< nx; x++){
               tmpstr = tmpstr + " " + QString::number(g_voxSurface[x][y][z]);
           }
           qDebug() << tmpstr;
       }
    }


}
