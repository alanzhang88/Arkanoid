#ifndef BALL
#define BALL

#include <QGraphicsEllipseItem>
#include <QBrush>

/** @class Ball
 * @brief this class represent the ball the player can control and hit the blocks
*/

class Ball:public QGraphicsEllipseItem{

public:
    Ball(double x, double y);
    const double ball_loc_x()const;
    const double ball_loc_y()const;
    void update_loc_x(double x);
    void update_loc_y(double y);

private:
    double loc_x;
    double loc_y;

};





#endif // BALL

