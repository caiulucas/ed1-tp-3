#include <string.h>
#include "indiceInvertido.h"
#include <stdio.h>
#include <stdlib.h>

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

  int iBusca = busca(indice, chave);
  int i = iBusca == -1 ? h(chave, M) : iBusca;

  strcpy(indice[i].chave, chave);
  strcpy(indice[i].documentos[indice[i].n++], nomeDocumento);

  return i != -1;
}

int busca(IndiceInvertido indice, Chave chave)
{
  int i = h(chave, M);                     // inicia a chave com o heap
  if (strcmp(indice[i].chave, VAZIO) == 0) // se o indice das posicoes encontradas do heap for sempre vazio, a pesquisa nao teve exito
    return -1;

  while (i != M && strcmp(indice[i].chave, chave) != 0) // busca a chave na posicao. enquanto ela for vazia ou diferente da chave procurada, ela entra no while
  {
    i++; // lista circular
  }

  return i == M ? -1 : i; // caso for encontrada, retorna o i (posicao da mesma dentro do heap)
}

int buscaDocumentos(NomeDocumento *documentos1, int nDocumentos1, NomeDocumento *documentos2, int nDocumentos2)
{
  int cont = 0;
  for (int i = 0; i < nDocumentos1; i++)
  {
    for (int j = 0; j < nDocumentos2; j++)
    {
      if (strcmp(documentos1[i], documentos2[j]) == 0)
      {
        cont++;
      }
    }
  }
  return cont;
}

int consulta(IndiceInvertido indice, Chave *chaves, int n, NomeDocumento *documentos)
{
  int *posicoes = malloc(sizeof(int) * n);
  int cont = 0;
  for (int i = 0; i < n; i++)
  {
    int atualPos = busca(indice, chaves[i]);
    if (atualPos != -1)
      posicoes[cont++] = atualPos;
  }

  if (cont == 1)
  {
    for (int i = indice[posicoes[0]].n - 1; i >= 0; i--)
      printf("%s\n", indice[posicoes[0]].documentos[i]);

    return 1;
  }

  int encontrados = 0;
  for (int i = 0; i < cont; i++)
  {
    for (int j = i + 1; j < cont; j++)
    {
      int documentosEncontrados = buscaDocumentos(indice[posicoes[i]].documentos, indice[posicoes[i]].n,
                                                  indice[posicoes[j]].documentos, indice[posicoes[j]].n);
      if (documentosEncontrados > 0)
      {
        encontrados++;
        for (int k = 0; k < documentosEncontrados; k++)
        {
          printf("%s\n", documentos[k]);
        }
      }
    }
  }

  if (!encontrados)
  {
    printf("none\n");
    return 0;
  }

  return 1;
}

void imprime(IndiceInvertido indice)
{
  int i, j;
  for (i = 0; i < M; i++)
  {
    if (strcmp(indice[i].chave, VAZIO) != 0)
    {
      printf("%s - ", indice[i].chave);
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