#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int ordem=0, transporte=0, i;
int nif[SIZE], distancia[SIZE], tempo[SIZE], meio[SIZE], autonomia[SIZE], tipo[SIZE], codigo[SIZE];
float custo[4], valor;
FILE *file;

int main(void){
  custo[1]=0.8;
  custo[2]=0.2;
  custo[3]=0.3;

  read();

  read2();

  printf("Dados Carregados com sucesso!\n\n");

  menu();

  save();

  save2();

  printf("\n\nDados Guardados com sucesso!");

  return 0;
}

int read(){
  file = fopen("pedidos.txt", "rt");

    for(i=1;i<SIZE;i++){
      fscanf(file,"%d;%d;%d;%d;%d;%d\n",&i,&nif[i],&codigo[i],&tempo[i],&distancia[i], &ordem);
    }

  fclose(file);

  return 0;
}

int read2(){
  file = fopen("meios.txt", "rt");

    for(i=1;i<SIZE;i++){
      fscanf(file, "%d;%d;%d;%d\n", &i,&tipo[i], &autonomia[i], &transporte);
    }

  fclose(file);

  return 0;
}

int save2(){
  file = fopen("meios.txt", "wt");

    for(i=1;i<SIZE;i++){
      if(autonomia[i]>0) fprintf(file,"%d;%d;%d;%d\n", i, tipo[i], autonomia[i], transporte);
    }

  fclose(file);
  return 0;
}

int save(){
  file = fopen("pedidos.txt", "wt");

    for(i=1;i<SIZE;i++){
      if (nif[i]>0) fprintf(file,"%d;%d;%d;%d;%d;%d\n", i, nif[i], codigo[i], tempo[i], distancia[i], ordem);
    }

  fclose(file);
  return 0;
}

int menu(){
  int opcao;
    //MENU
    printf("NOVO PEDIDO DE UTILIZACAO..................................1\n");
    printf("CANCELAR PEDIDO DE UTILIZACAO..............................2\n");
    printf("LISTAR PEDIDOS DE UTILIZACAO...............................3\n");
    printf("ADICIONAR MEIO DE MOBILIDADE...............................4\n");
    printf("REMOVER MEIO DE MOBILIDADE.................................5\n");
    printf("LISTAR MEIOS DE MOBILIDADE.................................6\n");
    printf("CONSULTAR VALOR DE PEDIDO DE UTILIZACAO....................7\n");
    printf("SAIR.......................................................0\n");
    scanf("%d", &opcao);

  switch (opcao){

    case 1:
    ordem++;

    printf("Introduza o seu NIF");
    scanf("%d", &nif[ordem]);

    printf("Introduza o meio de transporte pretendido\nCarro.............1\nBicicleta.........2\nTrotinete.........3\n");
    scanf("%d", &meio[ordem]);

    printf("Introduza o tempo pretendido");
    scanf("%d", &tempo[ordem]);

    printf("Introduza a distancia pretendida");
    scanf("%d", &distancia[ordem]);

      for(i=1;i<SIZE;i++){
        if (autonomia[i] >= distancia[ordem] && meio[ordem]==tipo[i]) codigo[ordem] = i;
      }

      if(codigo[ordem]>0) printf("Pedido efetuado com sucesso com o numero de ordem 0%d. O seu meio tem o codigo M%d.\n", ordem, codigo[ordem]);
        else{
          printf("Nenhum meio de transporte disponivel. Tente outro meio de transporte\n");
          nif[ordem]=0;
          meio[ordem]=0;
          tempo[ordem]=0;
          distancia[ordem]=0;
          ordem--;
        }

      autonomia[codigo[ordem]] -= distancia[ordem];

    menu();
    break;

    case 2:
    printf("Introduza o codigo que pretende remover\n");
    scanf("%d", &ordem);

    nif[ordem]=0;
    meio[ordem]=0;
    tempo[ordem]=0;
    distancia[ordem]=0;

    printf("Codigo Removido com sucesso!\n");

    menu();
    break;

    case 3:

    printf("NOrdem\tNIF\tMeio\tTempo\tDistancia\n");

      for(i=0;i<SIZE;i++){
        if(tempo[i]>0) printf("%d\t%d\tM%d\t%d\t%d\n", i, nif[i], codigo[i], tempo[i], distancia[i]);
      }

    menu();
    break;

    case 4:
    transporte++;

    printf("Introduza o meio de transporte\nCarro...........1\nTrotinete........2\nBicicleta.........3\n");
    scanf("%d", &tipo[transporte]);

    printf("Introduza a autonomia do meio de transporte ");
    scanf("%d", &autonomia[transporte]);

    printf("Meio de mobilidade adicionado com sucesso!\n");

    menu();
    break;

    case 5:

    printf("introduza o codigo do meio que pretende remover");
    scanf("%d", transporte);

    tipo[transporte]=0;
    autonomia[transporte]=0;

    menu();
    break;

    case 6:

    printf("Codigo\tMeio\t\tCusto\tAutonomia\n");

      for(i=1;i<SIZE;i++){
        if(autonomia[i]>0){
          switch(tipo[i]){
          case 1: printf("M%d\tCarro\t\t%.2f\t%d\n", i, custo[tipo[i]], autonomia[i]); break;
          case 2: printf("M%d\tTrotinete\t%.2f\t%d\n", i, custo[tipo[i]], autonomia[i]); break;
          case 3: printf("M%d\tBicicleta\t%.2f\t%d\n", i, custo[tipo[i]], autonomia[i]); break;
          }
        }
      }

    menu();
    break;

    case 7:

    printf("Introduza o codigo do pedido\n");
    scanf("%d", &ordem);

    valor = custo[ordem] * tempo[ordem];

    printf("A sua viagem tera um custo de %.2feuros\n", valor);

    menu();
    break;

  }

  return (0);
}
