#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "projeto.h"

//EXTRATO:
//funcao para obter a data e hora atual:
DataHora data() {
    DataHora data;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    data.dia = tm_info->tm_mday;
    data.mes = tm_info->tm_mon + 1;
    data.ano = tm_info->tm_year + 1900;
    data.hora = tm_info->tm_hour;
    data.minuto = tm_info->tm_min;
    data.segundo = tm_info->tm_sec;
    return data;
}

//funcao que salva o extrato em arquivo binario:
void salvarExtrato(Usuario *usuario) {
    char nomeArquivo[100];
    sprintf(nomeArquivo, "extrato_%s.bin", usuario->cpf);

    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao salvar extrato!\n");
        return;
    }
    fwrite(&usuario->totalTransacoes, sizeof(int), 1, arquivo);
    fwrite(usuario->transacoes, sizeof(Extrato), usuario->totalTransacoes, arquivo);
    fclose(arquivo);
}

//funcao que carrega o extrato:
void carregarExtrato(Usuario *usuario) {
    char nomeArquivo[100];
    sprintf(nomeArquivo, "extrato_%s.bin", usuario->cpf);

    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        usuario->totalTransacoes = 0;
        return; 
    }
    fread(&usuario->totalTransacoes, sizeof(int), 1, arquivo);
    fread(usuario->transacoes, sizeof(Extrato), usuario->totalTransacoes, arquivo);
    fclose(arquivo);
}

//DADOS DE USUARIOS:
//funcao para salvar dados de usuarios no arquivo
void salvarUsuarios(Usuario usuarios[], int total) {
    FILE *fp = fopen("usuarios.dat", "wb");
    if (fp) {
        fwrite(&total, sizeof(int), 1, fp);
        fwrite(usuarios, sizeof(Usuario), total, fp);
        fclose(fp);
    } else {
        printf("Erro ao salvar arquivo de usuarios!\n");
    }
}

//funcao que carrega dados do usuario no arquivo
int carregarUsuarios(Usuario usuarios[]) {
    FILE *fp = fopen("usuarios.dat", "rb");
    int total = 0;
    if (fp) {
        fread(&total, sizeof(int), 1, fp);
        fread(usuarios, sizeof(Usuario), total, fp);
        //carrega o extrato:
        for (int i = 0; i < total; i++) {
            carregarExtrato(&usuarios[i]);
        }
        fclose(fp);
    }
    return total;
}

//LOGIN
//funcao para realizacao do login
int login(Usuario usuarios[], int total, char *cpf, char *senha) {
    for (int i = 0; i < total; i++) {
        if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return i;
        }
    }
    return -1;
}

//CADASTRO
//funcao para realizacao de cadastro 
int cadastrarUsuario(Usuario usuarios[], int *total) {
    if (*total >= TOTAL_USUARIOS) {
        printf("Limite de usuarios atingido!\n");
        return -1;
    }

    Usuario novo = {0};

    printf("Digite seu CPF: ");
    scanf(" %11s", novo.cpf);

    for (int i = 0; i < *total; i++) {
        if (strcmp(usuarios[i].cpf, novo.cpf) == 0) {
            printf("Usuario com este CPF ja está cadastrado.\n");
            return -1;
        }
    }
    
    printf("Digite seu primeiro nome: ");
    scanf(" %49s", novo.nome);

    printf("Digite sua senha: ");
    scanf(" %19s", novo.senha);

    novo.reais = 0.0;
    novo.bitcoin = 0.0;
    novo.ethereum = 0.0;
    novo.ripple = 0.0;
    novo.totalTransacoes = 0;

    usuarios[*total] = novo;
    (*total)++;

    printf("Cadastro realizado com sucesso!\n");
    return 0;
}

//FUNCIONALIDADES:
//funcao depositar
void depositar(Usuario *usuario) {
    float valor;
    printf("Digite o valor a ser depositado R$ ");
    scanf(" %f", &valor);

    if (valor <= 0) {
        printf("Valor invalido!\n");
        return;
    }

    usuario->reais += valor;

    //registra no extrato:
    if (usuario->totalTransacoes < TOTAL_TRANSACOES) {
        Extrato *transacao = &usuario->transacoes[usuario->totalTransacoes++];
        strcpy(transacao->operacao, "Deposito");
        strcpy(transacao->moeda, "R$");
        transacao->valor = valor;
        transacao->taxa = 0.0;
        transacao->data = data();
    }
    salvarExtrato(usuario);
    printf("Deposito realizado com sucesso!\n");
}

//funcao sacar
void sacar(Usuario *usuario) {
    float valor;
    char senhaDigitada[SENHA_TAM];

    printf("Digite o valor a ser sacado R$ ");
    scanf(" %f", &valor);

    if (valor <= 0 || valor > usuario->reais) {
        printf("Valor invalido ou saldo insuficiente!\n");
        return;
    }

    printf("Confirme sua senha: ");
    scanf(" %19s", senhaDigitada);

    if (strcmp(usuario->senha, senhaDigitada) != 0) {
        printf("Senha incorreta. Saque cancelado!\n");
        return;
    }

    usuario->reais -= valor;

    //registra no extrato:
    if (usuario->totalTransacoes < TOTAL_TRANSACOES) {
        Extrato *transacao = &usuario->transacoes[usuario->totalTransacoes++];
        strcpy(transacao->operacao, "Saque");
        strcpy(transacao->moeda, "R$");
        transacao->valor = valor;
        transacao->taxa = 0.0;
        transacao->data = data();
    }
    salvarExtrato(usuario);
    printf("Saque realizado com sucesso!\n");
}