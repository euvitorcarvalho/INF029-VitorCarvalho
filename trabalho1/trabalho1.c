// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do
//  trabalho

//  ----- Dados do Aluno -----
//  Nome: Vitor Carvalho
//  email: euvitordev@proton.me
//  Matrícula: 20261160029
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include "trabalho1.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y) {
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x) {  // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--) fat = fat * i;

  return fat;
}

int teste(int a) {
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia,
mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa
podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[]) {
  DataQuebrada d;
  int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  d = quebraData(data);

  if (!d.valido) return 0;

  if (d.iMes < 1 || d.iMes > 12) return 0;

  if (d.iAno < 0) return 0;

  if (d.iAno < 100) {
    if (d.iAno < 50)
      d.iAno += 2000;
    else
      d.iAno += 1900;
  }

  if (d.iAno % 400 == 0 || (d.iAno % 4 == 0 && d.iAno % 100 != 0))
    diasPorMes[1] = 29;

  if (d.iDia < 1 || d.iDia > diasPorMes[d.iMes - 1]) return 0;

  return 1;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis
 valores abaixo 1 -> cálculo de diferença realizado com sucesso 2 -> datainicial
 inválida 3 -> datafinal inválida 4 -> datainicial > datafinal Caso o cálculo
 esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos
 com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
  DiasMesesAnos dma = {0, 0, 0, 0};
  DataQuebrada inicio, fim;
  int dia, mes, ano;
  int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (!q1(datainicial)) {
    dma.retorno = 2;
    return dma;
  }

  if (!q1(datafinal)) {
    dma.retorno = 3;
    return dma;
  }

  inicio = quebraData(datainicial);
  fim = quebraData(datafinal);

  if (inicio.iAno < 100) inicio.iAno += (inicio.iAno < 50) ? 2000 : 1900;

  if (fim.iAno < 100) fim.iAno += (fim.iAno < 50) ? 2000 : 1900;

  if (inicio.iAno > fim.iAno ||
      (inicio.iAno == fim.iAno && inicio.iMes > fim.iMes) ||
      (inicio.iAno == fim.iAno && inicio.iMes == fim.iMes &&
       inicio.iDia > fim.iDia)) {
    dma.retorno = 4;
    return dma;
  }

  dia = fim.iDia - inicio.iDia;
  mes = fim.iMes - inicio.iMes;
  ano = fim.iAno - inicio.iAno;

  if (dia < 0) {
    int mesAnterior = fim.iMes - 2;
    int anoAnterior = fim.iAno;

    if (mesAnterior < 0) {
      mesAnterior = 11;
      anoAnterior--;
    }

    dia += diasPorMes[mesAnterior];

    if (mesAnterior == 1 && (anoAnterior % 400 == 0 ||
                             (anoAnterior % 4 == 0 && anoAnterior % 100 != 0)))
      dia++;

    mes--;
  }

  if (mes < 0) {
    mes += 12;
    ano--;
  }

  dma.qtdDias = dia;
  dma.qtdMeses = mes;
  dma.qtdAnos = ano;
  dma.retorno = 1;

  return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa
 Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar
 diferenças entre maiúsculos e minúsculos. Se isCaseSensitive != 1, a pesquisa
 não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char* texto, char c, int isCaseSensitive) {
  int qtdOcorrencias = 0;
  int i;

  if (!texto) return 0;

  for (i = 0; texto[i] != '\0'; i++) {
    char atual = texto[i];

    if (!isCaseSensitive) {
      atual = (char)tolower((unsigned char)atual);
      c = (char)tolower((unsigned char)c);
    }

    if (atual == c) qtdOcorrencias++;
  }

  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros
 (posicoes) que irá guardar as posições de início e fim de cada ocorrência da
 palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída
 correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do
 vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve
 ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a
 segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente.
 Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como
 há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da
 seguinte forma: posicoes[0] = 13; posicoes[1] = 16; Observe que o índice da
 posição no texto deve começar ser contado a partir de 1. O retorno da função,
 n, nesse caso seria 1;

 */
int q4(char* strTexto, char* strBusca, int posicoes[30]) {
  int qtdOcorrencias = 0;
  int i, j;
  int tamanhoTexto, tamanhoBusca;

  if (!strTexto || !strBusca || !posicoes) return 0;

  tamanhoTexto = (int)strlen(strTexto);
  tamanhoBusca = (int)strlen(strBusca);

  if (tamanhoBusca == 0 || tamanhoBusca > tamanhoTexto) return 0;

  for (i = 0; i <= tamanhoTexto - tamanhoBusca; i++) {
    for (j = 0; j < tamanhoBusca; j++) {
      if (strTexto[i + j] != strBusca[j]) break;
    }

    if (j == tamanhoBusca) {
      int inicio = 1;
      int fim = 1;
      int k;

      for (k = 0; k < i; k++) {
        if (((unsigned char)strTexto[k] & 0xC0) != 0x80) inicio++;
      }

      fim = inicio;

      for (k = 0; k < tamanhoBusca; k++) {
        if (((unsigned char)strBusca[k] & 0xC0) != 0x80) fim++;
      }

      if (qtdOcorrencias < 15) {
        posicoes[qtdOcorrencias * 2] = inicio;
        posicoes[qtdOcorrencias * 2 + 1] = fim - 1;
        qtdOcorrencias++;
      }
    }
  }

  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
  int invertido = 0;
  int sinal = 1;

  if (num < 0) {
    sinal = -1;
    num = -num;
  }

  do {
    invertido = invertido * 10 + num % 10;
    num /= 10;
  } while (num > 0);

  return invertido * sinal;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    char base[32], busca[32];
    int qtdOcorrencias = 0;
    int i, j;

    sprintf(base, "%d", numerobase);
    sprintf(busca, "%d", numerobusca);

    if (numerobusca < 0 || numerobase < 0)
        return 0;

    if (numerobusca == 0)
        strcpy(busca, "0");

    for (i = 0; base[i] != '\0'; i++) {
        for (j = 0; busca[j] != '\0'; j++) {
            if (base[i + j] == '\0' ||
                base[i + j] != busca[j])
                break;
        }

        if (busca[j] == '\0')
            qtdOcorrencias++;
    }

    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as
 direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5])
{
    int direcoes[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},           { 0, 1},
        { 1, -1}, { 1, 0},  { 1, 1}
    };

    int linha, coluna, d, k;
    int tamanho = 0;

    while (tamanho < 5 && palavra[tamanho] != '\0')
        tamanho++;

    if (tamanho == 0)
        return 0;

    for (linha = 0; linha < 8; linha++) {
        for (coluna = 0; coluna < 10; coluna++) {
            for (d = 0; d < 8; d++) {
                int achou = 1;

                for (k = 0; k < tamanho; k++) {
                    int novaLinha =
                        linha + k * direcoes[d][0];
                    int novaColuna =
                        coluna + k * direcoes[d][1];

                    if (novaLinha < 0 || novaLinha >= 8 ||
                        novaColuna < 0 || novaColuna >= 10 ||
                        matriz[novaLinha][novaColuna] != palavra[k]) {
                        achou = 0;
                        break;
                    }
                }

                if (achou)
                    return 1;
            }
        }
    }

    return 0;
}

DataQuebrada quebraData(char data[]) {
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++) {
    sDia[i] = data[i];
  }
  if (i == 1 || i == 2) {  // testa se tem 1 ou dois digitos
    sDia[i] = '\0';        // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  int j = i + 1;  // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++) {
    sMes[i] = data[j];
    i++;
  }

  if (i == 1 || i == 2) {  // testa se tem 1 ou dois digitos
    sMes[i] = '\0';        // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  j = j + 1;  // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '\0'; j++) {
    sAno[i] = data[j];
    i++;
  }

  if (i == 2 || i == 4) {  // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';        // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}
