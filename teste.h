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

void realizar_teste(char *user_nome, char *user_prontuario) {
	int i;
	for(i = 0; i < 5; i++) {
		teste_header();
		printf ("\n%d. %s:\n   a) %s.\n   b) %s.\n   c) %s.\n   d) %s.",
		questionario[i].NroFrase, questionario[i].Frase, questionario[i].item_1, questionario[i].item_2, questionario[i].item_3, questionario[i].item_4);
		if (i == 0) getAnswers(answers, 0);
		if (i == 1) getAnswers(answers, 4);
		if (i == 2) getAnswers(answers, 8);
		if (i == 3) getAnswers(answers, 12);
		if (i == 4) getAnswers(answers, 16);
  	}

    sum_answers[0] = sum(answers, profile_types[0]);
    sum_answers[1] = sum(answers, profile_types[1]);
    sum_answers[2] = sum(answers, profile_types[2]);
    sum_answers[3] = sum(answers, profile_types[3]);
	
    writeResultFile(sum_answers, user_nome, user_prontuario);
	menu(user_nome, user_prontuario);
};

int getAnswers(int *answers, int index) {
	while (1) {
    	printf("\n\n[a]: ");
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
	
    profile = fopen(file_name , "w");
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
    
    system("cls"); printf("Arquivo resultado gerado com sucesso!\n\n"); sleep(1);
    system(file_name);
    
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
