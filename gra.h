#ifndef GRA_H
#define GRA_H

#include <iostream>
#include "plansza.h"
#include <windows.h>

class gra
{
public:
    gra();
    void menu();
    int dwochGraczy();//zwraca wynik zwyciezcy, mozna cos z tym zrobic potem (wyswietlic, zapisac do pliku.. tylko wtedy potrzeba jakos przekazac nick jeszcze
    int graZKomputerem(char pierwszy);
    plansza optymalnyRuch(char kolor, plansza& p);
    //
    //wyslac do przesun parametr ktory, jesli jakis to wywola ja ze zautomatyzowanymi cin-ami
    //wtedy tworze kopie planszy, sprawdzam dla jakiejs glebokowsci i wybieram najlepszy dlugofalowo ruch
    //
    //Statystyka? Moglby po wygranej liczyc punkty zwyciezcy (pionek - 1pkt., damka - 3pkt.) i zapisywac do pliku tabele rekordow
    //Moze zapisywac tez jakos liczbe ruchow, czas gry albo cos takiego
    //Ranking userow, ktorzy wygrali najwieksza ilosc razy
};

#endif // GRA_H
