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
        fclose(fp);
    }
    return total;
}