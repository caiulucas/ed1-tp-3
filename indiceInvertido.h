#pragma once
#include <stdbool.h>
#include "hash.h"

/* Os cabeçalhos de todas as funções e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef Item IndiceInvertido[M];

/* Funções */

void inicia(IndiceInvertido);
bool insereDocumento(Hash *, Item);

int busca(Hash *hash, Chave chave, Item *item);
int consulta(IndiceInvertido, Chave *, int, NomeDocumento *);
void imprime(IndiceInvertido);

void sort(NomeDocumento *documentos, int left, int right);