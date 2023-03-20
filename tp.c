#include "indiceInvertido.h"
#include <stdio.h>

int main()
{
  int n, nDocumentos = 0;
  IndiceInvertido indice;

  inicia(indice);

  Chave chaves[N];
  NomeDocumento documentos[ND];

  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%s ", documentos[i]);
    int nChaves = pegarChaves(chaves);

    for(int j = 0; j < nChaves; j++)
    {
      insereDocumento(indice, chaves[j], documentos[i]);
    }
  }

  sort(documentos, nDocumentos);
  char ehBusca;
  scanf("%c ", &ehBusca);

  if(ehBusca == 'B') {
    Chave buscaChaves[N];
    int nChaves = pegarChaves(buscaChaves);

    consulta(indice, buscaChaves, nChaves, documentos);
  } else {
    imprime(indice);
  }

  return 0;
}
