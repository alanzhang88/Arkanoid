/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>

/** This is the constructor of mainwindow which will set up the welcom screen
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    display();
}
/** This is the destructor of mainwindow class
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/** This function will be called when the player decide to play single ball, it creates a board and start the game
*/
void MainWindow::begin_game_single(){
    //to be modified
    if(easy->isChecked()){
        board=new Board(this,Easy,1);
        //board->setFocus();
        setCentralWidget(board);


    }
    else if(normal->isChecked()){
        board=new Board(this,Normal,1);
        setCentralWidget(board);
    }
    else if(hard->isChecked()){
        board=new Board(this,Hard,1);
        setCentralWidget(board);
    }
    //board->setFocus();
}

/** This function will be called when the player decide to play double balls, it creates a board and start the game
*/
void MainWindow::begin_game_double(){
    //to be modified
    if(easy->isChecked()){
        board=new Board(this,Easy,2);
        setCentralWidget(board);
    }
    else if(normal->isChecked()){
        board=new Board(this,Normal,2);
        setCentralWidget(board);
    }
    else if(hard->isChecked()){
        board=new Board(this,Hard,2);
        setCentralWidget(board);
    }
    //board->setFocus();
}
/**This function reset the mainwindow after the game is over
*/
void MainWindow::game_over(){
    //to be changed...

    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    // Line above will delete the widget gracefully (no memory errors)

    // Display something which says that you lost, maybe display high score.

    // Reset the MainWindow with the initial startup screen
    ui->setupUi(this);
    display();


}

void MainWindow::show_instruction()
{
    QWidget* instruction=new QWidget();
    QVBoxLayout* instr_central=new QVBoxLayout();
    instr_central->addSpacing(50);
    QLabel* instr_label=new QLabel();
    QString instr_text="This game allows user to control the paddle with left arrow key and right arrow key, \nand pressing space to shoot the ball in the air. Before shooting the ball, the player \ncan use click left mouse to choose the angle he wants the ball to go and right mouse \nfor the second ball if any. The player should move the paddle to catch \nthe ball when it is falling or the plaer loses a life. There are also chances that the \nblock will create a random drop with versatile functions when the block is hit.\n(stretch/shrink paddle, add lives, reset the state,reverse control)";
    instr_label->setText(instr_text);
    instr_central->addWidget(instr_label);
    instr_central->addSpacing(50);
    instruction->setLayout(instr_central);
    instruction->show();
}

/** This function display all the labels and buttons on the mainwindow
*/
void MainWindow::display(){

    setWindowTitle("Arkanoid");
    setFixedSize(520,650);
    QVBoxLayout* central=new QVBoxLayout;
    QLabel* wel_message=new QLabel("Welcome to Arkanoid!");
    wel_message->setAlignment(Qt::AlignCenter);
    QFont wel_message_font=wel_message->font();
    wel_message_font.setPointSize(36);
    wel_message->setFont(wel_message_font);
    central->addWidget(wel_message);
    central->addSpacing(100);
    QHBoxLayout* select_mode=new QHBoxLayout;
    select_mode->addSpacing(400);
    QVBoxLayout* select_num_ball=new QVBoxLayout;
    QLabel* ball_num_print=new QLabel("Game Mode");
    ball_num_print->setAlignment(Qt::AlignCenter);
    select_num_ball->addWidget(ball_num_print);
    select_num_ball->addSpacing(40);
    QPushButton* sing_ball=new QPushButton("Single Ball");
    select_num_ball->addWidget(sing_ball);
    select_num_ball->addSpacing(40);
    QPushButton* doub_ball=new QPushButton("Double Balls");

    select_num_ball->addWidget(doub_ball);
    select_mode->addLayout(select_num_ball);
    select_mode->addSpacing(100);
    QVBoxLayout* select_diff=new QVBoxLayout;
    QLabel* diff_print=new QLabel("Difficulty");
    diff_print->setAlignment(Qt::AlignCenter);
    select_diff->addWidget(diff_print);
    select_diff->addSpacing(10);
    easy=new QRadioButton("Esay");
    normal=new QRadioButton("Normal");
    hard=new QRadioButton("Hard");
    select_diff->addWidget(easy);
    select_diff->addSpacing(20);
    select_diff->addWidget(normal);
    select_diff->addSpacing(20);
    select_diff->addWidget(hard);
    select_diff->addSpacing(20);



    select_mode->addLayout(select_diff);
    select_mode->addSpacing(400);
    central->addLayout(select_mode);
    QHBoxLayout* instruction_layout=new QHBoxLayout();
    instru =new QPushButton("instruction");
    instruction_layout->addSpacing(300);
    instruction_layout->addWidget(instru);
    instruction_layout->addSpacing(300);
    central->addLayout(instruction_layout);
    central->addSpacing(150);
    QObject::connect(instru,SIGNAL(clicked()),this,SLOT(show_instruction()));
    QObject::connect(sing_ball,SIGNAL(clicked()),this,SLOT(begin_game_single()));
    QObject::connect(doub_ball,SIGNAL(clicked()),this,SLOT(begin_game_double()));
    centralWidget()->setLayout(central);

}

/** This function will pop up a message box if the user want to close the window to check if the user really want to close it
*/
void MainWindow::closeEvent(QCloseEvent *event)
{
        QMessageBox msgBox;

        msgBox.setText("Are you sure you want to close?");
        msgBox.setStandardButtons(QMessageBox::Close | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Close);
        int result = msgBox.exec();
        switch (result) {
          case QMessageBox::Close:
              event->accept();
              break;
          case QMessageBox::Cancel:
              event->ignore();
              break;
          default:
              QMainWindow::closeEvent(event);
              break;
        }


    /*
    QWidget* close_widget=new QWidget;
    close_widget->setFixedSize(400,200);
    QPushButton* ok=new QPushButton();
    QPushButton* cancel=new QPushButton();
    QLabel* assure_text=new QLabel("Are you sure you want to quit?");
    QFont text_font=assure_text->font();
    text_font.setPointSize(18);
    assure_text->setFont(text_font);
    assure_text->setAlignment(Qt::AlignCenter);

    //assure_text->setFixedHeight(80);
    ok->setText("OK");
    cancel->setText("Cancel");
    QVBoxLayout* main=new QVBoxLayout();
    QHBoxLayout* button=new QHBoxLayout();
    button->addSpacing(150);
    button->addWidget(ok);
    button->addWidget(cancel);
    button->addSpacing(150);
    //main->addSpacing(65);
    main->addWidget(assure_text);
    main->addLayout(button);
    main->addSpacing(10);
    close_widget->setLayout(main);
    close_widget->show();
    */
    //QObject::connect(ok,SIGNAL(clicked()),event,SLOT(accept()));
    //QObject::connect(cancel,SIGNAL(clicked()),event,SLOT(ignore()));
    //event->ignore();
}
