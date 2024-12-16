#include "spaceship.h"
#include "auxiliar.h"
#include "user.h"
#include "readData/readData.h"
#include <stdlib.h>
#include <time.h>

int atoiAux(String str){
    int num;
    if(!isdigit(str[1])){
        num = str[0] - '0';
    }else{
        num = atoi(str);
    }
    str[1] = '\0';
    return num;
}

void deleteLineSpace(String str){
    str[strlen(str)-1] = '\0';
}

void printSpaceship(DataSpaceship data, int i) {
    printf("Spaceship %d:\n", i + 1);
    printf("ID: %d\n", data.spaceship[i].id_spaceship);
    printf("Name: %s\n", data.spaceship[i].name);
    printf("Crew capacity: %d\n", data.spaceship[i].crew_capacity);
    printf("Passenger capacity: %d\n", data.spaceship[i].passenger_capacity);
    printf("Communication: %s\n", data.spaceship[i].communication);
    printf("Motor: %s\n", data.spaceship[i].motor);
    if (data.spaceship[i].broken_motor) {
        printf("Motor is broken\n");
    }
    printf("Navigation system: %s\n", data.spaceship[i].navigation);
    printf("Propulsion: %s\n", data.spaceship[i].propulsion);
    printf("Potency: %d\n", data.spaceship[i].potency);
    printf("Instrumentation: %s\n", data.spaceship[i].instrumentation);
    printf("Modules: %d\n", data.spaceship[i].module);
    printf("Pieces broken: %d\n", data.spaceship[i].broken_pieces);
    printf("\n");
}

//tt1 - story 13
int searchSpaceshipByName(String str, DataSpaceship data) {
    int index = -1, found = 0;
    for (int i = 0; i < data.n_spaceships && !found; i++) {
        if(strcmp(data.spaceship[i].name, str) == 0) {
            index = i;
            found = 1;
        }
    }
    return index;
}

//tt1 - story 10
void addSpaceship(DataSpaceship* d, Spaceship newSpaceship) {
    d->n_spaceships++;
    Spaceship* aux = realloc(d->spaceship, (d->n_spaceships) * sizeof(Spaceship));
    if(aux == NULL){
        printf("(ERROR) Memory failed");
    } else {
        d->spaceship = aux;
        d->spaceship[d->n_spaceships - 1] = newSpaceship;
    }
}

//tt2 - story 10
Spaceship readString(String str) {
    Spaceship spaceship;

    char* token = strtok(str, ",");
    spaceship.id_spaceship = atoi(token); // Primer valor: id (entero)

    token = strtok(NULL, ",");
    strcpy(spaceship.name, token); // Segundo valor: name (cadena)

    token = strtok(NULL, ",");
    spaceship.crew_capacity = atoi(token); // Tercer valor: crew_capacity (entero)

    token = strtok(NULL, ",");
    spaceship.passenger_capacity = atoi(token); // Cuarto valor: passenger_capacity (entero)

    token = strtok(NULL, ",");
    strcpy(spaceship.communication, token); // Quinto valor: communication (cadena)

    token = strtok(NULL, ",");
    strcpy(spaceship.motor, token); // Sexto valor: motor (cadena)

    token = strtok(NULL, ",");
    strcpy(spaceship.navigation, token); // Séptimo valor: navigation (cadena)

    token = strtok(NULL, ",");
    strcpy(spaceship.propulsion, token); // Octavo valor: propulsion (cadena)

    token = strtok(NULL, ",");
    spaceship.potency = atoi(token); // Noveno valor: potency (entero)

    token = strtok(NULL, "\n");
    strcpy(spaceship.instrumentation, token); // Décimo valor: instrumentation (cadena)

    spaceship.module = 0;

    spaceship.broken_motor = 0;

    spaceship.broken_pieces = 0;

    spaceship.launch = 0;

    return spaceship;
}

//tt3 - story 10
DataSpaceship readSpaceship() {
    DataSpaceship data;

    FILE *file = fopen("textFiles/space.txt", "r");

    if (file == NULL) {
        printf("Error opening file\n");
    } else {
        while (!feof(file)) {
            String str;
            fgets(str, 100, file);
            Spaceship spaceship = readString(str);
            addSpaceship(&data, spaceship);
        }
    }
    fclose(file);

    return data;
}

void removeStock (DataSpaceship* d, int index) {
    if (d->n_spaceships < 1){
        printf("Memory is already empty");
    } else {
        memmove(&d->spaceship[index], &d->spaceship[index+1], (d->n_spaceships-(index+1)) * sizeof(Spaceship));
        d->n_spaceships--;
    }
}

void removeStockByData(DataSpaceship d, DataSpaceship* stock) {
    for (int i = 0; i < d.n_spaceships; i++) {
        int index = searchSpaceshipByName(d.spaceship[i].name, *stock);
        if (index >= 0) {
            removeStock(stock, index);
        }
    }
}

void showStock (DataSpaceship d) {
    printf("Spaceships in stock:\n");
    for (int i = 0; i < d.n_spaceships; i++) {
        printSpaceship(d, i);
    }
}

int searchId(DataSpaceship d, DataSpaceship stock) {
    int id = 1;
    for (int i = 0; i < stock.n_spaceships; i++) {
        if (id == stock.spaceship[i].id_spaceship) {
            id++;
        }
    }

    for (int i = 0; i < d.n_spaceships; i++) {
        if (id == d.spaceship[i].id_spaceship) {
            id++;
        }
    }

    return id;
}

//story 10
DataSpaceship buySpaceship(DataSpaceship d, DataSpaceship* stock, String email) {
    int index_data, index_stock;
    Spaceship new;
    char aux, option;
    String name;
    String str;

    printf("Do you want to personalize a spaceship? (Y/N): ");
    scanf("%c", &option);
    scanf("%c", &aux);

    switch (option) {
        case 'N':
            showStock(*stock);
        printf("Enter name: ");
        fgets(name, 50, stdin);
        deleteLineSpace(name);

        index_data = searchSpaceshipByName(name, *stock);

        if (index_data >= 0) {
            // Agregar la nave seleccionada a la lista de naves del usuario
            strcpy(stock->spaceship[index_data].email_user, email);
            addSpaceship(&d, stock->spaceship[index_data]);
        } else {
            printf("(ERROR) Spaceship not found\n");
        }
        break;
        case 'Y':
            new.id_spaceship = searchId(d, *stock);
            strcpy(new.email_user, email);

            do {
                askForString(new.name, "Enter name: ");
                index_data = searchSpaceshipByName(new.name, d);
                index_stock = searchSpaceshipByName(new.name, *stock);
                if (index_data >= 0 || index_stock >= 0) {
                    printf("(ERROR) Name is already selected\n");
                }
            } while (index_data >= 0 || index_stock >= 0);

            do {
                askForString(str, "Enter crew capacity: ");
                new.crew_capacity = checkInt(str);
                if (new.crew_capacity < 0) {
                    printf("ERROR\n");
                }
            } while (new.crew_capacity < 0);

            do {
                askForString(str, "Enter passengers capacity: ");
                new.passenger_capacity = checkInt(str);
                if (new.passenger_capacity < 0) {
                    printf("ERROR\n");
                }
            } while (new.passenger_capacity < 0);

            askForString(new.communication, "Enter communication: ");

            askForString(new.motor, "Enter motor: ");

            askForString(new.navigation, "Enter navigation system: ");

            askForString(new.propulsion, "Enter propulsion system: ");

            do {
                askForString(str, "Enter potency: ");
                new.potency = checkInt(str);
                if (new.potency < 0) {
                    printf("ERROR\n");
                }
            } while (new.potency < 0);

            printf("Has the spaceship scientific instrumentation? (Y/N): ");
            scanf("%c", &option);
            scanf("%c", &aux);

            if (option == 'N') {
                strcpy(new.instrumentation, "");
            } else {
                printf("Enter scientific instrumentation: ");
                askForString(new.instrumentation, "Enter scientific instrumentation: ");
            }

            do {
                askForString(str, "How many modules has the spaceship? ");
                new.module = checkInt(str);
                if (new.module < 0) {
                    printf("ERROR\n");
                }
            } while (new.module < 0);
            // Agregar la nueva nave
            new.broken_motor = 0;
            new.broken_pieces = 0;
            new.launch = 0;
            addSpaceship(&d, new);
            break;
        default:
            printf("(ERROR) Invalid option!\n");
            break;
    }

    return d;
}

//tt1 - story 11
void inputModules(DataSpaceship* data, int index) {
    char aux;
    String str;
    int error = 0, option;
    int num = 0;

    printf("\t1. Add modules\n\t2. Remove modules\n");
    printf("Enter option: ");
    scanf("%d", &option);
    scanf("%c", &aux);

    switch(option) {
        case 1:
            do {
                error = 0;
                askForString(str, "How many modules do you want to add? ");
                num = checkInt(str);
                if (num < 0) {
                    error = 1;
                    printf("(ERROR) Please, enter a number\n");
                } else {
                    data->spaceship[index].module += num;
                }
            } while (error);
        break;
        case 2:
            do {
                error = 0;
                askForString(str, "How many modules do you want to remove? ");
                num = checkInt(str);
                if (num < 0) {
                    error = 1;
                    printf("ERROR. Please, enter a number\n");
                } else {
                    data->spaceship[index].module -= num;
                }
            } while (error);
            break;
        default:
            printf("(ERROR) Invalid option\n\n");
            break;
    }
}

//tt2 - story 11
int printMenuModify() {
    String str;
    printf("1. Modify name\n");
    printf("2. Modify crew capacity\n");
    printf("3. Modify passengers capacity\n");
    printf("4. Modify motor\n");
    printf("5. Modify communication\n");
    printf("6. Modify navigation\n");
    printf("7. Modify propulsion\n");
    printf("8. Modify potency\n");
    printf("9.  Modify instrumentation\n");
    printf("10. Modify modules\n)");
    printf("11. Stop modifying\n\n");
    askForString(str, "choose an option: ");
    int option = checkInt(str);
    if (option < 1) {
        printf("(ERROR) Please, enter a number\n");
    }
    printf("\n");
    return option;
}

//story 11
DataSpaceship modifySpaceship(DataSpaceship data, DataSpaceship stock) {
    char aux;
    String name;
    int option;

    askForString(name, "Enter name of spaceship: ");
    int index = searchSpaceshipByName(name, data);
    if(index == -1) {
        printf("No such spaceship\n");
    } else {
        int index_stock;
        int index_data;
        int error = 0;
        while(option != 11) {
            String str;
            printf("1. Modify name\n2. Modify crew capacity\n3. Modify passengers capacity\n4. Modify motor\n5. Modify communication"
                   "\n6. Modify navigation\n7. Modify propulsion\n8. Modify potency\n9. Modify instrumentation\n"
                   "10. Modify modules\n11. Stop modifying\n\nChoose an option: ");
            scanf("%d", &option);
            scanf("%c", &aux);
            printf("\n");

            switch(option){
                case 1:
                    printf("Actual name: %s\n", data.spaceship[index].name);
                    do {
                        askForString(name, "New name: ");
                        index_data = searchSpaceshipByName(name, data);
                        index_stock = searchSpaceshipByName(name, stock);
                        if (index_data >= 0 || index_stock >= 0) {
                            printf("(ERROR) Name already exists\n");
                        }
                    } while(index_data >= 0 || index_stock >= 0);
                    strcpy(data.spaceship[index].name, name);
                    printf("\n");
                    break;
                case 2:
                    printf("Actual crew capacity: %d\n", data.spaceship[index].crew_capacity);
                    do {
                        error = 0;
                        askForString(str, "New crew capacity: ");
                        data.spaceship[index].crew_capacity = checkInt(str);
                        if (data.spaceship[index].crew_capacity < 0) {
                            error = 1;
                            printf("(ERROR) Please, enter a number\n");
                        }
                    } while (error);
                    printf("\n");
                    break;
                case 3:
                    printf("Actual passenger capacity: %d\n", data.spaceship[index].passenger_capacity);
                    do {
                        error = 0;
                        askForString(str, "Enter passenger capacity: ");
                        data.spaceship[index].passenger_capacity = checkInt(str);
                        if (data.spaceship[index].passenger_capacity < 0) {
                            error = 1;
                            printf("(Error) Please enter a number\n");
                        }
                    } while (error);
                printf("\n");
                break;
                case 4:
                    printf("Actual motor: %s\n", data.spaceship[index].motor);
                    askForString(data.spaceship[index].motor, "New motor: ");
                    printf("\n");
                    break;
                case 5:
                    printf("Actual communication: %s\n", data.spaceship[index].communication);
                    askForString(data.spaceship[index].communication, "New communication: ");
                    printf("\n");
                break;
                case 6:
                    printf("Actual navigation: %s\n", data.spaceship[index].navigation);
                    askForString(data.spaceship[index].navigation, "New navigation: ");
                    printf("\n");
                    break;
                case 7:
                    printf("Actual propulsion: %s\n", data.spaceship[index].propulsion);
                    askForString(data.spaceship[index].propulsion, "New propulsion: ");
                    printf("\n");
                    break;
                case 8:
                    printf("Actual potency: %d\n", data.spaceship[index].potency);
                    do {
                        error = 0;
                        askForString(str, "New potency: ");
                        data.spaceship[index].potency = checkInt(str);
                        if (data.spaceship[index].potency < 0) {
                            error = 1;
                            printf("(ERROR) Please, enter a number\n");
                        }
                    } while (error);
                break;
                case 9:
                    printf("Actual Instrumentation: %s\n", data.spaceship[index].instrumentation);
                    askForString(data.spaceship[index].instrumentation, "New instrumentation: ");
                    printf("\n");
                break;
                case 10:
                    printf("Actual modules: %d\n", data.spaceship[index].module);
                    inputModules(&data, index);
                    break;
                case 11:
                    printf("See you in the next modification\n\n");
                    break;
                default:
                    if (option >= 0) {
                        printf("(ERROR) Invalid option!\n\n");
                    }
                    break;
            }
        }
    }
    return data;
}

//tt2 - story 13
void compactArray(DataSpaceship* d, int index) {
    int size = d->n_spaceships;
    if (index < size - 1) {
        memmove(&d->spaceship[index], &d->spaceship[index + 1], (size - index - 1) * sizeof(Spaceship));
    }
    d->n_spaceships--;
}

//story 13
DataSpaceship removeSpaceship (DataSpaceship d) {
    if (d.n_spaceships < 1) {
        printf("There are no spaceships\n");
    }
    else {
        String name;
        int index = 0;
        askForString(name, "What spaceship do you want to remove? ");
        index = searchSpaceshipByName(name, d);
        if (index < 0){
            printf("Spaceship does not exist\n");
        } else {
            compactArray(&d, index);
        }
    }
    return d;
}

//tt1 - story 14
int mailFound(String str, DataSpaceship data) {
    int found = 0, i = 0;
    while (!found && i < data.n_spaceships) {
        if(strcmp(data.spaceship[i].email_user, str) == 0) {
            found = 1;
        }
        i++;
    }
    return found;
}

int coincidenceMail(String str, Spaceship spaceship) {
    int found = 0, i = 0;
    if(strcmp(spaceship.email_user, str) == 0) {
        found = 1;
    }

    return found;
}

//tt2 - story 14
void printBoughtSpaceship (DataSpaceship data, String mail) {
    if (mailFound(mail, data)) {
        for (int i = 0; i < data.n_spaceships; i++) {
            if (coincidenceMail(mail, data.spaceship[i])) {
                printSpaceship(data, i);
            }
        }
    } else {
        printf("Any spaceship bought\n\n");
    }
}

//story 14
void showSpaceship (DataSpaceship d, String mail) {
    printBoughtSpaceship(d, mail);
}

//tt1 - story 16
void showFiltered(DataSpaceship data, String str, char* attribute) {
    for (int i = 0; i < data.n_spaceships; i++) {
        String num;
        if (strcmp(attribute, "name") == 0 && strstr(data.spaceship[i].name, str) ||
            (strcmp(attribute, "crew capacity") == 0 && strstr(itoa(data.spaceship[i].crew_capacity, num, 10), str)) ||
            (strcmp(attribute, "passenger capacity") == 0 && strstr(itoa(data.spaceship[i].passenger_capacity, num, 10), str)) ||
            (strcmp(attribute, "motor") == 0 && strstr(data.spaceship[i].motor, str)) ||
            (strcmp(attribute, "communication") == 0 && strstr(data.spaceship[i].communication, str)) ||
            (strcmp(attribute, "navigation") == 0 && strstr(data.spaceship[i].navigation, str)) ||
            (strcmp(attribute, "propulsion") == 0 && strstr(data.spaceship[i].propulsion, str)) ||
            (strcmp(attribute, "potency") == 0 && strstr(itoa(data.spaceship[i].potency, num, 10), str)) ||
            (strcmp(attribute, "instrumentation") == 0 && strstr(data.spaceship[i].instrumentation, str))) {
            printSpaceship(data, i);
        }
    }
}

//tt2 - story 16
int printMenuFilter() {
    int option;
    printf("1. Filter by name\n");
    printf("2. Filter by crew capacity\n");
    printf("3. Filter by passengers capacity\n");
    printf("4. Filter by motor\n");
    printf("5. Filter by communication\n");
    printf("6. Filter by navigation\n");
    printf("7. Filter by propulsion\n");
    printf("8. Filter by potency\n");
    printf("9. Filter by instrumentation\n");
    printf("10. Stop filtring\n\n");

    do {
        String str;
        askForString(str, "choose an option: ");
        option = checkInt(str);
        if (option == -1) {
            printf("(ERROR) Please, enter a number\n");
        }
    } while (option < 0);
    return option;
}

//story 16
void filterSpaceship(DataSpaceship data) {
    int option = 0;
        do {
            String str;
            option = printMenuFilter();
            switch(option) {
                case 1:
                    askForString(str, "Enter characters to filter: ");
                    showFiltered(data, str, "name");
                    printf("\n");
                    break;
                case 2:
                    askForString(str, "Enter nums to filter: ");
                    showFiltered(data, str, "crew capacity");
                    printf("\n");
                    break;
                case 3:
                    askForString(str, "Enter nums to filter: ");
                    showFiltered(data, str, "passengers capacity");
                    printf("\n");
                    break;
                case 4:
                    askForString(str, "Enter characters to filter: ");
                showFiltered(data, str, "motor");
                printf("\n");
                break;
                case 5:
                    askForString(str, "Enter characters to filter: ");
                    showFiltered(data, str, "communication");
                    printf("\n");
                    break;
                case 6:
                    askForString(str, "Enter characters to filter: ");
                    showFiltered(data, str, "navigation");
                    printf("\n");
                    break;
                case 7:
                    askForString(str, "Enter characters to filter: ");
                    showFiltered(data, str, "propulsion");
                    printf("\n");
                    break;
                case 8:
                    askForString(str, "Enter nums to filter: ");
                    showFiltered(data, str, "potency");
                    printf("\n");
                    break;
                case 9:
                    askForString(str, "Enter characters to filter: ");
                    showFiltered(data, str, "instrumentation");
                    printf("\n");
                    break;
                case 10:
                    printf("See you in the next filtration\n\n");
                    break;
                default:
                    printf("(ERROR) Invalid option!\n");
                    break;
            }
    } while (option != 10);
}

//tt1 - story 12
int canRepair(Spaceship spaceship) {
    if (!spaceship.broken_motor && spaceship.broken_pieces < 4) {
        return 1;
    }
    return 0;
}

//tt2 - story 12
int isRepaired(Spaceship spaceship) {
    if (!spaceship.broken_motor && spaceship.broken_pieces == 0) {
        return 1;
    }
    return 0;
}

//story 12
DataSpaceship repairSpaceship(DataSpaceship data) {
    String str;
    askForString(str, "What spaceship do yo want to repair? ");
    int i = searchSpaceshipByName(str, data);
    if (i < 0) {
        printf("(ERROR) Spaceship does not exist\n");
    }
    else {
        if (isRepaired(data.spaceship[i])) {
            printf("Spaceship is already repaired\n");
        } else if (canRepair(data.spaceship[i])) {
            data.spaceship[i].broken_pieces = 0;
        }
    }
    return data;
}