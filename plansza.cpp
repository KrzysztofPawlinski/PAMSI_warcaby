#include "plansza.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

plansza::plansza()
{
    int tmp[8][8]={
        {0,1,0,1,0,1,0,1},
        {0,0,0,0,0,0,1,0},
        {0,2,0,1,0,1,0,1},
        {0,0,0,0,2,0,4,0},
        {0,1,0,0,0,0,0,0},
        {2,0,0,0,2,0,2,0},
        {0,2,0,4,0,2,0,2},
        {2,0,2,0,0,0,2,0}
    };
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            _pionki[i][j]=tmp[i][j];
        }
    }
}

int konwerter(char arg){
    int result;
    switch(arg){
    case 'A':
        result=0;
        break;
    case 'B':
        result=1;
        break;
    case 'C':
        result=2;
        break;
    case 'D':
        result=3;
        break;
    case 'E':
        result=4;
        break;
    case 'F':
        result=5;
        break;
    case 'G':
        result=6;
        break;
    case 'H':
        result=7;
        break;
    }
    return result;
}

void plansza::wypisz(){
    std::cout<<"   ";
    for(char i='A';i<'I';i++){
        std::cout<<" "<<i<<" ";
    }
    std::cout<<std::endl<<std::endl<<std::endl;
    for(int i=0;i<8;i++){
        std::cout<<i+1<<"  ";
        for(int j=0;j<8;j++){
            if(_pionki[i][j]==0){
                std::cout<<" - ";
            }
            else if(_pionki[i][j]==1){
                std::cout<<" B ";
            }
            else if(_pionki[i][j]==2){
                std::cout<<" C ";
            }
            else if(_pionki[i][j]==4){
                std::cout<<"DC ";
            }
            else{
                std::cout<<"DB ";
            }
        }
        std::cout<<std::endl<<std::endl;
    }
}

int plansza::przesunPionek(int xstart, int ystart, char kierunek, char gracz, bool komputer){
    int result=0;//Przyjmuje wartosc 1 jesli przesunieto pionek bez bicia, 2 jesli z biciem i 0 jesli blad
    if(xstart<0||xstart>8||ystart<0||ystart>8||(kierunek!='l'&&kierunek!='p')){
        std::cout<<"Podano zle dane pola lub kierunku ruchu."<<std::endl;
        return 0;
    }
    if(gracz=='c'){
        if(_pionki[xstart][ystart]!=2){
            std::cout<<"Na zadanym polu nie ma Twojego pionka! Sproboj ponownie"<<std::endl;
            return 0;
        }
    }
    else if(gracz=='b'){
        if(_pionki[xstart][ystart]!=1){
            std::cout<<"Na zadanym polu nie ma Twojego pionka! Sproboj ponownie"<<std::endl;
            return 0;
        }
    }
    int xnowy, ynowy;
    //4 NASTEPNE ify - PRZESUWANIE JESLI NIE NAPOTKA PRZECIWNIKA
    if(kierunek=='l' && gracz=='c' && _pionki[xstart-1][ystart-1]==0 &&
            xstart-1>=0 && xstart-1<=7 && ystart-1>=0 && ystart-1<=7){
        xnowy=xstart-1;
        ynowy=ystart-1;
        _pionki[xnowy][ynowy]=2;
        result+=1;
        if(zamianaNaDamke(xstart-1,ystart-1,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }
    }
    else if(kierunek=='p' && gracz=='c' && _pionki[xstart-1][ystart+1]==0 &&
            xstart-1>=0 && xstart-1<=7 && ystart+1>=0 && ystart+1<=7){
        xnowy=xstart-1;
        ynowy=ystart+1;
        _pionki[xnowy][ynowy]=2;
        result+=1;
        if(zamianaNaDamke(xstart-1,ystart+1,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }
    }
    else if(kierunek=='l' && gracz=='b' && _pionki[xstart+1][ystart-1]==0 &&
            xstart+1>=0 && xstart+1<=7 && ystart-1>=0 && ystart-1<=7){
        xnowy=xstart+1;
        ynowy=ystart-1;
        _pionki[xnowy][ynowy]=1;
        result+=1;
        if(zamianaNaDamke(xstart+1,ystart-1,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }
    }
    else if(kierunek=='p' && gracz=='b' && _pionki[xstart+1][ystart+1]==0 &&
            xstart+1>=0 && xstart+1<=7 && ystart+1>=0 && ystart+1<=7){
        xnowy=xstart+1;
        ynowy=ystart+1;
        _pionki[xnowy][ynowy]=1;
        result+=1;
        if(zamianaNaDamke(xstart+1,ystart+1,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }
    }
    //4 KOLEJNE ify - PRZESUWANIE JESLI NAPOTKANO PRZECIWNIKA
    else if(kierunek=='l' && gracz=='c' && (_pionki[xstart-1][ystart-1]==1||_pionki[xstart-1][ystart-1]==3) && _pionki[xstart-2][ystart-2]==0 &&
            xstart-1>=0 && xstart-1<=7 && ystart-1>=0 && ystart-1<=7 &&
            xstart-2>=0 && xstart-2<=7 && ystart-2>=0 && ystart-2<=7){
        xnowy=xstart-2;
        ynowy=ystart-2;
        _pionki[xstart-1][ystart-1]=0;
        _pionki[xstart-2][ystart-2]=2;
        result+=2;
        if(zamianaNaDamke(xstart-2,ystart-2,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }
    }
    else if(kierunek=='p' && gracz=='c' && (_pionki[xstart-1][ystart+1]==1 || _pionki[xstart-1][ystart+1]==3)&& _pionki[xstart-2][ystart+2]==0 &&
            xstart-1>=0 && xstart-1<=7 && ystart+1>=0 && ystart+1<=7 &&
            xstart-2>=0 && xstart-2<=7 && ystart+2>=0 && ystart+2<=7){
        xnowy=xstart-2;
        ynowy=ystart+2;
        _pionki[xstart-1][ystart+1]=0;
        _pionki[xstart-2][ystart+2]=2;
        result+=2;
        if(zamianaNaDamke(xstart-2,ystart+2,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }
    }
    else if(kierunek=='l' && gracz=='b' && (_pionki[xstart+1][ystart-1]==2 || _pionki[xstart+1][ystart-1]==4)&& _pionki[xstart+2][ystart-2]==0 &&
            xstart+1>=0 && xstart+1<=7 && ystart-1>=0 && ystart-1<=7 &&
            xstart+2>=0 && xstart+2<=7 && ystart-2>=0 && ystart-2<=7){
        xnowy=xstart+2;
        ynowy=ystart-2;
        _pionki[xstart+1][ystart-1]=0;
        _pionki[xstart+2][ystart-2]=1;
        result+=2;
        if(zamianaNaDamke(xstart+2,ystart-2,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }
    }
    else if(kierunek=='p' && gracz=='b' && (_pionki[xstart+1][ystart+1]==2 || _pionki[xstart+1][ystart+1]==4)&& _pionki[xstart+2][ystart+2]==0 &&
            xstart+1>=0 && xstart+1<=7 && ystart+1>=0 && ystart+1<=7 &&
            xstart+2>=0 && xstart+2<=7 && ystart+2>=0 && ystart+2<=7){
        xnowy=xstart+2;
        ynowy=ystart+2;
        _pionki[xstart+1][ystart+1]=0;
        _pionki[xstart+2][ystart+2]=1;
        result+=2;
        if(zamianaNaDamke(xstart+2,ystart+2,gracz)==true){
            _pionki[xstart][ystart]=0;
            return result;
        }

    }
    else{
        result=0;
        std::cout<<"Nie mozna przesunac pionka w wybrane miejsce."<<std::endl;
        std::cout<<_pionki[xstart+1][ystart-1]<<" "<<_pionki[xstart+1][ystart+1]<<std::endl;
        return result;
    }
    _pionki[xstart][ystart]=0;

    //Ta czesc odpowiada za wielokrotnosc ruchu
    plansza tmpPlansza;
    if(result!=0){
        char wybor;
        int sygnal2=1;
        do{
            if(komputer==false){
                system("cls");
                wypisz();
                std::cout<<"Czy chcesz zakonczyc swoj ruch? (t/n)"<<std::endl;
                std::cin>>wybor;
                system("cls");
                wypisz();
                if(wybor=='t'){
                    tmpPlansza.kopiujUklad(this);
                    //wypisz();
                }
                if(wybor=='n'&&result<=1){
                    tmpPlansza.kopiujUklad(this);

                }
                else if(wybor=='n'&&result>1){
                    int sygnal3=1;
                    do{
                        if(komputer==false){
                            std::cout<<"Podaj kierunek w jakim chcesz sie poruszyc (l lub p) (wpisz q zeby zrezygnowac): "<<std::endl;
                            std::cin>>kierunek;
                            system("cls");
                            wypisz();
                        }
                        if(kierunek=='l'||kierunek=='p'){
                            tmpPlansza.kopiujUklad(this);
                            int wynik=tmpPlansza.przesunPionek(xnowy,ynowy,kierunek,gracz,komputer);
                            if(wynik>1){
                                result+=wynik;
                            }
                            else{
                                std::cout<<"Nie mozna wykonac zadnego bicia"<<std::endl;
                                break;
                            }
                        }
                        else if(kierunek=='q'){
                             tmpPlansza.kopiujUklad(this);
                        }
                        else{
                            std::cout<<"Podaj 'l' lub 'p'"<<std::endl;
                            sygnal3=0;
                        }
                    }while(sygnal3==0);
                }
                else{
                    std::cout<<"Podaj t, n lub q"<<std::endl;
                    sygnal2=1;
                    //result=0;
                }
            }
            //else{
              //  tmpPlansza.kopiujUklad(this);
                //if(tmpPlansza.przesunPionek(xnowy,ynowy,'l',gracz,komputer)==2){
              //    result+=2;
                //
                //}
                //else if(tmpPlansza.przesunPionek(xnowy,ynowy,'p',gracz,komputer)==2){
                  //result+=2;
                  //
                //}
            //}
        }while(sygnal2==0);
        //if(result==2)
        this->kopiujUklad(&tmpPlansza);//jest tak bo dziwne problemy ze scopem
    }
    return result;
}//1. W rekurencji wywala z petli jesli podamy zly kierunek, nawet jesli drugi jest dobry(linie 184-192)

void plansza::kopiujUklad(plansza *arg){
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            _pionki[i][j]=arg->_pionki[i][j];
        }
    }
}

int plansza::sprawdzCzyDamkaBije(int xstart,int ystart, int xdest, int ydest, char gracz){
    int x=xstart,y=ystart,licznik=0,result;
    int xfound,yfound;
    while(x!=xdest){
        //DO TESTOW: std::cout<<xstart<<" "<<ystart<<" "<<x<<" "<<y<<" "<<xdest<<" "<<ydest<<std::endl;
        if(xdest>xstart && ydest>ystart){
            x++;
            y++;
        }
        else if(xdest>xstart && ydest<ystart){
            x++;
            y--;
        }
        else if(xdest<xstart || ydest<ystart){
            x--;
            y--;
        }
        else if(xdest<xstart || ydest>ystart){
            x--;
            y++;
        }
        if(gracz=='c'){
            if(_pionki[x][y]==1 || _pionki[x][y]==3){
                xfound=x;
                yfound=y;
                licznik++;
            }
            else if(_pionki[x][y]==2 || _pionki[x][y]==4){
                std::cout<<"Nie mozesz przeskakiwac swoich figur"<<std::endl;
                result=0;
                break;
            }
            else{
                result=1;
            }
            if(licznik==1){
                _pionki[xfound][yfound]=0;
                std::cout<<"Found!"<<xfound<<" "<<yfound<<std::endl;
                result=2;
            }
            else if(licznik>1){
                std::cout<<"Na drodze damki jest wiecej niz jedna figura przeciwnika"<<std::endl;
            }
        }
        if(gracz=='b'){
            if(_pionki[x][y]==2 && _pionki[x][y]==4){
                xfound=x;
                yfound=y;
                licznik++;
            }
            else if(_pionki[x][y]==1 && _pionki[x][y]==3){
                std::cout<<"Nie mozesz przeskakiwac swoich figur"<<std::endl;
                result=0;
                break;
            }
            else{
                result=1;
            }
            if(licznik==1){
                _pionki[xfound][yfound]=0;
                std::cout<<"Found!"<<xfound<<" "<<yfound<<std::endl;
                result=2;
            }
            else if(licznik>1){
                std::cout<<"Na drodze damki jest wiecej niz jedna figura przeciwnika"<<std::endl;
            }
        }
    }
    return result;
}

int plansza::przesunDamke(int xstart, int ystart, int xdest, int ydest, char gracz, bool komputer){
    int result;//Przyjmuje wartosc 1 jesli przesunieto pionek bez bicia, 2 jesli z biciem i 0 jesli blad
    if(_pionki[xdest][ydest]==0){
        int roznicastart=ystart-xstart;
        int roznicadest=ydest-xdest;
        int sumadest=ydest+xdest;
        int sumastart=ystart+xstart;
        if(roznicadest==roznicastart || sumadest==sumastart){
            result=sprawdzCzyDamkaBije(xstart,ystart,xdest,ydest,gracz);
            if(result==2){
                _pionki[xdest][ydest]=_pionki[xstart][ystart];
                _pionki[xstart][ystart]=0;
            }
            if(result==1){
                _pionki[xdest][ydest]=_pionki[xstart][ystart];
                _pionki[xstart][ystart]=0;
            }
        }
        else{
            std::cout<<"Damka moze poruszac sie tylko po przekatnej!"<<std::endl;
            result=0;
        }
    }

    else if(_pionki[xdest][ydest]==1 || _pionki[xdest][ydest]==2 ||
            _pionki[xdest][ydest]==3 || _pionki[xdest][ydest]==4){
        std::cout<<"Na zadanym polu jest pionek. Sproboj jeszcze raz!"<<std::endl;
        result=0;
    }

    //Ta czesc odpowiada za wielokrotnosc ruchu
    plansza tmpPlansza;
    if(result!=0){
        char wybor;
        int sygnal2=1;
        int xdes,ydes;
        char XDes;
        do{
            if(komputer==false){
                system("cls");
                wypisz();
                std::cout<<"Czy chcesz zakonczyc swoj ruch? (t/n)"<<std::endl;
                std::cin>>wybor;
                system("cls");
                wypisz();
            }
            //else{
            //}
            if(wybor=='t'){
                tmpPlansza.kopiujUklad(this);
                wypisz();
            }
            if(wybor=='n'&&result<=1){
                tmpPlansza.kopiujUklad(this);
            }
            else if(wybor=='n'&&result<=1){
                result=5;
                int sygnal3=1;
                do{
                    if(komputer==false){
                        std::cout<<"Podaj wspolrzedne pola, na ktore chcesz sie przemiescic: (np. A1): "<<std::endl;
                        std::cin>>XDes;
                        std::cin>>ydes;
                        system("cls");
                        wypisz();
                        xdes=konwerter(XDes);
                    }
                    //else{
                    //}
                    if(XDes=='q'){}
                    else if(xdes>0||xdes<8||ydes>0||ydes<8){
                        tmpPlansza.kopiujUklad(this);
                        std::cout<<tmpPlansza.przesunDamke(xdest,ydest,ydes-1,xdes,gracz,komputer)<<std::endl;
                        if(tmpPlansza.przesunDamke(xdest,ydest,ydes-1,xdes,gracz,komputer)==2){
                            result=2;
                        }
                        else{
                            std::cout<<"Nie mozna wykonac zadnego bicia"<<std::endl;
                            break;
                        }
                    }

                    else{
                        std::cout<<"Podaj wspolrzedne mieszczace sie w zakresie planszy"<<std::endl;
                        sygnal3=0;
                    }
                }while(sygnal3==0);
            }
            else{
                std::cout<<"Podaj t, n lub q"<<std::endl;
                result=1;
            }
            this->kopiujUklad(&tmpPlansza);
        }while(sygnal2==0);
        this->kopiujUklad(&tmpPlansza);//jest tak bo dziwne problemy ze scopem
        return result;
    }

    //1. Jak w kolejnym ruchu wpisze sie zle pole docelowe to konczy ruch gracza
    return result;
}

bool plansza::zamianaNaDamke(int xstop,int ystop,char gracz){
    if(gracz=='c'){
        if(xstop==0){
            _pionki[xstop][ystop]=4;
            return true;
        }
    }
    else if(gracz=='b'){
        if(xstop==7){
            _pionki[xstop][ystop]=3;
            return true;
        }
    }
    return false;
}

int plansza::policzPrzeciwnika(char gracz){
    int result=0;
    if(gracz=='c'){
        for(int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if(_pionki[i][j]==1)
                    result++;
                if(_pionki[i][j]==3)
                    result=result+3;
            }
        }
    }
    else if(gracz=='b'){
        for(int i=0;i<7;i++){
            for(int j=0;j<7;j++){
                if(_pionki[i][j]==2)
                    result++;
                if(_pionki[i][j]==4)
                    result=result+3;
            }
        }
    }
    return result*2;
}

int plansza::przesun(char gracz, bool komputer, int xstartkomp, int ystartkomp, int xdestkomp, int ydestkomp, char kierunekkomp){
    int waga;//Zmienna ktora przekazuje ile i jakich figur zbito w ruchu
    int przecStart=policzPrzeciwnika(gracz);//Liczy w ten sposob zeby uwzglednic to, ze bicie damki jest bardziej korzystne
    int sygnal;//sygnal bledu
    int x,y,xdes,ydes,xstart,ystart;
    char XDes,X,kierunek;

    do{
        if(komputer==false){
            std::cout<<"Podaj wspolrzedne pionka, ktory chcesz przesunac (np. A1): ";
            std::cin>>X;
            std::cin>>y;
            system("cls");
            wypisz();
            x=konwerter(X);
        }
        else{
            x=xstartkomp;
            y=ystartkomp+1;
        }
        sygnal=1;
        xstart=y-1;
        ystart=x;
        if(x<0||x>8||y<0||y>8){
            std::cout<<"Podano zle wspolrzedne poczatkowe."<<std::endl;
            sygnal=0;
        }
        else if(gracz=='c'){
            if(_pionki[xstart][ystart]==2){
                if(komputer==false){
                    std::cout<<"Podaj kierunek w jakim chcesz sie poruszyc (l lub p): "<<std::endl;
                    std::cin>>kierunek;
                    system("cls");
                    wypisz();
                    sygnal=przesunPionek(y-1,x,kierunek,gracz,komputer);
                }
                else{
                    sygnal=przesunPionek(ystartkomp,xstartkomp,kierunekkomp,gracz,komputer);
                }
            }
            else if(_pionki[xstart][ystart]==4){
                if(komputer==false){
                    std::cout<<"Podaj wspolrzedne pola, na ktore chcesz sie przemiescic: (np. A1): "<<std::endl;
                    std::cin>>XDes;
                    std::cin>>ydes;
                    system("cls");
                    wypisz();
                    xdes=konwerter(XDes);
                    sygnal=przesunDamke(y-1,x,ydes-1,xdes,gracz,komputer);
                }
                else{
                    sygnal=przesunDamke(ystartkomp,xstartkomp,ydestkomp,xdestkomp,gracz,komputer);
                }
            }
            else{
                std::cout<<"Na zadanym polu nie ma Twojego pionka! Sproboj ponownie"<<std::endl;
                sygnal=0;
            }
        }
        else if(gracz=='b'){
            if(_pionki[xstart][ystart]==1){
                if(komputer==false){
                    std::cout<<"Podaj kierunek w jakim chcesz sie poruszyc (l lub p): "<<std::endl;
                    std::cin>>kierunek;
                    system("cls");
                    wypisz();
                    sygnal=przesunPionek(y-1,x,kierunek,gracz,komputer);
                }
                else{
                    sygnal=przesunPionek(ystartkomp,xstartkomp,kierunekkomp,gracz,komputer);
                }
            }
            else if(_pionki[xstart][ystart]==3){
                if(komputer==false){
                    std::cout<<"Podaj wspolrzedne pola, na ktore chcesz sie przemiescic: (np. A 1): "<<std::endl;
                    std::cin>>XDes;
                    std::cin>>ydes;
                    system("cls");
                    wypisz();
                    xdes=konwerter(XDes);
                    sygnal=przesunDamke(y-1,x,ydes-1,xdes,gracz,komputer);
                }
                else{
                    sygnal=przesunDamke(ystartkomp,xstartkomp,ydestkomp,xdestkomp,gracz,komputer);
                }
            }
            else{
                std::cout<<"Na zadanym polu nie ma Twojego pionka! Sproboj ponownie"<<std::endl;
                sygnal=0;
            }
            if(komputer==true){
                break;
            }
        }
   }while(sygnal==0);
   int przecKonc=policzPrzeciwnika(gracz);
   waga=przecStart-przecKonc;
   if(sygnal==1){
       waga=1;
   }
   return waga;
}

