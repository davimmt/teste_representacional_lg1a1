#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <conio.h>

/**
 * Variables header
 */
int *answers[20], sum_visual, sum_cinestegico, sum_auditivo, sum_digital, bigger_sum;
float sum_answers[4];
char profile_type[20], final_result[20];
const char *profiles[20] = {"CINESTEGICO", "AUDITIVO", "VISUAL", "DIGITAL",
	                       "AUDITIVO", "VISUAL", "DIGITAL", "CINESTEGICO",
	                       "VISUAL", "CINESTEGICO", "DIGITAL", "AUDITIVO",
	                       "AUDITIVO", "DIGITAL", "CINESTEGICO", "VISUAL",
	                       "AUDITIVO", "DIGITAL", "CINESTEGICO", "VISUAL"},
    		*profile_types[4] = {"CINESTEGICO", "AUDITIVO", "VISUAL", "DIGITAL"};

/**
 * Functions header
 */
int getAnswers(int *answers, int index);
char *getFinalResult(float *sum_answers);
int writeResultFile(float *sum_answers, char *user_nome, char *user_prontuario);
int sum(int *answers, char *profile_type);
int questao_1();
int questao_2();
int questao_3();
int questao_4();
int questao_5();

int realizar_teste(char *user_nome, char *user_prontuario) {
    questao_1();
    questao_2();
    questao_3();
    questao_4();
    questao_5();
    system("cls");
	
    sum_answers[0] = sum(answers, profile_types[0]);
    sum_answers[1] = sum(answers, profile_types[1]);
    sum_answers[2] = sum(answers, profile_types[2]);
    sum_answers[3] = sum(answers, profile_types[3]);
	
    writeResultFile(sum_answers, user_nome, user_prontuario);
    printf("Arquivo resultado gerado com sucesso!\n\n");
	system("pause");
	
    return 0;
};

int getAnswers(int *answers, int index) {
	while (1) {
    	printf("[a]: ");
    	scanf("%i", &answers[index]);

    	if (answers[index] >= 1 && answers[index] <= 4) break;
    	else printf("\nSelecione um valor entre 1 e 4.\n\n");
	}
	
	while (1) {
    	printf("[b]: ");
    	scanf("%i", &answers[index + 1]);

    	if (!(answers[index + 1] >= 1 && answers[index + 1] <= 4)) {
    		printf("\nSelecione um valor entre 1 e 4.\n\n");
    		continue;
		}

    	if (answers[index + 1] == answers[index]) printf("\nSelecione um valor nao escolhido.\n\n");
    	else break;
	}

    while (1) {
    	printf("[c]: ");
    	scanf("%i", &answers[index + 2]);

    	if (!(answers[index + 2] >= 1 && answers[index + 2] <= 4)) {
    		printf("\nSelecione um valor entre 1 e 4.\n\n");
    		continue;
		}

    	if (answers[index + 2] == answers[index] || answers[index + 2] == answers[index + 1]) printf("\nSelecione um valor nao escolhido.\n\n");
    	else break;
	}
	
	while (1) {
    	printf("[d]: ");
    	scanf("%i", &answers[index + 3]);

    	if (!(answers[index + 3] >= 1 && answers[index + 3] <= 4)) {
    		printf("\nSelecione um valor entre 1 e 4.\n\n");
    		continue;
		}

    	if (answers[index + 3] == answers[index] || answers[index + 3] == answers[index + 1] || answers[index + 3] == answers[index + 2]) printf("\nSelecione um valor nao escolhido.\n\n");
    	else break;
	}
	
    return answers;
}

int sum(int *answers, char *profile_type) {
    int sum, i;
    sum = 0;
    for(i = 0; i < 20; i++) {
        if (strncmp(profiles[i], profile_type, 6) == 0) {
            sum += answers[i];
        }
    }

    return sum;
}

int writeResultFile(float *sum_answers, char *user_nome, char *user_prontuario) {
    char file_name[64] = {};
    FILE * profile;
    
    int i;
    for(i = 0; i < strlen(user_nome); i++) if(user_nome[i] == ' ') user_nome[i] = '_';

    strncat(file_name, "RESULTADO_", 10);
    strncat(file_name, user_nome, 20);
    strncat(file_name, "_", 1);
    strncat(file_name, user_prontuario, 20);
    strncat(file_name, ".TXT", 4);

    for(i = 0; i < strlen(user_nome); i++) {
    	if(user_nome[i] == '_') user_nome[i] = ' ';
	}

    strcpy(final_result, getFinalResult(sum_answers));
	
    profile = fopen(file_name , "a");
        fprintf(profile, "========================================== PERFIL REPRESENTACIONAL DE %s ================================================================", user_nome);
        fprintf(profile, "\n                   %.0f%% %s            %.0f%% %s            %.0f%% %s               %.0f%% %s", 
        ((sum_answers[0] / 50) * 100), profile_types[0],
        ((sum_answers[1] / 50) * 100), profile_types[1],
        ((sum_answers[2] / 50) * 100), profile_types[2],
        ((sum_answers[3] / 50) * 100), profile_types[3]);
        fprintf(profile, "\n=============================================================================================================================================");
        fprintf(profile, "\nAlgumas pessoas captam melhor as mensagens do mundo exterior atraves da audicao, sao as pessoas chamadas auditivas.");
        fprintf(profile, "\nOutras pessoas sentem necessidade de perguntar muito, necessitem de muitas informacoes e fatos. Estas sao as digitais.");
        fprintf(profile, "\nAs cinestesicas aprendem melhor por meio das sensacoes tateis, como o tato, a temperatura, a umidade, as sensacoes internas e as emocoes.");
        fprintf(profile, "\nJa as pessoas visuais aprendem melhor quando se valendo da visao.");
        fprintf(profile, "\n=============================================================================================================================================");
        fprintf(profile, "\nSeu perfil: %s", final_result);
        fprintf(profile, "\n=============================================================================================================================================\n\n");
    fclose(profile);
    
    return 0;
}

char *getFinalResult(float *sum_answers) {
	int i;
	char separator[3] = " & ";
	// Definir o tipo de perfil para o primeiro elemento
    strcpy(profile_type, "CINESTEGICO");
    
    // Definir a maior porcentagem para o minimo possivel
    bigger_sum = 1;

    for (i = 0; i < 4; i++) {
        // Trocar a maior porcentagem e o tipo de perfil, caso superados
        if (bigger_sum < sum_answers[i]) {
            bigger_sum = sum_answers[i];
            strcpy(profile_type, profile_types[i]);
        }
        else if (bigger_sum == sum_answers[i] && strncmp(profile_type, profile_types[i], 1)) { // Caso de dois valores iguais
            strcat(profile_type, strcat(separator, profile_types[i]));
        }
    }

    return profile_type;
}

int about(char user_nome, char user_prontuario) {
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

int questao_1() {
    teste_header();
    printf("\n1. Eu tomo decisoes importantes baseado em:\n\
            a) intuicao.\n\
            b) o que me soa melhor.\n\
            c) o que me parece melhor.\n\
            d) um estudo preciso e minucioso do assunto.\n\n");
    getAnswers(answers, 0);

    return 0;
}

int questao_2() {
    teste_header();
    printf("\n2. Durante uma discussao eu sou mais influenciado por:\n\
            a) o tom da voz da outra pessoa.\n\
            b) se eu posso ou nao ver o argumento da outra pessoa.\n\
            c) a logica do argumento da outra pessoa.\n\
            d) se eu entro em contato ou nao com os sentimentos reais do outro.\n\n");
    getAnswers(answers, 4);

    return 0;
}

int questao_3() {
    teste_header();
    printf("\n3. Eu comunico mais facilmente o que se passa comigo:\n\
            a) do modo como me visto e aparento.\n\
            b) pelos sentimentos que compartilho.\n\
            c) pelas palavras que escolho.\n\
            d) pelo tom da minha voz.\n\n");
    getAnswers(answers, 8);

    return 0;
}

int questao_4() {
    teste_header();
    printf("\n4. Muito facil para mim:\n\
            a) achar o volume e a sintonia ideais num sistema de som.\n\
            b) selecionar o ponto mais relevante relativo a um assunto interessante.\n\
            c) escolher os moveis mais confortaveis.\n\
            d) escolher as combinacoes de cores mais ricas e atraentes.\n\n");
    getAnswers(answers, 12);

    return 0;
}

int questao_5() {
    teste_header();
    printf("\n5. Eu me percebo assim:\n\
            a) se estou muito em sintonia com os sons dos ambientes.\n\
            b) se sou muito capaz de raciocinar com fatos e dados novos.\n\
            c) eu sou muito sensivel ao jeito como a roupa veste o meu corpo.\n\
            d) eu respondo fortemente ao coloramento e ao visual de uma sala.\n\n");
    getAnswers(answers, 16);

    return 0;
}
