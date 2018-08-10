#ifndef MATRIX_H
#define MATRIX_H

#define X_SPACE 40 // to do initializ
#define Y_SPACE 120 // to do initializ
#define WIDTH_SQR 100 // width of square
#define HEIGHT_SQR 100 // height of square
#define SQR_SPACE 5 // space around the square
#define ANIM_TIME 200 // time of nimation in milliseconds
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#include <QLabel>
#include <QImage>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>


class MainWindow;

class Matrix
{
public:
    Matrix(QWidget* pr);
    ~Matrix();
    void Up();      //
    void Down();    // In the end of each function making check
    void Left();    // if the game is over or not. If not function
    void Right();   // adding on Field new Square.With function newSquare
private:
    void shift(int,int);
    static QWidget* parent; //Pointer on MainWindow atribute
    struct pair; // Struct for cordinats on field using in newSquare()
    class Square;
    std::vector<pair> Avaible_Sqr; // Empty Squares
    Square* Field[4][4]; //(Field 4x4)
    pair newSquare(); // Making pair[]
    unsigned int Score; // Variable for score
    void GmaeOver(); // Show "Game Over" and a Score
};

#endif // MATRIX_H
