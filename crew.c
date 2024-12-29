#include "crew.h"
#include "auxiliar.h"
#include "spaceship.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void viewCrew(Crew_data data){
    for(int i = 0; i < data.n_crew; i++){
        if(!data.crew[i].support){
            printf("\tCrew member number %d:\n\tId: %d\n\tName: %s\n\tAge: %d\n\tRol: %s\n\tUniform color: %s\n\tContact information: %s\n", i+1, data.crew[i].id, data.crew[i].name, data.crew[i].age, data.crew[i].rol, data.crew[i].uniform_color, data.crew[i].contact_info);
            for (int j = 0; j < data.crew[i].id_spaceship.n_spaceships; j++) {
                printf("\tSpaceships assigned:\n\t\tId: %d\n\t\tId spaceship: %d\n", data.crew[i].id_spaceship.id_spaceship[j].id, data.crew[i].id_spaceship.id_spaceship[j].id_spaceship);
            }
        }
    }
}

void viewSupportCrew(Crew_data data){
    for(int i = 0; i < data.n_crew; i++){
        if(data.crew[i].support){
            printf("\tCrew member number %d:\n\tId: %d\n\tName: %s\n\tAge: %d\n\tRol: %s\n\tUniform color: %s\n\tContact information: %s\n", i+1, data.crew[i].id, data.crew[i].name, data.crew[i].age, data.crew[i].rol, data.crew[i].uniform_color, data.crew[i].contact_info);
            for (int j = 0; j < data.crew[i].id_spaceship.n_spaceships; j++) {
                printf("\tSpaceships assigned:\n\t\tId: %d\n\t\tId spaceship: %d\n", data.crew[i].id_spaceship.id_spaceship[j].id, data.crew[i].id_spaceship.id_spaceship[j].id_spaceship);
            }
        }
    }
}

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

int addIdSpaceship(Crew_data* d, int i, Id_Spaceship newIdSpaceship) {
    int error = 0;

    // Obtener el puntero a Id_spaceship del miembro Crew
    Id_spaceship* id_spaceship_data = &d->crew[i].id_spaceship;
    // Intentar reasignar memoria para el arreglo de Id_Spaceship
    Id_Spaceship* aux = realloc(id_spaceship_data->id_spaceship, (id_spaceship_data->n_spaceships + 1) * sizeof(Id_Spaceship));

    if (aux == NULL) {
        // Si falla realloc, retornar error sin modificar el puntero original
        printf("(ERROR) Memory allocation failed.\n");
        error = 1;
    } else {
        // Si realloc es exitoso, actualizar el puntero y agregar el nuevo elemento
        id_spaceship_data->id_spaceship = aux;
        id_spaceship_data->id_spaceship[id_spaceship_data->n_spaceships] = newIdSpaceship;
        id_spaceship_data->n_spaceships++;
    }

    return error;
}


Crew_data deleteCrew(Crew_data data, int index){
    if(data.n_crew < 1){
        printf("There are no crew members in the database\n");
    }else{
        memmove(&data.crew[index], &data.crew[index+1], (data.n_crew-(index+1))* sizeof(Crew));
        Crew* aux = realloc(data.crew, (data.n_crew - 1)*sizeof(Crew));
        if(aux == NULL && data.n_crew != 1){
            printf("Memory error\n");
        }else{
            if (data.n_crew == 1) {
                data.crew = NULL;
                data.n_crew = 0;
            }else {
                data.crew = aux;
                data.n_crew--;
            }
            printf("El tripulante ha sido eliminado con exito\n");
        }
    }
    return data;
}

Crew_data deleteIdSpaceship(Crew_data data, int index, int index_spaceship){
    if(data.crew[index].id_spaceship.n_spaceships < 1){
        printf("There are no spaceships assigned to this member in the database\n");
    }else{
        memmove(&data.crew[index].id_spaceship.id_spaceship[index_spaceship], &data.crew[index].id_spaceship.id_spaceship[index_spaceship+1], (data.crew[index].id_spaceship.n_spaceships-(index_spaceship+1))* sizeof(Id_Spaceship));
        Id_Spaceship* aux = realloc(data.crew[index].id_spaceship.id_spaceship, (data.crew[index].id_spaceship.n_spaceships - 1)*sizeof(Id_Spaceship));
        if(aux == NULL && data.crew[index].id_spaceship.n_spaceships != 1){
            printf("(ERROR) Memory error\n");
        }else{
            if (data.crew[index].id_spaceship.n_spaceships == 1) {
                data.crew[index].id_spaceship.id_spaceship = NULL;
                data.crew[index].id_spaceship.n_spaceships = 0;
            }else {
                data.crew[index].id_spaceship.id_spaceship = aux;
                data.crew[index].id_spaceship.n_spaceships--;
            }
            printf("La nave ha sido eliminada del tripulante con exito\n");
        }
    }
    return data;
}

Crew_data hireCrew(Crew_data data, int support_crew_member){
    Crew new_crew;
    String input;
    int error = 0;

    askForString(input, "Enter '1' to hire a support crew or '0' to hire a normal crew member: ");
    new_crew.support = checkInt(input);
    if (new_crew.support != -1 && new_crew.support >= 0 && new_crew.support <= 1) {
        //Pide el nombre del tripulante
        askForString(new_crew.name, "Enter crew name: ");
        //Pide la edad del tripulante
        askForString(input, "Enter crew age: ");
        new_crew.age = checkInt(input);
        if(new_crew.age != -1){
            //Pide el rol del tripulante
            askForString(new_crew.rol, "Enter crew rol: ");
            //Pide el color del uniforme del tripulante
            askForString(new_crew.uniform_color, "Enter crew uniform color: ");
            //Pide la información de contacto del tripulante
            askForString(new_crew.contact_info, "Enter crew contact information: ");
            Id_Spaceship id_spaceship;
            new_crew.id_spaceship.id_spaceship = NULL;
            new_crew.id_spaceship.n_spaceships = 0;
            if(data.n_crew == 0){
                new_crew.id = 1;
            }else{
                new_crew.id = data.crew[data.n_crew - 1].id + 1;
            }
            error = addCrew(&data, new_crew);
            if(!error){
                printf("Crew succesfully registered\n");
            }else {
                printf("Error adding crew\n");
            }
        }else{
            printf("(ERROR) Age not valid\n");
        }
    }else {
        printf("(ERROR) Number not valid\n");
    }
    return data;
}

//Te dice el indice del tripulante en la lista mediante el ID que tiene el tripulante
int searchCrewById(int id, Crew_data data) {
    int index = -1, found = 0;
    for (int i = 0; i < data.n_crew && !found; i++) {
        if(data.crew[i].id == id) {
            index = i;
            found = 1;
        }
    }
    return index;
}

//Te dice el indice del tripulante en la lista mediante la información de contacto
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

void viewCrewMember(Crew_data data, int i){
    printf("\tCrew member number %d:\n\tId: %d\n\tName: %s\n\tAge: %d\n\tRol: %s\n\tUniform color: %s\n\tContact information: %s\n\tSupport Crew: %d\n", i+1, data.crew[i].id, data.crew[i].name, data.crew[i].age, data.crew[i].rol, data.crew[i].uniform_color, data.crew[i].contact_info, data.crew[i].support);
}

Crew_data fireCrew(Crew_data data){
    String input;
    int id_crew = -1, first, index;

    printf("Listado de los tripulantes actuales:\n");
    viewCrew(data);
    first = 0;
    askForString(input, "Introduce el ID del tripulante que quieres eliminar: ");
    id_crew = checkInt(input);
    if (id_crew == -1 && id_crew >= 0 && id_crew <= data.n_crew) {
        index = searchCrewById(id_crew, data);
        data = deleteCrew(data, index);
    }else {
        printf("(ERROR) ID not valid\n");
    }
    return data;
}

Crew_data addSuppportCrewToSpaceship(int index, int index_spaceship, Crew_data data, DataSpaceship data_spaceship){
    Id_Spaceship id_spaceship;
    id_spaceship.id = data.crew[index].id;
    id_spaceship.id_spaceship = data_spaceship.spaceship[index_spaceship].id_spaceship;
    addIdSpaceship(&data, index, id_spaceship);
    return data;
}

//Te devuelve el indice del tripulante en l a lista mediante el id de la nave asociada
int findCrewBySpaceship(int index_spaceship, DataSpaceship data_spaceship, Crew_data data) {
    int index = -1;
    for (int i = 0; i < data.n_crew; i++) {
        for (int j = 0; j < data.crew[i].id_spaceship.n_spaceships; j++) {
            if(data_spaceship.spaceship[index_spaceship].id_spaceship == data.crew[i].id_spaceship.id_spaceship[j].id_spaceship) {
                index = i;
            }
        }
    }
    return index;
}

void viewAllSpaceships(DataSpaceship data) {
    for(int i = 0; i < data.n_spaceships; i++) {
        printSpaceship(data, i);
    }
}

int searchSpaceshipById(int id_spaceship, DataSpaceship data_spaceship) {
    int index = -1, found = 0;
    for (int i = 0; i < data_spaceship.n_spaceships && !found; i++) {
        if(data_spaceship.spaceship[i].id_spaceship == id_spaceship) {
            index = i;
            found = 1;
        }
    }
    return index;
}

int checkSameSpaceship(int index, int spaceship_id, Crew_data data) {
    int same = 0;
        for (int i = 0; i < data.crew[index].id_spaceship.n_spaceships; i++) {
            if (data.crew[index].id_spaceship.id_spaceship[i].id_spaceship == spaceship_id) {
                same = 1;
            }
        }
    return same;
}

Crew_data assignCrewToSpaceship(Crew_data data, DataSpaceship data_spaceship){
    String input;
    int crew_id, index, spaceship_id, index_spaceship, index_crew;
    Id_Spaceship id_spaceship;

    printf("Tripulantes sin nave asignada: \n");
    viewCrew(data);
    printf("Tripulantes de soporte contratados:\n");
    viewSupportCrew(data);
    askForString(input, "Introduce el ID del tripulante que quieres asignar a alguna nave: ");
    crew_id = checkInt(input);
    index = searchCrewById(crew_id, data);
    printf("Naves disponibles:\n");
    viewAllSpaceships(data_spaceship);
    askForString(input, "Introduce el ID de la nave a la que asignar el tripulante:");
    spaceship_id = checkInt(input);
    index_spaceship = searchSpaceshipById(spaceship_id, data_spaceship);
    if(data.crew[index].support){
        //Asignar tripulante de soporte
        if(data_spaceship.spaceship[index_spaceship].crew_capacity > data_spaceship.spaceship[index_spaceship].actual_n_crew){
            if(data_spaceship.spaceship[index_spaceship].actual_n_crew){
                //Chequear el color del resto de tripulantes
                index_crew = findCrewBySpaceship(index_spaceship, data_spaceship, data);
                if(index_crew != -1){
                    if(!strcmp(data.crew[index].uniform_color, data.crew[index_crew].uniform_color)) {
                        if(checkSameSpaceship(index, spaceship_id, data) == 0) {
                            data_spaceship.spaceship[index_spaceship].actual_n_crew++;
                            addSuppportCrewToSpaceship(index, index_spaceship, data, data_spaceship);
                            printf("Crew member succesfully assigned to the spaceship!\n");
                        }else{
                            printf("This crew member is already assigned to this spaceship\n");
                        }
                    }else{
                        printf("(ERROR) El color del uniforme del tripulante no es el mismo que el del resto de tripulantes de la nave\n");
                    }
                }else {
                    printf("Crew not found!\n");
                }
            }else{
                //Añadir tripulante tal cual, no importa el color
                data_spaceship.spaceship[index_spaceship].actual_n_crew++;
                data = addSuppportCrewToSpaceship(index, index_spaceship, data, data_spaceship);
                printf("Crew member succesfully assigned to the spaceship!");
            }
        }else{
            printf("(ERROR) Esta nave ya no puede tener más tripulantes, ¡está llena!\n");
        }
    }else{
        //Asignar tripulante normal
        if(data.crew[index].id_spaceship.n_spaceships){
            printf("(ERROR) Este tripulante ya tiene una nave asignada\n");
        }else{
            if(data_spaceship.spaceship[index_spaceship].crew_capacity > data_spaceship.spaceship[index_spaceship].actual_n_crew){
                if(data_spaceship.spaceship[index_spaceship].actual_n_crew){
                    //Chequear el color del resto de tripulantes
                    index_crew = findCrewBySpaceship(index_spaceship, data_spaceship, data);
                    if(!strcmp(data.crew[index].uniform_color, data.crew[index_crew].uniform_color)){
                        data_spaceship.spaceship[index_spaceship].actual_n_crew++;
                        id_spaceship.id = index;
                        id_spaceship.id_spaceship = data_spaceship.spaceship[index_spaceship].id_spaceship;
                        addIdSpaceship(&data, index, id_spaceship);
                        printf("Crew member succesfully assigned to the spaceship!");
                    }else{
                        printf("(ERROR) El color del uniforme del tripulante no es el mismo que el del resto de tripulantes de la nave\n");
                    }
                }else{
                    //Añadir tripulante tal cual, no importa el color
                    data_spaceship.spaceship[index_spaceship].actual_n_crew++;
                    id_spaceship.id = index;
                    id_spaceship.id_spaceship = data_spaceship.spaceship[index_spaceship].id_spaceship;
                    addIdSpaceship(&data, index, id_spaceship);
                    printf("Crew member succesfully assigned to the spaceship!");
                }
            }else{
                printf("(ERROR) Esta nave ya no puede tener más tripulantes, ¡está llena!\n");
            }
        }
    }

    return data;
}

//Busca el index del tripulante en la lista mediante el ID
int searchIndexById(int crew_index, int spaceship_id, Crew_data data) {
    int index = -1, found = 0;
    for (int i = 0; i < data.crew[crew_index].id_spaceship.n_spaceships && !found; i++) {
        if(spaceship_id == data.crew[crew_index].id_spaceship.id_spaceship[i].id_spaceship) {
            index = i;
            found = 1;
        }
    }
    return index;
}

void viewAllSpaceshipsAssigned(DataSpaceship data_spaceship, Crew_data data, int index) {
    for (int i = 0; i < data_spaceship.n_spaceships; i++) {
        for (int j = 0; j < data.crew[index].id_spaceship.n_spaceships; j++) {
            if (data_spaceship.spaceship->id_spaceship == data.crew[index].id_spaceship.id_spaceship[j].id_spaceship) {
                printSpaceship(data_spaceship, i);
            }
        }
    }
}

//Story 20
Crew_data deleteCrewFromSpaceship(Crew_data data, DataSpaceship* data_spaceship){
    int crew_id, index, delete_index, index_spaceship, spaceship_id;
    String input;

    askForString(input, "Introduce el ID del tripulante que quieres eliminar de alguna nave: ");
    crew_id = checkInt(input);
    index = searchCrewById(crew_id, data);
    if (data.crew[index].support) {
        //Tripulante de soporte
        printf("Naves asignadas por el tripulante:");
        viewAllSpaceshipsAssigned(*data_spaceship, data, index);
        askForString(input, "Introduce el ID de la nave que quieres eliminar: ");
        spaceship_id = checkInt(input);
        delete_index = searchSpaceshipById(spaceship_id, *data_spaceship);
        (*data_spaceship).spaceship[delete_index].actual_n_crew--;
        data = deleteIdSpaceship(data, index, delete_index);
    }else {
        //Tripulante normal
        index_spaceship = searchSpaceshipById(data.crew[index].id_spaceship.id_spaceship[0].id_spaceship, *data_spaceship);
        (*data_spaceship).spaceship[index_spaceship].actual_n_crew--;
        data = deleteIdSpaceship(data, index, 0);
    }
    return data;
}

void filteredCrew(Crew_data data, String str, char* attribute) {
    String num;
    for (int i = 0; i < data.n_crew; i++) {
        // Compara el atributo elegido con la cadena
        if (strcmp(attribute, "name") == 0 && strstr(data.crew[i].name, str)) {
            viewCrewMember(data, i);
        }
        else if (strcmp(attribute, "rol") == 0 && strstr(data.crew[i].rol, str)) {
            viewCrewMember(data, i);
        }
        else if (strcmp(attribute, "age") == 0 && strstr(itoa(data.crew[i].age, num, 10), str)) {
            viewCrewMember(data, i);
        }
        else if (strcmp(attribute, "uniform_color") == 0 && strstr(data.crew[i].uniform_color, str)) {
            viewCrewMember(data, i);
        }
    }
}

int crewFilterMenu() {
    String str;
    int option;
    printf("1. Filter by uniform color\n");
    printf("2. Filter by name\n");
    printf("3. Filter by age\n");
    printf("4. Filter by role\n");
    printf("5. Back to the Crew Menu\n");
    askForString(str, "Choose an option: ");
    option = checkInt(str);
    if (option < 1) {
        printf("(ERROR) Please, enter a number\n");
    }
    printf("\n");
    return option;
}

Crew_data filterCrew(Crew_data data) {
    String str;
    int option;

        do {
            option = crewFilterMenu();

            switch(option) {
                case 1:
                    askForString(str, "Enter characters to filter: ");
                    filteredCrew(data, str, "uniform_color");
                    printf("\n");
                    break;
                case 2:
                    askForString(str, "Enter characters to filter: ");
                    filteredCrew(data, str, "name");
                    printf("\n");
                    break;
                case 3:
                    askForString(str, "Enter numbers to filter: ");
                    filteredCrew(data, str, "age");
                    printf("\n");
                    break;
                case 4:
                    askForString(str, "Enter characters to filter: ");
                    filteredCrew(data, str, "rol");
                    printf("\n");
                break;
                case 5:
                    printf("\nCrew menu:");
                    option = 5;
                    break;
                default:
                    if (option >= 0) {
                        printf("(ERROR) Invalid option!\n\n");
                    }
                    break;
            }
    } while (option != 5);
    return data;
}

int printMenuCrew() {
    String str;
    int option;
    printf("\n\t1. Hire Crew Member\n");
    printf("\t2. Assign Crew Member\n");
    printf("\t3. Deassign Crew Member\n");
    printf("\t4. Fire Crew Member\n");
    printf("\t5. Search Crew Member\n");
    printf("\t6. Show Crew Members\n");
    printf("\t7. Back to General Menu\n");
    askForString(str, "Choose an option: ");
    option = checkInt(str);
    if (option < 1) {
        printf("(ERROR) Please, enter a number\n");
    }
    printf("\n");
    return option;
}

Crew_data menuCrew(Crew_data data, DataSpaceship data_spaceship) {
    String str;
    int option;

    do {
        option = printMenuCrew();

        switch(option) {
            case 1:
                data = hireCrew(data, 0);
                break;
            case 2:
                data = assignCrewToSpaceship(data, data_spaceship);
                break;
            case 3:
                data = deleteCrewFromSpaceship(data, &data_spaceship);
                break;
            case 4:
                data = fireCrew(data);
                break;
            case 5:
                data = filterCrew(data);
                break;
            case 6:
                viewCrew(data);
                viewSupportCrew(data);
                break;
            case 7:
                printf("\nGeneral menu:");
                break;
            default:
                if (option >= 0) {
                    printf("(ERROR) Invalid option!\n\n");
                }
            break;
        }
    } while (option != 7);
    return data;
}