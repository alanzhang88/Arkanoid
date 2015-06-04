/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#include "board.h"
#include "ui_board.h"
#include <QVBoxLayout>



/** This is the constructor of board where the game is playing on, the ball will take care of ball vairiable and the wall variable
 which are two important things in this game while the paddle and the block will have their own class
 * @param parent is the pointer to parent widget
 * @param level_diff is the level_difficulty
 * @param ball_num is the number of balls
*/
Board::Board(QWidget *parent, Level level_diff,int ball_num):
    ui(new Ui::Board),wall_number(3),max_horizontal_block(10),max_vertical_block(20),left_wall_co(-250),top_wall_co(-284),
    num_ball(ball_num),level_difficulty(level_diff),ball_in_air(false),count_colliding_increment_speed(0),ball_is_dead(false),
    REVERSE_is_on(false)
{
    this->parent=parent;
    ui->setupUi(this);
    srand(time(nullptr));

    scene=new QGraphicsScene();
    scene->setSceneRect(-250,-300,500,600);//set the size of the board

    //centerOn(0,0);

    //lives label
    lives_label=new QLabel("Lives:");
    lives_label->setGeometry(-259,-307,50,10);//set the geometry of the label says lives


    //add ellipse that represents the lives number after the lives label
    total_lives=3;
    lives=new QGraphicsEllipseItem*[total_lives];
    for(int i=0;i<total_lives;i++){
        lives[i]=scene->addEllipse(-209+10*i,-307,10,10,QPen(),QBrush(Qt::blue));
    }

    //level label
    level_num=1;
    level_label=new QLabel("Level: "+QString::number(level_num));
    level_label->setGeometry(207,-307,50,10);

    //QGridLayout* game_center=new QGridLayout();
    //game_center->setGeometry(QRect(-259,-307,517,613));
    //setLayout(game_center);


    //wall variable
    //ceiling is 0, left side is 1, right side is 2
    wall=new QGraphicsRectItem*[wall_number];
    wall[0]=new QGraphicsRectItem(-259,-294,517,10);
    wall[1]=new QGraphicsRectItem(-259,-284,9,590);
    wall[2]=new QGraphicsRectItem(250,-284,8,590);
    //for the space of game board I have 500*590 pixels left


    //label->setGeometry(-(scene->width()/2),-(scene->height()/2),50,10);
    //scene->addEllipse(*recta);
    //scene->addText("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
    //scene->addEllipse(100,100,200,200);
    //scene->addItem(rect);

    //add walls
    for(int i=0;i<wall_number;++i){
        wall[i]->setBrush(Qt::black);
        scene->addItem(wall[i]);
    }

    //add lives & level label
    scene->addWidget(lives_label);
    scene->addWidget(level_label);

    //display the blocks of level 1
    display_level_1_block_pile();

    //creating ball or balls according the user's choice
    reking_ball=new Ball*[num_ball];
    reking_ball[0]=new Ball(-12,256);
    if(num_ball>1){
        reking_ball[0]->moveBy(-13,0);
        reking_ball[0]->update_loc_x(-13);
        reking_ball[1]=new Ball(0,256);
    }
    for(int i=0;i<num_ball;++i){
        scene->addItem(reking_ball[i]);
    }

    //reking_ball[0]=scene->addEllipse(-12,256,25,25,QPen(),QBrush(Qt::blue));
    //if(num_ball>1){
      //  reking_ball[0]->moveBy(-13,0);
       // reking_ball[1]=scene->addEllipse(0,256,25,25,QPen(),QBrush(Qt::blue));
    // }
    /*QGraphicsEllipseItem* newball=new QGraphicsEllipseItem(-50,256,25,25);
    newball->setBrush(Qt::yellow);
    scene->addItem(newball);
    qDebug()<<newball->pos();*/
    //set initial velocity
    for(int i=0;i<num_ball;++i){
        ball_x_velocity[i]=-5+rand()%11;
        ball_y_velocity[i]=-5;
    }

    //create the paddle
    paddle=new Paddle(Level_decode(level_diff),281);
    scene->addItem(paddle);

    //create a group that includes paddle and ball
    start_group=new QGraphicsItemGroup();
    start_group->addToGroup(paddle);
    for(int i=0;i<num_ball;++i){
       start_group->addToGroup(reking_ball[i]);
    }

    start_group->setFlag(QGraphicsItem::ItemIsFocusable);
    start_group->setFocus();
    scene->addItem(start_group);

    score=new Score();
    scene->addItem(score);
    score->moveBy(120,-290);
    //setFocusPolicy(Qt::FocusPolicy);
    //scene->setFocus();
    setScene(scene);
    //scene->setFocus();

    //scale(1,-1);
    //QGraphicsView* view=new QGraphicsView(scene);
    //view->show();
    //QRect* recta=new QRect(0,0,100,100);
    //QVBoxLayout* display=new QVBoxLayout();
    //display->addWidget(recta);
    //setLayout(display);
    QObject::connect(this,SIGNAL(game_over()),parent,SLOT(game_over()));//connect the gameover signal to game_over function of tha mainwindow
}

/** This is destructor of board
*/
Board::~Board()
{
    delete ui;
}

/** This function is mainly a helper function to get the pixel locatioon of the board user will not see it
*/
void Board::mousePressEvent(QMouseEvent *event)
    {
    qDebug() << event->pos()<<" "<<event->pos().x()<<" "<<event->pos().y();
    //setting shooting angle with mouse click, left click setting the angle of left ball(if there are two) right click to the right, if there is only one ball, left click setting angle of it

    if(ball_in_air==false){
        if(event->button()==Qt::MouseButton::LeftButton){
            //qDebug()<<ball_y_velocity[0]<<" "<<ball_x_velocity[0];
            double angle_left=static_cast<double>((event->pos().x()-259))/(event->pos().y()-586);
            ball_y_velocity[0]=-sqrt(49/(angle_left*angle_left+1));
            ball_x_velocity[0]=ball_y_velocity[0]*angle_left;
            //qDebug()<<angle_left<<" "<<ball_y_velocity[0]<<" "<<ball_x_velocity[0];
        }
        if(num_ball>1){
            if(event->button()==Qt::MouseButton::RightButton){
                //qDebug()<<ball_y_velocity[1]<<" "<<ball_x_velocity[1];
                double angle_right=static_cast<double>((event->pos().x()-259))/(event->pos().y()-586);
                ball_y_velocity[1]=-sqrt(49/(angle_right*angle_right+1));
                ball_x_velocity[1]=ball_y_velocity[1]*angle_right;
                //qDebug()<<ball_y_velocity[1]<<" "<<ball_x_velocity[1];
            }
        }
    }
}

/** This function displays the level 1 blocks with nested for loops
*/
void Board::display_level_1_block_pile()
{
    int num_row=5;
    total_num_block_level_1=max_horizontal_block*num_row;
    block_level_1_display=new Block*[max_horizontal_block*num_row];
    for(int j=0;j<num_row;j++){
        for(int i=0;i<max_horizontal_block;++i){
            block_level_1_display[i+j*max_horizontal_block]=new Block(left_wall_co+50*i,-184+25*j);
            scene->addItem(block_level_1_display[i+j*max_horizontal_block]);
        }
    }


}

/** This function displays the level 2 blocks with nested for loops
*/
void Board::display_level_2_block_pile()
{
    level_num++;
    level_label->setText("Level: "+QString::number(level_num));
    int row_Level_2=8;
    total_num_block_level_2=row_Level_2*(row_Level_2+1);
    block_level_2_display=new Block*[row_Level_2*(row_Level_2+1)];
    for(int i=1;i<=row_Level_2;++i){
        for(int j=0;j<i;++j){
            block_level_2_display[static_cast<int>(0.5*i*(i-1))+j]=new Block(-25+(50*j)+(-25*(i-1)),-234+25*(i-1));
            scene->addItem(block_level_2_display[static_cast<int>(0.5*i*(i-1))+j]);
        }
    }
    for(int i=0;i<row_Level_2;++i){
        for(int j=0;j<row_Level_2-i;++j){
            block_level_2_display[static_cast<int>(0.5*row_Level_2*(row_Level_2+1))+j+(static_cast<int>((2*row_Level_2+1-i)*0.5*i))]=new Block(-25-(25*(row_Level_2-1))+(50*j)+(25*(i)),-234+25*row_Level_2+25*(i));
            scene->addItem(block_level_2_display[static_cast<int>(0.5*row_Level_2*(row_Level_2+1))+j+static_cast<int>((2*row_Level_2+1-i)*0.5*i)]);
        }
    }

    /*
    level_num++;
    level_label->setText("Level: "+QString::number(level_num));
    int row_Level_2=8;
    total_num_block_level_2=row_Level_2*(row_Level_2+1);
    block_level_2_display=new Block*[row_Level_2*(row_Level_2+1)];
    for(int i=1;i<=row_Level_2;++i){
        for(int j=0;j<i;++j){
            block_level_2_display[(int)(0.5*i*(i-1))+j]=new Block(-25+(50*j)+(-25*(i-1)),-234+25*(i-1));
            scene->addItem(block_level_2_display[(int)(0.5*i*(i-1))+j]);
        }
    }*/
    /*for(int i=0;i<row_Level_2;++i){
        for(int j=0;j<row_Level_2-i;++j){
            block_level_2_display[21+j+(int)((2*row_Level_2+1-i)*0.5*i)]=new Block(-150+(50*j)+(25*(i)),-34+25*(i));
            scene->addItem(block_level_2_display[21+j+(int)((2*row_Level_2+1-i)*0.5*i)]);
        }
    }*//*
    for(int i=0;i<row_Level_2;++i){
        for(int j=0;j<row_Level_2-i;++j){
            block_level_2_display[(int)(0.5*row_Level_2*(row_Level_2+1))+j+((int)((2*row_Level_2+1-i)*0.5*i))]=new Block(-25-(25*(row_Level_2-1))+(50*j)+(25*(i)),-234+25*row_Level_2+25*(i));
            scene->addItem(block_level_2_display[(int)(0.5*row_Level_2*(row_Level_2+1))+j+(int)((2*row_Level_2+1-i)*0.5*i)]);
        }
    }
    */
}

/** This function gets called the the user decide to shoot the ball
*/
void Board::ball_move()
{
    //disable the group
    if(ball_in_air==false){
        start_group->removeFromGroup(paddle);
        for(size_t i=0;i<num_ball;++i){
            start_group->removeFromGroup(reking_ball[i]);
        }
        scene->removeItem(start_group);
        delete start_group;
        start_group=nullptr;//start group is nullptr now
    }

    ball_in_air=true;
    //create the timer so that ball will move when the timer emmits timeout signal every 50 miliseconds
    ball_timer=new QTimer(this);
    QObject::connect(ball_timer,SIGNAL(timeout()),this,SLOT(ball_moving_path()));
    ball_timer->start(50);




}

/** This function basically reset the starting position of ball and paddle
*/
void Board::start_group_reset()
{
    //reset initial position of paddle and ball and ball speed
    ball_timer->stop();
    delete ball_timer;
    start_group=new QGraphicsItemGroup();//since the start group get deleted first
    for(int i=0;i<num_ball;i++){
        scene->removeItem(reking_ball[i]);
        delete reking_ball[i];}
    scene->removeItem(paddle);
    delete paddle;
    reking_ball=new Ball*[num_ball];
    reking_ball[0]=new Ball(-12,256);
    if(num_ball>1){
        reking_ball[0]->moveBy(-13,0);
        reking_ball[0]->update_loc_x(-13);
        reking_ball[1]=new Ball(0,256);
    }
    for(int i=0;i<num_ball;++i){
        scene->addItem(reking_ball[i]);
    }
    /*reking_ball[0]=scene->addEllipse(-12,256,25,25,QPen(),QBrush(Qt::blue));
    if(num_ball>1){
        reking_ball[0]->moveBy(-13,0);
        reking_ball[1]=scene->addEllipse(0,256,25,25,QPen(),QBrush(Qt::blue));
    }*/
    paddle=new Paddle(Level_decode(level_difficulty),281);
    scene->addItem(paddle);//delete and readd those items
    /*paddle->setPos(Level_decode(level_difficulty),281);
    reking_ball[0]->setPos(-12,256);
    if(num_ball>1){
        reking_ball[0]->moveBy(-13,0);
        reking_ball[1]->setPos(0,256);
    }*/
    for(int i=0;i<num_ball;++i){
        ball_x_velocity[i]=-5+rand()%11;
        ball_y_velocity[i]=-5;
    }

    start_group->addToGroup(paddle);
    for(int i=0;i<num_ball;++i){
       start_group->addToGroup(reking_ball[i]);
    }
    scene->addItem(start_group);
    count_colliding_increment_speed=0;
}

/** This function advance to next level when the level 1 is passed
*/
void Board::advance_level()
{//need to be changed since we need one more level
    if(level_num<2){
        display_level_2_block_pile();
        start_group_reset();
    }
    /*
    else{
        stats_and_conclusion();
        this->game_over();
    }*/
}

/** This function execute the function of the drop
 * @param new_function is the function in the drop
*/
void Board::execute_function(Drop_Func new_function)
{
    if(ball_in_air==false)return;
    for(int i=0,n=timers.size();i<n;++i){
        if(timers[i]!=nullptr&&timers[i]->get_function_type()==new_function){
            if((!(timers[i]->isActive()))||(timers[i]->isActive()&&ball_is_dead==true)){
                paddle_transformation(new_function);
                if(ball_is_dead==true)ball_is_dead=false;
            }
            if(new_function==REVERSE)REVERSE_is_on=true;
            timers[i]->start();
            return;
        }
    }
    //QList<QGraphicsView*> the_view=this->scene()->views();

    FunctionTimer* new_timer=new FunctionTimer(new_function,this);
    switch(new_function){
        case RESET: QObject::connect(new_timer,SIGNAL(timeout()),this,SLOT(functional_reset()));
                    new_timer->start(5);
                    break;
        case ADDLIFE: QObject::connect(new_timer,SIGNAL(timeout()),this,SLOT(functional_addlife()));
                    new_timer->start(5);
                    break;

        case STRETCH:QObject::connect(new_timer,SIGNAL(timeout()),this,SLOT(functional_stretch()));
                    //qDebug()<<paddle->paddle_loc_x()<<paddle->pos().x()<<"old";
                    //paddle->setRect(paddle->paddle_loc_x(),paddle->paddle_loc_y(),paddle->get_width()+50,paddle->get_height());
                    //paddle->update_loc_x(-25);
                    //QRect myrect=QRect(QPoint(paddle->paddle_loc_x(),paddle->paddle_loc_y()),QSize(paddle->get_width()+50,paddle->get_height()));
                    //paddle->setRect(myrect);
                    /*QPoint loc(paddle->paddle_loc_x(),paddle->paddle_loc_y());
                    QSize siz(paddle->get_width(),paddle->get_height());
                    //qDebug()<<loc<<siz;
                    scene->removeItem(paddle);
                    delete paddle;
                    paddle=new Paddle(loc.x(),loc.y(),siz.width()+50,siz.height());
                    //qDebug()<<paddle->paddle_loc_x()<<paddle->pos().x()<<"new";
                    scene->addItem(paddle);
                    //paddle->update_p_width(50);*/
                    paddle_transformation(STRETCH);
                    new_timer->start(5000);
                    break;
    case SHRINK:QObject::connect(new_timer,SIGNAL(timeout()),this,SLOT(functional_shrink()));
                paddle_transformation(SHRINK);
                new_timer->start(5000);
                break;
    case REVERSE:QObject::connect(new_timer,SIGNAL(timeout()),this,SLOT(functional_reverse()));
                 REVERSE_is_on=true;
                 new_timer->start(5000);
                 break;

    }

    timers.push_back(new_timer);

}

/** This function does the tranformation for the paddle it can either stretch it or shrink it
 * @param func is the function is side the drop
*/
void Board::paddle_transformation(Drop_Func func)
{
    if(func==STRETCH||func==SHRINK){
        QPoint loc(paddle->paddle_loc_x(),paddle->paddle_loc_y());
        QSize siz(paddle->get_width(),paddle->get_height());
        //qDebug()<<loc<<siz;
        scene->removeItem(paddle);
        delete paddle;
        if(func==STRETCH){
            paddle=new Paddle(loc.x(),loc.y(),siz.width()+25,siz.height());
        }
        else {
            paddle=new Paddle(loc.x(),loc.y(),siz.width()-25,siz.height());
        }
        //qDebug()<<paddle->paddle_loc_x()<<paddle->pos().x()<<"new";
        scene->addItem(paddle);
    }
}

/** This function outputs the score after the game is over
*/
void Board::stats_and_conclusion()
{
    QWidget* conclusion=new QWidget();
    QLabel* end_word=new QLabel();
    if(total_lives>=0)end_word->setText(QString("Congratulations. You won!\n Your total score is ")+QString::number(score->get_score()));
    else end_word->setText(QString("Sorry. You lose.\n Your total score is ")+QString::number(score->get_score()));
    QVBoxLayout* central_lay=new QVBoxLayout();
    central_lay->addSpacing(50);
    central_lay->addWidget(end_word);
    central_lay->addSpacing(50);
    conclusion->setLayout(central_lay);
    conclusion->show();
}

/** This function detect what key user pressed and reacts to it
*/
void Board::keyPressEvent(QKeyEvent *event)
{
    //(REVERSE_is_on?Qt::Key_Left:Qt::Key_Right);
    switch(event->key()){
    case Qt::Key_Left:
     //225 for hard 200 for normal 175 for easy
     //if the ball is not in the air, we move the group together, if it is we just move the paddle
     if(REVERSE_is_on==false){
        if(ball_in_air==false){
            if(start_group->pos().x()>(-175-level_difficulty*25)){
                paddle->update_loc_x(-5);
                start_group->moveBy(-5,0);

            }
        }
        else{
            /*
            if(paddle->pos().x()>(-175-level_difficulty*25)){
                paddle->moveBy(-5,0);
                //qDebug()<<paddle->pos();
            }*/
            //qDebug()<<paddle->paddle_loc_x()<<paddle->pos().x();
            if(paddle->paddle_loc_x()>-250){
                //qDebug()<<paddle->loc_x();
                paddle->update_loc_x(-5);
                paddle->moveBy(-5,0);

                //qDebug()<<paddle->pos();
            }
        }
     }
     else{
         if(ball_in_air==false){
             if(start_group->pos().x()<(175+level_difficulty*25)){
                 paddle->update_loc_x(5);
                 start_group->moveBy(5,0);
             }
         }
         else{

             if(paddle->paddle_loc_x()+paddle->get_width()<250){
                 paddle->update_loc_x(5);
                 paddle->moveBy(5,0);

             }
         }

     }
     break;
    case Qt::Key_Right:
     if(REVERSE_is_on==false){
        if(ball_in_air==false){
            if(start_group->pos().x()<(175+level_difficulty*25)){
                //qDebug()<<start_group->pos().x();
                paddle->update_loc_x(5);
                start_group->moveBy(5,0);
            }
        }
        else{
             /*
            if(paddle->pos().x()<(175+level_difficulty*25)){
                paddle->moveBy(5,0);
                //qDebug()<<paddle->pos();
            }*/
            //qDebug()<<paddle->paddle_loc_x()<<paddle->pos().x();
            if(paddle->paddle_loc_x()+paddle->get_width()<250){
                paddle->update_loc_x(5);
                paddle->moveBy(5,0);

                //qDebug()<<paddle->pos();
            }
        }
     }
     else{
         if(ball_in_air==false){
                 if(start_group->pos().x()>(-175-level_difficulty*25)){
                     paddle->update_loc_x(-5);
                     start_group->moveBy(-5,0);

                 }
              }
          else{


                  if(paddle->paddle_loc_x()>-250){

                      paddle->update_loc_x(-5);
                      paddle->moveBy(-5,0);

                      }
              }
     }
     break;
    case Qt::Key_Space:
        if(ball_in_air==false)ball_move();
        break;
    default :QGraphicsView::keyPressEvent(event);

    }
}
/** This function set the focus to the board
*/
void Board::showEvent(QShowEvent *event)
{
    activateWindow();
    setFocus();
    QGraphicsView::showEvent(event);
}

/** This function is the main big function that consists of how ball will move and collision function of the ball and checking if the ball is dead and checking if we can advance to next level
*/
void Board::ball_moving_path()
{
    //move the ball
    for(size_t i=0;i<num_ball;++i){
        if(reking_ball[i]->pos().y()<=50/*&&reking_ball[i]->pos().y()>=-540&&reking_ball[i]->pos().x()>=-250&&reking_ball[i]->pos().x()<=250*/)
            reking_ball[i]->moveBy(ball_x_velocity[i],ball_y_velocity[i]);
            reking_ball[i]->update_loc_x(ball_x_velocity[i]);
            reking_ball[i]->update_loc_y(ball_y_velocity[i]);
    }
   //check if the ball is dead
    if(reking_ball[0]->pos().y()>50||reking_ball[num_ball-1]->pos().y()>50){
        ball_in_air=false;
        start_group_reset();

        if(total_lives>0){
            --total_lives;
            lives[total_lives]->hide();
            ball_is_dead=true;
            //scene->removeItem(lives[total_lives]);
            //delete lives[total_lives];
        }

        else{
            //delete[] lives;
            //lives=nullptr;
            --total_lives;
            //ball_timer->stop();
            stats_and_conclusion();
            this->game_over();

        }
    }







    //check if we hit all the brick
    Block** temp;
    int temp_number;
    bool finish=true;
    switch(level_num){
    case 1:temp=block_level_1_display;temp_number=total_num_block_level_1;   break;
    default:temp=block_level_2_display;temp_number=total_num_block_level_2;break;//default case needs to be changed
    }
    for(int i=0;i<temp_number;++i){
        if(temp[i]->isVisibleTo(0))finish=false;
    }
    if(finish==true){
        if(level_num>=2){
            ball_timer->stop();
            stats_and_conclusion();
            this->game_over();
            return;
        }
        for(int i=0;i<temp_number;++i){
            delete temp[i];
            temp[i]=nullptr;
        }
        delete[] temp;
        temp=nullptr;
        ball_in_air=false;
        advance_level();

    }









    //collision check
    int index;//index of the block
    //Drop* random_drop=nullptr;//pointer to the drop
    //QTimer* drop_timer=nullptr;//timer to the drop
    for(int j=0;j<num_ball;++j){
        QList<QGraphicsItem*> colliding_items_ball_1=reking_ball[j]->collidingItems();
        for(int i=0,n=colliding_items_ball_1.size();i<n;++i){
            //qDebug()<<"assdasdasdasd";
            if(typeid(*(colliding_items_ball_1[i]))==typeid(Block)){
                //Drop* random_drop= new Drop(rand()%501-250,-284);
                //scene->addItem(random_drop);
                //QObject::connect(ball_timer,SIGNAL(timeout()),random_drop,SLOT(drop_move()));
                //int index;
                for(index=0;index<temp_number;++index){
                    if(colliding_items_ball_1[i]==temp[index])break;
                }
                temp[index]->drop_spawn();//find out which block is colliding and spawn the drop

                int drop_index;
                for(drop_index=0;drop_index<random_drop.size();++drop_index){
                    if(random_drop[drop_index]==nullptr){
                        random_drop[drop_index]=temp[index]->drop_pointer();
                        break;
                    }
                }
                if(drop_index==random_drop.size())random_drop.push_back(temp[index]->drop_pointer());
                //random_drop=temp[index]->drop_pointer();
                //drop_timer=temp[index]->timer();
                //qDebug()<<temp[index]->block_loc_x()<<" "<<temp[index]->block_loc_y();
                //qDebug()<<reking_ball[j]->ball_loc_x()<<" "<<reking_ball[j]->ball_loc_y();
                score->increase_score();
                scene->removeItem(colliding_items_ball_1[i]);
                colliding_items_ball_1[i]->hide();
                //if the ball collides with two blocks we only want it to change direction once

                    //ball_x_velocity[j]=-ball_x_velocity[j];
                    //ball hits from the left and right side of the block
                    if(reking_ball[j]->ball_loc_y()+25>=(temp[index]->block_loc_y()+5)&&reking_ball[j]->ball_loc_y()+25<=(temp[index]->block_loc_y()+45)){
                        //if(reking_ball[j]->ball_loc_x()<(temp[index]->block_loc_x()+25))ball_x_velocity[j]=-ball_x_velocity[j];
                        //qDebug()<<temp[index]->block_loc_x()<<" "<<temp[index]->block_loc_y();
                        //qDebug()<<reking_ball[j]->ball_loc_x()<<" "<<reking_ball[j]->ball_loc_y();

                        ball_x_velocity[j]=-ball_x_velocity[j];
                    }
                    else{

                        ball_y_velocity[j]=-ball_y_velocity[j];
                    }

                    if(i-1>=0&&typeid(*(colliding_items_ball_1[i-1]))==typeid(Block)){
                        if(reking_ball[j]->ball_loc_y()+25>=(temp[index]->block_loc_y()+5)&&reking_ball[j]->ball_loc_y()+25<=(temp[index]->block_loc_y()+45)){
                            //if(reking_ball[j]->ball_loc_x()<(temp[index]->block_loc_x()+25))ball_x_velocity[j]=-ball_x_velocity[j];
                            ball_x_velocity[j]=-ball_x_velocity[j];
                        }
                        else{

                            ball_y_velocity[j]=-ball_y_velocity[j];
                        }
                    }

            }
            if(ball_in_air==true){
                if(typeid(*(colliding_items_ball_1[i]))==typeid(Paddle)){
                    //QList<QGraphicsItem*> paddle_colliding=paddle->collidingItems();
                    //qDebug()<<paddle_colliding[0]->scenePos();
                    //qDebug()<<reking_ball[0]->boundingRect().x()<<reking_ball[0]->boundingRect().y();
                    //qDebug()<<colliding_items_ball_1[i]->scenePos();
                    //qDebug()<<reking_ball[0]->pos();
                    count_colliding_increment_speed++;
                    if(ball_x_velocity[j]>0){
                        if(reking_ball[j]->pos().x()<paddle->pos().x()){
                            ball_x_velocity[j]=-(ball_x_velocity[j]);
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                        else if(reking_ball[j]->pos().x()>paddle->pos().x()){
                            //ball_x_velocity[j]=-(ball_x_velocity[j]);
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                        else {
                            ball_x_velocity[j]=0;
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                    }
                    else if(ball_x_velocity[j]<0){
                        if(reking_ball[j]->pos().x()<paddle->pos().x()){
                            //ball_x_velocity[j]=-(ball_x_velocity[j]);
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                        else if(reking_ball[j]->pos().x()>paddle->pos().x()){
                            ball_x_velocity[j]=-(ball_x_velocity[j]);
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                        else{
                            ball_x_velocity[j]=0;
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }

                    }
                    else{
                        if(reking_ball[j]->pos().x()<paddle->pos().x()){
                            ball_x_velocity[j]=-rand()%11;
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                        else if(reking_ball[j]->pos().x()>paddle->pos().x()){
                            ball_x_velocity[j]=rand()%11;
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                        else{
                            ball_x_velocity[j]=0;
                            ball_y_velocity[j]=-ball_y_velocity[j];
                            //if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=1;
                        }
                    }
                    //ball_x_velocity[j]=-(ball_x_velocity[j]-5+rand()%11);
                    //ball_y_velocity[j]=-ball_y_velocity[j];
                    //qDebug()<<count_colliding_increment_speed;
                    if(count_colliding_increment_speed%10==0)ball_y_velocity[j]-=5;
                    if(ball_x_velocity[j]<0)ball_x_velocity[j]--;
                    if(ball_x_velocity[j]>0)ball_x_velocity[j]++;
                    //qDebug()<<ball_x_velocity[j]<<" "<<ball_y_velocity[j];
                }
            }
            if(colliding_items_ball_1[i]==wall[0]){
                //ball_x_velocity[j]=-ball_x_velocity[j];
                ball_y_velocity[j]=-ball_y_velocity[j];
            }
            if(colliding_items_ball_1[i]==wall[1]||colliding_items_ball_1[i]==wall[2]){
                ball_x_velocity[j]=-ball_x_velocity[j];
                //ball_y_velocity[j]=-ball_y_velocity[j];
            }

        }
    }

    for(int random_index=0,random_size=random_drop.size();random_index<random_size;++random_index){
        if(random_drop[random_index]!=nullptr){
            //qDebug()<<"drop entered";
            //bool job_done=false;
            if(random_drop[random_index]->collidesWithItem(paddle)){

                //random_drop[random_index]->functional(timers,this);
                execute_function(random_drop[random_index]->functional());
                random_drop[random_index]->timer()->stop();
                scene->removeItem(random_drop[random_index]);
                delete (random_drop[random_index]->timer());
                delete random_drop[random_index];
                random_drop[random_index]=nullptr;
                //qDebug()<<"drop hit the paddle and deleted";
                //job_done=true;
                continue;
            }

            /*QList<QGraphicsItem*> colliding_item_of_drop=random_drop[random_index]->collidingItems();
            for(int i=0,n=colliding_item_of_drop.size();i<n;++i){
                if(colliding_item_of_drop[i]==paddle){
                    random_drop[random_index]->functional();
                    random_drop[random_index]->timer()->stop();
                    delete (random_drop[random_index]->timer());
                    delete random_drop[random_index];
                    random_drop[random_index]=nullptr;
                    job_done=true;
                }
                if(typeid(*(colliding_item_of_drop[i]))==typeid(Ball)){
                    continue;
                }
            }*/
            //qDebug()<<random_drop[random_index]->drop_loc_y();
            if(/*job_done==false&&*/random_drop[random_index]->drop_loc_y()>306){
                scene->removeItem(random_drop[random_index]);
                random_drop[random_index]->timer()->stop();
                delete (random_drop[random_index]->timer());
                delete random_drop[random_index];
                random_drop[random_index]=nullptr;
                //qDebug()<<"drop deleted";
            }
        }
    }
}

/** This function reset the paddle positino after the paddle hit the drop with this function
*/
void Board::functional_reset()
{
    for(int i=0,n=timers.size();i<n;++i){
        if(timers[i]!=nullptr&&timers[i]->get_function_type()==RESET){
            timers[i]->stop();
            break;
        }
    }
    for(int i=0;i<timers.size();++i){
        if(timers[i]!=nullptr&&(timers[i]->get_function_type()==SHRINK||timers[i]->get_function_type()==STRETCH)){
            if(timers[i]->isActive()){
                ball_is_dead=true;
                break;
            }
        }
    }

    ball_in_air=false;
    start_group_reset();
}

/** This function add another life for player
*/
void Board::functional_addlife()
{
    for(int i=0,n=timers.size();i<n;++i){
        if(timers[i]!=nullptr&&timers[i]->get_function_type()==ADDLIFE){
            timers[i]->stop();
            break;
        }
    }
    if(total_lives<3){
        lives[total_lives]->show();
        ++total_lives;
    }
}

/** This function will return the original shape of the function if it hits the drop that stretch it
*/
void Board::functional_stretch()
{
    for(int i=0,n=timers.size();i<n;++i){
        if(timers[i]!=nullptr&&timers[i]->get_function_type()==STRETCH){
            timers[i]->stop();
            break;
        }
    }/*
    paddle->setRect(paddle->paddle_loc_x(),paddle->paddle_loc_y(),paddle->get_width()-50,paddle->get_height());
    //paddle->update_loc_x(25);
    paddle->update_p_width(-50);*/
    if(ball_is_dead==false){
        paddle_transformation(SHRINK);
    }
    else
        ball_is_dead=false;
}

/** This function will return the original shape of the function if it hits the drop that shrinks it
*/
void Board::functional_shrink()
{
    for(int i=0,n=timers.size();i<n;++i){
        if(timers[i]!=nullptr&&timers[i]->get_function_type()==SHRINK){
            timers[i]->stop();
            break;
        }
    }
    if(ball_is_dead==false){
        paddle_transformation(STRETCH);
    }
    else
        ball_is_dead=false;

}

/** This function helps player comeback from te reversing control function
*/
void Board::functional_reverse()
{
    for(int i=0,n=timers.size();i<n;++i){
        if(timers[i]!=nullptr&&timers[i]->get_function_type()==REVERSE){
            timers[i]->stop();
            break;
        }
    }
    REVERSE_is_on=false;
}


/** This function decode the level difficulty and return the position the paddle should be at the start
*/
int Board::Level_decode(Level diff)
{
    switch(diff){
    case Easy:return -75;break;
    case Normal:return -50;break;
    case Hard:return -25;break;

    }
}
