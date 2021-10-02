#include "qobj3dviewer.h"
#include <QDebug>

QObj3dViewer::QObj3dViewer(QWidget *parent) : QOpenGLWidget(parent)
{
    texture = Q_NULLPTR;
}

QObj3dViewer::~QObj3dViewer()
{
    if(texture != Q_NULLPTR)
        delete texture;
}

void QObj3dViewer::setTriangles(QVector<QOpenGLTriangle3D> &_triangles)
{
    triangles.clear();
    normals.clear();

    for(int i=0; i<_triangles.count(); i++)
    {
        triangles.append(_triangles.at(i).p1);
        triangles.append(_triangles.at(i).p2);
        triangles.append(_triangles.at(i).p3);

        normals.append(_triangles.at(i).p1Normal);
        normals.append(_triangles.at(i).p2Normal);
        normals.append(_triangles.at(i).p3Normal);

        textureUV.append(_triangles.at(i).p1UV);
        textureUV.append(_triangles.at(i).p2UV);
        textureUV.append(_triangles.at(i).p3UV);
    }

    update();
}

void QObj3dViewer::initializeGL()
{
    initializeOpenGLFunctions();

    //-start- org
//    Q_ASSERT(openglProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
//                                                   ":/vert-shader.vsh"));

//    Q_ASSERT(openglProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
//                                                       ":/frag-shader.fsh"));

//    Q_ASSERT(openglProgram.link());
//    Q_ASSERT(openglProgram.bind());
    //-end- org

    //-start- new
    openglProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vert-shader.vsh");
    openglProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/frag-shader.fsh");
    openglProgram.link();
    //openglProgram.bind(); //bind は　paintGLに書く
    //-end- new

    perspective.aspectRatio =  height() > 0.0f ? float(width()) / float(height()) : 1.0f;

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE); //kuroda 片面のみ表示する設定（コメントアウなしで有効だと回転途中で見えなくなってしまう。） 透明の時もこれで実際OKだった。　//チュートリアルによると有効にするべきかもしれないが、今回はそうしていない。→ (glDesableをオフが必須とのこと）http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-10-transparency/

    glEnable(GL_BLEND); //kuroda 透明表示のため追加
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //kuroda 透明表示のため追加

}

void QObj3dViewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    openglProgram.bind(); //new OpenGLshaderクラスの場合はInitializeに書いていたが、 QGLshaderProgramに変更して位置も変更

    projectionMat.setToIdentity();
    projectionMat.perspective(perspective.verticalAngle, perspective.aspectRatio, perspective.nearPlane, perspective.farPlane);

    viewMat.setToIdentity();
    viewMat.lookAt(lookAt.eye, lookAt.center, lookAt.up);

    modelMat.setToIdentity();
    modelMat.scale(modelScale);
    modelMat.rotate(modelRotation);
    modelMat.translate(modelTranslation);

    openglProgram.enableAttributeArray("vertexPosition");
    openglProgram.setAttributeArray("vertexPosition", triangles.constData());

    openglProgram.enableAttributeArray("vertexNormal");
    openglProgram.setAttributeArray("vertexNormal", normals.constData());

    openglProgram.enableAttributeArray("vertexUV_a");
    openglProgram.setAttributeArray("vertexUV_a", textureUV.constData());

    if(texture != Q_NULLPTR)
    {
        openglProgram.setUniformValue("renderTexture", true);
        openglProgram.setUniformValue("texture", 0);
        texture->bind();
    }
    else
    {
        openglProgram.setUniformValue("renderTexture", false);
    }

    openglProgram.setUniformValue("normalMatrix", modelMat.normalMatrix()); // world normal
    openglProgram.setUniformValue("modelViewMatrix", viewMat * modelMat);
    openglProgram.setUniformValue("projectionMatrix", projectionMat);
    openglProgram.setUniformValue("modelViewProjMatrix", projectionMat * viewMat * modelMat);

    openglProgram.setUniformValue("lightPosition", lightPosition);
    openglProgram.setUniformValue("lightKd", lightKd);
    openglProgram.setUniformValue("lightLd", lightLd);

    //-start- kuroda [DEBUG] テストデータ1平面　色設定用
    //QVector<QVector3D> colors;
    //-start- NG
    //colors << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
    //       << QVector3D(1, 0, 0) << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
    //       << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
    //       << QVector3D(0, 1, 0) << QVector3D(0, 1, 0) << QVector3D(0, 1, 0);
    //-end- NG
    //-start- OK
    //for(int i=0; i<triangles.count(); i++){
    //    if(i < 1) {
    //        colors.append(QVector3D(1, 0, 0));
    //        colors.append(QVector3D(1, 0, 0));
    //        colors.append(QVector3D(1, 0, 0));
    //    } else {
    //        colors.append(QVector3D(0, 0, 1));
    //        colors.append(QVector3D(0, 0, 1));
    //        colors.append(QVector3D(0, 0, 1));
    //    }
    //}
    //openglProgram.setAttributeArray("color", colors.constData());
    //openglProgram.enableAttributeArray("color");
    //-end- OK
    openglProgram.setAttributeArray("color", g_GLColors.constData());
    openglProgram.enableAttributeArray("color");

    //-end- kuroda [DEBUG] 1平面用

    //-start- kuroda [DEBUG] テストデータ1平面　半透明色設定用
    //QVector<float> acolors;
    //for(int i=0; i<triangles.count(); i++){
    //    acolors.append(0.3); //半透明
    //  if(i < 1) {
    //      acolors.append(0.3); //半透明
    //  } else {
    //      acolors.append(1.0); //通常色（透明にしない）
    //  }
    //}
    //openglProgram.setAttributeArray("acolor", acolors.constData()); //記述ミスしていた。。 colorsでなく, acolorsが正しいが、それだと文法エラー。。これから考える
    //openglProgram.enableAttributeArray("acolor");
    //↑半透明設定　マテリアルごといまだできずのため　↓　全部半透明のための設定

    float acolorOne;
    acolorOne = 0.3; //半透明
    openglProgram.setUniformValue("acolorOne", acolorOne);

    //-end- kuroda [DEBUG] 1平面用　半透明色設定用

    glDrawArrays(GL_TRIANGLES, 0, triangles.count());

    //qDebug() << "[DEBUG]qobj3dviewr.cpp-paintGL";
}

void QObj3dViewer::resizeGL(int w, int h)
{
    perspective.aspectRatio =  h > 0.0f ? float(w) / float(h) : 1.0f;
}

void QObj3dViewer::setRotation(float angle, float x, float y, float z)
{
    modelRotation = QQuaternion::fromAxisAndAngle(x, y, z, angle);
}

void QObj3dViewer::setTranslation(float x, float y, float z)
{
    modelTranslation = QVector3D(x, y, z);
}

void QObj3dViewer::setScale(float s)
{
    modelScale = s;
}

void QObj3dViewer::setPerspective(float verticalAngle, float nearPlane, float farPlane)
{
    perspective.verticalAngle = verticalAngle;
    perspective.nearPlane = nearPlane;
    perspective.farPlane = farPlane;
}

void QObj3dViewer::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    lookAt.eye = eye;
    lookAt.center = center;
    lookAt.up = up;
}

void QObj3dViewer::setLighting(const QVector3D &lightPos, const QVector3D &kd, const QVector3D &ld)
{
    lightPosition = lightPos;
    lightKd = kd;
    lightLd = ld;
}

void QObj3dViewer::setTextureFile(const QString &file)
{
    if(texture == Q_NULLPTR)
        delete texture;
    texture = new QOpenGLTexture(QImage(file).mirrored());
}

void QObj3dViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << Q_FUNC_INFO << "Not implemented yet!";
}

void QObj3dViewer::DEBUG01_setTriangles(QVector<QOpenGLTriangle3D_vox> &_triangles)
{
    triangles.clear();
    normals.clear();

    for(int i=0; i<_triangles.count(); i++)
    //for(int i=0; i<6; i++)
    {
        triangles.append(_triangles.at(i).p1);
        triangles.append(_triangles.at(i).p2);
        triangles.append(_triangles.at(i).p3);

        normals.append(_triangles.at(i).p1Normal);
        normals.append(_triangles.at(i).p2Normal);
        normals.append(_triangles.at(i).p3Normal);

        textureUV.append(_triangles.at(i).p1UV);
        textureUV.append(_triangles.at(i).p2UV);
        textureUV.append(_triangles.at(i).p3UV);

        g_GLColors.append(_triangles.at(i).color); //色は3頂点とも同色を入れる
        g_GLColors.append(_triangles.at(i).color);
        g_GLColors.append(_triangles.at(i).color);
    }

    update();
}
