// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"


MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    alpha = 25;
    beta = -25;
    distance = 2.5;

    g_paintExeFlag = 0; //kuroda プログラム起動時点では描画しない。
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(640, 480);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}


//! [0]
//void MyGLWidget::initializeGL()
//{
//    //! [0]
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

//    qglClearColor(QColor(Qt::black));

//    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
//    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
//    shaderProgram.link();

////    vertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) // Front
////             << QVector3D( 0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5)
////             << QVector3D( 0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) // Back
////             << QVector3D(-0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5)
////             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) // Left
////             << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
////             << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) // Right
////             << QVector3D( 0.5,  0.5, -0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5)
////             << QVector3D(-0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) << QVector3D( 0.5,  0.5, -0.5) // Top
////             << QVector3D( 0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5,  0.5)
////             << QVector3D(-0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5,  0.5) // Bottom
////             << QVector3D( 0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5, -0.5, -0.5);

//    //QVector(X,Y,Z) ←　openGL では(正面から見て) X:左右　Y：上下　Z:奥行。（手前＋、奥が- で通常の座標と違う）
//    //↑　通常座標 (x, y, z)が入力されたら、openGL座標(X1, Y1, Z1) =  (x, z, -y) で代入することになる ※openGL座標は奥行Z1方向手前が+になるので -yにする
//    vertices << QVector3D(-0.2, -0.5,  0.9) << QVector3D( 0.2, -0.5,  0.9) << QVector3D( 0.2,  0.5,  0.9) // Front
//             << QVector3D( 0.2,  0.5,  0.9) << QVector3D(-0.2,  0.5,  0.9) << QVector3D(-0.2, -0.5,  0.9)
//             << QVector3D( 0.2, -0.5, -0.9) << QVector3D(-0.2, -0.5, -0.9) << QVector3D(-0.2,  0.5, -0.9) // Back
//             << QVector3D(-0.2,  0.5, -0.9) << QVector3D( 0.2,  0.5, -0.9) << QVector3D( 0.2, -0.5, -0.9)
//             << QVector3D(-0.2, -0.5, -0.9) << QVector3D(-0.2, -0.5,  0.9) << QVector3D(-0.2,  0.5,  0.9) // Left
//             << QVector3D(-0.2,  0.5,  0.9) << QVector3D(-0.2,  0.5, -0.9) << QVector3D(-0.2, -0.5, -0.9)
//             << QVector3D( 0.2, -0.5,  0.9) << QVector3D( 0.2, -0.5, -0.9) << QVector3D( 0.2,  0.5, -0.9) // Right
//             << QVector3D( 0.2,  0.5, -0.9) << QVector3D( 0.2,  0.5,  0.9) << QVector3D( 0.2, -0.5,  0.9)
//             << QVector3D(-0.2,  0.5,  0.9) << QVector3D( 0.2,  0.5,  0.9) << QVector3D( 0.2,  0.5, -0.9) // Top
//             << QVector3D( 0.2,  0.5, -0.9) << QVector3D(-0.2,  0.5, -0.9) << QVector3D(-0.2,  0.5,  0.9)
//             << QVector3D(-0.2, -0.5, -0.9) << QVector3D( 0.2, -0.5, -0.9) << QVector3D( 0.2, -0.5,  0.9) // Bottom
//             << QVector3D( 0.2, -0.5,  0.9) << QVector3D(-0.2, -0.5,  0.9) << QVector3D(-0.2, -0.5, -0.9);

//    //! [1] 直方体1面分=3角形2つ=頂点数6個
////    colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Front
////           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
////           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Back
////           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
////           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Left
////           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
////           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right
////           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
////           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Top
////           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1)
////           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom
////           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);

//    myfunction *m_myfunction = new myfunction;
//    QVector3D tmpColor = m_myfunction->func_defineColor(0);
//    colors << tmpColor << tmpColor << tmpColor // Front
//           << tmpColor << tmpColor << tmpColor
//           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Back
//           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Left
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Right
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Top
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1)
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) // Bottom
//           << QVector3D(0, 0, 1) << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);
//}
//! [1]

//void MyGLWidget::initializeGL()
//{
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

//    qglClearColor(QColor(Qt::black));

//    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
//    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
//    shaderProgram.link();
//    //　6組で一つの四角形=3角形2つ分　描き方としては 6個は1つながりである必要があるが。Front, Left など別項目図形はつながってなくて良い。(前に描いた座標に近い方からの順番でないとだめとかはない）
//    vertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5) // Front
//             << QVector3D( 0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5, -0.5,  0.5)
//             << QVector3D(-0.5, -0.5, -0.5) << QVector3D(-0.5, -0.5,  0.5) << QVector3D(-0.5,  0.5,  0.5) // Left
//             << QVector3D(-0.5,  0.5,  0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5)
//             << QVector3D(-0.5, -0.5, -0.5) << QVector3D( 0.5, -0.5, -0.5) << QVector3D( 0.5,  0.5, -0.5) // Back
//             << QVector3D( 0.5,  0.5, -0.5) << QVector3D(-0.5,  0.5, -0.5) << QVector3D(-0.5, -0.5, -0.5);

//    colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) // Front
//           << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) // Left
//           << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
//           << QVector3D(1, 1, 0) << QVector3D(1, 1, 0) << QVector3D(1, 1, 0) // Back
//           << QVector3D(1, 1, 0) << QVector3D(1, 1, 0) << QVector3D(1, 1, 0);
//}

void MyGLWidget::initializeGL()
{
    //! [0]
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    qglClearColor(QColor(Qt::black));

    shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fragmentShader.fsh");
    shaderProgram.link();

}

void MyGLWidget::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(0, 0, width, height);
}

//! [2]
void MyGLWidget::paintGL()
{
    //-start- kuroda
    if(g_paintExeFlag == 0){ return; } //kuroda-2021.05.xx
    if(! QFile::exists(g_voxfilepath)){
        //QMessageBox::information(this, "notice", "Error Nofile voxpath=" + g_voxfilepath);
        qDebug() << "[DEBUG]Error Nofile voxpath=" << g_voxfilepath;
        return;
    }

    miWidget *m_miWidget = new miWidget;
    //[DEBUG]vertices = m_miWidget->func_get_voxGraffic("C:/kuroda/work/00_Data_vox/test_mini_vox.txt" , "vertex");
    //[DEBUG]colors   = m_miWidget->func_get_voxGraffic("C:/kuroda/work/00_Data_vox/test_mini_vox.txt" , "color");
    vertices = m_miWidget->func_get_voxGraffic(g_voxfilepath , "vertex");
    colors   = m_miWidget->func_get_voxGraffic(g_voxfilepath , "color");
    //帰り値を一度に取得   //std::tie(vertices, colors) = m_miWidget->func_get_voxGraffic(g_voxfilepath, gval_MainWindow_uiTableListMat, "vertex");
    //qDebug() << "MyGLWidget.cpp-initializeGL vertices=" << vertices;
    //qDebug() << "MyGLWidget.cpp-initializeGL colors=" << colors;

    //-end- kuroda

    //! [2]
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);

    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

    //! [3]
    shaderProgram.bind();

    shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

    shaderProgram.setAttributeArray("vertex", vertices.constData());
    shaderProgram.enableAttributeArray("vertex");

    shaderProgram.setAttributeArray("color", colors.constData());
    shaderProgram.enableAttributeArray("color");

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    shaderProgram.disableAttributeArray("vertex");

    shaderProgram.disableAttributeArray("color");

    shaderProgram.release();
}
//! [3]

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();

    event->accept();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();

    if (event->buttons() & Qt::LeftButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }
        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        if (beta < -90) {
            beta = -90;
        }
        if (beta > 90) {
            beta = 90;
        }

        updateGL();
    }

    lastMousePosition = event->pos();

    event->accept();
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();

    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            distance *= 1.1;
        } else if (delta > 0) {
            distance *= 0.9;
        }

        updateGL();
    }

    event->accept();
}

void MyGLWidget::func_DEBUG_kuroda(){
     g_paintExeFlag =1;
     g_voxfilepath = "C:/kuroda/work/Qt/00_Data_vox/test_mini_vox.txt";

     updateGL();

    //miWidget *m_miWidget = new miWidget;
    //QVector<QVector3D> my_verticesVector = m_miWidget->func_get_voxGraffic("C:/kuroda/work/Qt/00_Data_vox/test_mini0_my_vox.txt" , "vertex");
    //QVector<QVector3D> my_colorsVector = m_miWidget->func_get_voxGraffic("C:/kuroda/work/Qt/00_Data_vox/test_mini0_my_vox.txt" , "vertex");

    //qDebug() << "MyGLWidget.cpp-func_DEBUG_kuroda() vertexList=" << vertexList;
    //qDebug() << "MyGLWidget.cpp-func_DEBUG_kuroda() colorList=" << colorList;
}

void MyGLWidget::func_load_voxfile(QString in_voxfilepath) //ユーザーGUI操作によるvoxファイルオープンから、widget画面への表示処理
{
    if(! QFile::exists(in_voxfilepath)){
        QMessageBox::information(this, "notice", "Error Nofile voxpath=" + in_voxfilepath);
        return;
    }

    g_paintExeFlag = 1; //描画フラグをON
    g_voxfilepath = in_voxfilepath;

    //初期値セット
    xRot = 0;
    yRot = 0;
    zRot = 0;

    alpha = 25;
    beta = -25;
    distance = 2.5;

    updateGL(); //updateで描画開始　→ inializeGL →　paintGL

}
