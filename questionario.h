#include <stdio.h>
#include <conio.h>
#include <locale.h>

typedef struct Questionario Questionario;
struct Questionario {
    int NroFrase;
    char Frase[100];
    int cinestesico;
    char item_1[100];
    int auditivo;
    char item_2[100];
    int visual;
    char item_3[100];
    int digital;
    char item_4[100];
};

Questionario questionario[5] = {
	{1, "Eu tomo decisoes importantes baseado em", 0, "intuicao", 0, "o que me soa melhor", 0, "o que me parece melhor", 0, "um estudo preciso e minucioso do assunto"},
	{2, "Durante uma discussao eu sou mais influenciado por", 0, "o tom da voz da outra pessoa", 0, "se eu posso ou nao ver o argumento da outra pessoa", 0, "a logica do argumento da outra pessoa", 0, "se eu entro em contato ou nao com os sentimentos reais do outro"},
	{3, "Eu comunico mais facilmente o que se passa comigo", 0, "do modo como me visto e aparento", 0, "pelos sentimentos que compartilho", 0, "pelas palavras que escolho", 0, "pelo tom da minha voz"},
	{4, "Muito facil para mim", 0, "achar o volume e a sintonia ideais num sistema de som", 0, "selecionar o ponto mais relevante relativo a um assunto interessante", 0, "escolher os moveis mais confortaveis", 0, "escolher as combinacoes de cores mais ricas e atraentes"},
	{5, "Eu me percebo assim", 0, "se estou muito em sintonia com os sons dos ambientes", 0, "se sou muito capaz de raciocinar com fatos e dados novos", 0, "eu sou muito sensivel ao jeito como a roupa veste o meu corpo", 0, "eu respondo fortemente ao coloramento e ao visual de uma sala"}
};

void cadastrar_questionario(char *user_nome, char *user_prontuario) {
    int i;
	char ARQUIVODAT[50] = "TESTE_SISTEMA_REPRESENTACIONAL.DAT";
	
	FILE *Arq = fopen (ARQUIVODAT,"w");	
	if (Arq == NULL) {
		printf ("\nErro ao abrir arquivo %s!", ARQUIVODAT);
		getch();
		exit(0);
	}
	for (i = 0; i < 5; i++) {
	fwrite (&questionario[i], sizeof(questionario[i]), 1, Arq);
		if (ferror(Arq)) {
		  printf ("\nErro ao gravar no arquivo %s!", ARQUIVODAT);
		  getch();
		  exit(0);
		}
	}
	fclose(Arq);
	system("cls"); printf("\nArquivo gerado!"); sleep(1);
	menu(user_nome, user_prontuario);
};

void visualizar_questionario(char *user_nome, char *user_prontuario) {
	char ARQUIVODAT[50] = "TESTE_SISTEMA_REPRESENTACIONAL.DAT", ARQUIVOTXT[50] = "QUESTIONARIO_1.TXT";
	FILE * input;
	FILE * visualizar;
	int i;
	fflush(stdin);
    input = fopen(ARQUIVODAT, "r"); visualizar = fopen(ARQUIVOTXT, "w");
	    fprintf(visualizar ,"%s %53s %5s %-60s %5s %-70s %5s %-65s %5s %-60s", "NroFrase", "Frase", "C", "Item 1", "A", "Item 2", "V", "Item 3", "D", "Item 4");
	    fprintf(visualizar ,"\n"); for(i = 0; i < 350; i++) fprintf(visualizar ,"=");
	    i = 0;
	    while(!feof(input)) {
	        i++;
	        fread(&questionario[i], sizeof(questionario[i]), 1, input);
	        if (questionario[i].NroFrase > 0) fprintf(visualizar ,"\n%d %60s %5d %-60s %5d %-70s %5d %-65s %5d %s", 
				questionario[i].NroFrase, questionario[i].Frase, questionario[i].cinestesico, questionario[i].item_1, questionario[i].auditivo, 
				questionario[i].item_2, questionario[i].visual, questionario[i].item_3, questionario[i].digital, questionario[i].item_4);
	    }
	    fprintf(visualizar ,"\n"); for(i = 0; i < 350; i++) fprintf(visualizar ,"=");
    fclose(input); fclose(visualizar);
    system(ARQUIVOTXT);
    menu(user_nome, user_prontuario);
};

void about(char *user_nome, char *user_prontuario) {
    system("cls");
	setlocale (LC_ALL, "");
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
}

void teste_header() {
    system("cls");
    printf("Nas frases a seguir, pontue com:\n\
            4 a que melhor descreve voce;\n\
            3 a proxima melhor descricao;\n\
            2 a proxima melhor; e\n\
            1 aquela que menos descreve voce.\n");
}
