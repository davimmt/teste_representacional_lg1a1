#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "questionario.h"
#include "teste.h"

#define MAX_NAME_SZ 256

int main() {
    char *user_credentials[64];

    printf("NOME: ");
    fgets(&user_credentials[0], MAX_NAME_SZ, stdin);

    printf("PRONTUARIO: ");
    scanf("%s", &user_credentials[54]);

    User user = __User__(&user_credentials[0], &user_credentials[54]);
    
    if(user.auth(&user) == 0) menu(user.nome, user.prontuario);
    else realizar_teste(user.nome, user.prontuario);

    system("pause");
    return 0;
};

int menu(char *user_nome, char *user_prontuario) {
    system("cls");
    char menu_choice[1];

    printf("============================================");
    printf("\n    TESTE DOS SISTEMAS REPRESENTACIONAIS    ");
    printf("\n============================================");
    printf("\n        1. Cadastrar questionario");
    printf("\n        2. Visualizar questionario");
    printf("\n        3. Realizar teste");
    printf("\n        4. Sobre o teste");
    printf("\n        F. FIM");
    printf("\n============================================");

    printf("\nEscolha: ");
    scanf("%s", menu_choice);

    if(strncmp(menu_choice, "1", 1) == 0) cadastrar_questionario();
    else if(strncmp(menu_choice, "2", 1) == 0) visualizar_questionario();
    else if(strncmp(menu_choice, "3", 1) == 0) realizar_teste(user_nome, user_prontuario);
    else if(strncmp(menu_choice, "4", 1) == 0) about(user_nome, user_prontuario);
    else if(strncmp(menu_choice, "F", 1) == 0 ||
            strncmp(menu_choice, "f", 1) == 0) exit(0);
    else {
        system("cls");
        printf("ERRO AO ESCOLHER!\n\n"); 
        system("pause");
        menu(user_nome, user_prontuario);
    }

    return 0;
}