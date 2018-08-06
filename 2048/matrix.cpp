#include "matrix.h"

Matrix::Matrix() // construcror
{
    Score = 0;

    for(int i = 0; i < 3; i++) // initializing field by NULL
    {
        for(int j; j < 3; j++)
        {
            this->Field[i][j] = nullptr;
        }
    }

    //to do: make two new Squares
}

Matrix::~Matrix() // destructur
{

}

void Matrix::Down() // function for swapping Squares Down
{

}

void Matrix::Up() // function for swapping Squares Up
{

}

void Matrix::Right() // function for swapping Squares Right
{

}

void Matrix::Left() // function for swapping Squares Left
{

}

void Matrix::GmaeOver() // Show "Game Over" and a Score
{

}

class Matrix::Square // class of Square
{
public:
    Square(int X_Cord, int Y_Cord) // constructor of Square. X_Cord,Y_Cord from 1 to 4
    {
        Level = 2; // Square umber
        X = (X_Cord * width) + X_SPACE;
        Y = (Y_Cord * height) + Y_SPACE;
        //to do: width,height initialization
    }
    void Animate(int X_Cord, int Y_Cord) // Cordinate of new place (form 1 to 4)
    {
        // to do animation of square
    }
    unsigned int Level;
    int X; //Pixel cordinate X (not field cordinate)
    int Y; //Pixel cordinate Y (not field cordinate)
    static int width;
    static int height;
    // to do: Image class
};

void Matrix::newSquare() // Return new free Square if its possible else NULL
{

}









