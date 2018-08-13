#include "matrix.h"

using namespace std;

#define IMAGE_NUMBER(a) #a

QWidget* Matrix::parent = nullptr;

struct Matrix::pair
{
    int memb[2];
};

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
        delete i;
        Image->show();
        Image->resize(width,height);
        Image->setGeometry(X + SQR_SPACE,Y + SQR_SPACE,width - SQR_SPACE,height - SQR_SPACE);
        Image->setPixmap(QPixmap::fromImage(ScaledImage,Qt::AutoColor));
        //--------------------------------//

        //to do: width,height initialization
    }

    ~Square()//destructor
    {
        delete Image;
    }

    void LevelUp() // increath Level and change Image
    {
        Level *= 2;
        i = new QImage (QString(":/img/Images/image") + QString::number(Level) + ".png");
        QImage ScaledImage = i->scaled(width,height,Qt::IgnoreAspectRatio);
        delete i;
        Image->setPixmap(QPixmap::fromImage(ScaledImage,Qt::AutoColor));

    }

    void Animate_PXL(int X_Cord, int Y_Cord)
    {
        Image->setGeometry(X_Cord  + SQR_SPACE,Y_Cord + SQR_SPACE,width - SQR_SPACE,height - SQR_SPACE);
    }

    void Animate(int X_Cord, int Y_Cord) // Cordinate of new place (form 0 to 3)
    {
        int X_Cord_PXL = (X_Cord * WIDTH_SQR) + X_SPACE;// cordinate in pixels
        int Y_Cord_PXL = (Y_Cord * HEIGHT_SQR) + Y_SPACE; //

        Image->setGeometry(X_Cord_PXL  + SQR_SPACE,Y_Cord_PXL + SQR_SPACE,width - SQR_SPACE,height - SQR_SPACE);

        /*f(X_Cord_PXL == X) // Y animation
        {
            int dist = Y_Cord_PXL - Y;
            int speed = dist / ANIM_TIME;
            while(Y_Cord_PXL != Y)
            {
                Y += speed;
                Image->setGeometry(X + SQR_SPACE,Y + SQR_SPACE,width - SQR_SPACE,height - SQR_SPACE);
                std::this_thread::sleep_for(std::chrono::milliseconds(ANIM_TIME));
            }
        }else if(Y_Cord_PXL == Y) // X animation
        {
            int dist = X_Cord_PXL - X;
            int speed =(-1);//dist / ANIM_TIME);
            for(int i = 0; i < 200; i++)
            {
                X += speed;
                Image->setGeometry(X + SQR_SPACE,Y + SQR_SPACE,width - SQR_SPACE,height - SQR_SPACE);
            }
            while(X_Cord_PXL != X)
            {
                X += speed;
                Image->setGeometry(X + SQR_SPACE,Y + SQR_SPACE,width - SQR_SPACE,height - SQR_SPACE);
                time_t last;
                time_t now;
                time(&last);
                now = last;
                while(difftime(now, last) < 1)
                {
                    time(&now);
                };
            }
         }*/

        }
        // to do animation of square

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

Matrix::~Matrix() // destructur
{
    for(int i = 0; i < 4; i++) // initializing field by NULL
    {
        for(int j = 0; j < 4; j++)
        {
            delete Field[i][j];
        }
    }
    //delete parent;
}

void Matrix::shift(int dir, int line)
{
    int start_point;

    switch (dir)
    {
    case DOWN:
        start_point = 3;
        for (int i = 3; i >= 0; i--)
        {
            if(Field[line][i] != nullptr)
            {
                if(start_point != 3  && Field[line][start_point + 1]->Level == Field[line][i]->Level)
                {
                    Field[line][i]->Animate(start_point + 1,line);

                    Square *tmp = Field[line][i];
                    delete tmp;
                    Field[line][i] = nullptr;

                    Field[line][start_point + 1]->LevelUp();

                    Score += Field[line][start_point + 1]->Level;
                    Score_Print->setText(QString("Score:\t") + QString::number(Score));

                    pair tmp1;
                    tmp1.memb[0] = line;
                    tmp1.memb[1] = i;
                    Avaible_Sqr.push_back(tmp1);

                }
                else
                {
                    int lvl = 1;
                    int last_lvl = Field[line][i]->Level;
                    while (last_lvl != 2)
                    {
                        last_lvl /= 2;
                        ++lvl;
                    }

                    Square *tmp = Field[line][i];
                    delete tmp;
                    Field[line][i] = nullptr;

                    Field[line][start_point] = new Square(line, i);

                    for(int j = 0; j < lvl - 1; j++)
                    {
                        Field[line][start_point]->LevelUp();
                    }
                    Field[line][start_point]->Animate(line, start_point);

                    pair tmp1;
                    tmp1.memb[0] = line;
                    tmp1.memb[1] = i;
                    Avaible_Sqr.push_back(tmp1);

                    for(auto it = Avaible_Sqr.begin(); it != Avaible_Sqr.end(); ++it)
                    {
                        if(it->memb[0] == line && it->memb[1] == start_point)
                        {
                            Avaible_Sqr.erase(it);
                            break;
                        }
                    }

                    --start_point;

                }
            }
        }

    break;

    case UP:
        start_point = 0;
        for (int i = 0; i < 4; i++)
        {
            if(Field[line][i] != nullptr)
            {
                if(start_point != 0  && Field[line][start_point - 1]->Level == Field[line][i]->Level)
                {
                    Field[line][i]->Animate(line, start_point - 1);

                    Square *tmp = Field[line][i];
                    delete tmp;
                    Field[line][i] = nullptr;

                    Field[line][start_point - 1]->LevelUp();

                    Score += Field[line][start_point - 1]->Level;
                    Score_Print->setText(QString("Score:\t") + QString::number(Score));

                    pair tmp1;
                    tmp1.memb[0] = line;
                    tmp1.memb[1] = i;
                    Avaible_Sqr.push_back(tmp1);

                }
                else
                {
                    int lvl = 1;
                    int last_lvl = Field[line][i]->Level;
                    while (last_lvl != 2)
                    {
                        last_lvl /= 2;
                        ++lvl;
                    }


                    Square *tmp = Field[line][i];
                    delete tmp;
                    Field[line][i] = nullptr;

                    Field[line][start_point] = new Square(line,i);

                    for(int j = 0; j < lvl - 1; j++)
                    {
                        Field[line][start_point]->LevelUp();
                    }
                    Field[line][start_point]->Animate(line, start_point);

                    pair tmp1;
                    tmp1.memb[0] = line;
                    tmp1.memb[1] = i;
                    Avaible_Sqr.push_back(tmp1);

                    for(auto it = Avaible_Sqr.begin(); it != Avaible_Sqr.end(); ++it)
                    {
                        if(it->memb[0] == line && it->memb[1] == start_point)
                        {
                            Avaible_Sqr.erase(it);
                            break;
                        }
                    }

                    ++start_point;

                }
            }
        }
    break;

    case LEFT:
        start_point = 0;
        for (int i = 0; i < 4; i++)
        {
            if(Field[i][line] != nullptr)
            {
                if(start_point != 0  && Field[start_point - 1][line]->Level == Field[i][line]->Level)
                {
                    Field[i][line]->Animate(start_point - 1,line);

                    Square *tmp = Field[i][line];
                    delete tmp;
                    Field[i][line] = nullptr;

                    Field[start_point - 1][line]->LevelUp();

                    Score += Field[start_point - 1][line]->Level;
                    Score_Print->setText(QString("Score:\t") + QString::number(Score));

                    pair tmp1;
                    tmp1.memb[0] = i;
                    tmp1.memb[1] = line;
                    Avaible_Sqr.push_back(tmp1);

                }
                else
                {
                    int lvl = 1;
                    int last_lvl = Field[i][line]->Level;
                    while (last_lvl != 2)
                    {
                        last_lvl /= 2;
                        ++lvl;
                    }

                    Square *tmp = Field[i][line];
                    delete tmp;
                    Field[i][line] = nullptr;

                    Field[start_point][line] = new Square(i,line);

                    for(int j = 0; j < lvl - 1; j++)
                    {
                        Field[start_point][line]->LevelUp();
                    }
                    Field[start_point][line]->Animate(start_point,line);

                    pair tmp1;
                    tmp1.memb[0] = i;
                    tmp1.memb[1] = line;
                    Avaible_Sqr.push_back(tmp1);

                    for(auto it = Avaible_Sqr.begin(); it != Avaible_Sqr.end(); ++it)
                    {
                        if(it->memb[0] == start_point && it->memb[1] == line)
                        {
                            Avaible_Sqr.erase(it);
                            break;
                        }
                    }

                    ++start_point;

                }
            }
        }
    break;

    case RIGHT:
        start_point = 3;
        for (int i = 3; i >= 0; i--)
        {
            if(Field[i][line] != nullptr)
            {
                if(start_point != 3  && Field[start_point + 1][line]->Level == Field[i][line]->Level)
                {
                    Field[i][line]->Animate(start_point + 1,line);

                    Square *tmp = Field[i][line];
                    delete tmp;
                    Field[i][line] = nullptr;

                    Field[start_point + 1][line]->LevelUp();

                    Score += Field[start_point + 1][line]->Level;
                    Score_Print->setText(QString("Score:\t") + QString::number(Score));

                    pair tmp1;
                    tmp1.memb[0] = i;
                    tmp1.memb[1] = line;
                    Avaible_Sqr.push_back(tmp1);

                }
                else
                {
                    int lvl = 1;
                    int last_lvl = Field[i][line]->Level;
                    while (last_lvl != 2)
                    {
                        last_lvl /= 2;
                        ++lvl;
                    }


                    Square *tmp = Field[i][line];
                    delete tmp;
                    Field[i][line] = nullptr;

                    Field[start_point][line] = new Square(i,line);

                    for(int j = 0; j < lvl - 1; j++)
                    {
                        Field[start_point][line]->LevelUp();
                    }
                    Field[start_point][line]->Animate(start_point,line);

                    pair tmp1;
                    tmp1.memb[0] = i;
                    tmp1.memb[1] = line;
                    Avaible_Sqr.push_back(tmp1);

                    for(auto it = Avaible_Sqr.begin(); it != Avaible_Sqr.end(); ++it)
                    {
                        if(it->memb[0] == start_point && it->memb[1] == line)
                        {
                            Avaible_Sqr.erase(it);
                            break;
                        }
                    }

                    --start_point;

                }
            }
        }
    break;
    }

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

    QPalette Score_Print_Pallet;
    Score_Print_Pallet.setColor(QPalette::WindowText, QColor(119, 110,101));

    Score_Print = new QLabel(parent);
    QFont font = Score_Print->font();
    font.setPixelSize(64);
    font.setBold(true);
    font.setFamily("Bauhaus 93");
    Score_Print->setFont(font);
    Score_Print->setPalette(Score_Print_Pallet);
    Score_Print->setGeometry(X_SPACE, X_SPACE, parent->width() - (X_SPACE * 2), X_SPACE * 2);
    Score_Print->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    Score_Print->setText(QString("Score:\t") + QString::number(Score));

    Score_Print->show();

    for(int i = 0; i < 2; i++)
    {
        pair tmp = newSquare();
        Field[tmp.memb[0]][tmp.memb[1]] = new Square(tmp.memb[0],tmp.memb[1]);
    }

}

void Matrix::Down() // function for swapping Squares Down
{
    /*thread TH1([&](){Matrix::shift(DOWN,0);});
    thread TH2([&](){Matrix::shift(DOWN,1);});
    thread TH3([&](){Matrix::shift(DOWN,2);});
    thread TH4([&](){Matrix::shift(DOWN,3);});
    TH1.join();
    TH2.join();
    TH3.join();
    TH4.join();*/

    Matrix::shift(DOWN,0);
    Matrix::shift(DOWN,1);
    Matrix::shift(DOWN,2);
    Matrix::shift(DOWN,3);

    pair tmp = newSquare();
    Field[tmp.memb[0]][tmp.memb[1]] = new Square(tmp.memb[0],tmp.memb[1]);
}
void Matrix::Up() // function for swapping Squares Up
{
    /*thread TH1([&](){Matrix::shift(UP,0);});
    thread TH2([&](){Matrix::shift(UP,1);});
    thread TH3([&](){Matrix::shift(UP,2);});
    thread TH4([&](){Matrix::shift(UP,3);});
    TH1.join();
    TH2.join();
    TH3.join();
    TH4.join();*/

    Matrix::shift(UP,0);
    Matrix::shift(UP,1);
    Matrix::shift(UP,2);
    Matrix::shift(UP,3);

    pair tmp = newSquare();
    Field[tmp.memb[0]][tmp.memb[1]] = new Square(tmp.memb[0],tmp.memb[1]);
}
void Matrix::Right() // function for swapping Squares Right
{
    /*thread TH1([&](){Matrix::shift(RIGHT,0);});
    thread TH2([&](){Matrix::shift(RIGHT,1);});
    thread TH3([&](){Matrix::shift(RIGHT,2);});
    thread TH4([&](){Matrix::shift(RIGHT,3);});
    TH1.join();
    TH2.join();
    TH3.join();
    TH4.join();*/
    Matrix::shift(RIGHT,0);
    Matrix::shift(RIGHT,1);
    Matrix::shift(RIGHT,2);
    Matrix::shift(RIGHT,3);

    pair tmp = newSquare();
    Field[tmp.memb[0]][tmp.memb[1]] = new Square(tmp.memb[0],tmp.memb[1]);
}
void Matrix::Left() // function for swapping Squares Left
{
    /*thread TH1([&](){Matrix::shift(LEFT,0);});
    thread TH2([&](){Matrix::shift(LEFT,1);});
    thread TH3([&](){Matrix::shift(LEFT,2);});
    thread TH4([&](){Matrix::shift(LEFT,3);});
    TH1.join();
    TH2.join();
    TH3.join();
    TH4.join();*/
    Matrix::shift(LEFT,0);
    Matrix::shift(LEFT,1);
    Matrix::shift(LEFT,2);
    Matrix::shift(LEFT,3);

    pair tmp = newSquare();
    Field[tmp.memb[0]][tmp.memb[1]] = new Square(tmp.memb[0],tmp.memb[1]);
}







