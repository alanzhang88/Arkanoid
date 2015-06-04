/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#include "paddle.h"
#include <QBrush>

/** This is the constructor of paddle
 * @param x is the x coordinate
 * @param y is the y coordinate
*/
Paddle::Paddle(int x, int y):loc_x(x),loc_y(y),p_width(-2*x),p_height(25)
{
    setRect(loc_x,loc_y,p_width,p_height);
    setBrush(Qt::black);
}

/** This is an overload constructor of paddle
 * @param x is the x coordinate
 * @param y is the y coordinate
 * @param w is the width
 * @param h is the height
*/
Paddle::Paddle(int x, int y, int w, int h):loc_x(x),loc_y(y),p_width(w),p_height(h),QGraphicsRectItem(x,y,w,h)
{
    setBrush(Qt::black);
}

/** This is an accessor of the width of the block
 * @returns the width of the block
*/
int Paddle::get_width() const
{
    return p_width;
}
/** This is an accessor of the height of the block
 * @returns the height of the block
*/
int Paddle::get_height() const
{
    return p_height;
}

/** This is an accessor of the x coordinate of the block
 * @returns the x coordinate of the block
*/
int Paddle::paddle_loc_x() const
{
    return loc_x;
}
/** THis is the mutator of x coordinate
 * @param x is the value we increase on x coordinate
*/
void Paddle::update_loc_x(int x)
{
    loc_x+=x;
}
/** This is an accessor of the y coordinate of the block
 * @returns the y coordinate of the block
*/
int Paddle::paddle_loc_y() const
{
    return loc_y;
}
/** THis is the mutator of y coordinate
 * @param y is the value we increase on y coordinate
*/
void Paddle::update_loc_y(int y)
{
    loc_y+=y;
}
/** THis is the mutator of width
 * @param w is the value we increase on width
*/
void Paddle::update_p_width(int w)
{
    p_width+=w;
}
/** THis is the mutator of height
 * @param h is the value we increase on height
*/
void Paddle::update_p_height(int h)
{
    p_height+=h;
}
