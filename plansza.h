#ifndef PLANSZA_H
#define PLANSZA_H

//enum pionki{
    //puste=0,
    //czarny=1,
    //bialy=2,
    //cDamka=3,
    //bDamka=4
//};

class plansza
{
public:
    plansza();
    char _gracz='c';
    void kopiujUklad(plansza *arg);
    int _pionki[8][8];
    void wypisz();
    int przesunPionek(int xstart, int ystart, char kierunek, char gracz, bool komputer);
    int przesunDamke(int xstart, int ystart, int xdest, int ydest, char gracz, bool komputer);
    int przesun(char gracz, bool komputer, int xstartkomp, int ystartkomp, int xdestkomp, int ydestkomp, char kierunekkomp);
    bool zamianaNaDamke(int xstop,int ystop,char gracz);
    int sprawdzCzyDamkaBije(int xstart,int ystart, int xdest, int ydest, char gracz);
    int policzPrzeciwnika(char gracz);
};

#endif // PLANSZA_H
