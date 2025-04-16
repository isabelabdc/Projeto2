#include <stdio.h>
#include <string.h>
#include "projeto.h"

int main() {   
    Usuario usuarios[TOTAL_USUARIOS];
    int totalUsuarios = carregarUsuarios(usuarios);
    printf("Total de usuarios carregados: %d\n", totalUsuarios);
    Cotacoes cotacoes = { 300000.0, 15000.0, 5.0 };   //cotações iniciais
    char cpf[CPF_TAM], senha[SENHA_TAM];
    int logado = -1;
    int escolha;

     //da a opcao de fazer login ou fazer cadastro:
     printf("Bem-vindo(a)!\n");
     printf("1. Login\n");
     printf("2. Fazer Cadastro\n");
     printf("Opcao: ");
     scanf(" %d", &escolha);
 
     //cadastro:
     if (escolha == 2) {
         cadastrarUsuario(usuarios, &totalUsuarios);
         salvarUsuarios(usuarios, totalUsuarios);
         return 0;
     }
 
     //login:
     printf("Digite seu CPF: ");
     scanf(" %11s", cpf);
     printf("Digite sua senha: ");
     scanf(" %19s", senha);
 
     logado = login(usuarios, totalUsuarios, cpf, senha);
 
     if (logado == -1) {
         printf("Erro! CPF ou senha incorretos.\n");
         return 1;
     }

    //menu
    int opcao;
    printf("Ola, %s!\n", usuarios[logado].nome);
    do {
        printf("1. Consultar saldo\n");
        printf("2. Consultar extrato\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Comprar criptomoedas\n");
        printf("6. Vender criptomoedas\n");
        printf("7. Atualizar cotacoes\n");
        printf("0. Sair\n");
        scanf("%d", &opcao);

   if(opcao==0){
    salvarUsuarios(usuarios, totalUsuarios);
   } else if(opcao==1){
   
    } else if(opcao==2){
   
    } else if(opcao==3){
        
    } else if(opcao==4){
        
    } else if(opcao==5){
       
    } else if(opcao==6){
       
    } else if(opcao==7){
        
    } else {
        printf("Opcao invalida. Tente novamente!\n");
    }

} while (opcao != 0);

salvarUsuarios(usuarios, totalUsuarios);
return 0;
}
