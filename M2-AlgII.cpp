#include <iostream>
#include <cstdlib>
#define TMAX 7
#include <string>
using namespace std;
// Ordenacao ainda nao funciona corretamente e existem alguns bugs que serao atualizados futuramente 
typedef struct{
    string local , assunto , tipo;
    int horaI , minutoI , horaF, minutoF;
}Compromissos;

typedef struct{
    int dia , mes ;
    Compromissos compromisso[6];
    //string dSemana;
}Agenda;

int validaNum();
int validaHora();
int validaMin();
int validaHorarios(int horaI , int horaF);

void inicioSemana(Agenda semana[] ,int numDias[] );
void inclusaoCompromisso(Agenda semana[],Compromissos compromisso[] ,int tam , int &tamComp ,int vetTamComp[]);
void ordenaData(Agenda semana[] , int tam);

bool procuraData(Agenda semana[] , int tam , int diaP);

bool procuraHora(Agenda semana[] ,Compromissos compromisso[] , int tam , int horaP);
bool procuraHora2(Agenda semana[] ,Compromissos compromisso[], int tam , int horaP , int minutoP,int achouD);
bool procuraMinuto(Agenda semana[] ,Compromissos compromisso[] , int tam , int minutoP);

int procuraPosDia(Agenda semana[] , int tam , int diaP);
int procuraPosComp(Compromissos compromisso[] , int tamComp);
int procuraPosHora(Agenda semana[] ,Compromissos compromisso[] , int achouD, int horaP, int vetTamComp[],int ind);

void relatorio1(Agenda semana[] , Compromissos compromisso[] ,int tam , int tamComp,int vetTamComp[],string diaSemana[]);
void relatorio2(Agenda semana[] , Compromissos compromisso[] ,int tam , int tamComp, int vetTamComp[],string diaSemana[]);
void excluiCompromisso(Agenda semana[] ,Compromissos compromisso[] ,int &tam , int &tamComp , int vetTamComp[]);
void ordenacaoRec(Agenda semana[], Compromissos compromisso[],int vetTamComp[],int incDia ,int incComp,int tam,int cont);

char outraOp();

int main()
{
    Agenda semana[7];
    Compromissos compromisso[6];
    string diaSemana[7] ={"Dom","Seg","Ter","Qua","Qui","Sex","Sab"};
    int numDias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // para verificar dara
    int vetTamComp[7] = {0,0,0,0,0,0,0};
    int op , tam = 7 , tamComp = 0;
    char resp , resp2;
    //int incDia = 0 , incComp = 0 , cont = 0;



do{
     cout<<"=========AGENDA SEMANAL========\n";
     cout<<"1-Inicializar uma nova semana\n";
     cout<<"2-Incluir Compromissos\n";
     cout<<"3-Relatorio Geral\n";
     cout<<"4-Exclusao de Compromisso\n";
     cout<<"5-Relatorio do dia\n";
     cout<<"6-Sair\n";
     cin>>op;

    switch(op){
    case 1:
        cin.ignore();
        cout<<"Deseja iniciar uma nova semana ? :";
        resp = outraOp();
        if(resp == 'S'){
            inicioSemana(semana ,numDias);
        }
        break;
    case 2:
        cin.ignore();
        cout<<"Informe data para inclusao : ";
        inclusaoCompromisso(semana,compromisso,tam,tamComp,vetTamComp);
        //ordenacaoRec(semana,compromisso,vetTamComp,incDia,incComp,tam,cont);
        break;
    case 3:
        cin.ignore();
        cout<<"RELATORIO GERAL"<<endl;
        relatorio2(semana,compromisso,tam,tamComp,vetTamComp,diaSemana);
        break;
    case 4:
        cin.ignore();
        cout<<"Exclusao de Compromisso";
        excluiCompromisso(semana,compromisso,tam,tamComp,vetTamComp);
        break;
    case 5:
        cin.ignore();
        cout<<"Agenda do dia"<<endl;
        relatorio1(semana,compromisso,tam,tamComp,vetTamComp,diaSemana);
        break;
    case 6:
        exit(1);
}

    cin.ignore();
    cout<<"\nDeseja outra acao ? : ";
    resp2 = outraOp();
    system("cls");
}while(resp2 == 'S');
    return 0;
}

void inicioSemana(Agenda semana[], int numDias[]){ //numDias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int aux , auxMes , proxDia = 1 , proxMes , dia = 0;
    do{
        do{
        cout<<"Informe o MES : ";
        auxMes = validaNum();// 28
        }while(auxMes > 12);
        cout<<"Informe o DIA inicial da semana : ";
        aux = validaNum(); //10
    }while(aux > numDias[auxMes-1]);
    proxMes = auxMes + 1;
    for(int i=0; i<7 ;i++){
        dia = aux;// entrou dia 28

        if(dia + i <= numDias[auxMes-1]){
            semana[i].dia = aux + i;
            semana[i].mes = auxMes;
        }else{
            semana[i].dia = proxDia ++;
            semana[i].mes = proxMes;
    }

}
    cout<<"A agenda foi inicializada no dia : "<<semana[0].dia<<"/"<<semana[0].mes;//<<"/"<<semana[tam].mes<<"/"<<semana[tam].ano;
}

void inclusaoCompromisso(Agenda semana[],Compromissos compromisso[] ,int tam , int &tamComp ,int vetTamComp[]){
    int diaP,horaP,achouD , ind , auxHoraF , minutoP , auxMinutoF;
    bool achouH , achouM;

    diaP = validaNum();
    achouD = procuraPosDia(semana,tam,diaP); //me retorna o indice do vetor grandao
    if(achouD == -1)
        cout<<"Dia nao encontrado";
    else{
        ind = vetTamComp[achouD]; // aqui eu quero o tam do vetor pequeno de compromissos , vou no indice 2 do meu vetor ver o tam do vet compromissos
        cout<<"INDICE RETORANDO PELO DIA : "<<achouD<<endl;
        cout<<"Hora Inicial:";
        horaP = validaHora();
        //achouDia = procuraPos(semana,tam,diaP);
        cout<<"Minuto  : ";
        minutoP = validaMin();
        achouH = procuraHora2(semana,compromisso,tam,horaP,minutoP,achouD);
        //achouM = procuraMinuto(semana,compromisso,tam,minutoP);
            if(!achouH){ //ACHOU dia mas NAO ACHOU horario , logo horario disp pode gravar
               semana[achouD].compromisso[ind].horaI = horaP;
               semana[achouD].compromisso[ind].minutoI = minutoP;
               cin.ignore();
               cout<<"Horario Final: ";
               auxHoraF = validaHora();
               semana[achouD].compromisso[ind].horaF = auxHoraF;
               cout<<"Minuto Final : ";
               auxMinutoF = validaMin();
               semana[achouD].compromisso[ind].minutoF = auxMinutoF;
               cin.ignore();
               cout<<"Tipo de evento(reuniao,atividade,aniversario) : ";
               getline(cin,semana[achouD].compromisso[ind].tipo);
               cout<<"Local : ";
               getline(cin,semana[achouD].compromisso[ind].local);
               cout<<"Assunto : ";
               getline(cin,semana[achouD].compromisso[ind].assunto);
               vetTamComp[achouD] += 1;
        }else // achou dia e achou horario , logo tem coisa
            cout<<"Horario nao disp";

    }
}

bool procuraData(Agenda semana[] , int tam , int diaP){ // tirei do exercicio 8 lista REC
    if(tam == 1){
        if(semana[0].dia == diaP)
            return true;
        return false;
    }else{
        if(semana[tam-1].dia == diaP)
            return true;                             // se n achou vai ser != 0 logo da pra continuar
        else
            return procuraData(semana,tam-1,diaP);  // retorna 0 se existe
    }
}

int procuraPosDia(Agenda semana[] , int tam , int diaP){ // tirei do exercicio 8 lista REC
    if(tam == 1){
        if(semana[0].dia == diaP)
            return 0;
        return -1; // -1 se n encontrar
    }else{
        if(semana[tam-1].dia == diaP)
            return tam-1;                               // se n achou vai ser != 0 logo da pra continuar
        else
            return procuraPosDia(semana,tam-1,diaP);  // retorna 0 se existe
    }
}

bool procuraHora(Agenda semana[] ,Compromissos compromisso[] , int tam , int horaP){ // tirei do exercicio 8 lista REC
    if(tam == 1){
        if(compromisso[0].horaI == horaP)
            return true;
        return false;
    }else{
        if(compromisso[tam-1].horaI == horaP)
            return true;                               // se n achou vai ser != 0 logo da pra continuar
        else
            return procuraHora(semana,compromisso,tam-1,horaP);  // retorna 0 se existe
    }
}

void relatorio2(Agenda semana[] , Compromissos compromisso[] ,int tam , int tamComp, int vetTamComp[],string diaSemana[]){
    int ind , achouD;


    for(int j=0 ;j<7; j++){
        cout<<"=========="<<diaSemana[j]<<"=========="<<endl;
        cout<<"Data : "<<semana[j].dia<<"/"<<semana[j].mes<<"/2022"<<endl;
        ind = vetTamComp[j];
            for(int i=0;i<ind; i++){
                cout<<"=====================================\n";
                cout<<"Hora Inicial : "<<semana[j].compromisso[i].horaI<<":"<<semana[j].compromisso[i].minutoI<<endl;
                cout<<"Hora Final : "<<semana[j].compromisso[i].horaF<<":"<<semana[j].compromisso[i].minutoF<<endl;
                cout<<"Tipo de atividade : "<<semana[j].compromisso[i].tipo<<endl;
                cout<<"Local : "<<semana[j].compromisso[i].local<<endl;
                cout<<"Assunto : "<<semana[j].compromisso[i].assunto<<endl;
                cout<<"=====================================\n";
        }

    }

}

void relatorio1(Agenda semana[] , Compromissos compromisso[] ,int tam , int tamComp , int vetTamComp[],string diaSemana[]){
    int ind;
    int achouD;
    int dia;

    cout<<"Qual dia a ser consultado ? : ";
    cin>>dia;
    achouD = procuraPosDia(semana,tam,dia);

    if(achouD == -1)
       cout<<"ERRO - DIA NAO ENCONTRADO\n";
    else{
        ind = vetTamComp[achouD]; // esse indice aqui recebe o tam de cada vetor compromisso
        cout<<"AGENDA DO DIA "<<dia<<"/"<<semana[achouD].mes<<endl;
        cout<<"=========="<<diaSemana[achouD]<<"=========="<<endl;
        for(int i=0;i<ind;i++){
            cout<<"Hora Inicial : "<<semana[achouD].compromisso[i].horaI<<":"<<semana[achouD].compromisso[i].minutoI<<endl;
            cout<<"Hora Final : "<<semana[achouD].compromisso[i].horaF<<":"<<semana[achouD].compromisso[i].minutoF<<endl;
            cout<<semana[achouD].compromisso[i].tipo<<endl;
            cout<<"Local : "<<semana[achouD].compromisso[i].local<<endl;
            cout<<"Assunto : "<<semana[achouD].compromisso[i].assunto<<endl;
            cout<<"=====================================\n";
        }

    }

}

int procuraPosHora(Agenda semana[] ,Compromissos compromisso[] , int achouD, int horaP, int vetTamComp[],int ind){ // tirei do exercicio 8 lista REC

    if(ind == 1){
        if(semana[achouD].compromisso[0].horaI == horaP)
            return 0;
        return -1;// -1 se n encontrar
    }else{
        if(semana[achouD].compromisso[ind-1].horaI == horaP)
            return ind-1;                               // se n achou vai ser != 0 logo da pra continuar
        else
            return procuraPosHora(semana,compromisso,achouD,horaP,vetTamComp,ind-1);  // retorna 0 se existe


    }
}

void excluiCompromisso(Agenda semana[] ,Compromissos compromisso[] ,int &tam , int &tamComp , int vetTamComp[]){ // Ta excluindo errado
    int dia , hora;
    int achouD , achouH;
    int ind;

    cout<<"Insira o dia do compromisso :"<<endl;
    cin>>dia;
    achouD = procuraPosDia(semana,tam,dia); //retorna o indice no vetor
    if(achouD == -1)
        cout<<"Dia nao encontrado";
    else {
        cout<<"Qual o horario do compromisso a ser excluido ? : ";
        cin>>hora;
        ind = vetTamComp[achouD];
        achouH=procuraPosHora(semana,compromisso,achouD,hora,vetTamComp,ind);// tam do vetor compromisso
        cout<<"Indice vetor compromissos procurando por hora : "<< achouH;
        if(achouH != -1){
            for(int i=achouH;i<ind;i++){
                semana[achouD].compromisso[i].horaI = semana[achouD].compromisso[i+1].horaI;
                semana[achouD].compromisso[i].horaF = semana[achouD].compromisso[i+1].horaF;
                semana[achouD].compromisso[i].tipo = semana[achouD].compromisso[i+1].tipo;
                semana[achouD].compromisso[i].local = semana[achouD].compromisso[i+1].local;
                semana[achouD].compromisso[i].assunto = semana[achouD].compromisso[i+1].assunto;
            }
            vetTamComp[achouD] = vetTamComp[achouD] - 1 ;
        }
    }
}

void ordenacaoRec(Agenda semana[], Compromissos compromisso[],int vetTamComp[],int incDia,int incComp,int tam,int cont){
    // MANDA O VETOR GRANDAO , O VETOR PEQUENO , OS TAMANHOS DOS VETORES PEQUENOS , 0 , E O DIR TRATA O TAM MAX
    // PARA ORDENAR EU PRECISO DO TAMANHO , DO VETOR DE TAMANHO , E COMPARAR OS ELEMENTOS
   int diaP , horaP , ind;
   int achouD , achouH ;

   diaP = semana[incDia].dia;
   achouD = procuraPosDia(semana,tam,diaP);// isso me da o indice do vetor grande

   ind = vetTamComp[achouD]; // me retorna o tam de cada vetor de compromissos vet = {0,0,0,0,0,0}

   horaP = semana[incDia].compromisso[incComp].horaI; // pega NO DIA 0  a HORA 0 no dia 10 a hr 11
   achouH = procuraPosHora(semana,compromisso,achouD,horaP,vetTamComp,ind);// isso me da o indice do vetor compormisss , vetor pequeno
   cout<<"indice  achouD : "<<achouD<<endl;
   cout<<"indice  achouH : "<<achouH<<endl;
   cout<<"indice  tam do vetor comp : "<<ind<<endl;

        if(ind <= 1) // se o indice inical for menor q o tamanho do vet compromissos
            ordenacaoRec(semana,compromisso,vetTamComp,incDia + 1 ,0, tam ,0);
        else
            if(semana[achouD].compromisso[achouH].horaI > semana[achouD].compromisso[achouH+1].horaI){
                swap(semana[achouD].compromisso[achouH].horaI ,semana[achouD].compromisso[achouH+1].horaI);
                swap(semana[achouD].compromisso[achouH].horaF ,semana[achouD].compromisso[achouH+1].horaF);
                swap(semana[achouD].compromisso[achouH].tipo ,semana[achouD].compromisso[achouH+1].tipo);
                swap(semana[achouD].compromisso[achouH].local ,semana[achouD].compromisso[achouH+1].local);
                swap(semana[achouD].compromisso[achouH].assunto ,semana[achouD].compromisso[achouH+1].assunto);
            }else
                ordenacaoRec(semana,compromisso,vetTamComp,incDia ,incComp + 1, tam , cont + 1);
}

bool procuraMinuto(Agenda semana[] ,Compromissos compromisso[] , int tam , int minutoP){
if(tam == 1){
        if(compromisso[0].minutoI == minutoP)
            return true;
        return false;
    }else{
        if(compromisso[tam-1].minutoI == minutoP)
            return true;                               // se n achou vai ser != 0 logo da pra continuar
        else
            return procuraHora(semana,compromisso,tam-1,minutoP);  // retorna 0 se existe
    }
}





char outraOp(){
    char c;
    do{
        //cout<< "\nMais alguma acao? S/N" << endl;
        c = toupper(cin.get());
    }while(c != 'S' && c != 'N');
    return c;
}

int validaNum(){
   int num;
   string aux="";
   bool verifica = false;
   do{
      cin>>num;
   }while(num <= 0);


   return num;
}

int validaHora(){
   int num;
   do{
       cin>>num;
   }while(num < 0 or num > 23);

   return num;
}

int validaMin(){
int num;

   do{
       cin>>num;
   }while(num < 0 or num > 59);

   return num;
}

int validaHorarios(int horaI , int horaF ){
    int num;

    if(horaF < horaI){
        do{
            cin>>num;
        }while(num < horaI);
        return num;
    } else
        return num;

}


bool procuraHora2(Agenda semana[] ,Compromissos compromisso[] , int tam , int horaP , int minutoP,int achouD){

    if(tam == 1){
        if((compromisso[achouD].horaI == horaP) and (compromisso[achouD].minutoI == minutoP))
            return true;
        return false;
    }else{
        if(semana[achouD].compromisso[tam-1].horaI == horaP and semana[achouD].compromisso[tam-1].minutoI == minutoP)
            return true;                               // se n achou vai ser != 0 logo da pra continuar
        else
            return procuraHora2(semana,compromisso,tam-1,horaP,minutoP,achouD);  // retorna 0 se existe
    }
}



