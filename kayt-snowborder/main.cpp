#include <iostream>
#include<fstream>
#include<ctime>
#include <math.h>
#include <iomanip>
#include <algorithm>
/*!
@author alessiaer
@file main.cpp
@brief programma in c++ che permette di monitorare una gara di kayt-snowborder
 */
using namespace std;

/*!
 @struct coordinate
 @brief struttura che serve per dichiarare le variabili opportune per la rilevazione delle coordinate
 */
struct coordinate
 {
/*! @var x
    @brief variabile x delle coordinate
    @var y
    @brief variabile y delle coordinate */
     int x, y;
 };

 /*!
 @struct atleta
 @brief struttura che serve per dichiarare le variabili contenute nella struttura atleta
 */
struct atleta
{
 /*! @var mat
     @brief matrice identificativa dell'atleta */
    int mat;

/*! @var cog
    @brief cognome dell'atlteta */
    string cog[100]= {"Rossi","Russo","Ferrari","Esposito","Bianchi","Romano","Colombo","Bruno","Ricci","Marino","Costa","Franco","Gallo","Conti","Greco","Martino","Giordano","Rizzo","Mancini","Villa","Mauro","Lombardi","Fontana","Roberto","Barbieri","Moretti","Bianco","Martini","Fratelli","Mariani","Rinaldi","Amato","Galli","Ferrara","Caruso","Leone","Mario","Santoro","Longo","Conte","Sala","Martinelli","Serra","D'Angelo","Dalla"	,"Marchetti","Marini","Salvatore","Fabbri","Fiore","Ferri","Gentile","Gatti","Palma","Monti","Soc","Vitale","Lombardo","De Luca","Bernardi","Pellegrini","Messina","Benedetti","Massimo","Coppola","Morelli","Grassi","Testa","Marchi","Parisi","Ferraro","Michele","Santis","Rocca","Valentini","Riva","Agostino","Angelis","Palumbo","Pasquale","Giorgi","Farina","Silvestri","Sanna","Rizzi","Cattaneo","Poli","Mazza","Paola","Lombardi","Pellegrino","Piazza","Leo","Orlando","Carbone","Re","Moro","Neri","Giuliani","Guerra"};

/*! @var cor
    @brief cordinate dei punti rilevati in 30 min degli atleti */
    coordinate cor[30];
    int dis;
};

/*!
 @fn scrivi
 @brief visualizza sullo schermo e scrive il file le informazioni degli atleti
 @param[in] n numero degli atleti
 @param[in] persona vettore di atleta

*/
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

/*!
 @fn genera
 @brief generazione casuale della matrice, delle coordinate e scelta casuale dei cognomi da assegnare ai vari atleti
 @param[in] n numero degli atleti
 @param[in] persona vettore di atleta
*/
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

/*!
 @fn calcolo_distanza
 @brief calcola la distanza tra i vari punti di ogni atleta e li somma tra di loro, ottenendo la distanza totale percorsa da ogni persona.
 @param[in] n numero degli atleti
 @param[in] persona vettore di atleta
*/
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

/*!
 @fn ordinamento
 @brief confronta le distanze di ogni atleta e ordina gli atleti in modo decrescente partendo da colui che ha percorso la distanza maggiore
 @param[in] n numero degli atleti
 @param[in] persona vettore di atleta
*/
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

/*!
 @fn stampa_dis
 @brief richiama la funzione di ordinamento , visualizza sullo schermo la classifica degli atleti e le inserisce nel file
 @param[in] n numero degli atleti
 @param[in] persona vettore di atleta
*/
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

/*!
 @fn vincitore
 @brief  visualizza sullo schermo e nel file di testo il vincitore della gara
 @param[in] n numero degli atleti
 @param[in] persona vettore di atleta
*/
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

/*!
 @fn grafica
 @brief  scelta dell' utente su quale atleta voler monitorare e stampa a video dei punti sul piano cartesiano che sono stati registrati dalla commmissione
 @param[in] n numero degli atleti
 @param[in] persona vettore di atleta
*/
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


int a=1;
     for(int c=0; c<n; c++)
    {
      if(app==persona[c].mat)
      {

       for( i=0; i<30; i++)
         {
             m[persona[c].cor[i].x][persona[c].cor[i].y]=a;
             a++;
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

/*!
 @fn main
 @brief  permette all'utente di eseguire il programma

*/

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
