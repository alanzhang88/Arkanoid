/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#ifndef M_BLOCK_H
#define M_BLOCK_H

#include <QGraphicsRectItem>
#include "drop.h"
#include <QObject>
#include <QTimer>

/** @class Block
 * @brief this class represents the block in the game
*/

class Block:public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Block(int x, int y);
    const int block_width();
    const int block_height();
    void drop_spawn();
    Drop *drop_pointer();
    //QTimer *timer();
    const int block_loc_x()const;
    const int block_loc_y()const;

public slots:
    void drop_move();
private:
    int loc_x;
    int loc_y;
    const int block_w;
    const int block_h;
    //QTimer* drop_timer;
    Drop* random_drop;
};



#endif // M_BLOCK_H

