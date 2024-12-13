//
// Created by nesto on 27/10/2024.
//
#include "user.h"
// #include <file.h>
#include "auxiliar.h"

int addUser(DataUsers* d, User newUser) {
    int error = 0;
    // Intenta reasignar memoria para el nuevo usuario
    User* aux = NULL;
    aux = realloc(d->user, (d->n_users + 1) * sizeof(User));

    // Si realloc falla, retorna error sin perder el puntero original
    if (aux == NULL) {
        printf("(ERROR) Memory allocation failed.\n");
        error = 1;
    } else {
        // Si realloc tiene éxito, actualiza el puntero y el número de usuarios
        d->user = aux;
        d->user[d->n_users] = newUser;
        d->n_users++;
    }

    return error;
}


DataUsers removeUser(DataUsers d, int index){
    if(d.n_users < 1){
        printf("Memory is already empty");
    }else{
        memmove(&d.user[index], &d.user[index+1], (d.n_users-(index+1))* sizeof(User));
        User* aux = realloc(d.user, (d.n_users-1)*sizeof(User));
        if(aux == NULL){
            printf("Memory error");
        }else{
            d.user = aux;
            d.n_users--;
        }
    }
    return d;
}


int checkComma(String str){
    int error = 0;
    if(strstr(str, ",")){
        printf("(ERROR) Field cannot contain ','\n");
        error = 1;
    }
    return error;
}

DataUsers registerUser(DataUsers d){
    User newUser;
    int error = 0;
    char aux;

    printf("Enter your name: \n");
    fgets(newUser.name, 50, stdin);
    deleteLinespace(newUser.name);
    error = checkComma(newUser.name);
    printf("Enter your mail: \n");
    fgets(newUser.email, 50, stdin);
    deleteLinespace(newUser.email);
    if(!error) {
        for (int i = 0; i < d.n_users; i++) {
            if (strcmp(newUser.email, d.user[i].email) == 0) {
                error = 1;
                printf("(ERROR) Email already registered\n");
            }
        }
        if (!strstr(newUser.email, "@")) {
            printf("(ERROR) Email must contain '@'\n");
            error = 1;
        }
        if(!error){
            error = checkComma(newUser.email);
        }
    }
    if(!error){
        printf("Enter your password: \n");
        fgets(newUser.password, 50, stdin);
        deleteLinespace(newUser.password);
        if(strlen(newUser.password) < 8){
            error = 1;
            printf("(ERROR) Password must be at least 8 characters\n");
        }
        if(!error) {
            error = checkComma(newUser.password);
        }
        if(!error){
            printf("Enter your rol: \n");
            scanf("%c", &newUser.rol);
            scanf("%c", &aux);
            newUser.rol = toupper(newUser.rol);
            if(newUser.rol != 'C' && newUser.rol != 'A' && newUser.rol != 'R'){
                printf("(ERROR) This rol does not exist\n");
                error = 1;
            }else{
                if(newUser.rol == 'A'){
                    printf("Enter your PIN: \n");
                    scanf("%s", newUser.pin);
                    scanf("%c", &aux);
                    for(int i = 0; i < strlen(newUser.pin); i++){
                        if(!isdigit(newUser.pin[i])){
                            error = 1;
                        }
                    }
                    if(error){
                        printf("(ERROR) PIN must contain only numeric values\n");
                    }
                    if(strlen(newUser.pin) != 4 && !error){
                        printf("(ERROR) PIN must be 4 numbers\n");
                        error = 1;
                    }
                }else{
                    strcpy(newUser.pin, "----");
                }
                if(!error){
                    if(d.n_users == 0){
                        newUser.id = 1;
                    }else{
                        newUser.id = d.user[d.n_users-1].id + 1;
                    }
                    error = addUser(&d, newUser);
                    if(!error) {
                        printf("Register successful with ID: %d!\n", newUser.id);
                    }
                }
            }
        }
    }
    return d;
}

DataUsers createReasercher(DataUsers d){
    User newUser;
    int error = 0;

    printf("Enter your name: ");
    fgets(newUser.name, 50, stdin);
    deleteLinespace(newUser.name);
    error = checkComma(newUser.name);
    printf("Enter your mail: ");
    fgets(newUser.email, 150, stdin);
    deleteLinespace(newUser.email);
    if(error) {
        for (int i = 0; i < d.n_users; i++) {
            if (strcmp(newUser.email, d.user[i].email) == 0) {
                error = 1;
                printf("(ERROR) Email already registered\n");
            }
        }
        if (!strstr(newUser.email, "@")) {
            printf("(ERROR) Email must contain '@'\n");
            error = 1;
        }else {
            error = checkComma(newUser.email);
        }
    }else {
        printf("Enter your password: ");
        fgets(newUser.password, 50, stdin);
        deleteLinespace(newUser.password);
        if(strlen(newUser.password) < 8){
            error = 1;
            printf("(ERROR) Password must be at least 8 characters\n");
        }else if (checkComma(newUser.password)){
            printf("(ERROR) Password mustn't have coma\n");
        }else {
            newUser.rol = 'R';
            newUser.id = (d.n_users == 0) ? 1 : d.user[d.n_users - 1].id + 1;
            strcpy(newUser.pin, "----");

            error = addUser(&d, newUser);
            if(!error) {
                printf("Register successful!\n");
                // saveUsersToFile(d);
            }
        }
    }

    return d;
}

void showClientData(DataUsers data) {
    int num_clients = 0;

    for (int i = 0; i < data.n_users; i++) {
        if (data.user[i].rol == 'C') {
            num_clients++;
        }
    }

    printf("\nTotal number of clients: %d\n", num_clients);
    if (num_clients == 0) {
        printf("No clients found.\n");
    } else {
        for (int i = 0; i < data.n_users; i++) {
            if (data.user[i].rol == 'C') {
                printf("Client %d:\n", i + 1);
                printf("\tName: %s\n", data.user[i].name);
                printf("\tID: %d\n", data.user[i].id);
                printf("\tEmail: %s\n", data.user[i].email);
                printf("\n");
            }
        }
    }
}


int logIn(DataUsers data){
    String username;
    String password;
    int found=0,index=-1;
    char aux;

    printf("Enter your email: ");
    scanf("%s",username);
    scanf("%c",&aux);
    printf("Enter your password: ");
    scanf("%s",password);
    scanf("%c",&aux);

    for(int i=0; i<data.n_users; i++){
        if(!strcmp(data.user[i].email,username) && !strcmp(data.user[i].password,password)){
            found=1;
            index=i;
            if(data.user[i].rol=='A'){
                printf("Enter your PIN: ");
                String pin;
                fgets(pin,50,stdin);
                deleteLinespace(pin);
                if(strcmp(data.user[i].pin,pin) == 0){
                    found=1;
                }else{
                    found=0;
                    index=-1;
                }
            }
        }
    }
    if(found==1){
        printf("\nLog In successful\n");
    }else{
        printf("\n(ERROR) wrong email or password\n");
    }
    return index;
}

int findUserByMail(DataUsers d) {
    String mail;
    int index = 0;
    int found = 0;

    printf("Enter mail of the user: ");
    fgets(mail, 50, stdin);
    mail[strlen(mail)-1]='\0';

    for(int i = 0; i < d.n_users && !found; i++) {
        if(!strcmp(mail, d.user[i].email)) {
            index = i;
            found = 1;
        }
    }
    if (!found) {
        index = -1;
    }
    return index;
}

DataUsers removeClient(DataUsers d) {
    int index = findUserByMail(d);
    if (index == -1) {
        printf("(ERROR) Client not found.\n");
    } else {
        if (d.user[index].rol == 'C') {
            d = removeUser(d, index);
            printf("Client deleted.\n");
        } else {
            printf("(ERROR) The user is not a client.\n");
        }
    }
    return d;
}

DataUsers removeResearcher(DataUsers d) {
    int index = findUserByMail(d);
    if (index == -1) {
        printf("ERROR: Reasercher not found\n");
    } else {
        if (d.user[index].rol == 'R') {
            removeUser(d, index);
            printf("Reasercher deleted\n");
        } else {
            printf("ERROR: The user is not a reasercher\n");
        }
    }
    return d;
}

User findReasercher(DataUsers d) {
    int index = findUserByMail(d);
    if (index == -1) {
        printf("ERROR: Reasercher not found\n");
    }
    return d.user[index];
}

void printUsers(DataUsers d) {
    for (int i = 0; i < d.n_users; i++) {
        printf("User %d:\n\tName: %s\n\tEmail: %s\n\tRol: %c\n", i + 1, d.user[i].name, d.user[i].email, d.user[i].rol);
    }
}

DataUsers modifyResearcher(DataUsers d) {
    int user_index = findUserByMail(d);
    if (user_index == -1) {
        printf("ERROR: Researcher not found\n");
    } else {
        if (d.user[user_index].rol != 'R') {
            printf("ERROR: The user is not a researcher\n");
        } else {
            int option;
            do {
                showResearcherModifications();
                printf("Choose an option: ");
                scanf("%d", &option);
                getchar(); // Limpia el buffer después de scanf

                switch (option) {
                    case 1: {
                        printf("Enter name: ");
                        fgets(d.user[user_index].name, sizeof(d.user[user_index].name), stdin);
                        deleteLinespace(d.user[user_index].name); // Elimina saltos de línea
                        break;
                    }
                    case 2: {
                        printf("Enter email: ");
                        fgets(d.user[user_index].email, sizeof(d.user[user_index].email), stdin);
                        deleteLinespace(d.user[user_index].email);

                        if (!strstr(d.user[user_index].email, "@")) {
                            printf("ERROR: Invalid email format\n");
                        }
                        break;
                    }
                    case 3: {
                        printf("Enter password: ");
                        fgets(d.user[user_index].password, sizeof(d.user[user_index].password), stdin);
                        deleteLinespace(d.user[user_index].password);

                        if (strlen(d.user[user_index].password) < 8) {
                            printf("ERROR: Password must be at least 8 characters long\n");
                        }
                        break;
                    }
                    case 4: {
                        printf("Enter PIN: ");
                        fgets(d.user[user_index].pin, sizeof(d.user[user_index].pin), stdin);
                        deleteLinespace(d.user[user_index].pin);

                        break;
                    }
                    case 5: {
                        printf("Enter rol (C: Customer, A: Admin, R: Researcher): ");
                        char character;
                        scanf(" %c", &character);
                        getchar(); // Limpia el buffer después de leer un carácter
                        character = toupper(character);

                        if (character != 'C' && character != 'A' && character != 'R') {
                            printf("ERROR: Invalid role\n");
                        } else {
                            d.user[user_index].rol = character;
                        }
                        break;
                    }
                    case 6:
                        printf("Researcher modified successfully!\n");
                        break;
                    default:
                        printf("ERROR: Invalid option\n");
                        break;
                }
            } while (option != 6);
        }
    }

    // saveUsersToFile(d); // Guarda los cambios en el archivo
    return d;
}

void showResearcherModifications() {
    printf("\nWhat attribute you want to change?\n");
    printf("\t1. Enter New Research name\n");
    printf("\t2. Enter New Research email\n");
    printf("\t3. Enter New Research password\n");
    printf("\t4. Enter New Research pin\n");
    printf("\t5. Enter New Reaserch rol\n");
    printf("\t6. Exit\n");
}

User createEmptyUser() {
    User emptyUser = { .id = -1, .name = "", .email = "", .password = "", .pin = "", .rol = '\0' };
    return emptyUser;
}

User* searchResearcherById(DataUsers d, int id) {
    for (int i = 0; i < d.n_users; i++) {
        if (d.user[i].id == id && d.user[i].rol == 'R') {
            return &d.user[i];
        }
    }
    printf("ERROR: Researcher with ID %d not found.\n", id);
    return NULL;
}

User* searchResearcherByName(DataUsers d, String name) {
    for (int i = 0; i < d.n_users; i++) {
        if (d.user[i].rol == 'R' && strstr(d.user[i].name, name) != NULL) {
            return &d.user[i];
        }
    }
    printf("ERROR: Researcher with name '%s' not found.\n", name);
    return NULL;
}

User* searchResearcherByEmail(DataUsers d, String email) {
    for (int i = 0; i < d.n_users; i++) {
        if (strcmp(d.user[i].email, email) == 0 && d.user[i].rol == 'R') {
            return &d.user[i];
        }
    }
    printf("ERROR: Researcher with email '%s' not found.\n", email);
    return NULL;
}

void showResearcherSearch() {
    printf("\nHow do you want to search the researcher?\n");
    printf("\t1. Search by id\n");
    printf("\t2. Search by name\n");
    printf("\t3. Search by email\n");
    printf("\t4. Exit\n");
}

User* searchResearcher(DataUsers d) {
    int option;
    char trash;
    do {
        showResearcherSearch();
        printf("\nChoose an option: ");
        scanf("%d", &option);
        scanf("%c", &trash);
        switch (option) {
            case 1: {
                int id;
                printf("\nEnter the researcher ID: ");
                scanf("%d", &id);
                scanf("%c", &trash); // Limpia el buffer
                return searchResearcherById(d, id);
            }
            case 2: {
                String name;
                printf("\nEnter the researcher name: ");
                fgets(name, sizeof(name), stdin);
                deleteLinespace(name);
                return searchResearcherByName(d, name);
            }
            case 3: {
                String email;
                printf("\nEnter the researcher email: ");
                scanf("%s", email);
                return searchResearcherByEmail(d, email);;
            }
            case 4:
                printf("Exiting researcher search.\n");
                return NULL;
            default:
                printf("ERROR: Invalid option.\n");
                return NULL;
        }
    } while (option != 4);

    return NULL;
}

DataUsers initializeData() {
    DataUsers d;
    d.n_users = 0;
    d.user = NULL;
    return d;
}

DataUsers* listResearchers(DataUsers d) {
    DataUsers* result = (DataUsers*)malloc(sizeof(DataUsers));
    *result = initializeData();

    int j = 0;
    for(int i = 0; i < d.n_users; i++) {
        if(d.user[i].rol == 'R') {
            addUser(result, d.user[i]);
            j++;
        }
    }

    return result;
}

void showResearchers(DataUsers d) {
    DataUsers* result = listResearchers(d);

    if (result->n_users > 0) {
        for(int i = 0; i < result->n_users; i++) {
            printf("\nResearcher %d:\n", i + 1);
            printf("\tID: %d\n", result->user[i].id);
            printf("\tNombre: %s\n", result->user[i].name);
            printf("\tEmail: %s\n", result->user[i].email);
            printf("\tRol: %c\n", result->user[i].rol);
        }
    } else {
        printf("No researchers found\n");
    }
    free(result);
}

DataUsers modifyDataClient(DataUsers data){
    int error = 0, i = 0, option = 0;
    char basura;

    showClientData(data);
    printf("\nChoose the client you want to modify the information of\n");
    i = findUserByMail(data);

    if(i >= 0 && data.user[i].rol == 'C'){
        while(option != 4){
            printf("1. Modify name\n2. Modify email\n3. Modify password\n4. Stop modifying\n\nChoose an option: ");
            scanf("%d", &option);
            scanf("%c", &basura);
            printf("\n");

            switch(option){
                case 1:
                    printf("Actual name: %s\nNew name: ", data.user[i].name);
                    fgets(data.user[i].name, sizeof(data.user[i].name), stdin);
                    deleteLinespace(data.user[i].name);
                    printf("\n");
                    break;
                case 2:
                    printf("Actual email: %s\nNew email: ", data.user[i].email);
                    scanf("%s", data.user[i].email);
                    printf("\n");
                    break;
                case 3:
                    printf("Actual password: %s\nNew password: ", data.user[i].password);
                    scanf("%s", data.user[i].password);
                    printf("\n");
                    break;
                case 4:
                    printf("See you in the next modification\n\n");
                    break;
                default:
                    printf("(ERROR) Invalid option!\n\n");
                    break;
            }
        }
    }else{
        printf("(ERROR) Client not found\n");
    }

    return data;
}
