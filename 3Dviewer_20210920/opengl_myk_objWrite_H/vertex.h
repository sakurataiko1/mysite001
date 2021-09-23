#ifndef VERTEX_H
#define VERTEX_H

#include <QDialog>
#include <QVector3D>

//kuroda 松岡さんプログラムより流用　いらないかもしれないが。。

//頂点クラス
class Vertex{








public:



    Vertex();
    Vertex(const QVector3D &position): m_position(position){}

    static int positionOffset(){return offsetof(Vertex, m_position);}
    static int stride(){return sizeof(Vertex);}



private:
    QVector3D m_position;
};
#endif // VERTEX_H
