/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#include "m_block.h"
#include <QBrush>
#include <QDebug>
#include <QGraphicsScene>
//#include <QTimer>
#include <QList>
#include <QGraphicsView>
#include <ctime>
#include <cstdlib>

/** This is the constructor of Block object
 * @param x is the top-left x coordinate of the block
 * @param y is the top-left y coordinate of the block
*/
Block::Block(int x, int y):loc_x(x),loc_y(y),block_w(50),block_h(25),random_drop(nullptr){
    setRect(loc_x,loc_y,block_w,block_h);
    setBrush(Qt::red);


}

/** This function access the width of the block
 * @returns the width of the block
*/
const int Block::block_width()
{
    return block_w;
}
/** This function access the height of the block
 * @returns the height of the block
*/
const int Block::block_height()
{
    return block_h;
}
/** This function spawns the drop item for the block
*/
void Block::drop_spawn()
{
    srand(time(nullptr));
    if(rand()%3==0){
        random_drop=new Drop(loc_x,loc_y);
        (this->scene())->addItem(random_drop);
        qDebug()<<"drop created and added to the scene";
        QList<QGraphicsView*> viewlist=this->scene()->views();
        QTimer* drop_timer_local= new QTimer(viewlist[0]);
        //QTimer* drop_timer= new QTimer(this);
        QObject::connect(drop_timer_local,SIGNAL(timeout()),this,SLOT(drop_move()));
        drop_timer_local->start(50);
        random_drop->set_timer(drop_timer_local);
    }
}

/** This function access the drop pointer which points to the drop created by the block
 * @returns the drop pointer
*/
Drop *Block::drop_pointer()
{
    return random_drop;
}
/*
QTimer *Block::timer()
{
    return drop_timer;
}
*/

/** This function access the x coordinate of the block
 * returns the x coordinate of the block
*/
const int Block::block_loc_x() const
{
    return loc_x;
}

/** This function access the y coordinate of the block
 * returns the y coordinate of the block
*/
const int Block::block_loc_y() const
{
    return loc_y;
}

/** This function moves the drop created by the block
*/
void Block::drop_move()
{
    random_drop->drop_move();
}

