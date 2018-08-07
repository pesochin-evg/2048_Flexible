#include "matrix.h"

#define IMAGE_NUMBER(a) #a

QWidget* Matrix::parent = nullptr;


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
        X = (X_Cord * width) + X_SPACE;
        Y = (Y_Cord * height) + Y_SPACE;
        Image = new QLabel (parent);
        i = new QImage (QString(":/images/image") + IMAGE_NUMBER(2) + ".png");
        QImage ScaledImage = i->scaled(width,height,Qt::IgnoreAspectRatio);
        Level = 2; // Square umber
        Image->show();
        Image->resize(width,height);
        Image->setGeometry(X,Y,width,height);
        Image->setPixmap(QPixmap::fromImage(ScaledImage,Qt::AutoColor));

        //to do: width,height initialization
    }
    void Animate(int X_Cord, int Y_Cord) // Cordinate of new place (form 0 to 3)
    {
        // to do animation of square
    }
    unsigned int Level;
    int X; //Pixel cordinate X (not field cordinate)
    int Y; //Pixel cordinate Y (not field cordinate)
    static int width;
    static int height;
    QLabel* Image;
private:
    QImage* i;
    // to do: Image class
};

int Matrix::Square::width = 100;
int Matrix::Square::height = 100;

void Matrix::newSquare() // Return new free Square if its possible else NULL
{

}

Matrix::Matrix(QWidget* pr) // construcror
{
    Score = 0;
    Matrix::parent = pr;
    for(int i = 0; i < 3; i++) // initializing field by NULL
    {
        for(int j; j < 3; j++)
        {
            Field[i][j] = nullptr;
        }
    }
    Field[1][1] = new Square(1,1);
    //to do: make two new Squares
}









