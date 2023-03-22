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

// merge sort para ordernar
void merge(NomeDocumento *documentos, int left, int mid, int right)
{
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // Vetores temporários
  NomeDocumento L[n1], R[n2];

  // Copia os dados para os vetores temporários L[] e R[]
  for (i = 0; i < n1; i++)
    memcpy(&L[i], &documentos[left + i], sizeof(NomeDocumento));
  for (j = 0; j < n2; j++)
    memcpy(&R[j], &documentos[mid + 1 + j], sizeof(NomeDocumento));

  // Mescla os vetores temporários de volta para o vetor documentos
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2)
  {
    if (strcmp(L[i], R[j]) <= 0)
    {
      memcpy(&documentos[k], &L[i], sizeof(NomeDocumento));
      i++;
    }
    else
    {
      memcpy(&documentos[k], &R[j], sizeof(NomeDocumento));
      j++;
    }
    k++;
  }

  // Copia os elementos restantes de L[], se houver
  while (i < n1)
  {
    memcpy(&documentos[k], &L[i], sizeof(NomeDocumento));
    i++;
    k++;
  }

  // Copia os elementos restantes de R[], se houver
  while (j < n2)
  {
    memcpy(&documentos[k], &R[j], sizeof(NomeDocumento));
    j++;
    k++;
  }
}

void sort(NomeDocumento *documentos, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;

    // Ordena a primeira e segunda metades
    sort(documentos, left, mid);
    sort(documentos, mid + 1, right);

    // Mescla as metades ordenadas
    merge(documentos, left, mid, right);
  }
}
