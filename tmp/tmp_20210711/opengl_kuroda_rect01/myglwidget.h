// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

#include <QGLWidget> // kuroda Qtチュートリアルサンプルから流用
#include <QGLShaderProgram> // kuroda Qtチュートリアルサンプルから流用

#include <miwidget.h>
#include <myfunction.h>

#include <tuple> //kuroda 2021.06.xx-01 //2つ以上の帰り値を返すため　std::tuple, std::forward_as_tuple, std::tie で使用する

//class MiWidget;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    int g_paintExeFlag; //kuroda 2021.05.xx-01
    QString g_voxfilepath; //kuroda 2021.05.xx-01
    void func_DEBUG_kuroda();
    void func_load_voxfile(QString in_voxfilepath); //kuroda ユーザーGUI操作に夜voxファイルオープンから、widget画面への表示処理

    //-start- [DEBUG]
    QVector<QVector3D> g_verticesVector; //kuroda
    QVector<QVector3D> g_colorsVector; //kuroda
    void func_getPointOfMesh_newDEBUG(int i, int j, int k, int surfaceNo, int input_MateNo);
    //-end- [DEBUG]

signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:


    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

    //-start- kuroda Qtチュートリアルサンプルから流用
    //! [1]
    QMatrix4x4 pMatrix;
    QGLShaderProgram shaderProgram;
    QVector<QVector3D> vertices;
    //! [2]
    QVector<QVector3D> colors;
    //! [2]
    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;
    //! [3]
    //-end- kuroda Qtチュートリアルサンプルから流用
};

#endif // MYGLWIDGET_H

