#include <stdio.h>
#include <stdlib.h>
// #include "user.h"
#include "readData/readData.h"
#include "auxiliar.h"
#include "interface.h"
#include "project.h"
#include "spaceship.h"
#include "crew.h"


void showMainMenu() {
    printf("Welcome to StellarSalleX:\n");
    printf("\n\t1. Log in\n");
    printf("\t2. Register\n");
    printf("\t3. Exit\n");
}


//DONE
void executeMainMenu(int option, DataUsers* dataUsers, DataSpaceship* ds, Crew_data* dc, DataSpaceship stock) {
    int userIndex;
    DataProjects dp;

    int projectOption = 0;
    String optionAdmin;


    switch(option) {
        case 1:
            userIndex = logIn(*dataUsers);
            User user = dataUsers->user[userIndex];
            //printf("%s\n", user.email);
            //DONE ADMIN
            if (user.rol == 'A') {
                do {
                    showAdminMenu();
                    askForString(optionAdmin, "Choose an option: ");
                    printf("%s\n", optionAdmin);
                    projectOption = checkInt(optionAdmin);
                    if(projectOption != -1) {
                        executeAdminMenu(projectOption, dataUsers, ds, dc, stock, user.email);
                    }else {
                        printf("(ERROR) Enter a valid option.\n");
                    }
                }while(projectOption != 7);
            }

            //DONE INVESTIGATOR
            if (user.rol == 'R') {
                int option = 0;
                do {
                    dp = readProjectsData();
                    showInvestigatorMenu();
                    askForString(optionAdmin, "Choose an option: ");
                    projectOption = checkInt(optionAdmin);
                    if(projectOption != -1) {
                        executeInvestigatorMenu(projectOption, *dataUsers, dp, userIndex);
                    }else {
                        printf("(ERROR) Enter a valid option.\n");
                    }
                }while(projectOption != 7);
            }

            if(user.rol == 'C') {
                String optionUser;
                do {
                    showManageClientMenu();
                    askForString(optionUser, "Choose an option: ");
                    projectOption = checkInt(optionUser);
                    if(projectOption != -1) {
                        runManageClient(*dataUsers);
                    }else {
                        printf("(ERROR) Enter a valid option.\n");
                    }
                }while(projectOption != 8);
            }
            break;
        case 2:
            registerUser(*dataUsers);
            break;
        case 3:
            printf("See you soon!\n");
            //FIXME put saveUser();
            break;
        default:
            printf("(ERROR) Enter a valid option.\n");
            break;
    }
}

int main() {
    int option = 0;
    String aux;
    DataUsers dataUsers = readUsersData();
    DataSpaceship dataSpaceship;
    dataSpaceship.n_spaceships = 0;
    dataSpaceship.spaceship = NULL;

    DataSpaceship stock;
    stock.n_spaceships = 0;
    stock.spaceship = NULL;

    Crew_data dataCrew;
    dataCrew.n_crew = 0;
    dataCrew.crew = NULL;
    dataCrew = readCrewData();

    //stock = readSpaceship(stock);
    dataSpaceship = readSpaceshipsData(&stock);

    do {
        showMainMenu();
        askForString(aux, "Choose an option: ");
        option = checkInt(aux);
        executeMainMenu(option, &dataUsers, &dataSpaceship, &dataCrew, stock);
    }while(option != 3);

    saveUsers(dataUsers);
    saveSpaceship(dataSpaceship);
    saveCrew(dataCrew);

    return 0;
}