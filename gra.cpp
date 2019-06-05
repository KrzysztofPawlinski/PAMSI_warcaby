#include "gra.h"

gra::gra()
{}

int gra::graZKomputerem(char pierwszy){
    int wynik;
    plansza p;
    p.wypisz();
    while(true){
        std::cout<<"Ruch czarnych"<<std::endl;
        p.przesun('c',false,0,0,0,0,'l');
        system("cls");
        p.wypisz();
        if(p.policzPrzeciwnika('c')==0){//Sprawdzamy czy przeciwnikowi pozostaly figury
            std::cout<<"Gratulacje! czare wygraly!"<<std::endl;
            wynik=p.policzPrzeciwnika('b');//liczy wynik
            break;
        }
        std::cout<<"Ruch bialych"<<std::endl;
        //p.przesun('b',false,0,0,0,0,'l');
        optymalnyRuch('b',p);
        //system("cls");
        p.wypisz();

        if(p.policzPrzeciwnika('b')==0){
            std::cout<<"Gratulacje! czare wygraly!"<<std::endl;
            wynik=p.policzPrzeciwnika('c');
            break;
        }
    }
    return wynik;
}

int gra::dwochGraczy(){
    int wynik;
    plansza p;
    p.wypisz();
    while(true){
        std::cout<<"Ruch czarnych"<<std::endl;
        p.przesun('c',false,0,0,0,0,'l');
        system("cls");
        p.wypisz();

        if(p.policzPrzeciwnika('c')==0){//Sprawdzamy czy przeciwnikowi pozostaly figury
            std::cout<<"Gratulacje! czare wygraly!"<<std::endl;
            wynik=p.policzPrzeciwnika('b');//liczy wynik
            break;
        }

        std::cout<<"Ruch bialych"<<std::endl;
        p.przesun('b',false,0,0,0,0,'l');
        system("cls");
        p.wypisz();

        if(p.policzPrzeciwnika('b')==0){
            std::cout<<"Gratulacje! czare wygraly!"<<std::endl;
            wynik=p.policzPrzeciwnika('c');
            break;
        }
    }
    return wynik;
}

plansza gra::optymalnyRuch(char kolor, plansza& p){
    int biezacy=0;
    int xb,yb,xdb,ydb;
    char kb;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(kolor=='b'){
                if(p._pionki[i][j]==1){

                    std::cout<<"PIONEK: "<<i<<" "<<j<<std::endl;
                    std::cout<<p._pionki[i][j]<<std::endl;
                    std::cout<<p._pionki[i+1][j-1]<<std::endl;
                    std::cout<<p._pionki[i+1][j+1]<<std::endl;


                    plansza p_tmp;
                    p_tmp.kopiujUklad(&p);
                    //std::cout<<"Przed ruchem w lewo: "<<std::endl;
                    //p_tmp.wypisz();
                    int lewo = p_tmp.przesun(kolor,true,j,i,0,0,'l');
                    //std::cout<<std::endl;
                    std::cout<<"Po ruchu w lewo: "<<std::endl;
                    p_tmp.wypisz();
                    p_tmp.kopiujUklad(&p);
                    int prawo = p_tmp.przesun(kolor,true,j,i,0,0,'p');
                    std::cout<<"LEWO: "<<lewo<<std::endl;
                    std::cout<<"PRAWO: "<<prawo<<std::endl;

                    if(lewo>biezacy){
                        std::cout<<"myk w lewo"<<std::endl;
                        biezacy=lewo;
                        xb=i;
                        yb=j;
                        kb='l';
                    }
                    if(prawo>biezacy){
                        std::cout<<"myk w prawo"<<std::endl;
                        biezacy=prawo;
                        xb=i;
                        yb=j;
                        kb='p';
                    }
                }
                else if(p._pionki[i][j]==3){
                    for(int k=0;k<8;k++){
                        for(int l=0;l<8;l++){
                            plansza p_tmp;
                            p_tmp.kopiujUklad(&p);
                            int nowy = p_tmp.przesun(kolor,true,i,j,k,l,'l');
                            if(nowy>biezacy){
                                biezacy=nowy;
                                xb=i;
                                yb=j;
                                xdb=k;
                                ydb=l;
                            }
                        }
                    }
                }
            }
            else if(kolor=='c'){
                if(p._pionki[i][j]==2){
                    plansza p_tmp;
                    p_tmp.kopiujUklad(&p);
                    int lewo = p_tmp.przesun(kolor,true,j,i,0,0,'l');
                    p_tmp.kopiujUklad(&p);
                    int prawo = p_tmp.przesun(kolor,true,j,i,0,0,'p');
                    if(lewo>biezacy){
                        biezacy=lewo;
                        xb=i;
                        yb=j;
                        kb='l';
                    }
                    if(prawo>biezacy){
                        biezacy=prawo;
                        xb=i;
                        yb=j;
                        kb='p';
                    }
                }
                else if(p._pionki[i][j]==4){
                    for(int k=0;k<8;k++){
                        for(int l=0;l<8;l++){
                            plansza p_tmp;
                            p_tmp.kopiujUklad(&p);
                            int nowy = p_tmp.przesun(kolor,true,i,j,k,l,'l');
                            if(nowy>biezacy){
                                biezacy=nowy;
                                xb=i;
                                yb=j;
                                xdb=k;
                                ydb=l;
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout<<xb<<" "<<yb<<" "<<xdb<<" "<<ydb<<" "<<kb<<std::endl;
    std::cout<<p.przesun(kolor,true,yb,xb,ydb,xdb,kb)<<" :AAAAAA"<<std::endl;
    p.wypisz();
    return p;
}
