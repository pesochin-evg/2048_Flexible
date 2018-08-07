#ifndef MATRIX_H
#define MATRIX_H

#define X_SPACE 40 // to do initializ
#define Y_SPACE 120 // to do initializ

#include <QLabel>
#include <QImage>

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
    static QWidget* parent; //Pointer on MainWindow atribute
    int pair[2];
    class Square;
    Square* Field[4][4]; // to do: Random x,y initialization  //(Field 4x4)
    void newSquare(); // Making pair[]
    unsigned int Score; // Variable for score
    void GmaeOver(); // Show "Game Over" and a Score
};

#endif // MATRIX_H
