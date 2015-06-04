/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#ifndef BOARD_H
#define BOARD_H
#include <QDebug>
#include "ball.h"
#include "m_block.h"
//#include "ball.h"
#include "paddle.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsRectItem>
//#include <QRect>
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>
//#include <QGridLayout>
#include <QLabel>
#include <QCloseEvent>
#include <QPushButton>
#include <QGraphicsItemGroup>
#include <QKeyEvent>
#include <QShowEvent>
#include <QTimer>
#include <QList>
#include "drop.h"
#include "functiontimer.h"
#include "score.h"

enum Level{Easy,Normal,Hard};

namespace Ui {
class Board;
}

/** @class Board
 * @brief this is the game board where main game action happens in here
*/


class Board : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent, Level level_diff, int ball_num);
    ~Board();
    void mousePressEvent(QMouseEvent *event);
    void display_level_1_block_pile();
    void display_level_2_block_pile();
    void ball_move();
    void start_group_reset();
    void advance_level();
    void execute_function(Drop_Func new_function);
    void paddle_transformation(Drop_Func func);
    void stats_and_conclusion();

    void keyPressEvent(QKeyEvent* event);
    void showEvent(QShowEvent* event);


signals:
    void game_over();

public slots:
    void ball_moving_path();

    //functional slots
    void functional_reset();
    void functional_addlife();
    void functional_stretch();
    void functional_shrink();
    void functional_reverse();

private:
    int Level_decode(Level diff);


    Ui::Board *ui;
    QWidget* parent;
    //main scnene
    QGraphicsScene* scene;

    //game interface
    QLabel* lives_label;
    QLabel* level_label;
    QGraphicsEllipseItem** lives;
    int level_num;
    const int wall_number;
    QGraphicsRectItem** wall;
    int total_lives;

    //after the interface area for game 500*590, (x,y)=(-250,-284), (right,down)=(250,306)
    const int max_horizontal_block;
    const int max_vertical_block;
    const int left_wall_co;
    const int top_wall_co;

    //ball variable
    //Ball** reking_ball;
    Ball** reking_ball;
    int num_ball;
    bool ball_in_air;
    double ball_y_velocity[2];
    double ball_x_velocity[2];
    bool ball_is_dead;//this variable is actually for the paddle stretch and shrink only, true means the ball died while the function is still on

    //paddle variable
    Paddle* paddle;

    //level one variable
    Block** block_level_1_display;
    int total_num_block_level_1;

    //level two variable
    Block** block_level_2_display;
    int total_num_block_level_2;

    //helper variable
    QGraphicsItemGroup* start_group;
    Level level_difficulty;
    int count_colliding_increment_speed;

    //timer variable
    QTimer* ball_timer;

    //drop variable
    QList<Drop*> random_drop;

    //functiontimer variable
    QList<FunctionTimer*> timers;
    bool REVERSE_is_on;//true when it is on, false otherwise

    //Score variable
    Score* score;
};

#endif // BOARD_H
