#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QSettings>

#include "qobj3dreader.h"
#include "voxRead_makeGLdata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_persVerticalAngleSpin_valueChanged(double arg1);

    void on_persNearSpin_valueChanged(double arg1);

    void on_persFarSpin_valueChanged(double arg1);

    void on_lookEyeXSpin_valueChanged(double arg1);

    void on_lookEyeYSpin_valueChanged(double arg1);

    void on_lookEyeZSpin_valueChanged(double arg1);

    void on_lookCenterXSpin_valueChanged(double arg1);

    void on_lookCenterYSpin_valueChanged(double arg1);

    void on_lookCenterZSpin_valueChanged(double arg1);

    void on_lookUpXSpin_valueChanged(double arg1);

    void on_lookUpYSpin_valueChanged(double arg1);

    void on_lookUpZSpin_valueChanged(double arg1);

    void on_scaleSpin_valueChanged(double arg1);

    void on_translateXSpin_valueChanged(double arg1);

    void on_translateYSpin_valueChanged(double arg1);

    void on_translateZSpin_valueChanged(double arg1);

    void on_rotateAngleSpin_valueChanged(double arg1);

    void on_rotateXSpin_valueChanged(double arg1);

    void on_rotateYSpin_valueChanged(double arg1);

    void on_rotateZSpin_valueChanged(double arg1);

    void on_lightPosXSpin_valueChanged(double arg1);

    void on_lightPosYSpin_valueChanged(double arg1);

    void on_lightPosZSpin_valueChanged(double arg1);

    void on_actionAbout_Qt_triggered();

    void on_action_Open_triggered();

    void on_actionE_xit_triggered();

    void on_persVerticalAngleSlider_valueChanged(int value);

    void on_persNearSlider_valueChanged(int value);

    void on_persFarSlider_valueChanged(int value);

    void on_lightKd1Spin_valueChanged(double arg1);

    void on_lightKd2Spin_valueChanged(double arg1);

    void on_lightKd3Spin_valueChanged(double arg1);

    void on_lightLd1Spin_valueChanged(double arg1);

    void on_lightLd2Spin_valueChanged(double arg1);

    void on_lightLd3Spin_valueChanged(double arg1);

    void on_textureFileEdit_returnPressed();

    void on_browseTextureBtn_pressed();

    void on_rotateAngleSlider_valueChanged(int value);

    void on_DEBUG01_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void updateEverything();

};

#endif // MAINWINDOW_H
