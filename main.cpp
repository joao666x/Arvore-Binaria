#include <iostream>
#include <time.h>
#include "trabalho.cpp"
using namespace std;

void pause (float);
void pause (float delay1) {
  if (delay1<0.001) return;
  float inst1=0, inst2=0;
  inst1 = (float)clock()/(float)CLOCKS_PER_SEC;
  while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;
  return;
}

int main() {

  Arvore* arvore = new Arvore();

  arvore->inserir_interface(1,"Arlindo", 30, "09361687905", 550.0, 12122020);
  arvore->inserir_interface(2,"Teste", 10, "00000000000", 0.0, 12122020);
  arvore->inserir_interface(3,"Teste 3", 11, "00000000001", 0.1, 12122020);
  arvore->inserir_interface(4,"Teste 4", 12, "00000000002", 0.2, 12122020);
  arvore->inserir_interface(5,"Teste 4", 13, "00000000003", 0.3, 12122020);
  /*
  ordem de atributos para inclusão:
  int codigo, string nome, int idade, string CPF, float divida, int data_pagamento
  */

inicio:

  cout<<"********************"<<endl;
  cout<<"******* Menu *******"<<endl;
  cout<<"********************"<<"\n"<<endl;

  cout<<"01: Incluir cadastro \n"<<endl;
  cout<<"02: Consulta em ordem \n"<<endl;
  cout<<"03: Excluir cadastro \n"<<endl;
  cout<<"04: Exibir a maior dívida, junto com CPF \n"<<endl;
  cout<<"05: Exibir as dívidas que estão em atraso \n"<<endl;
  
  int opcao = 0;
  int idEscolhido = 0;
  int voltar =0;

  int codigo;
  string nome;
  int idade;
  string cpf;
  float divida;
  int data_pagamento;
  
  cout << "Digite opção desejada: \n";
  cin>>opcao;
  system("clear");

  switch (opcao){
    case 1:
      cout<<"\n  .:Incluir cadastro:.\n"<<endl;
      cout << "Código: ";
      cin>>codigo;
      cout<<"\nNome: ";
      cin>>nome;
      cout<<"\nIdade: ";
      cin>>idade;
      cout<<"\nCPF: ";
      cin>>cpf;
      cout<<"\nDivida: ";
      cin>>divida;
      cout<<"\nData de Pagamento:";
      cin>>data_pagamento;
      arvore->inserir_interface(codigo,nome,idade,cpf,divida,data_pagamento);
      cout<<"\n\n\n****Inserido com sucesso****\n";
      pause(2);
      system("clear");
      goto inicio;
      break;
    case 2:
      cout<<"\n  .:Consulta em ordem:. \n"<<endl;
      arvore->exibir();
      cout<<"Digite 0 para voltar ao menu: ";
      again:
      cin>>voltar;
      if(voltar==0){
        system("clear");
        goto inicio;
      } else {
        cout<<"Opçao invalida\n";
        goto again;
      }
      break;
    case 3:
      cout<<"\n  .:Excluir cadastro:. \n"<<endl;
      cout << "Digite um código para excluir: \n";
      cin>>idEscolhido;
      arvore->remover(idEscolhido);
      cout << "O item de código "<<idEscolhido<<" foi excluído\n"<<endl;
      pause(2);
      system("clear");
      goto inicio;
      break;
    case 4:
      cout<<"\n  .:Exibir a maior dívida, junto com CPF:. \n"<<endl;
      break;
    case 5:
      cout<<"\n  .:Exibir as dívidas que estão em atraso:. \n"<<endl;
      break;
    default:
      cout<<"\n  Opção inválida"<<endl;
  }

  arvore->remover(1);
  arvore->remover(2);
  arvore->remover(3);
  arvore->remover(4);
  arvore->remover(5);
  if(arvore!=NULL)
    arvore->exibir();

}

//999563688