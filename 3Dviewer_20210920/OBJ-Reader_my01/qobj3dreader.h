#ifndef QOBJ3DREADER_H
#define QOBJ3DREADER_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QString>
#include <QStringList>

struct QOpenGLTriangle3D
{
    QVector3D p1;
    QVector3D p2;
    QVector3D p3;
    QVector3D p1Normal;
    QVector3D p2Normal;
    QVector3D p3Normal;
    QVector2D p1UV;
    QVector2D p2UV;
    QVector2D p3UV;
};

class QObj3dReader : public QObject
{
    Q_OBJECT
public:
    explicit QObj3dReader(QObject *parent = 0);

    void parseObjFile(const QString &fileName,
                      QStringList &comments,
                      QVector<QOpenGLTriangle3D> &triangles);

signals:

public slots:

};

#endif // QOBJ3DREADER_H
