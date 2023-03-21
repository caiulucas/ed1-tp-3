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

  strcpy(indice[i].chave, chave); // insere as infos
  strcpy(indice[i].documentos[indice[i].n++], nomeDocumento);

  return i != -1;
}

int busca(IndiceInvertido indice, Chave chave)
{
  int i = h(chave, M);                     // inicia a chave com o heap
  if (strcmp(indice[i].chave, VAZIO) == 0) // se o indice das posicoes encontradas do heap for sempre vazio, a pesquisa nao teve exito
    return -1;

  while (i != M && strcmp(indice[i].chave, chave) != 0) // busca a chave na posicao. enquanto ela for vazia ou diferente da chave procurada, ela entra no while
    i++;

  return i == M ? -1 : i; // caso for encontrada, retorna o i (posicao da mesma dentro do heap)
}

int buscaDocumentos(NomeDocumento *documentos1, int nDocumentos1, NomeDocumento *documentos2, int nDocumentos2, NomeDocumento *documentos)
{
  int cont = 0;
  for (int i = 0; i < nDocumentos1; i++)
  {
    for (int j = 0; j < nDocumentos2; j++)
    {
      if (strcmp(documentos1[i], documentos2[j]) == 0) // co0mpara se e igual
      {
        strcpy(documentos[cont++], documentos1[i]); // se for igual, armazena no array de documentos
      }
    }
  }
  return cont; // retorna a quantidade de iguais
}

int consulta(IndiceInvertido indice, Chave *chaves, int n, NomeDocumento *documentos)
{
  int *posicoes = malloc(sizeof(int) * n); // aloca array de posicoes
  int cont = 0;                            // contagem
  int iniPos;
  iniPos = busca(indice, chaves[0]);

  if (iniPos == -1)
  {
    printf("none\n");
    return 0;
  }

  for (int i = 1; i < n; i++) // posicao e armazenada no array e soma 1 no cont
  {
    int pos = busca(indice, chaves[i]);
    if (iniPos != -1)
    {
      cont = buscaDocumentos(indice[iniPos].documentos, indice[iniPos].n, indice[pos].documentos, indice[pos].n, documentos);
    }
  }

  if (cont == 0 && n == 1)
  {
    for (int i = indice[iniPos].n - 1; i >= 0; i--)
    {
      printf("%s\n", indice[iniPos].documentos[i]);
    }
    return 1;
  }

  if (n != 1 && cont == 0)
  {
    printf("none\n");
    return 0;
  }

  for (int i = 0; i < cont; i++)
  {
    printf("%s\n", documentos[i]);
  }

  return 1;
}

// funcao para imprimir os resultados
void imprime(IndiceInvertido indice)
{
  int i, j;
  for (i = 0; i < M; i++)
  {
    if (strcmp(indice[i].chave, VAZIO) != 0) // nao imprimir vazio
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

// bubble sort para ordernar
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