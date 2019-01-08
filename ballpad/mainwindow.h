#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>


class QGraphicsScene;
class QGraphicsView;
class QPushButton;
class QLabel;
class QKeyEvent;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
     bool eventFilter(QObject *object, QEvent *event);

private slots:
    void genButt_clicked();
    void colButt_clicked();

private:
    void initScene();
    void initSceneBackground();
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *genButt;
    QPushButton *colButt;
    QLabel *count;
    QLabel *num;


};

#endif // MAINWINDOW_H
