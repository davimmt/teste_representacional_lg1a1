#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <conio.h>

/**
 * Variables header
 */
int *answers[20], sum_visual, sum_cinestegico, sum_auditivo, sum_digital, sum_answers[4], bigger_sum[1];
char *profile_type[1], *final_result[1];
const char *profiles[20] = {"CINESTEGICO", "AUDITIVO", "VISUAL", "DIGITAL",
                           "AUDITIVO", "VISUAL", "DIGITAL", "CINESTEGICO",
                           "VISUAL", "CINESTEGICO", "DIGITAL", "AUDITIVO",
                           "AUDITIVO", "DIGITAL", "CINESTEGICO", "VISUAL",
                           "AUDITIVO", "DIGITAL", "CINESTEGICO", "VISUAL"},
            *profile_types[4] = {"CINESTEGICO", "AUDITIVO", "VISUAL", "DIGITAL"};

/**
 * Functions header
 */
int *getAnswers(int *answers, int index);
char *getFinalResult(int *sum_answers);
int writeResultFile(int *sum_answers, char *user_nome, char *user_prontuario);
int sum(int *answers, char *profile_type);

int realizar_teste(char *user_nome, char *user_prontuario) {
    questao_1(answers);
    questao_2(answers);
    questao_3(answers);
    questao_4(answers);
    questao_5(answers);
    system("cls");

    sum_answers[0] = sum(answers, profile_types[0]);
    sum_answers[1] = sum(answers, profile_types[1]);
    sum_answers[2] = sum(answers, profile_types[2]);
    sum_answers[3] = sum(answers, profile_types[3]);

    writeResultFile(sum_answers, user_nome, user_prontuario);
    printf("Arquivo resultado gerado com sucesso!\n\n");

    return 0;
};

int *getAnswers(int *answers, int index) {
    printf("[a]: ");
    scanf("%i", &answers[index]);

    printf("[b]: ");
    scanf("%i", &answers[index + 1]);

    printf("[c]: ");
    scanf("%i", &answers[index + 2]);

    printf("[d]: ");
    scanf("%i", &answers[index + 3]);

    return *answers;
}

char *getFinalResult(int *sum_answers) {
    // Definir a maior porcentagem para o primeiro elemento
    bigger_sum[0] = sum_answers[0];

    // Definir o tipo de perfil para o primeiro elemento
    profile_type[0] = profile_types[0];

    for (int i = 0; i < 4; i++) {
        // Trocar a maior porcentagem e o tipo de perfil, caso superados
        if (bigger_sum[0] < sum_answers[i]) {
            bigger_sum[0] = sum_answers[i];
            profile_type[0] = profile_types[i];
        }
    }

    return profile_type[0];
}

int writeResultFile(int *sum_answers, char *user_nome, char *user_prontuario) {
    char file_name[64] = {};
    FILE * profile;

    // Trocar espaços por underscores, remover quebra de linha do fgets()
    for(int i = 0; i < strlen(user_nome); i++) {  
        if(user_nome[i] == ' ') user_nome[i] = '_';
        if(user_nome[i] == '\n') user_nome[i] = '\0';
    }

    strncat(file_name, "RESULTADO_", 10);
    strncat(file_name, user_nome, 20);
    strncat(file_name, "_", 1);
    strncat(file_name, user_prontuario, 20);
    strncat(file_name, ".TXT", 4);

    // Trocar underscores por espaços 
    for(int i = 0; i < strlen(user_nome); i++) {  
        if(user_nome[i] == '_') user_nome[i] = ' ';
    }

    final_result[0] = getFinalResult(sum_answers);
    profile = fopen(file_name , "a");
        fprintf(profile, "========================================== PERFIL REPRESENTACIONAL DE %s ================================================================", user_nome);
        fprintf(profile, "\n                   %d%% %s            %d%% %s            %d%% %s               %d%% %s", 
            sum_answers[0], profile_types[0],
            sum_answers[1], profile_types[1],
            sum_answers[2], profile_types[2],
            sum_answers[3], profile_types[3]);
        fprintf(profile, "\n=============================================================================================================================================");
        fprintf(profile, "\nAlgumas pessoas captam melhor as mensagens do mundo exterior atraves da audicao, sao as pessoas chamadas auditivas.");
        fprintf(profile, "\nOutras pessoas sentem necessidade de perguntar muito, necessitem de muitas informacoes e fatos. Estas sao as digitais.");
        fprintf(profile, "\nAs cinestesicas aprendem melhor por meio das sensacoes tateis, como o tato, a temperatura, a umidade, as sensacoes internas e as emocoes.");
        fprintf(profile, "\nJa as pessoas visuais aprendem melhor quando se valendo da visao.");
        fprintf(profile, "\n=============================================================================================================================================");
        fprintf(profile, "\nSeu perfil: %s", final_result[0]);
        fprintf(profile, "\n=============================================================================================================================================\n\n");
    fclose(profile);

    return 0;
}

int sum(int *answers, char *profile_type) {
    int sum;
    sum = 0;
    for(int i = 0; i < 20; i++) {
        if (strncmp(profiles[i], profile_type, 6) == 0) {
            sum += answers[i];
        }
    }

    return sum;
}

int about(char *user_nome, char *user_prontuario) {
    system("cls");

    FILE * about;
    about = fopen("REFERENCIAL_TEORICO.TXT", "r");
        char about_txt;
        do {
            about_txt = getc(about);
            printf("%c", about_txt);
        } while(about_txt != EOF);
	fclose(about);
    printf("\n\n");

    system("pause");
    menu(user_nome, user_prontuario);

    return 0;
}

int teste_header() {
    system("cls");
    printf("Nas frases a seguir, pontue com:\n\
            4 a que melhor descreve voce;\n\
            3 a proxima melhor descricao;\n\
            2 a proxima melhor; e\n\
            1 aquela que menos descreve voce.\n");

    return 0;
}

int questao_1(int *answers) {
    teste_header();
    printf("\n1. Eu tomo decisoes importantes baseado em:\n\
            a) intuicao.\n\
            b) o que me soa melhor.\n\
            c) o que me parece melhor.\n\
            d) um estudo preciso e minucioso do assunto.\n\n");
    getAnswers(answers, 0);

    return 0;
}

int questao_2(int *answers) {
    teste_header();
    printf("\n2. Durante uma discussao eu sou mais influenciado por:\n\
            a) o tom da voz da outra pessoa.\n\
            b) se eu posso ou nao ver o argumento da outra pessoa.\n\
            c) a logica do argumento da outra pessoa.\n\
            d) se eu entro em contato ou nao com os sentimentos reais do outro.\n\n");
    getAnswers(answers, 4);

    return 0;
}

int questao_3(int *answers) {
    teste_header();
    printf("\n3. Eu comunico mais facilmente o que se passa comigo:\n\
            a) do modo como me visto e aparento.\n\
            b) pelos sentimentos que compartilho.\n\
            c) pelas palavras que escolho.\n\
            d) pelo tom da minha voz.\n\n");
    getAnswers(answers, 8);

    return 0;
}

int questao_4(int *answers) {
    teste_header();
    printf("\n4. Muito facil para mim:\n\
            a) achar o volume e a sintonia ideais num sistema de som.\n\
            b) selecionar o ponto mais relevante relativo a um assunto interessante.\n\
            c) escolher os moveis mais confortaveis.\n\
            d) escolher as combinacoes de cores mais ricas e atraentes.\n\n");
    getAnswers(answers, 12);

    return 0;
}

int questao_5(int *answers) {
    teste_header();
    printf("\n5. Eu me percebo assim:\n\
            a) se estou muito em sintonia com os sons dos ambientes.\n\
            b) se sou muito capaz de raciocinar com fatos e dados novos.\n\
            c) eu sou muito sensivel ao jeito como a roupa veste o meu corpo.\n\
            d) eu respondo fortemente ao coloramento e ao visual de uma sala.\n\n");
    getAnswers(answers, 16);

    return 0;
}