//#ifndef WINDOW_H
//#define WINDOW_H

//#include <QWidget>

//QT_BEGIN_NAMESPACE
//namespace Ui { class Window; }
//QT_END_NAMESPACE

//class Window : public QWidget
//{
//    Q_OBJECT

//public:
//    Window(QWidget *parent = nullptr);
//    ~Window();

//private:
//    Ui::Window *ui;
//};
//#endif // WINDOW_H

// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QSlider>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:

    void on_pushButton_DEBUG_clicked();
    void on_pushButton_voxpathSelect_clicked();
    void on_pushButton_voxpathLoad_clicked();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
