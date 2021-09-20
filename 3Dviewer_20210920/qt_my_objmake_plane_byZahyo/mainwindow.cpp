#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_inputZahyoText->setText("C:/tmp/test_obj/input_zahyo.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Run_clicked()
{
    //ファイル読み込み
    QStringList zahyoList = readTextFileAll("C:/tmp/test_obj/input_zahyo.txt");

    int surfaceCnt = 0;
    //インプットのファイル形式は、以下 #point start 文言があったら次から4行取得する
    //# point start
    //0 1 0
    //0 0 0
    //1 1 0
    //1 0 0
    for(int i=0; i<zahyoList.size(); i++){
        if (zahyoList.at(i).startsWith("# point start")){
            QString surfaceStr = zahyoList.at(i+1).trimmed(); //Front,Back,Right,Left,Top,Bottom　のいずれか

            QStringList tmpList = zahyoList.at(i+2).trimmed().split(" ");
            QVector3D vertex1 = QVector3D(tmpList.at(0).toInt(), tmpList.at(1).toInt(), tmpList.at(2).toInt());

            tmpList = zahyoList.at(i+3).split(" ");
            QVector3D vertex2 = QVector3D(tmpList.at(0).toInt(), tmpList.at(1).toInt(), tmpList.at(2).toInt());

            tmpList = zahyoList.at(i+4).split(" ");
            QVector3D vertex3 = QVector3D(tmpList.at(0).toInt(), tmpList.at(1).toInt(), tmpList.at(2).toInt());

            tmpList = zahyoList.at(i+5).split(" ");
            QVector3D vertex4 = QVector3D(tmpList.at(0).toInt(), tmpList.at(1).toInt(), tmpList.at(2).toInt());

            //objファイル形式にしたものを1行ずつlineEditに入れる
            int matNum = 1; //matnum今回は不要だけど、流用元のまま残しておく
            QString msg1 = "Plane_" + QString::number(surfaceCnt) + " " + surfaceStr;
            func_objfile_write_plane(vertex1, vertex2, vertex3, vertex4, matNum, surfaceCnt, msg1, surfaceStr); //objファイル書き込み

            surfaceCnt++;
        }
    }

    //書き出す
    QString WriteFilePath = "C:/tmp/test_obj/result_obj.txt";
    QString WriteMode = "WriteOnly";
    fileWriteForWindows(WriteFilePath, WriteMode, g_out_obj1);

    QMessageBox::information(this, "notice", "Program End.\n resultfile=" + WriteFilePath);
}


void MainWindow::func_objfile_write_plane(QVector3D in_vertex1, QVector3D in_vertex2, QVector3D in_vertex3, QVector3D in_vertex4, int input_matNum, int in_surfaceCnt, QString in_msg1, QString in_surfaceStr) //objファイル書き込み
{
    //-start- objファイル作成前準備
    //QString voxfilePath = ui->lineEdit_voxpath->text();
//    QString srcfilePath = ui->lineEdit_inputZahyoText->text();
//    QString outfileDir =  QFileInfo(QFile(srcfilePath)).absolutePath() + "/objfile_" + QFileInfo(QFile(srcfilePath)).baseName() ;//2021.06.xx-01 for-obj
//    QString outfilePath = outfileDir + "/" + QFileInfo(QFile(srcfilePath)).baseName() + "_" + QString::number(input_matNum) + ".obj"; //
//    QFile outfile1(outfilePath);
//    if(!outfile1.open(QIODevice::Append | QIODevice::Text)){
//        QMessageBox::information(this, tr("Unable to openfile"), outfile1.errorString());
//        return;
//    }
//    QTextStream g_out_obj1(&outfile1);
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
    g_out_obj1 << "# " + in_msg1;
    g_out_obj1 << "o Plane." + QString::number(in_surfaceCnt);
    //objでは、(x,y,z) 水平：Xは小さいほうから、奥行Zは大きい方から。高さYはx,z に合わせて。
    g_out_obj1 << "v " + QString::number(in_vertex1.x()) + " " + QString::number(in_vertex1.y()) + " " + QString::number(in_vertex1.z()) ; //objの場合↑とは描き方が違うので注意すること　objテキストファイルに書き出すは4頂点だけ
    g_out_obj1 << "v " + QString::number(in_vertex2.x()) + " " + QString::number(in_vertex2.y()) + " " + QString::number(in_vertex2.z()) ; //頂点順番はこれから修正する
    g_out_obj1 << "v " + QString::number(in_vertex3.x()) + " " + QString::number(in_vertex3.y()) + " " + QString::number(in_vertex3.z()) ;
    g_out_obj1 << "v " + QString::number(in_vertex4.x()) + " " + QString::number(in_vertex4.y()) + " " + QString::number(in_vertex4.z()) ;
    //vt,vn,s行：固定
    g_out_obj1 << "vt 0.000000 0.000000" ;
    g_out_obj1 << "vt 1.000000 0.000000" ;
    g_out_obj1 << "vt 1.000000 1.000000" ;
    g_out_obj1 << "vt 0.000000 1.000000" ;
    QString vnStr = "vn 0.0000 0.0000 1.0000";
    if(in_surfaceStr == "Front"){  vnStr = "vn 0.0000 0.0000 1.0000" ; }
    if(in_surfaceStr == "Back"){   vnStr = "vn 0.0000 0.0000 -1.0000" ; }
    if(in_surfaceStr == "Right"){  vnStr = "vn 1.0000 0.0000 0.0000" ; }
    if(in_surfaceStr == "Left"){   vnStr = "vn -1.0000 0.0000 0.0000" ; }
    if(in_surfaceStr == "Top"){    vnStr = "vn 0.0000 1.0000 0.0000" ; }
    if(in_surfaceStr == "Bottom"){ vnStr = "vn 0.0000 -1.0000 0.0000" ; }
    g_out_obj1 << vnStr;
    g_out_obj1 << "s off";
    //f行：可変。Planeごとにカウントアップ必要。
    //g_out_obj1 << "f 1/1/1 2/2/1 4/3/1"; //D A B
    //g_out_obj1 << "f 4/3/1 3/4/1 1/1/1"; //B C D
    QList<int> vList,vtList;
    vList << 1 << 2 << 4 << 4 << 3 << 1;
    vtList << 1 << 2 << 3 << 3 << 4 << 1;
    for(int i=0; i < vList.count(); i++ ){
        vList[i] = vList.at(i) + 4 * in_surfaceCnt;
        vtList[i] = vtList.at(i) + 4 * in_surfaceCnt;
    }
    QString tmpstr;
    g_out_obj1 << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d",
                                 vList.at(0), vtList.at(0), in_surfaceCnt + 1,
                                 vList.at(1), vtList.at(1), in_surfaceCnt + 1,
                                 vList.at(2), vtList.at(2), in_surfaceCnt + 1);
    g_out_obj1 << tmpstr.asprintf("f %d/%d/%d %d/%d/%d %d/%d/%d",
                                 vList.at(3), vtList.at(3), in_surfaceCnt + 1,
                                 vList.at(4), vtList.at(4), in_surfaceCnt + 1,
                                 vList.at(5), vtList.at(5), in_surfaceCnt + 1);

    //outfile1.close(); //objファイル書き込み。
}

void MainWindow::fileWriteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList)
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

