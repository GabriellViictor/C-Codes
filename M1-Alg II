#include <iostream>
#include <cstring>
#include <limits>
#define TMAX 100
using namespace std;

void leituraLivro(string titulo[] , string autor[] , string editora[] , string isbn[] , int qntd[], int &tam);
void consultaLivro(string isbn[],string numeroISBN,string titulo[],string autor[],string editora[],int qntd[] ,int tam);
void relatorio(string titulo[] , string autor[] , string editora[] , string isbn[] , int qntd[],int tam);
void exclusao(string isbn[],string numeroISBN,string titulo[],string autor[],string editora[],int qntd[] ,int &tam);
void aquisicaoExemplar(string isbn[],string numeroISBN,string titulo[],string autor[],string editora[],int qntd[] ,int tam);
void ordenaTitulo(string titulo[] , string autor[] , string editora[] , string isbn[] , int qntd[], int tam);
string referenciaString(string nomeAutor);
char outraOp();
int  verificaISBN(string isbn[] , string numeroISBN, int tam);

int main()
{
    string titulo[TMAX] , autor[TMAX] , editora[TMAX] , isbn[TMAX] ;
    int qntd[TMAX], op , tam = 0;
    string numeroISBN;
    char resp;

do{
    cout<<"==========ACERVO BIBLIOTECA==========  \n";
    cout << "Escolha uma das opcoes: " << endl;
    cout << "1 - Cadastrar um novo livro/titulo " << endl << "2 - Consultar um livro" << endl;
    cout << "3 - Exclusao de um livro" << endl ;
    cout << "4 - Aquisicao de um livro" << endl ;
    cout << "5 - Relatorio (livros do acervo)" << endl;
    cout << "6 - Saida do programa"<<endl;
    cin>>op;

    switch (op){

    case 1:
        leituraLivro(titulo,autor,editora,isbn,qntd,tam);
        ordenaTitulo(titulo,autor,editora,isbn,qntd,tam); //Verificação do livro com if else
        break;
    case 2:
        cin.ignore();
        cout<<"Digite o numero ISBN a ser consultado :";
        getline(cin,numeroISBN);
        consultaLivro(isbn, numeroISBN,titulo,autor,editora,qntd,tam);

        break;
    case 3:
        cin.ignore();
        cout<<"Digite o numero ISBN a ser excluido :";
        getline(cin,numeroISBN);
        exclusao(isbn, numeroISBN,titulo,autor,editora,qntd,tam);
        break;
    case 4 :
        cin.ignore();
        cout<<"Digite o numero ISBN a ser adquirido :";
        getline(cin,numeroISBN);
        aquisicaoExemplar(isbn, numeroISBN,titulo,autor,editora,qntd,tam);//MEXER AQUI DPS , TIRAR UMAS VARIAVEIS

        break;
    case 5 :
        relatorio(titulo,autor,editora,isbn,qntd,tam);
        break;
    case 6 :
        exit(1);

    }

    cin.ignore();
    resp = outraOp();
    system("cls");
}while(resp == 'S');
    return 1;
}

void leituraLivro(string titulo[] , string autor[] , string editora[] , string isbn[] , int qntd[],int &tam){
    string nomeLivro,nomeAutor , nomeEditora, numeroISBN , auxNome ;
    int quantidadeExemplares;
    bool resp = true;

    cin.ignore();
    cout<< "Numero ISBN: " << endl; // VALIDAR ISBN , SO PODE DIGITO E TRAÇO
    do{
        getline(cin,numeroISBN);
    }while(numeroISBN.length() != 13 || (numeroISBN.find_first_not_of( "0123456789" ) == string::npos )!= true);

    if(verificaISBN(isbn , numeroISBN , tam) == -1){
        isbn[tam]=numeroISBN;

        cout<< "Nome do livro: " << endl;
        do{
            getline(cin,nomeLivro);
        }while(nomeLivro.empty());
        titulo[tam]=nomeLivro;


        cout<< "Nome do autor:  " << endl;

        do{
            getline(cin,nomeAutor);

            for(unsigned int i = 0; i<nomeAutor.size();i++){
                resp = true;
                if(!isalpha(nomeAutor.at(i))){
                    resp = false;
            }
            }
        }while(resp == false or nomeAutor.empty()); // VALIDACAO FEITA ATRAVES DO EXERCICO 05 DA LISTA STRING
        autor[tam]=referenciaString(nomeAutor);;

        cout<< "Editora: " << endl;
        do{
            getline(cin,nomeEditora);
        }while(nomeEditora.empty());
        editora[tam]=nomeEditora;

        do{
            cout<< "Quantos exemplares tem? " << endl;
            cin >> quantidadeExemplares;
            while(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Quantos exemplares tem? " << endl;
            cin >> quantidadeExemplares ;
        }
            }while(quantidadeExemplares < 0);


        qntd[tam]=quantidadeExemplares;
        tam++;
        cout<<"Inclusao de livro confirmada"<<endl;
    }else
        cout<<"TITULO JA EXISTENTE";

}

void relatorio(string titulo[] , string autor[] , string editora[] , string isbn[] , int qntd[],int tam)
{
    for(int i = 0; i < tam; i++){
        cout << "Livro " << i+1 << " :" << endl;
        cout << "O titulo do livro eh: " << titulo[i] << endl << "O autor do livro eh: " << autor[i] << endl;
        cout<< "Editora: "<<editora[i] <<endl;
        cout << "O ISBN do livro eh: " << isbn[i] << endl;
        cout << "O livro possui " << qntd[i] << " exemplares" << endl;
        cout<<"==========================================================================\n";
    }
}

int  verificaISBN(string isbn[] , string numeroISBN, int tam){
    for (int i = 0; i< tam; i++){
        if(isbn[i] == numeroISBN){
            return i; // se ele existe retorna o indice
            break;
            }
        }
return -1; // senao retorna -1 (NAO EXISTE)
}
char outraOp(){
    char c;
    do{
        cout<< "\nMais alguma acao? S/N" << endl;
        c = toupper(cin.get());
    }while(c != 'S' && c != 'N');
    return c;
}
void  consultaLivro(string isbn[],string numeroISBN,string titulo[],string autor[],string editora[],int qntd[] ,int tam){
    int pos;
    pos = verificaISBN(isbn , numeroISBN , tam);

    if( pos == -1){
        cout<<"LIVRO INEXISTENTE";
    }else{
        cout << "O titulo do livro eh: " << titulo[pos] << endl << "O autor do livro eh: " << autor[pos] << endl;
        cout<< "Editora: "<<editora[pos] <<endl;
        cout << "O ISBN do livro eh: " << isbn[pos] << endl;
        cout << "O livro possui " << qntd[pos] << " exemplares" << endl;
    }
}
void exclusao(string isbn[],string numeroISBN,string titulo[],string autor[],string editora[],int qntd[] ,int &tam){
    int pos;
    pos = verificaISBN(isbn , numeroISBN , tam);

    if(pos == -1 ){
        cout<<"LIVRO INEXISTENTE, IMPOSSIVEL EXCLUIR";
    }else{
        for(int i=pos;i<tam-1;i++){
            titulo[i] = titulo[i+1];
            autor[i] = autor[i+1];
            editora[i] = editora[i+1];
            qntd[i] = qntd[i+1];
            isbn[i] = isbn[i+1];
            }
        tam--;
        cout<<"Exclusao do livro confrimada";
    }
}
void aquisicaoExemplar(string isbn[],string numeroISBN,string titulo[],string autor[],string editora[],int qntd[] ,int tam){
    int pos , novosExempalres;
    pos = verificaISBN(isbn , numeroISBN , tam);

     if(pos == -1 ){
        cout<<"LIVRO INEXISTENTE";
    }else{
        cout<<"Quantos exemplares deseja adquirir ? :";
        cin>>novosExempalres;
        qntd[pos]+=novosExempalres;
        cout<<"Exemplares incluidos";
    }
}
void ordenaTitulo(string titulo[] , string autor[] , string editora[] , string isbn[] , int qntd[], int tam){
    string auxTitulo , auxAutor, auxEditora , auxISBN;
    int auxQntd;
    for(int i = 0; i<tam ; i++)
        for(int j=i+1;j<tam;j++)
            if(titulo[i] > titulo[j]){
               auxTitulo = titulo[i];
               titulo[i]=titulo[j];
               titulo[j]=auxTitulo;
               //=====Editora=====
               auxEditora = editora[i];
               editora[i]=editora[j];
               editora[j]=auxEditora;
               //=====AUTOR=======
               auxAutor = autor[i];
               autor[i]=autor[j];
               autor[j]=auxAutor;
               //====isbn======
               auxISBN = isbn[i];
               isbn[i]=isbn[j];
               isbn[j]=auxISBN;
               //====QAUNTIDADE====
               auxQntd = qntd[i];
               qntd[i]=qntd[j];
               qntd[j]=auxQntd;
            }
}
string referenciaString(string nomeAutor){
string novo1 , novo2  ,formatado;
char nome[100];
char b,c[20];
int i,j,a,f=1,g=0;
strcpy(nome, nomeAutor.c_str());

    a=strlen(nome); // tam
    for(i=a;i>=0;i--){ // AQUI CONTROLA O PRIMEIRO NOME
        if(nome[i]==' '){
            b=nome[i+1];
            b=toupper(b);
            c[0]=b;
            novo1+=b;
            nome[i]='.';
            for(j=i+2;j<a;j++){
                c[f]=toupper(nome[j]);
                novo1+=c[f];
                f++;
            }
            g=1;
            break;
        }
    }
    g=0;f=0;
    for(i=0;i<a;i++){
        if(nome[i]=='.'){break;}
        if(nome[i]==' '){
            g=0;
            i++;
            if(nome[i+3]==' '||nome[i+3]=='.'){ // AQUI TA CONTROLANDO O TAMANHO DOS CONECTIVOS
                i+=3;g=1;
            }
        }
        if(nome[i]==' '){g=0;i++;}
        if(g==0){
            if(nome[i+2]!=' '){
                b=toupper(nome[i]);
                novo2+=b;
                novo2+='.';
                g=1;
            }
        }
    }
    formatado = novo1 + ',' + novo2  ;

    return formatado;
}
