#include "drop.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <ctime>
#include <cstdlib>

/** This function is the constructor of drop object
 * @param x is the top-left x coordinate of the drop
 * @param y is the top-left y coordinate of the drop
 * @param drop_timer is the timer that takes care of the drop process
*/
Drop::Drop(double x, double y):loc_x(x),loc_y(y),drop_timer(nullptr)
{
    setRect(loc_x,loc_y,10,10);
    setBrush(Qt::yellow);
}

/** This function is an accessor
 * @returns the x coordinate of the drop
*/
double Drop::drop_loc_x() const
{
    return loc_x;
}

/** This function is an accessor
 * @returns the y coordinate of the drop
*/
double Drop::drop_loc_y() const
{
    return loc_y;
}
/*
Drop_Func Drop::functional()
{
    Drop_Func new_function;
    switch(rand()%2){
       default:new_function=RESET;
    }
    for(int i=0,n=timers.size();i<n;++i){
        if(timers[i]!=nullptr&&timers[i]->get_function_type()==new_function){
            timers[i]->start();
            return;
        }
    }
    //QList<QGraphicsView*> the_view=this->scene()->views();

    FunctionTimer* new_timer=new FunctionTimer(new_function,the_board);
    switch(new_function){
        case RESET: QObject::connect(new_timer,SIGNAL(timeout()),the_board,SLOT(functional_reset()));
                    new_timer->start(5);
    }

    timers.push_back(new_timer);


}*/

/** This function generate what function the drop should perform
 * @returns the function the drop should perform
*/
Drop_Func Drop::functional(){
    srand(time(nullptr));
    Drop_Func new_function;
    switch(rand()%5){
       case 0:new_function=RESET;break;
       case 1: new_function=ADDLIFE;break;
       case 2:new_function=STRETCH;break;
       case 3:new_function=SHRINK;break;
       default:new_function=REVERSE;
    }
    return new_function;
}

/** Tis function access the timer of the drop
 * @returns the timer of the drop
*/
QTimer *Drop::timer()
{
    return drop_timer;
}

/** This function set the timer to be the drop timer
 * @param timer is the timer we need to set
*/
void Drop::set_timer(QTimer *timer)
{
    drop_timer=timer;
}

/** This function moves the drop
*/
void Drop::drop_move()
{
    this->moveBy(0,10);
    loc_y+=10;
    //qDebug()<<drop_loc_y();
}
