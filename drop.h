#ifndef DROP
#define DROP

#include <QGraphicsRectItem>
#include <QBrush>
#include <QObject>
#include "functiontimer.h"
#include <QList>
//#include "board.h"

//class Board;

/** @class Drop
 * @brief this class represents the drop in the game which are little gadgets for players to use
*/

class Drop:public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Drop(double x, double y);
    double drop_loc_x()const;
    double drop_loc_y()const;
    Drop_Func functional();
    QTimer* timer();
    void set_timer(QTimer* timer);

public slots:
    void drop_move();

private:
    double loc_x;
    double loc_y;
    QTimer* drop_timer;

};

#endif // DROP

