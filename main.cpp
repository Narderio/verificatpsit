#include <iostream>
#include <fstream>
#define DIM 20


using namespace std;
const string DATABASE= "dati.dat";//dichiarazione del file binario
int n=0;//numero di utenti immessi

struct Datiutenti
{
    char nome[20];
    char cognome[20];
    char password[20];
    int identificatore;
}dati[DIM],lettur;




void input()
{int a;
    cout<<"Si prega di inserire tutti gli utenti in un'unica volta(massimo "<<DIM<<")\n\n";//
    fstream miofile;
    miofile.open(DATABASE, ios::app | ios::binary);
        do{
        fflush(stdin);
        cout<<"\nInserisci il codice identificativo dell'utente:";
        cin>> dati[n].identificatore;
        fflush(stdin);
        cout << "Inserisci nome utente:";
       cin.getline(dati[n].nome,20);
       cout << "Inserisci cognome utente:";
       cin.getline(dati[n].cognome,20);
       fflush(stdin);
       cout << "Inserisci password associata all'utente:";
       cin.getline(dati[n].password,20);
       n++;

   if(n!=DIM)
    {
        cout<<"\nPremere 1 per inserire un nuovo utente, altrimenti 0: ";
        cin>>a;
    }
    else
        a=0;

    }while(a==1);

    if(!miofile)

       cout<<"Errore apertura file!"<<endl;//errore

    else
    {
        for(int c=0;c<n;c++)
            miofile.write((char*)&dati,sizeof(dati));
    }

miofile.close();

}





void lettura()
{

    fstream miofile;
    miofile.open(DATABASE, ios::in  | ios::binary);
    if(!miofile)
        cout<<"Errore nell'apertura del file"<<endl;
    else
    {
     cout<<"\t\t\tSTAMPA DI TUTTI GLI UTENTI"<<endl;
        for(int c=0;miofile.read((char*)&dati[c],sizeof(dati[c]));c++)
        {
            if(dati[c].nome[0]=='\0')
                break;

            cout<<"Nome:"<<dati[c].nome<<endl<<"Cognome: "<<dati[c].cognome<<endl
            <<"Password: "<<dati[c].password<<endl<<"Identificatore: "<<dati[c].identificatore<<endl<<endl<<endl;

        }

    }
    miofile.close();
    fflush(stdin);
}

void ricerca()
{
    int cod;long cont;int scelta;
    Datiutenti rice;
    fstream miofile;
    miofile.open(DATABASE,ios::in | ios::out | ios::binary);
    if(!miofile)
        cout<<"Errore nell'apertura del file"<<endl;

    else{
        bool trovato=false;
        cout<<"Inserisci il codice da cercare:";
        cin>>cod;
        for(int j=0;j<n;j++)
            if(cod==dati[j].identificatore)
                trovato=true;
    if(trovato==true)
    {
        cont=(cod-1)*(sizeof(rice));
        miofile.seekg(cont);
        miofile.read((char*)&rice,sizeof(rice));

        if(rice.nome[0]!='\0')
        cout<<"\nNome:"<<rice.nome<<endl<<"Cognome:"<<rice.cognome<<endl<<"Password:"
        <<rice.password<<endl<<"Identificatore:"<<rice.identificatore<<endl<<endl;

        cout<<"\n\n Vuoi modificare l'utente?(0=no/1=si)"<<endl;
        cin>>scelta;
        if(scelta==1)
            {
                cout<<"1.Nome \n2.Cognome \n3.Password"<<endl;
                cin>>scelta;
                switch(scelta)
                {
                    case 1: cout<<"Inserisci il nome modificato:";
                            fflush(stdin);
                            cin.getline(rice.nome,20);
                                break;

                    case 2:cout<<"Inserisci il cognome modificato:";
                            fflush(stdin);
                            cin.getline(rice.cognome,20);
                                break;

                    case 3:cout<<"Inserisci la password modificata:";
                            fflush(stdin);
                            cin.getline(rice.password,20);
                                break;

                }
                 miofile.seekp(cont);
            miofile.write((char*)&rice, sizeof(rice));

            }

        else{
                cout<<"Vuoi eliminare l'utente?(0=no/1=si)\n";
                cin>>scelta;
                if(scelta==1)
            {
                    miofile.clear();

                    for(int i=0;i<(n-1);i++)
                    {
                        miofile.read((char*)&rice,sizeof(rice));

                        if(cod==rice.identificatore)
                        {
                            miofile.read((char*)&rice,sizeof(rice));
                        }
                        dati[i]=rice;
                    }
                    n--;
                miofile.close();

                fstream miofile;
                miofile.open(DATABASE.c_str(),ios::out | ios::binary);

                for(int c=0;c<n;c++)
                        miofile.write((char*)&dati[c],sizeof(dati[c]));


                cout<<"\nUtente eliminato dal database"<<endl;
                miofile.close();
            }}
    }else
         cout<<"Codice non trovato\n"<<endl;

    }
}



int main()
{int scelta;

    do{
    cout<<"\t\t\t GESTIONE FILE DI RECORD";
    cout<<"\n\t\t\t MENU PRINCIPALE\n";
    cout << "1.Inserisci utenti" << endl;
    cout << "2.Ricerca utente"<<endl;
    cout << "3.Visualizza elenco utenti" << endl;
    cout << "4.Esci" << endl;
    cin>>scelta;
    switch(scelta)
    {
        case 1:input();
                    break;

        case 2:ricerca();
                    break;

        case 3:lettura();
                break;

        case 4: cout << "Grazie di aver utilizzato questo programma!" << endl;
                    break;
    }

    }while(scelta!=4);
    return 0;
}

