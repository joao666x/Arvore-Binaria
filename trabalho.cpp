#include <iostream>
#include <string>
#include <stdio.h>
#include <cfloat>
#include <ctime>

using namespace std;
typedef struct No {
  int codigo;
  string nome;
  int idade;
  string CPF;
  float divida;
  int data_pagamento;
  struct No* esq;
  struct No* dir;
  int altura;
  void exibir_no() {
    cout <<"Codigo: "<< this->codigo <<endl;
    cout <<"Nome: "<< this->nome <<endl;
    cout <<"Idade: "<< this->idade <<endl;
    cout <<"CPF: "<< this->CPF <<endl;
    cout <<"Dívida: "<< this->divida <<endl;
    cout <<"Data de pagamento: "<< this->data_pagamento <<endl;
    //cout <<"ALTURA NA ARVORE: "<< this->altura<<endl;
    cout<<endl;
  }
} No;


class Arvore {
  No* raiz;
  No* maior_divida;
  float acumulador_de_dividas;
  int numero_de_dividas;

  No* inserir(int codigo, string nome, int idade, string CPF, float divida, int data_pagamento, No* A) {
    if(A == NULL) {
      A = new No;
      A->codigo = codigo;
      A->nome=nome;
      A->idade=idade;
      A->CPF=CPF;
      A->divida=divida;
      A->data_pagamento=data_pagamento;
      A->altura = 0;
      A->esq = A->dir = NULL;

      if((A->divida)>this->maior_divida->divida)
        this->maior_divida = A;

      acumulador_de_dividas+=A->divida;
      this->numero_de_dividas++;
    } else if(codigo < A->codigo) {
      A->esq = inserir(codigo, nome, idade, CPF, divida, data_pagamento, A->esq);
      if(altura(A->esq) - altura(A->dir) == 2) {
        if(codigo < A->esq->codigo)
          A = rotacao_simples_a_direita(A);
        else
          A = rotacao_dupla_a_direita(A);
      }
    } else if(codigo > A->codigo) {
      A->dir = inserir(codigo, nome, idade, CPF, divida, data_pagamento, A->dir);
      if(altura(A->dir) - altura(A->esq) == 2) {
        if(codigo > A->dir->codigo)
          A = rotacao_simples_a_esquerda(A);
        else
          A = rotacao_dupla_a_esquerda(A);
      }
    }
    A->altura = max(altura(A->esq), altura(A->dir))+1;

    return A;
  }

  No* rotacao_simples_a_direita(No* &A) {
    No* B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    A->altura = max(altura(A->esq), altura(A->dir))+1;
    B->altura = max(altura(B->esq), A->altura)+1;
    return B;
  }

  No* rotacao_simples_a_esquerda(No* &A) {
    No* B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    A->altura = max(altura(A->esq), altura(A->dir))+1;
    B->altura = max(altura(A->dir), A->altura)+1 ;
    return B;
  }

  No* rotacao_dupla_a_esquerda(No* &A) {
    A->dir = rotacao_simples_a_direita(A->dir);
    return rotacao_simples_a_esquerda(A);
  }

  No* rotacao_dupla_a_direita(No* &A) {
    A->esq = rotacao_simples_a_esquerda(A->esq);
    return rotacao_simples_a_direita(A);
  }

  No* para_encontrar_o_minimo_codigo(No* A) {
    if(A!=NULL)
      while(A->esq!=NULL)
        A = A->esq;
    return A;
  }

  No* para_encontrar_o_maximo_codigo(No* A) {
    if(A == NULL)
      return NULL;
    else if(A->dir == NULL)
      return A;
    else
      return para_encontrar_o_maximo_codigo(A->dir);
  }

  int altura(No* A) {
    return (A == NULL ? -1 : A->altura);
  }

  int retorna_fator_de_balanceameno(No* A) {
    if(A == NULL)
      return 0;
    else
      return altura(A->dir) - altura(A->esq);
  }

  void inorder(No* A) {
    if(A == NULL)
      return;
    inorder(A->esq);
    A->exibir_no();
    cout<<endl;
    inorder(A->dir);
  }

  No* busca_recursiva(int codigo,No* raiz_Sub_Arvore) {

    if(codigo==raiz_Sub_Arvore->codigo)
      return raiz_Sub_Arvore;

    else if(codigo>raiz_Sub_Arvore->codigo)
      return busca_recursiva(codigo,raiz_Sub_Arvore->dir);
    else return busca_recursiva(codigo,raiz_Sub_Arvore->esq);

  }

  No* remover_no( int codigo,No* A) {
    if (A == NULL)
      return A;

    if ( codigo < A->codigo )
      A->esq = remover_no(codigo,A->esq);

    else if(codigo > A->codigo )
      A->dir = remover_no(codigo,A->dir);

    else {
      if( (A->esq == NULL) || (A->dir == NULL) ) {
        No *temp = A->esq ? A->esq : A->dir;

        if (temp == NULL) {
          temp = A;
          A = NULL;
        } else
          *A = *temp;
        delete(temp);
      } else {

        No* temp = para_encontrar_o_minimo_codigo(A->dir);

        A->codigo = temp->codigo;

        A->dir = remover_no( temp->codigo,A->dir);
      }
    }

    if (A == NULL)
      return A;

    A->altura = 1 + max(altura(A->esq),altura(A->dir));

    int balance = retorna_fator_de_balanceameno(A);

    if (balance > 1 && retorna_fator_de_balanceameno(A->esq) >= 0)
      return rotacao_simples_a_esquerda(A);

    if (balance > 1 && retorna_fator_de_balanceameno(A->esq) < 0) {
      return rotacao_dupla_a_esquerda(A);
    }

    if (balance < -1 && retorna_fator_de_balanceameno(A->dir) <= 0)
      return rotacao_simples_a_direita(A);

    if (balance < -1 && retorna_fator_de_balanceameno(A->dir) > 0) {
      return rotacao_dupla_a_direita(A);
    }
    return A;
  }

public:

  void remover(int codigo) {
    raiz=remover_no(codigo,raiz);
  }

  void exibe_intervalo(No* A, float divida1, float divida2) {
    if(A == NULL)
      return;
    exibe_intervalo(A->esq,divida1,divida2);
    if( divida1<=A->divida &&  A->divida<=divida2 ) {
      A->exibir_no();
      cout<<endl;
    }
    exibe_intervalo(A->dir,divida1,divida2);
  }

  Arvore() {
    raiz = NULL;
    maior_divida=new No;
    maior_divida->divida=DBL_MIN;
    this->acumulador_de_dividas=0.0;
    this->numero_de_dividas=0;
  }

  float get_valor_medio_das_dividas() {
    return this->acumulador_de_dividas/(float)this->numero_de_dividas;
  }

  No* get_maior_divida() {
    return this->maior_divida;
  }

  int get_numero_de_devedores() {
    return this->numero_de_dividas;
  }

  void inserir_interface(int codigo, string nome, int idade, string CPF, float divida, int data_pagamento) {
    raiz = inserir(codigo, nome, idade, CPF, divida, data_pagamento, raiz);
  }

  void exibir() {
    inorder(raiz);
    cout << endl;
  }

  void exibir_no_intervalo(float divida1, float divida2) {
    if(divida1<=0||divida2<=0) {
      cout<<endl<<"dividas invalidas";
      return;
    }
    if(divida1>divida2)
      swap(divida1,divida2);

    exibe_intervalo(raiz,divida1,divida2);
    cout << endl;
  }

  No* busca(int codigo) {
    No* i = this->raiz;
    i=busca_recursiva(codigo,i);
    return i;
  }

};