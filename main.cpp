#include <iostream>
#include <cstdlib>
#include <fstream>
#include <conio.h>

#include <ctime>

using namespace std;

/*
Napisz program, który umożliwi przeprowadzenie testu wyboru z „Fizyki”. Pytania i odpowiedzi podane są
w pliku tekstowym W teście jest 20 pytań losowanych z puli 100 pytań. Użytkownik po wykonaniu tekstu
uzyskuje informacje o liczbie zdobytych punktów i poprawności udzielanych odpowiedzi. Wyniki kolejnych
użytkowników są zapisywane w pliku. Podaj rozwiązanie bez tablic pomocniczych. Uwzględnij moduł,
umożliwiający edycję wskazanych pytań.
*/

void zapisywanie(string imie, int punkty, int &bledne)
{
    fstream plik;
    plik.open("spis.txt", ios::in|ios::out|ios::app);
    if(!plik.good())
    {
        cout << "Nie otwarto pliku";
        system("pause");
    }
    else
    {
    cout<<endl<<"Gratulacje, ukonczono test! Uzyskano "<<punkty<<" punktow."<<endl<<"Pomylono sie "<<bledne<<" razy!"<<endl;
    plik<<imie<<"\t"<<"Uzyskano: "<<punkty<<" punktow"<<"\t"<<"Zlych odpowiedzi: "<<bledne<<endl;
    plik.close();
    }
}

void edytowanie() {
    int nr;
    cout<<"Podaj nr pytania do edycji: ";
    cin>>nr;
    cin.ignore(1000,'\n');
    while(nr<1 && nr>100) {
        cout<<"Podano niepoprawny numer. Podaj poprawny nr: ";
        cin>>nr;
        cin.ignore(1000,'\n');
    }
    string pyt, odpA, odpB, odpC, odpD, popr;
    cout<<"Podaj tresc pytania: ";getline(cin,pyt);
    cout<<"Podaj odpowiedz A: ";getline(cin,odpA);
    cout<<"Podaj odpowiedz B: ";getline(cin,odpB);
    cout<<"Podaj odpowiedz C: ";getline(cin,odpC);
    cout<<"Podaj odpowiedz D: ";getline(cin,odpD);
    cout<<"Podaj litere oznaczajaca poprawna odpowiedz (mala litera): ";cin>>popr;
    while(popr!="a" && popr!="b" && popr!="c" && popr!="d") {
        cout<<"Podaj litere oznaczajaca poprawna odpowiedz (mala litera): ";cin>>popr;
    }
    fstream plikStary;
    system("ren pytania.txt stary.txt"); //zmiana nazwy pliku z pytaniami na "stary.txt"
    plikStary.open("stary.txt", ios::in);
    if(!plikStary.good())
    {
        cout << "Nie otwarto pliku"<<endl;
        system("pause");
    }
    fstream plikNowy;
    plikNowy.open("pytania.txt", ios::out);
    for(int i=1;i<=100;i++) {
        if(i==nr) {
            //nadpisanie
            for(int i=0;i<6;i++) { //pobieram 6 razy linie, zeby przeskoczyc cale pytanie
                string temp;
                getline(plikStary,temp);
            }
            plikNowy<<i<<". "<<pyt<<endl;
            plikNowy<<odpA<<endl;
            plikNowy<<odpB<<endl;
            plikNowy<<odpC<<endl;
            plikNowy<<odpD<<endl;
            plikNowy<<popr<<endl;
        }
        else {
            //przepisanie
            for(int j=0;j<6;j++) {
                string temp;
                getline(plikStary,temp);
                plikNowy<<temp<<endl;
            }
        }
    }
    plikStary.close();
    plikNowy.close();
    system("del stary.txt");
    system("pause");
}


void losowanie(string &pop_odpowiedz, string &pytanie, int &l)
{
    int nr_pytania=0, k=0;
    char abcd = 'a';
    string linja, linja1;

    fstream plik; // otwieranie głównego pliku z pytaniami
    plik.open("pytania.txt", ios::in|ios::out|ios::app);
    if(!plik.good())
    {
        cout << "Nie otwarto pliku"<<endl;
        system("pause");
    }
    else {
        fstream plik2; //otwieranie pliku gdzie beda przechowywane wylosowane pytania
        plik2.open("wylosowany.txt", ios::app|ios::in|ios::out);
        if(!plik2.good())
        {
            cout << "Nie otwarto pliku nr 2";
            system("pause");
        }
        else{
            do {
                nr_pytania=(rand()%100)*6+1;
                plik2.seekg(0);
                while (!plik2.eof())
                {
                    getline(plik2, linja1);
                    if (atoi(linja1.c_str())==nr_pytania)
                    {
                        //cout<<"-----------------Powtorzylo sie "<<nr_pytania<<endl;;
                        k=0;
                        break;
                    }
                    else
                    {
                      //cout<<"Bez powtorzenia "<<nr_pytania<<endl;
                      k=1;
                    }
                }
            }
            while(k==0);
            plik2.close();
        }


        plik2.open("wylosowany.txt", ios::app|ios::in|ios::out);
        if(!plik2.good())
        {
            cout << "Nie otwarto pliku nr 2";
            system("pause");
        }
        else{
            plik2<<nr_pytania<<endl;


            for (int i=0; i<nr_pytania+5; i++) // petla w której pobieram odpowiednie pytanie i i przypisuje pod zmienna
            {
                    getline(plik, linja);
                    if (i==nr_pytania-1)
                    {
                        cout<<endl<<l<<". "<<linja<<endl;
                    }
                    if (i>nr_pytania-1 && i<nr_pytania+4)
                    {
                        cout<<abcd<<") "<<linja<<endl;
                        abcd++;
                    }
                    if (i==nr_pytania+4)
                    {
                       // cout<<linja<<endl;
                        pop_odpowiedz=linja;
                    }
                }
            plik.close();
            plik2.close();
        }
    }
}


void odpowiadanie (string &pop_odpowiedz, int &punkty, int &bledne)
{
    int k=1;
    do {
        string odp_uzytkownika="";
        cout<<endl<<"Podaj swoja odpowidz: ";
        cin.sync();
        getline(cin, odp_uzytkownika);


        if(odp_uzytkownika=="a" || odp_uzytkownika=="b" || odp_uzytkownika=="c" || odp_uzytkownika=="d")
        {
            //if(strcmp(pop_odpowiedz.c_str(), odp_uzytkownika.c_str()) == 0)
            if (pop_odpowiedz==odp_uzytkownika)
            {
                cout<<endl<<"Odpowiedz poprawna! Otrzymales punkt!"<<endl;
                punkty++;
                k=1;
            }
            else
            {
                cout<<endl<<"Twoja odpowiedz jest bledna. Poprawna to: "<<pop_odpowiedz<<endl<<"Brak punktow."<<endl;
                bledne++;
                k=1;
            }
        }
        else
        {
            cout<<endl<<"Wprowadziles zly znak. Wybierz a, b, c lub d. Pamietaj o malych literach!"<<endl;
            k=0;
        }
    }
    while(k==0);
}




int main()
{
    srand(time(NULL));
    char znak;
    char tryb;
    int punkty=0, numerek=1, bledne=0;
    string  imie, pop_odpowiedz, pytanie;
    cout<<"--------------------------Test z fizyki!--------------------------"<<endl;

    cout<<"Tryb pracy programu"<<endl<<"u - Tryb ucznia"<<endl<<"n - Tryb nauczyciela"<<endl;
    cin.sync();
    cin.get(tryb);

    switch(tryb)
    {
        case 'u':
            do{
                cout<<"Dostepne opjce w programie"<<endl<<"1 - Wziecie udzialu w tescie"<<endl<<"2 - Wyjscie z programu"<<endl;
                cin.sync();
                cin.get(znak);

                switch(znak)
                {
                    case '1':
                        cout<<"Podaj swoje imie i nazwisko: ";
                        cin.sync();
                        getline(cin, imie);
                        for(int l=1; l<=20; l++)
                        {
                        losowanie(pop_odpowiedz, pytanie, l);
                        odpowiadanie(pop_odpowiedz, punkty, bledne);
                        }
                        zapisywanie(imie, punkty, bledne);
                        remove("wylosowany.txt");
                        break;

                    case '2':
                        cout<<"Dziekuje za spedzony czas. Pozdrawiam."<<endl;
                        break;

                    default:
                        break;
                }
            }while(znak!='1' && znak!='2');
            return 0;
        case 'n':
        do{
            cout<<"Dostepne opjce w programie"<<endl<<"1 - Wziecie udzialu w tescie"<<endl<<"2 - Edycja pytan"<<endl<<"3 - Wyjscie z programu"<<endl;
            cin.sync();
            cin.get(znak);

            switch(znak)
            {
                case '1':
                    cout<<"Podaj swoje imie i nazwisko: ";
                    cin.sync();
                    getline(cin, imie);
                    for(int l=1; l<=20; l++)
                    {
                    losowanie(pop_odpowiedz, pytanie, l);
                    odpowiadanie(pop_odpowiedz, punkty, bledne);
                    }
                    zapisywanie(imie, punkty, bledne);
                    remove("wylosowany.txt");
                    break;

                case '2':
                    edytowanie();
                    break;

                case '3':
                    cout<<"Dziekuje za spedzony czas. Pozdrawiam."<<endl;
                    break;

                default:
                    break;
            }
        }while(znak!='1' && znak!='2' && znak!='3');
    }while(tryb!='n' && tryb!='u');
    return 0;
}
