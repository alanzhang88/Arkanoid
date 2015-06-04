#include "score.h"

#include <QFont>

/** This is the score constructor
 * @param parent is the parent pointer
*/
Score::Score(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    score=0;
    setPlainText(QString("Score: ")+QString::number(score));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

/** This function access the score
 * @returns the score
*/
int Score::get_score() const
{
    return score;
}

/** This function increases the score by 10
*/
void Score::increase_score()
{
    score+=10;
    setPlainText(QString("Score: ")+QString::number(score));
}
