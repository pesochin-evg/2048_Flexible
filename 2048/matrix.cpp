#include "matrix.h"

#define IMAGE_NUMBER(a) #a

QWidget* Matrix::parent = nullptr;

struct Matrix::pair
{
    int memb[2];
};

Matrix::~Matrix() // destructur
{
    for(int i = 0; i < 3; i++) // initializing field by NULL
    {
        for(int j; j < 3; j++)
        {
            delete Field[i][j];
        }
    }
    //delete parent;
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
    Square(int X_Cord, int Y_Cord) // constructor of Square. X_Cord,Y_Cord from 0 to 3
    {
        Level = 2; // Square umber
        X = (X_Cord * width) + X_SPACE;
        Y = (Y_Cord * height) + Y_SPACE;

        //----------Image showing----------//
        Image = new QLabel (parent);
        i = new QImage (QString(":/img/Images/image") + IMAGE_NUMBER(2) + ".png");
        QImage ScaledImage = i->scaled(width,height,Qt::IgnoreAspectRatio);
        Image->show();
        Image->resize(width,height);
        Image->setGeometry(X,Y,width,height);
        Image->setPixmap(QPixmap::fromImage(ScaledImage,Qt::AutoColor));
        //--------------------------------//

        //to do: width,height initialization
    }

    ~Square()//destructor
    {
        delete i;
        delete Image;
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
};

int Matrix::Square::width = WIDTH_SQR;
int Matrix::Square::height = HEIGHT_SQR;

Matrix::pair Matrix::newSquare() // Return new free Square if its possible else NULL
{
    pair tmp;
    srand(time(NULL));
    int i = rand() % (Avaible_Sqr.size());
    tmp = Avaible_Sqr[i];
    auto it = Avaible_Sqr.begin();
    Avaible_Sqr.erase(it + i);
    return tmp;
}

Matrix::Matrix(QWidget* pr) // construcror
{
    Avaible_Sqr.resize(16);
    Score = 0;
    short int cur = 0;
    Matrix::parent = pr;
    for(short int i = 0; i < 4; i++) // initializing field by NULL
    {
        for(short int j = 0; j < 4; j++)
        {
            Avaible_Sqr[cur].memb[0] = i;
            Avaible_Sqr[cur].memb[1] = j;
            cur++;
            Field[i][j] = nullptr;
        }
    }
    for(int i = 0; i < 2; i++)
    {
        pair tmp = newSquare();
        Field[tmp.memb[0]][tmp.memb[1]] = new Square(tmp.memb[0],tmp.memb[1]);
    }

}









