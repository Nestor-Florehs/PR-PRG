#include "crew.h"
#include "auxiliar.h"


int addCrew(Crew_data* d, Crew newCrew) {
    int error = 0;
    // Intenta reasignar memoria para el nuevo usuario
    Crew* aux = NULL;
    aux = realloc(d->crew, (d->n_crew + 1) * sizeof(Crew));

    // Si realloc falla, retorna error sin perder el puntero original
    if (aux == NULL) {
        printf("(ERROR) Memory allocation failed.\n");
        error = 1;
    } else {
        // Si realloc tiene éxito, actualiza el puntero y el número de usuarios
        d->crew = aux;
        d->crew[d->n_crew] = newCrew;
        d->n_crew++;
        if(d->crew == NULL){
            printf("(ERROR) Memory pointers elsewhere\n");
            error = 1;
        }
    }

    return error;
}

Crew_data deleteCrew(Crew_data data, int index){
    if(data.n_crew < 1){
        printf("Memory is already empty\n");
    }else{
        memmove(&data.crew[index], &data.crew[index+1], (data.n_crew-(index+1))* sizeof(Crew));
        Crew* aux = realloc(data.crew, (data.n_crew-1)*sizeof(Crew));
        if(aux == NULL){
            printf("Memory error\n");
        }else{
            data.crew = aux;
            data.n_crew--;
        }
    }
    return data;
}

Crew_data hireCrew(Crew_data data, int support_crew_member) {
    Crew new_crew;
    String input;
    int error = 0;

    new_crew.support = support_crew_member;
    askForString(new_crew.name, "Enter crew name: \n");
    error = checkHashtag(new_crew.name);
    if (!error) {
        askForString(input, "Enter crew age: \n");
        new_crew.age = checkInt(input);
        if (new_crew.age != -1) {
            askForString(new_crew.rol, "Enter crew rol: \n");
            error = checkHashtag(new_crew.rol);
            if (!error) {
                askForString(new_crew.uniform_color, "Enter crew uniform color: \n");
                error = checkHashtag(new_crew.uniform_color);
                if (!error) {
                    askForString(new_crew.contact_info, "Enter crew contact information: \n");
                    error = checkHashtag(new_crew.contact_info);
                    if (!error) {
                        new_crew.spaceship = NULL;
                        if (data.n_crew == 0) {
                            new_crew.id = 1;
                        } else {
                            new_crew.id = data.crew[data.n_crew - 1].id + 1;
                        }
                        error = addCrew(&data, new_crew);
                        if (!error) {
                            printf("Crew successfully registered\n");
                        }
                    } else {
                        printf("(ERROR) Contact information not valid\n");
                    }
                } else {
                    printf("(ERROR) Uniform color not valid\n");
                }
            } else {
                printf("(ERROR) Rol not valid\n");
            }
        } else {
            printf("(ERROR) Age not valid\n");
        }
    } else {
        printf("(ERROR) Name not valid\n");
    }
    return data;
}

int findUserByContactInfo(Crew_data d) {
    String mail;
    int index = 0;
    int ok = 0;
    printf("Enter the contact information of the crew member: \n");
    fgets(mail, 50, stdin);
    for(int i = 0; i < d.n_crew && !ok; i++) {
        if(!strcmp(mail, d.crew[i].contact_info)) {
            index = i;
            ok = 1;
        }
        else {
            index = -1;
        }
    }
    return index;
}

Crew_data removeCrew(Crew_data d) {
    int index = findUserByContactInfo(d);
    if(index == -1) {
        printf("ERROR: Crew Member not found");
    }
    else {
        deleteCrew(d, index);
        printf("Crew Member deleted\n");
    }
    return d;
}

void viewCrew(Crew_data data){
    for(int i = 0; i < data.n_crew; i++){
        printf("Crew member number %d:\n\tId: %d\n\tName: %s\n\tAge: %d\n\tRol: %s\n\tUniform color: %s\n\tContact information: %s\n", i+1, data.crew[i].id, data.crew[i].name, data.crew[i].age, data.crew[i].rol, data.crew[i].uniform_color, data.crew[i].contact_info);
        if(data.crew[i].support){
            printf("\tType of member: Support\n\n");
        }else{
            printf("\tType of member: Normal\n\n");
        }
    }
}