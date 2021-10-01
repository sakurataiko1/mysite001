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
    updateEverything();

    QVector<QOpenGLTriangle3D_vox> triangles;
    QStringList comments;

    //QString voxfilepath = "c:/tmp/tmp.vox";
    QString voxfilepath = QFileDialog::getOpenFileName(this,"Open vox",QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0) ) ; //, "*obj");

    if(QFile(voxfilepath).exists())
    {
        voxRead_makeGLdata().func_01main_GL_make_getPointOfMesh(triangles, voxfilepath);

        qDebug() << "[DEBUG]MainWindow.cpp-on_DEBUG01_pushButton_clicked(): start openGL-draw-setTriangle " +  QDateTime::currentDateTime().toString("hh:mm:ss");
        ui->obj3dViewer->DEBUG01_setTriangles(triangles);
        qDebug() << "[DEBUG]MainWindow.cpp-on_DEBUG01_pushButton_clicked(): end openGL-draw-setTriangle " +  QDateTime::currentDateTime().toString("hh:mm:ss");
    } else {
        QMessageBox::information(this, "notice", "file non-exsist " + voxfilepath);
    }

}
