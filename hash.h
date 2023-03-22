#pragma once

#define N 21    // tamanho da chave ( string )
#define D 51    // tamanho do nome do documento ( string )
#define ND 100  // numero maximo de documentos
#define NN 1000 // numero maximo de chaves por documentos
#define M 1000  // tamanho da tabela
#define MAX_STR 20001

typedef char Chave[N];
typedef char NomeDocumento[D];

typedef struct
{
  int n; // numero de documentos
  Chave chave;
  NomeDocumento documentos[ND];
} Item;

typedef struct celula
{
  struct celula *pProx;
  Item item;
} Celula;

typedef struct
{
  Celula *pPrimeiro, *pUltimo;
} Lista;

typedef struct
{
  int n;          // numero de itens na hash
  int nro_listas; // tamanho do array de listas
  int nro_pesos;  // tamanho do array de pesos
  int *p;         // array de pesos
  Lista *v;       // array de listas
} Hash;

int h(Hash *, Chave);
int pegarChaves(Chave *);