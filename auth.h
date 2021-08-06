#include <stdio.h>
#include <string.h>

// Defina o nome do usuario admin aqui
#define AUTH "MASTER"

typedef struct User User;
struct User {
    /**
     * Variables header
     */
    char *nome, *prontuario;

    /**
     * Functions header
     */
    int (*auth)(User *user);
};

/**
 * Functions
 */
int auth(User *user) {
    if(strcasecmp(user->nome, AUTH) == 0)
       return 0;
    return 1;
}

/**
 * Constructor
 */
User __User__(char *nome, char *prontuario) {
    User user;
    user.nome = nome;
    user.prontuario = prontuario;
    user.auth = auth;
    return user;
}
