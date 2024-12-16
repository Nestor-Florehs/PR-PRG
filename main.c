#include <stdio.h>
#include <stdlib.h>
// #include "user.h"
#include "readData/readData.h"
#include "auxiliar.h"
#include "interface.h"
#include "project.h"
#include "spaceship.h"
#include "readData/readData.h"


void showMainMenu() {
    printf("Welcome to StellarSalleX:\n");
    printf("\n\t1. Log in\n");
    printf("\t2. Register\n");
    printf("\t3. Exit\n");
    printf("Choose: ");
}


//DONE
DataUsers executeMainMenu(int option, DataUsers dataUsers) {
    int userIndex;
    DataProjects dp;
    DataSpaceship ds;
    DataSpaceship stock;
    stock.n_spaceships = 0;
    stock.spaceship = NULL;
    int projectOption = 0;
    ds.n_spaceships = 0;
    ds.spaceship = NULL;
    String optionAdmin;

    // stock = readSpaceship(stock);
    ds = readSpaceshipsData(&stock);

    switch(option) {
        case 1:
            userIndex = logIn(dataUsers);
            User user = dataUsers.user[userIndex];
            printf("%s\n", user.email);
            //DONE ADMIN
            if (user.rol == 'A') {
                do {
                    showAdminMenu();
                    askForString(optionAdmin, "Choose an option: ");
                    printf("%s\n", optionAdmin);
                    projectOption = checkInt(optionAdmin);
                    if(projectOption != -1) {
                        dataUsers = executeAdminMenu(projectOption, dataUsers, ds, stock, user.email);
                    }else {
                        printf("Please enter a valid option!");
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
                        executeInvestigatorMenu(projectOption, dataUsers, dp, userIndex);
                    }else {
                        printf("Please enter a valid option!");
                    }
                }while(projectOption != 7);
            }

            //TODO CLIENT

            break;
        case 2:
            dataUsers = registerUser(dataUsers);
            break;
        case 3:
            printf("Exiting\n");
            //FIXME put saveUser();
            break;
        default:
            printf("Invalid option\n");
            break;
    }
    return dataUsers;
}

int main() {
    int option = 0;
    char aux;
    DataUsers dataUsers = readUsersData();

    do {
        showMainMenu();
        scanf("%d", &option);
        scanf("%c", &aux);
        dataUsers = executeMainMenu(option, dataUsers);
    }while(option != 3);

    saveUsers(dataUsers);

    return 0;
}