#include "ball.h"

/** This is the constructor of Ball which can create a ball in the game
 * @param x is the top-left x coordinate of the ball
 * @param y is the top-left y coordinate of the ball
*/
Ball::Ball(double x, double y):loc_x(x),loc_y(y)
{
    setRect(x,y,25,25);
    setBrush(Qt::blue);

}

/** This is an accessor which gets the coordinate of the ball
 * @returns the x coordinate of the ball
*/
const double Ball::ball_loc_x() const
{
    return loc_x;
}

/** This is an accessor which gets the coordinate of the ball
 * @returns the y coordinate of the ball
*/
const double Ball::ball_loc_y() const
{
    return loc_y;
}

/** This is an mutator which updates the coordinate of the ball
 * @param x is the number we need to add to the original x cooordinate
*/
void Ball::update_loc_x(double x)
{
    loc_x+=x;
}

/** This is an mutator which updates the coordinate of the ball
 * @param y is the number we need to add to the original y cooordinate
*/
void Ball::update_loc_y(double y)
{
    loc_y+=y;
}
