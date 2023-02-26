#include <iostream>
#include<fstream>
#include<ctime>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;

struct coordinate
 {
     int x, y;
 };
struct atleta
{
    int mat;
    string cog[100]= {"Rossi","Russo","Ferrari","Esposito","Bianchi","Romano","Colombo","Bruno","Ricci","Marino","Costa","Franco","Gallo","Conti","Greco","Martino","Giordano","Rizzo","Mancini","Villa","Mauro","Lombardi","Fontana","Roberto","Barbieri","Moretti","Bianco","Martini","Fratelli","Mariani","Rinaldi","Amato","Galli","Ferrara","Caruso","Leone","Mario","Santoro","Longo","Conte","Sala","Martinelli","Serra","D'Angelo","Dalla"	,"Marchetti","Marini","Salvatore","Fabbri","Fiore","Ferri","Gentile","Gatti","Palma","Monti","Soc","Vitale","Lombardo","De Luca","Bernardi","Pellegrini","Messina","Benedetti","Massimo","Coppola","Morelli","Grassi","Testa","Marchi","Parisi","Ferraro","Michele","Santis","Rocca","Valentini","Riva","Agostino","Angelis","Palumbo","Pasquale","Giorgi","Farina","Silvestri","Sanna","Rizzi","Cattaneo","Poli","Mazza","Paola","Lombardi","Pellegrino","Piazza","Leo","Orlando","Carbone","Re","Moro","Neri","Giuliani","Guerra"};
    coordinate cor[30];
    int dis;
};

void scrivi(int n, atleta persona[])
{
   ofstream fout("kayt.txt");
   fout<<"";
   for(int h=0; h<n;h++)
   {
       fout<<"* " <<persona[h].mat<<" - "<< persona[h].cog[h]<<endl;
       cout<<"* " <<persona[h].mat<<" - "<< persona[h].cog[h]<<endl;
       for(int i=0; i<10; i++)
        {
            fout<<'\t'<<"("<<persona[h].cor[i].x<<" ; "<<persona[h].cor[i].y<<")"<<endl;
             cout<<'\t'<<"("<<persona[h].cor[i].x<<" ; "<<persona[h].cor[i].y<<")"<<endl;
        }
        cout<<endl;
   }
   fout.close();
}

void visualizza()
{
    ifstream fin ("kayt.txt");
    string app;
    while(!fin.eof())
    {
        getline(fin,app);
        cout<<"\t"<<app<<endl;
    }
    fin.close();
}

void genere(int n, atleta persona[])
{
    srand(time(NULL));

    for(int c=0; c<n; c++)
    {
        int j=rand()%100;
        std::swap(persona[c].cog[c], persona[c].cog[j]);
        ripeti:
        persona[c].mat=rand()%500;
        for(int j=c-1; j>=0; j--)
        {
           if( persona[c].mat== persona[j].mat)
                goto ripeti;
        }

        for(int i=0; i<30; i++)
        {
            persona[c].cor[i].x=rand()%100;
            persona[c].cor[i].y=rand()%100;
        }
    }
}

void calcolo_distanza(int n, atleta persona[])
{
    int d, k;
    for(int c=0; c<n; c++)
    {
      d=0;
      persona[c].dis=0;
      for(int i=0; i<29; i++)
      {
            k = i+1;
            d= sqrt(pow(persona[c].cor[i].x-persona[c].cor[k].x, 2)+ pow(persona[c].cor[i].y-persona[c].cor[k].y, 2) );
            persona[c].dis+=+d;
            //cout<<d<<endl;

      }
    }
}

void ordinamento(int n, atleta persona[])
{

     for(int c=0; c<n-1; c++)
     {
         for(int t=c+1; t<n; t++)
         {
             if(persona[c].dis < persona[t].dis)
                 std::swap(persona[c], persona[t]);
         }
     }
}

void stampa_dis(int n, atleta persona[])
{
    calcolo_distanza(n,  persona);
    ordinamento(n,persona);
    ofstream fout("kayt.txt", ios::app);
    fout<<"__________________________________________________________________________"<<endl;
     for(int c=0; c<n; c++)
     {
          cout<<c+1<<") "<<persona[c].mat<<" - "<< persona[c].cog[c]<<" - "<< persona[c].dis<<endl;
          fout<<c+1<<") "<<persona[c].mat<<" - "<< persona[c].cog[c]<<" - "<< persona[c].dis<<endl;
     }
     fout.close();

}


void vincitore(int n, atleta persona[])
{
   ofstream fout("kayt.txt", ios::app);
   calcolo_distanza(n,  persona);
   ordinamento(n,persona);

     cout<<endl<<"il vincitore della gera e' l'atleta con n. matricola = "<<persona[0].mat<<" ed ha compiuto "<<persona[0].dis<<" m"<<endl;
     fout<<"__________________________________________________________________________"<<endl;
     fout<<endl<<endl<<"il vincitore della gera e' l'atleta con n. matricola = "<<persona[0].mat<<" ed ha compiuto "<<persona[0].dis<<" m"<<endl;

   fout.close();
}

void grafica(int n, atleta persona[])
{
    char m[100][100];

    for(int i=0; i<100; i++)
    {
        for(int j=0; j<100; j++)
        {
            m[i][j]=' ';

        }
    }

    for(int i=0; i<100; i++)
    {
        for(int j=0; j<100; j++)
        {
            m[i][0]='|';
            m[0][j]='_';
        }
    }
    int app, i;
    cout<<"scegli il numero di matricola di cui vuoi visualizzare il percorso grafico: ";
    cin>>app;



     for(int c=0; c<n; c++)
    {
      if(app==persona[c].mat)
      {

       for( i=0; i<30; i++)
         {
             m[persona[c].cor[i].x][persona[c].cor[i].y]='*';
         }
       }
    }

    for(int i=0; i<100; i++)
    {
        for(int j=0; j<100; j++)
        {
            cout<<m[i][j];

        } cout<<endl;
    }

}


int main()
{
    atleta persona[500];
    //coordinate cor;
    int s, n;
    string decisione;
    cout<<"-Salve, hai la possibilita' di avviare una gara tra Kayt-Snowborder. Desideri continuare (si/no): ";
    cin>>decisione;

   if(decisione=="si")
   {
       cout<<"quanti partecipanti vuoi in gara?";
       cin>>n;
       genere(n,persona);
       do{
         cout<<"1- visualizzare elenco degli atleti "<<endl;
         cout<<"2- visualizzare la classifica degli atleti"<<endl;
         cout<<"3- visualizzare il vincitore della competizione"<<endl;
         cout<<"4- scegliere un'atleta e visualizzare il suo percorso"<<endl;
         cout<<"5- uscita"<<endl;

         cin>>s;

         switch(s)
         {
          case 1:

                    scrivi(n,persona);
                    break;

          case 2:
                  stampa_dis( n,  persona);
                    break;

          case 3: vincitore(n,persona);
                  break;
          case 4:grafica (n,persona);

                  break;
          case 5: break;

          }
        }while(s!= 5);
     }


    else if(decisione=="no")
    cout<<"Mi dispiace, hai perszo la tua occasione... CIAOOO";

    else cout<<"opss... inserimento sbagliato";



return 0;
}
