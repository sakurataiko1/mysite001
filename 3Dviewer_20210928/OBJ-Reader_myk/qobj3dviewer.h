#ifndef QOBJ3DVIEWER_H
#define QOBJ3DVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QQuaternion>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QPoint>

#include <QtMath>

#include "qobj3dreader.h"
#include "voxRead_makeGLdata.h"

class QObj3dViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit QObj3dViewer(QWidget *parent = 0);
    ~QObj3dViewer();

    void setTriangles(QVector<QOpenGLTriangle3D> &_triangles);
    void setTextureFile(const QString &file);

    void DEBUG01_setTriangles(QVector<QOpenGLTriangle3D_vox> &_triangles);
    QVector<QVector3D> g_GLColors;

public slots:
    void setRotation(float angle, float x, float y, float z);
    void setTranslation(float x, float y, float z);
    void setScale(float s);
    void setPerspective(float verticalAngle, float nearPlane, float farPlane);
    void setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up);
    void setLighting(const QVector3D &lightPos, const QVector3D &kd, const QVector3D &ld);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:

public slots:

private:
    QVector<QVector3D> triangles;
    QVector<QVector3D> normals;
    QVector<QVector2D> textureUV;
    QOpenGLTexture *texture;

    //org//QOpenGLShaderProgram openglProgram;
    QGLShaderProgram openglProgram;

    QQuaternion modelRotation;
    QVector3D modelTranslation;
    float modelScale;
    QMatrix4x4 modelMat, viewMat, projectionMat;

    struct
    {
        float verticalAngle;
        float aspectRatio;
        float nearPlane;
        float farPlane;
    } perspective;

    struct
    {
        QVector3D eye;
        QVector3D center;
        QVector3D up;
    } lookAt;

    QVector3D lightPosition;
    QVector3D lightKd;
    QVector3D lightLd;

    QPoint lastMousePos;

};

#endif // QOBJ3DVIEWER_H
