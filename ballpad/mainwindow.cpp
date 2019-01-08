#include "mainwindow.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QLabel>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
#include <QList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene,this)),
      genButt(new QPushButton("New shape",this)),
      colButt(new QPushButton("New Color",this)),
      count(new QLabel(this)),
      num(new QLabel(this))
{
    setCentralWidget(view);
    resize(800,600);

    genButt->setGeometry(QRect(10,10,100,50));
    QObject::connect(genButt,&QPushButton::clicked,this,&MainWindow::genButt_clicked);

    colButt->setGeometry(QRect(10,60,100,50));
    QObject::connect(colButt, &QPushButton::clicked,this,&MainWindow::colButt_clicked);



    count->setText("<b>Count:</b>");
    count->setGeometry(QRect(150,10,100,50));


    num->setNum(0);
    num->setGeometry(QRect(200,10,50,50));



    initScene();
    initSceneBackground();
    scene->installEventFilter(this);




}

MainWindow::~MainWindow()
{

}

void MainWindow::initScene() {
    scene->setSceneRect(0,0,800,600);
}

void MainWindow::initSceneBackground() {
    scene->setBackgroundBrush(Qt::gray);
}

void MainWindow::genButt_clicked() {
   static int num_clk =0;
   num_clk = num->text().toInt();
   ++num_clk;
   if(num_clk > 5) return;
   num->setNum(num_clk);
   int pos_x = QRandomGenerator::global()->bounded(-20,700);
   int pos_y = QRandomGenerator::global()->bounded(-20,500);
    QGraphicsEllipseItem * circle =scene ->addEllipse(pos_x,pos_y,100,100,QPen(Qt::NoPen),QBrush(Qt::red));
    circle->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

void MainWindow::colButt_clicked() {
    if(!scene->items().isEmpty()) {

      QList<QGraphicsItem*> item_List = scene->items();
      int i =  QRandomGenerator::global()->bounded(0,item_List.size());
       QGraphicsEllipseItem *item = static_cast<QGraphicsEllipseItem *>(item_List[i]);
       item->setBrush(QColor(rand() % 256,rand() % 256,rand() % 256));
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event){
    if(event ->type() == QEvent::KeyPress ) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_X) {
            if(!scene->selectedItems().isEmpty()) {
                scene->removeItem(scene->selectedItems().front());

                    int num_clk = num->text().toInt();
                    --num_clk;
                    num->setNum(num_clk);

            }
            return true;
        } else
            return false;
    }
    return QMainWindow::eventFilter(object,event);
}
