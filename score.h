#ifndef SCORE
#define SCORE

#include <QGraphicsTextItem>

/** @class Score
 * @brief this class represents the score the user get when they hit those blocks
*/

class Score:public QGraphicsTextItem{

public:
    Score(QGraphicsItem* parent=0);
    int get_score()const;
    void increase_score();

private:
    int score;

};

#endif // SCORE

