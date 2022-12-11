#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;
typedef struct Nodo{
    int     numVoo;
	int  CodDestino;
	struct  Nodo* prox;
}Voos;

typedef struct {
    int  codAero;
	string  nomeCidade,sigla;
	Voos*   prox2;
}Aeroporto;

typedef struct Nodo2 {
    int  codDeOrigem , codDeDestino , maxConexoes;
	struct Nodo2*  prox3;
}Viagem;

int validaNum();
void CadastraAeroporto(int cod , string nome,string sigla,Aeroporto aux ,vector<Aeroporto>& vet,int &tam);
void Print(vector<Aeroporto>& vetor , Aeroporto *ptrAux2);
vector<Aeroporto> removeAeroporto(vector<Aeroporto>& vetor , int cod);
int procuraAeroporto(vector<Aeroporto> vetor , int cod);
int procuraVoo(vector<Aeroporto> vetor , int numVoo);
void CadastraVoo(Voos *ptrAux , vector<Aeroporto>& vetor, Aeroporto *ptrAux2,int codOrigem);
void iniciaLista(Voos*ptrAux);
void iniciaLista2(Aeroporto*ptrAux2);
void mostraVoo(Aeroporto *ptrAux2, vector<Aeroporto> vetor, int cod);
void excluiElemento (Voos **ptrAux, int elemento,vector<Aeroporto> &vetor);
void procuraDestino(vector<Aeroporto> vetor , int codOrigem , int codDestino , int maxConexoes );
void gravaArq(vector<Aeroporto> vetor);
void recuperacao(vector<Aeroporto> &vetor);
void gravaLista(vector<Aeroporto>&vetor , string vet[],int tam);
int validaSigla(vector<Aeroporto> vetor , string sigla);

char outraOp();

int main()
{
    int op ;
    char resp;
    Aeroporto aux;
    aux.prox2 = NULL;
    Voos aux2;
    aux2.prox = NULL;
    Viagem aux3;
    aux3.prox3 = NULL;
    Viagem *ptrViagem = (Viagem *)malloc(sizeof(Viagem));

    vector<Aeroporto> vetor;

    string nome , sigla;
    int cod,numVoo,tam=0;
    int origem ,dest,maxCone;
    Voos *ptrAux = (Voos *)malloc(sizeof(Voos));
    Aeroporto *ptrAux2 = (Aeroporto *)malloc(sizeof(Aeroporto));

        if(!ptrAux or !ptrAux2){
            cout<<("sem memoria")<<endl;
            cin.get();
            exit(1);
        }
    iniciaLista(ptrAux);
    iniciaLista2(ptrAux2);

    ptrAux2->prox2 = NULL;
    ptrAux->prox = NULL;

    do{
        system("cls");
        cout<<("Reorganizaco da malha aerea do pais")<<endl;
        cout<<endl;
        cout<<"1. - Cadastro Aeroporto"<<endl;
        cout<<"2. - Remove Aeroporto"<<endl;
        cout<<"3. - Mostra Aeroportos:"<<endl;
        cout<<"4. - Cadastra Voo"<<endl;
        cout<<"5. - Remove Voo"<<endl;
        cout<<"6. - Mostra Voos"<<endl;
        cout<<"7. - Procura Voo"<<endl;
        cout<<"8. - Gravacao de arquivos"<<endl;
        cout<<"9. - Recuperacao de arquivos"<<endl;
        cout<<"-1. - Sair"<<endl;
        cout<<"Opcao: ";
        cin>>op;
        cout<<endl;
        system("cls");

    switch(op){
        case 1:
            cin.ignore();
            CadastraAeroporto(cod,nome,sigla,aux,vetor,tam);
        break;
        case 2:
            cin.ignore();
            do{
                cout<<"Codigo a ser removido :";
                cin>>cod;
            }while(cod<0);
            vetor=removeAeroporto(vetor,cod);
            break;
        case 3:
            cin.ignore();
            Print(vetor,ptrAux2);
        break;
        case 5:
            cin.ignore();
            do{
            cout<<"Numero do Voo a ser removido :";
            cin>>numVoo;
            }while(numVoo<0);
            excluiElemento(&ptrAux,numVoo,vetor);

        break;
        case 4:
            cin.ignore();
            do{
            cout<<"Digite o cod do aeroporto p/ acessar cadastro de voos :";
            cin>>cod;
            }while(cod<0);

            CadastraVoo(ptrAux,vetor,ptrAux2,cod);

        break;

        case 6:
            cin.ignore();
            int c;
            do{
                cout<<"Digite o cod do AEROPORTO ORIGEM a ser consultado :";
                cin>>cod;
            }while(cod<0);
            mostraVoo(ptrAux2,vetor,cod);
        break;

        case 7:
            cin.ignore();
            cout<<"Insira o Numero do Voo a ser procurado:";
            cin>>numVoo;
            procuraDestino(vetor,origem,dest,maxCone);
        break;

        case 8:
            gravaArq(vetor);
            cout<<"Arquivos gravados com sucesso";
        break;
        case 9:
            recuperacao(vetor);
            cout<<"Arquivos recuperados com sucesso";
        break;
        case -1:
            exit(1);
        break;
    }

    cin.ignore();
    resp = outraOp();
    }while(resp == 'S');
    return 0;
}

void CadastraAeroporto(int cod, string nome ,string sigla ,Aeroporto aux , vector<Aeroporto>& vet,int &tam){
    int achou;
    cout<<"Cadastro de Aeroporto"<<endl;

    cout<<"Codigo do aeroporto : " <<vet.size()<<endl;
    aux.codAero = vet.size();
    tam++;

    cout<<"Insira a Sigla do aeroporto : ";
    do{
        getline(cin,sigla);
    }while(validaSigla(vet,sigla) != -1);
    aux.sigla = sigla;

    cout<<"Insira o Nome do aeroporto : ";
    getline(cin,nome);
    aux.nomeCidade = nome;

    vet.push_back({aux});

    cout<<"Aeroporto Gravado com sucesso";

}
void Print(vector<Aeroporto>& vetor , Aeroporto *ptrAux2) {

    for (unsigned int i = 0; i < vetor.size(); i++) {
        cout <<"CODIGO AEROPORTO :" << vetor[i].codAero << "\nSIGLA AEROPORTO " <<vetor[i].sigla << "\nNOME CIDADE "<<vetor[i].nomeCidade <<"\n"<< endl; // AQUI ATE TA GRAVANDO MAS NAO SEI SE E DESSA FORAM EXATAMENTE
    }
    cout << endl;
}
char outraOp(){
    char c;
    do{
        cout<< "\nMais alguma acao? S/N" << endl;
        c = toupper(cin.get());
    }while(c != 'S' && c != 'N');
    return c;
}
vector<Aeroporto> removeAeroporto(vector<Aeroporto>& vetor , int cod){
    vector<Aeroporto> vet;
    bool achou= false;

    int tamC=1;

     for(unsigned int k=0; k<vetor.size(); k++){
            if(vetor[k].codAero != cod){
                achou=true;
                vet.push_back(vetor[k]);
            }

     }
    if(achou == false){
        cout<<"Aeroporto REMOVIDO com sucesso";
    }else{
        cout<<"Aeroporto NAO EXISTE";
        return vet;
    }

}
void iniciaLista(Voos *ptrAux){
	ptrAux->prox = NULL;
}
void iniciaLista2(Aeroporto *ptrAux2){
	ptrAux2->prox2 = NULL;
}

void CadastraVoo(Voos *ptrAux , vector<Aeroporto>& vetor, Aeroporto *ptrAux2,int codOrigem){
    int cod;
    int numeroVoo;
    int pos = procuraAeroporto(vetor,codOrigem);

    Voos *pant;
    Voos *novo = (Voos *)malloc(sizeof(Voos));
    novo = new Voos;

    if(!novo){
            cout<<("sem memoria")<<endl;
            cin.get();
            exit(1);
        }

    if(pos != -1){

            vetor[pos].codAero = codOrigem;

            cout<<"CADASTRO VOOS"<<endl;
            cout<<"Codigo Aeroporto Destino: ";
            cin>>cod;
            cout<<"Numero do Voo: ";
            cin>>numeroVoo;

        if(procuraVoo(vetor,numeroVoo) == -1){

            novo->CodDestino = cod;
            novo->numVoo = numeroVoo;
            novo->prox = NULL;


            cout<<("INCLUSAO CONFIRMADA")<<endl;
            cout<<endl;

            if(vetor[pos].prox2==NULL)
            {
                    novo->prox = vetor[pos].prox2;
                    vetor[pos].prox2 = novo;
                    return;
            }

            pant = vetor[pos].prox2;

            while(pant->prox != NULL){
                pant = pant->prox ;
            }
            novo->prox = pant->prox;
            pant->prox = novo;
        }else
            cout<<"Voo ja cadastrado"<<endl;



            system("pause");
            system("cls");
    }else
        cout<<"Aeroporto inexistente , Impossivel cadastrar lista de voos";
}

void mostraVoo(Aeroporto *ptrAux2, vector<Aeroporto> vetor, int cod){
    int   pos = procuraAeroporto(vetor,cod);
    Voos *temp = vetor[pos].prox2;

    int dest;
    if(pos != -1){
        while(temp != NULL)
        {
                cout<<"Cod Destino : "<<temp->CodDestino<<endl;
                dest = temp->CodDestino;
                cout<<"Aeropoto : "<<vetor[dest].sigla<<endl;
                cout<<"Para : "<<vetor[dest].nomeCidade<<endl;
                cout<<"Numero do Voo :"<<temp->numVoo<<endl;

            temp = temp->prox;
            vetor[pos].prox2 =temp;
        }
    }else
        cout<<"Aeroporto inexistente , Impossivel apresentar lista de voos";
}
int procuraAeroporto(vector<Aeroporto> vetor , int cod){
    int achou;
    for (unsigned int i = 0; i < vetor.size(); i++) {
            if(vetor[i].codAero == cod){
                return i;
                break;
            }
}
return -1;
}

int validaSigla(vector<Aeroporto> vetor , string sigla){
    int achou;
    for (unsigned int i = 0; i < vetor.size(); i++) {
            if(vetor[i].sigla == sigla){
                return i;
                break;
            }
}
return -1;
}

int procuraVoo(vector<Aeroporto> vetor , int numVoo){
    Voos *aux,*pant;

    for(unsigned int i = 0; i < vetor.size(); i++) {
        if(vetor[i].prox2!=NULL){
            aux = vetor[i].prox2;
            if(aux->numVoo ==numVoo ){
                return i;
                break;
            }else{
               aux = aux->prox;
               while(aux != NULL && aux->numVoo != numVoo){
                    aux=aux->prox;
                }
                if(aux!=NULL)
                    return i;
            }
        }
    }
    return -1;
}
void excluiElemento (Voos **ptrAux, int elemento,vector<Aeroporto>& vetor){
    int   pos = procuraVoo(vetor,elemento);

    Voos *p, *pant = NULL;
    p = vetor[pos].prox2;

    cout<< "\nP : " << p;
    cout<< "\n P : " << p->prox;
    cout<< "\n VETOR : " << vetor[pos].prox2;
    cout<< "\nC1: " << p->numVoo;
    cout<< "\nC2 : " << p->CodDestino;

    if (p!=NULL)
    {
        if (p->numVoo == elemento){

            vetor[pos].prox2 = p->prox;
        cout<< "\nP : " << p;
        cout<< "\n P : " << p->prox;
        cout<< "\n VETOR : " << vetor[pos].prox2;
        cout<< "\nC1: " << p->numVoo;
        cout<< "\nC2 : " << p->CodDestino;

            delete p;
            return;
        }
        pant = vetor[pos].prox2 ;
        p = p->prox;
        while (p != NULL && p->numVoo != elemento){
            cout<<"VOO INEXISTENTE"<<endl;
            pant = p;
            p=p->prox;
        }
        if (p!=NULL)
        {
            pant->prox = p->prox;

            delete p;
            cout<<"EXCLUSAO CONFIRMADA"<<endl;
        }
    }else
        cout<<"VOO INEXISTENTE 2"<<endl;
}
void procuraDestino(vector<Aeroporto> vetor , int codOrigem , int codDestino , int maxConexoes ){
    Voos *aux,*pant;
    cin.ignore();
    bool achou = false;
    cout<<"cod origem :";
    cin>>codOrigem;
    cout<<"cod DEST :";
    cin>>codDestino;
    cout<<"MAX :";
    cin>>maxConexoes;
    for(unsigned int i = 0; i < vetor.size(); i++) {

        if(vetor[i].prox2!=NULL ){
            aux = vetor[i].prox2;
            if(aux->CodDestino == codDestino and aux->prox != NULL ){
                cout<<"Opcao : ("<<aux->numVoo<<")"<<vetor[i].codAero<<"-"<<aux->CodDestino<<endl;
                achou=true;
            }
            if(vetor[i].prox2->prox != NULL){
                aux = aux->prox;
                while(aux != NULL){
                    if(aux->CodDestino == codDestino && vetor[i].codAero == codOrigem)
                        cout<<"Opcao : ("<<aux->numVoo<<")"<<vetor[i].codAero<<"-"<<aux->CodDestino<<endl;
                        achou=true;
                    aux=aux->prox ;
                }

            }
        }

    }
 if(achou == false)
    cout<<"VOO NAO ENCONTRADO";
}
void gravaArq(vector<Aeroporto> vetor) {
    Voos *aux;
    ofstream arqTexto("text2.txt", ios::out); // isso aqui cria o arquivo

    if(!arqTexto)
        cout<< "\nNao posso abrir arquivo copia.xxx\n";
    else
        cout<< "\nArquivo aberto com sucesso\n";

    for(int i=0 ; i<vetor.size();i++){
       aux = vetor[i].prox2;
       arqTexto<<std::to_string(vetor[i].codAero);
       arqTexto<<","+vetor[i].sigla;
       arqTexto<<","+vetor[i].nomeCidade + ",";

         while(aux != NULL)
        {
            arqTexto<<  std::to_string(aux->CodDestino) + "," ;
            arqTexto<< std::to_string(aux->numVoo) + "," ;
            aux = aux->prox;
            vetor[i].prox2 = aux;
        }

            arqTexto<<";"<<endl;
        }
        arqTexto.close();
}
void recuperacao(vector<Aeroporto> &vetor){
    string vet[100] = {};
    ifstream ifs("text2.txt");
    string linha;
    string palavra = "";
    int tam = 0 ;

    while(!ifs.eof()){
       getline(ifs,linha);
      for(int i = 0;i<linha.length() ; i++) {
          if(linha[i] != ';' and linha[i] != '\n'){
            palavra += linha[i];
          }else{
            vet[tam] = palavra;
            cout<<vet[tam]<<endl;
            tam++;
            palavra="";
            }

        }
    }


    gravaLista(vetor,vet,tam);

}

void gravaLista(vector<Aeroporto>& vetor , string vet[],int tam){

	int  CodDestino, i=0 , cont=3;
	char ch;
	string palavra = "";
	string strAux = "";
	vector<string> vetorPalavra;
    int pos;
    Aeroporto aux;
    aux.prox2 = NULL;
    Voos *pant;
    Voos *novo = (Voos *)malloc(sizeof(Voos));
    novo = new Voos;
    if(!novo){
            cout<<("sem memoria")<<endl;
            cin.get();
            exit(1);

    }

    for(int j = 0;j<tam;j++){
            vetorPalavra.clear();
            palavra = vet[j];
            ch = palavra.at(0);
          for(int i=0;i<palavra.length();i++){
                ch = palavra.at(i);
                if(palavra.at(i) != ',' and palavra.at(i) !=';'){
                    strAux += ch;
                }else{
                   vetorPalavra.push_back(strAux);
                   strAux = "";
                }
            }



        aux.codAero = stoi(vetorPalavra[0]); //stoi(vetorPalavra[0]);

        aux.sigla = vetorPalavra[1];

        aux.nomeCidade = vetorPalavra[2];
        vetor.push_back({aux});

        if(vetorPalavra.size() > 3){

            do{

                pos = procuraAeroporto(vetor,aux.codAero);
                vetor[pos].codAero = stoi(vetorPalavra[0]);

                novo->CodDestino = stoi(vetorPalavra[cont]);

                cont++;

                novo->numVoo = stoi(vetorPalavra[cont]);

                cont++;




                //if(cont == 5){

                    novo->prox = vetor[pos].prox2;
                    vetor[pos].prox2 = novo;
                    novo->prox = NULL;
 /*
                }

                if(cont > 5){
                    pant = vetor[pos].prox2 ;
                    cout<<"+---2: "<<pant<<endl;
                    while(pant->prox != NULL){
                        pant = pant->prox ;
                        cout<<"----2: "<<pant<<endl;
                }
                   cout<<"vetor[pos].prox2 "<<vetor[pos].prox2<<endl;
                    cout<<"novo->prox "<<novo->prox<<endl;
                    novo->prox = pant->prox;
                    pant->prox = novo;
                }
                */



       }while(cont != vetorPalavra.size());

    }

}
}



