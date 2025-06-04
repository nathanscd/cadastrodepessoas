#include <stdio.h>
#include <stdlib.h>

typedef struct PESSOA{
  char Nome[20];
  char CPF[11];
  int Idade;
  float Altura;
} PESSOA;

typedef struct NO{
  PESSOA p;
  struct NO *pont;
} NO;

void empilhar (NO **pilha, PESSOA pessoa){
    NO *novono=(NO*)malloc (sizeof(NO));
    novono->p=pessoa;
    novono->pont=*pilha;
    *pilha=novono;
}

PESSOA desempilhar(NO **pilha) {
  PESSOA vazio = {"", "", 0, 0.0f};
  if (*pilha == NULL) {
    printf("Pilha vazia! Nada para desempilhar.\n");
    return vazio;
  }
  NO *temp = *pilha;
  PESSOA pessoa = temp->p;
  *pilha = temp->pont;
  free(temp);
  return pessoa;
}



void main()
{
  int TAM;
  printf("Bem-vindo ao sistema de cadastros!\n");
  printf("Deseja cadastrar quantos indivíduos? ");
  scanf("%d", &TAM);

  PESSOA *pessoas = (PESSOA *)malloc(TAM * sizeof(PESSOA));
  while (TAM == 0 || TAM < 0)
  {
    printf("\n");
    printf("Digite um número válido.\n");
    printf("Deseja cadastrar quantos indivíduos? ");
    scanf("%d", &TAM);
  }

  for (int i = 0; i < TAM; i++)
  {
    printf("Digite o nome da pessoa %d: ", i + 1);
    scanf("%s", pessoas[i].Nome);

    int cpf_valido = 0;
    while (!cpf_valido)
    {
      printf("Digite o CPF da pessoa %d (somente números): ", i + 1);
      scanf("%s", pessoas[i].CPF);

      int tamanho = 0;
      while (pessoas[i].CPF[tamanho] != '\0')
      {
        tamanho++;
      }

      if (tamanho != 11)
      {
        printf("CPF inválido: deve conter 11 dígitos.\n");
        continue;
      }

      int soma = 0;
      int dig1, dig2;
      for (int j = 0; j < 9; j++)
      {
        soma += (pessoas[i].CPF[j] - '0') * (10 - j);
      }

      int resto = soma % 11;
      if (resto == 0 || resto == 1)
        dig1 = 0;
      else
        dig1 = 11 - resto;

      soma = 0;
      for (int j = 0; j < 10; j++)
      {
        soma += (pessoas[i].CPF[j] - '0') * (11 - j);
      }

      resto = soma % 11;
      if (resto == 0 || resto == 1)
        dig2 = 0;
      else
        dig2 = 11 - resto;

      if ((pessoas[i].CPF[9] - '0') == dig1 && (pessoas[i].CPF[10] - '0') == dig2)
      {
        cpf_valido = 1;
      }
      else
      {
        printf("CPF inválido: CPF não existe.\n");
      }
    }

    printf("Digite a idade da pessoa %d: ", i + 1);
    scanf("%d", &pessoas[i].Idade);
    while (pessoas[i].Idade < 0 || pessoas[i].Idade > 150)
    {
      printf("Idade inválida! Digite novamente: ");
      scanf("%d", &pessoas[i].Idade);
    }

    printf("Digite a altura da pessoa %d: ", i + 1);
    scanf("%f", &pessoas[i].Altura);
    while (pessoas[i].Altura <= 0.0 || pessoas[i].Altura > 3.0)
    {
      printf("Altura inválida! Digite novamente: ");
      scanf("%f", &pessoas[i].Altura);
    }
  }

  NO *lista = NULL;
  for (int i = 0; i < TAM; i++){
    empilhar(&lista, pessoas[i]);
  }

  printf("\nLista de Pessoas:\n");
  NO *atual = lista;
  while(atual != NULL) {
    printf("Nome: %s\n", atual->p.Nome);
    printf("CPF: %s\n", atual->p.CPF);
    printf("Idade: %d\n", atual->p.Idade);
    printf("Altura: %0.2f\n", atual->p.Altura);
    printf("-----------\n");
    atual = atual->pont;
  }

PESSOA removido = desempilhar(&lista);
printf("Desempilhado: %s\n", removido.Nome);

PESSOA ana;
char nomeAna[20] = "Ana";
char cpfAna[12] = "11111111111";
ana.Idade = 31;
ana.Altura = 1.67f;
empilhar(&lista, ana);

PESSOA pedro;
char nomePedro[20] = "Pedro";
char cpfPedro[12] = "22222222222";
pedro.Idade = 45;
pedro.Altura = 1.78f;
empilhar(&lista, pedro);

printf("%s %s", nomePedro,nomeAna);

}