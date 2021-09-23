#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include <QWidget>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLWindow>
#include <QOpenGLVertexArrayObject>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLVertexArrayObject>
#include <QMouseEvent>
#include <QMouseEventTransition>
#include <QOpenGLShader>
#include <QtOpenGL/QtOpenGL>
#include <QVector3D>
#include <QArrayData>
#include <gl/GL.h>
#include <gl/GL.h>
#include <math.h>
#include <QMatrix4x4>

#include <QSurfaceFormat>
#include <GL/GLU.h>
#include <gl/GL.h>

#include <QDebug>

class myfunction : public QWidget
{
    Q_OBJECT
public:
    explicit myfunction(QWidget *parent = nullptr);
    ~myfunction();

    QVector3D func_defineColor(int input_num);

    void fileWriteForWindows(QString WriteFilePath, QString WriteMode, QStringList msgList);
    QStringList readTextFileAll(QString fileName);//ファイル読み込みして、1行ごとにリストに格納する

signals:


};

#endif // MYFUNCTION_H
