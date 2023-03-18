#include <string.h>
#include "indiceInvertido.h"
#include <stdio.h>

void inicia(IndiceInvertido indice)
{
  for (int i = 0; i < M; i++)
  {
    indice[i].n = 0;                // zera a quantidade de documentos nas chaves
    strcpy(indice[i].chave, VAZIO); // coloca vazio em todas as chaves
  }
}

bool insereDocumento(IndiceInvertido indice, Chave chave, NomeDocumento nomeDocumento)
{

  if (busca(indice, chave) == -1)
  {
    int i = h(chave, M);
    strcpy(indice[i].chave, chave);
    strcpy(indice[i].documentos[indice[i].n++], nomeDocumento);
    return true;
  }

  return false;
}

int busca(IndiceInvertido indice, Chave chave)
{
  int i = h(chave, M);                     // inicia a chave com o heap
  if (strcmp(indice[i].chave, VAZIO) == 0) // se o indice das posicoes encontradas do heap for sempre vazio, a pesquisa nao teve exito
  {
    return -1;
  }

  while (i != M && strcmp(indice[i].chave, chave) != 0) // busca a chave na posicao. enquanto ela for vazia ou diferente da chave procurada, ela entra no while
  {
    i++; // lista circular
  }

  return i == M ? -1 : i; // caso for encontrada, retorna o i (posicao da mesma dentro do heap)
}

int consulta(IndiceInvertido indice, Chave *chaves, int n, NomeDocumento *documentos)
{
  int k = 0;
  for (int i = 0; i < n; i++)
  {
    int pos = busca(indice, chaves[i]);
    if (pos != -1)
    {
      for (int j = 0; j < indice[pos].n; j++)
      {
        memcpy(documentos[k++], indice[pos].documentos[j], D);
      }
    }
  }
  sort(documentos, k);
  return k;
}

void imprime(IndiceInvertido indice)
{
  int i, j;
  for (i = 0; i < M; i++)
  {
    if (strcmp(indice[i].chave, VAZIO) != 0)
    {
      printf("%s - ", indice[i].chave);
      printf("%d - ", indice[i].n);
      for (j = 0; j < indice[i].n; j++)
      {
        printf("%s ", indice[i].documentos[j]);
      }
      printf("\n");
    }
  }
}

void sort(NomeDocumento *documentos, int nDocumentos)
{
  int i, j;
  NomeDocumento aux;
  for (i = 0; i < nDocumentos; i++)
  {
    for (j = i + 1; j < nDocumentos; j++)
    {
      if (strcmp(documentos[i], documentos[j]) > 0)
      {
        memcpy(aux, documentos[i], D);
        memcpy(documentos[i], documentos[j], D);
        memcpy(documentos[j], aux, D);
      }
    }
  }
}