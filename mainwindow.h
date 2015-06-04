/*Shuang Zhang ID:804296230
  PIC 10C Spring 2015
  This is a design of my game and it has basic gaming feature
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "board.h"
#include <QMainWindow>
#include <QRadioButton>

namespace Ui {
class MainWindow;
}

/** @class MainWindow
 * @brief this class is the welcome window and UI for the player to choose difficulties and number of balls of the game
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void display();
    void closeEvent(QCloseEvent *event);


public slots:
    void begin_game_single();
    void begin_game_double();
    void game_over();
    void show_instruction();
    //void window_close();
    //void window_remain();


private:
    Ui::MainWindow *ui;
    Board* board;
    QRadioButton* easy;
    QRadioButton* normal;
    QRadioButton* hard;
    QPushButton* instru;

};

#endif // MAINWINDOW_H
