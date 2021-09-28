#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainTabs->setCurrentIndex(0);

    updateEverything();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateEverything()
{
    ui->obj3dViewer->setPerspective(ui->persVerticalAngleSpin->value(),
                                    ui->persNearSpin->value(),
                                    ui->persFarSpin->value());

    ui->obj3dViewer->setLookAt(QVector3D(ui->lookEyeXSpin->value(),
                                         ui->lookEyeYSpin->value(),
                                         ui->lookEyeZSpin->value()),
                               QVector3D(ui->lookCenterXSpin->value(),
                                         ui->lookCenterYSpin->value(),
                                         ui->lookCenterZSpin->value()),
                               QVector3D(ui->lookUpXSpin->value(),
                                         ui->lookUpYSpin->value(),
                                         ui->lookUpZSpin->value()));

    ui->obj3dViewer->setTranslation(ui->translateXSpin->value(),
                                    ui->translateYSpin->value(),
                                    ui->translateZSpin->value());

    ui->obj3dViewer->setScale(ui->scaleSpin->value());

    ui->obj3dViewer->setRotation(ui->rotateAngleSpin->value(),
                                 ui->rotateXSpin->value(),
                                 ui->rotateYSpin->value(),
                                 ui->rotateZSpin->value());

    ui->obj3dViewer->setLighting(QVector3D(ui->lightPosXSpin->value(),
                                           ui->lightPosYSpin->value(),
                                           ui->lightPosZSpin->value()),
                                 QVector3D(ui->lightKd1Spin->value(),
                                           ui->lightKd2Spin->value(),
                                           ui->lightKd3Spin->value()),
                                 QVector3D(ui->lightLd1Spin->value(),
                                           ui->lightLd2Spin->value(),
                                           ui->lightLd3Spin->value()));

    ui->obj3dViewer->update(); // have to call this manually (for better performance)
}

void MainWindow::on_persVerticalAngleSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_persNearSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_persFarSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookEyeXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookEyeYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookEyeZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookCenterXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookCenterYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookCenterZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookUpXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookUpYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lookUpZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_scaleSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_translateXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_translateYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_translateZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_rotateAngleSpin_valueChanged(double arg1)
{
    ui->rotateAngleSlider->setValue(arg1 * 10);
    updateEverything();
}

void MainWindow::on_rotateXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_rotateYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_rotateZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightPosXSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightPosYSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightPosZSpin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_action_Open_triggered()
{
    updateEverything();

    QVector<QOpenGLTriangle3D> triangles;
    QStringList comments;

    QString file = QFileDialog::getOpenFileName(this,
                                                "Open Object",
                                                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
                                                "*.obj");

    if(QFile(file).exists())
    {
        QObj3dReader().parseObjFile(file, comments, triangles);
        ui->obj3dViewer->setTriangles(triangles);
        qDebug() << "[DEBUG]MainWindow::on_action_Open_triggered"; //triangles" << triangles;
    }
}

void MainWindow::on_actionE_xit_triggered()
{
    close();
}

void MainWindow::on_persVerticalAngleSlider_valueChanged(int value)
{
    ui->persVerticalAngleSpin->setValue(double(value) / 100.0);
}

void MainWindow::on_persNearSlider_valueChanged(int value)
{
    ui->persNearSpin->setValue(double(value) / 100.0);
}

void MainWindow::on_persFarSlider_valueChanged(int value)
{
    ui->persFarSpin->setValue(double(value) / 100.0);
}

void MainWindow::on_lightKd1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightKd2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightKd3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightLd1Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightLd2Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_lightLd3Spin_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateEverything();
}

void MainWindow::on_textureFileEdit_returnPressed()
{
    ui->obj3dViewer->setTextureFile(ui->textureFileEdit->text());
    updateEverything();
}

void MainWindow::on_browseTextureBtn_pressed()
{
    QString file = QFileDialog::getOpenFileName(this,
                                                "Open Texture",
                                                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
                                                "*.jpg *.png *.tif *.bmp");
    ui->textureFileEdit->setText(file);
    on_textureFileEdit_returnPressed();
}

void MainWindow::on_rotateAngleSlider_valueChanged(int value)
{
    ui->rotateAngleSpin->setValue(double(value) / 10.0);
}

void MainWindow::on_DEBUG01_pushButton_clicked() //kuroda
{
}
//void MainWindow::on_DEBUG01_pushButton_clicked() //kuroda
//{
//    updateEverything();

//    QVector<QOpenGLTriangle3D> triangles;
//    QStringList comments;
//    triangles.clear();
////    QString file = QFileDialog::getOpenFileName(this,
////                                                "Open Object",
////                                                QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0),
////                                                "*.obj");
////
////    if(QFile(file).exists())
////    {
////        QObj3dReader().parseObjFile(file, comments, triangles);
////        ui->obj3dViewer->DEBUG01_setTriangles(triangles);
////        qDebug() << "[DEBUG]MainWindow::on_DEBUG01_pushButton_clicked "; //triangles" << triangles;
////    }

//    QVector<QVector3D> v, vn;
//    QVector<QVector2D> vt;


//    int in_i, in_j, in_k;
//    in_i = 1;
//    in_j = 1;
//    in_k = 1;
//    //GLfloat nowOP_x, nowOP_y , nowOP_z;
//    float nowOP_x, nowOP_y , nowOP_z;
//    float meshsize_x, meshsize_y, meshsize_z;
//    meshsize_x = 1;
//    meshsize_y = 1;
//    meshsize_z = 1;
//    nowOP_x = in_i * meshsize_x; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
//    nowOP_y = in_j * meshsize_y; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処
//    nowOP_z = in_k * meshsize_z; //kuroda変更　-0.5 では表示が小さすぎになってしまうための対処

//    //前準備 openGL座標作成 1メッシュ立方体の頂点座標を定義する
//    QVector3D vertexA = QVector3D(nowOP_x, nowOP_y, nowOP_z);
//    QVector3D vertexB = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z);
//    QVector3D vertexC = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z);
//    QVector3D vertexD = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z);
//    QVector3D vertexE = QVector3D(nowOP_x, nowOP_y, nowOP_z - meshsize_z);
//    QVector3D vertexF = QVector3D(nowOP_x + meshsize_x, nowOP_y, nowOP_z - meshsize_z);
//    QVector3D vertexG = QVector3D(nowOP_x + meshsize_x, nowOP_y + meshsize_y, nowOP_z - meshsize_z);
//    QVector3D vertexH = QVector3D(nowOP_x , nowOP_y + meshsize_y, nowOP_z - meshsize_z);

//    //[DEBUG]
//    vertexA = QVector3D(0, 0, 0); //Front, Bottom, Left
//    vertexB = QVector3D(1, 0, 0);
//    vertexC = QVector3D(1, 1, 0);
//    vertexD = QVector3D(0, 1, 0);
//    vertexE = QVector3D(0, 0, -1); //Back,  Bottom, Left
//    vertexF = QVector3D(1, 0, -1);
//    vertexG = QVector3D(1, 1, -1);
//    vertexH = QVector3D(0, 1, -1);

//    //前準備(openGL座標作成)  使う対象全部 前後・左右・上下で共通　　後処理trianglesアレイに入れる順番だけ違う。
//    vt.append(QVector2D(0, 0));
//    vt.append(QVector2D(1, 0));
//    vt.append(QVector2D(1, 1));
//    vt.append(QVector2D(0, 1));

//    //前準備(openGL座標作成) objファイルのf情報(v, vn, vt の描画上での並び） 使う対象全部 面：前後・左右・上下で共通
//    //f 1/1/1 2/2/1 4/3/1
//    //f 4/3/1 3/4/1 1/1/1
//    QList<int> vList,vtList;
//    //vList << 1 << 2 << 4 << 4 << 3 << 1;
//    vtList << 1 << 2 << 3 << 3 << 4 << 1;

//    //-start- openGL描画用情報作成
//    //in_surfaceStr = "Front";

//    QString in_surfaceStr = "Front";
//    //前準備(openGL座標作成)
//    QVector<QVector3D> rectVec; //Front など 1平面（四角形の4頂点をopenGL描画用の並びにした座標リスト
//    rectVec.clear();
//    //Front
//    rectVec << vertexA; //1つ目の三角形
//    rectVec << vertexB;
//    rectVec << vertexC;
//    rectVec << vertexC; //2つ目の三角形
//    rectVec << vertexD;
//    rectVec << vertexA;

//    //前準備(openGL座標作成) objファイルのvn情報　(法線)
////    if(in_surfaceStr == "Front"){  vnStr = "vn 0.0000 0.0000 1.0000" ; }
////    if(in_surfaceStr == "Back"){   vnStr = "vn 0.0000 0.0000 -1.0000" ; }
////    if(in_surfaceStr == "Right"){  vnStr = "vn 1.0000 0.0000 0.0000" ; }
////    if(in_surfaceStr == "Left"){   vnStr = "vn -1.0000 0.0000 0.0000" ; }
////    if(in_surfaceStr == "Top"){    vnStr = "vn 0.0000 1.0000 0.0000" ; }
////    if(in_surfaceStr == "Bottom"){ vnStr = "vn 0.0000 -1.0000 0.0000" ; }
//    QVector3D vn_now;
//    vn_now = QVector3D(0, 0, 1);
//    if(in_surfaceStr == "Front"){ vn_now = QVector3D(0, 0, 1);  }
//    if(in_surfaceStr == "Back"){  vn_now = QVector3D(0, 0, -1); }
//    if(in_surfaceStr == "Right"){ vn_now = QVector3D(1, 0, 0);  }
//    if(in_surfaceStr == "Left"){  vn_now = QVector3D(-1, 0, 0); }
//    if(in_surfaceStr == "Top"){   vn_now = QVector3D(0, 1, 0);  }
//    if(in_surfaceStr == "Bottom"){vn_now = QVector3D(0, -1, 0); }

//    // 1平面(四角形)-1つ目の三角形 頂点情報 (objファイルのvt)
//    QOpenGLTriangle3D triangle;
//    triangle.p1 = rectVec.at(0);
//    triangle.p2 = rectVec.at(1);
//    triangle.p3 = rectVec.at(2);
//    //-start- [DEBUG]
////    triangle.p1 = QVector3D(0, 0, 0); //Front, Bottom, Left
////    triangle.p2 = QVector3D(1, 0, 0);
////    triangle.p3 = QVector3D(1, 1, 0);
//    //-end- [DEBUG]

//    triangle.p1UV = vt.at(vtList.at(0)-1);
//    triangle.p2UV = vt.at(vtList.at(1)-1);
//    triangle.p3UV = vt.at(vtList.at(2)-1);

//    triangle.p1Normal = vn_now;
//    triangle.p2Normal = vn_now;
//    triangle.p3Normal = vn_now;

//    triangles.append(triangle);

//    // 1平面(四角形)-2つ目の三角形 頂点情報 (objファイルのvt)
//    QOpenGLTriangle3D triangle2;
////    triangle2.p1 = rectVec.at(3);
////    triangle2.p2 = rectVec.at(4);
////    triangle2.p3 = rectVec.at(5);
//    //-start- [DEBUG]
//    triangle2.p1 = QVector3D(1, 1, 0);
//    triangle2.p2 = QVector3D(0, 1, 0);
//    triangle2.p3 = QVector3D(0, 0, 0);
//    //-end- [DEBUG]

////    triangle2.p1UV = vt.at(vtList.at(3)-1);
////    triangle2.p2UV = vt.at(vtList.at(4)-1);
////    triangle2.p2UV = vt.at(vtList.at(5)-1);
//    triangle2.p1UV = vt.at(2);
//    triangle2.p2UV = vt.at(3);
//    triangle2.p3UV = vt.at(0);

//    triangle2.p1Normal = vn_now;
//    triangle2.p2Normal = vn_now;
//    triangle2.p3Normal = vn_now;
//    triangles.append(triangle2);

//    ui->obj3dViewer->setTriangles(triangles);
//}
