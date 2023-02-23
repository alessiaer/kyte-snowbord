#include <iostream>
#include<fstream>
#include<ctime>

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
};

void gen_coordinate()
{
   srand(time(NULL));

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
        cout<<"* " <<persona[c].mat<<" - "<< persona[c].cog[c]<<endl;
        for(int i=0; i<10; i++)
        {
            persona[c].cor[i].x=rand()%100;
            persona[c].cor[i].y=rand()%100;

            cout<<'\t'<<"("<<persona[c].cor[i].x<<" ; "<<persona[c].cor[i].y<<")"<<endl;
        }
        cout<<endl;

    }
}
void scrivi(int n, atleta persona[])
{
   ofstream fout("kayt.txt");
   fout<<"";
   for(int h=0; h<n;h++)
   {
       fout<<"* " <<persona[h].mat<<" - "<< persona[h].cog[h]<<endl;
       for(int i=0; i<10; i++)
        {
            fout<<'\t'<<"("<<persona[h].cor[i].x<<" ; "<<persona[h].cor[i].y<<")"<<endl;
        }
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

int main()
{
    atleta persona[500];
    int s, n;
    do{
        cout<<"";
        cin>>s;

        switch(s)
        {
        case 1: cout<<"-quanti partecipanti vuoi in gara?";
                cin>>n;
               genere(n,persona);
               scrivi(n,persona);
               break;
        }
    }while(s!= 3);

return 0;
}
