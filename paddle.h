/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>

/** @class Paddle
 * @brief this class represents the paddle that is under player's control
*/

class Paddle:public QGraphicsRectItem{

public:
    Paddle(int x, int y);
    Paddle(int x,int y, int w,int h);
    int get_width()const;
    int get_height()const;
    int paddle_loc_x()const;
    void update_loc_x(int x);
    int paddle_loc_y()const;
    void update_loc_y(int y);
    void update_p_width(int w);
    void update_p_height(int h);

private:
    int loc_x;
    int loc_y;
    int p_width;
    int p_height;

};



#endif // PADDLE_H

