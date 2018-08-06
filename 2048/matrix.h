#ifndef MATRIX_H
#define MATRIX_H

#define X_SPACE 1 // to do initializ
#define Y_SPACE 1 // to do initializ

class Matrix
{
public:
    Matrix();
    ~Matrix();
    void Up();      //
    void Down();    // In the end of each function making check
    void Left();    // if the game is over or not. If not function
    void Right();   // adding on Field new Square.With function newSquare
private:
    int pair[2];
    class Square;
    Square* Field[4][4]; // to do: Random x,y initialization  //(Field 4x4)
    void newSquare(); // Making pair[]
    unsigned int Score; // Variable for score
    void GmaeOver(); // Show "Game Over" and a Score
};

#endif // MATRIX_H
