#include <stdio.h>
#include "readData/readData.h"
#include "auxiliar.h"
#include "interface.h"
#include "project.h"
#include "spaceship.h"
#include "voyage.h"

void showMainMenu() {
    printf("Welcome to StellarSalleX:\n");
    printf("\n\t1. Log in\n");
    printf("\t2. Register\n");
    printf("\t3. Exit\n");
}


//DONE
void executeMainMenu(int option, DataUsers* dataUsers, DataSpaceship* ds, Crew_data* dc, DataSpaceship stock, VoyageData* voyage_data) {
    int userIndex;
    DataProjects dp;

    int projectOption = 0;
    String optionAdmin;


    switch(option) {
        case 1:
            userIndex = logIn(*dataUsers);
            User user = dataUsers->user[userIndex];
            printf("%s\n", user.email);
            //DONE ADMIN
            if (user.rol == 'A') {
                do {
                    showAdminMenu();
                    askForString(optionAdmin, "Choose an option: ");
                    projectOption = checkInt(optionAdmin);
                    if(projectOption != -1) {
                        executeAdminMenu(projectOption, dataUsers, ds, dc, stock, user.id,voyage_data);
                    }else {
                        printf("Please enter a valid option!");
                    }
                }while(projectOption != 7);
            }

            //DONE INVESTIGATOR
            if (user.rol == 'R') {
                do {
                    dp = readProjectsData();
                    showInvestigatorMenu();
                    askForString(optionAdmin, "Choose an option: ");
                    projectOption = checkInt(optionAdmin);
                    if(projectOption != -1) {
                        executeInvestigatorMenu(projectOption, *dataUsers, dp, userIndex);
                    }else {
                        printf("Please enter a valid option!");
                    }
                }while(projectOption != 7);
            }
        if(user.rol == 'C') {
            String optionUser;
            do {
                showClientMenu();
                askForString(optionUser, "Choose an option: ");
                projectOption = checkInt(optionUser);
                if(projectOption != -1) {
                    executeClientMenu(projectOption, dataUsers, voyage_data, stock, userIndex);
                }else {
                    printf("Please enter a valid option!");
                }
            }while(projectOption != 8);
        }
            //TODO CLIENT

            break;
        case 2:
            *dataUsers = registerUser(*dataUsers);
            saveUsers(*dataUsers);
            break;
        case 3:
            printf("Exiting\n");
            //FIXME put saveUser();
            break;
        default:
            printf("Invalid option\n");
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

    VoyageData dataVoyage;
    dataVoyage.num_voyages=0;
    dataVoyage.voyages = NULL;


    stock = readStock();
    dataSpaceship = readSpaceshipsData(&stock);
    dataVoyage = readVoyagesFromFile("../textFiles/voyages.txt");

    launchSpaceship(&dataSpaceship, dataVoyage);

    do {
        showMainMenu();
        askForString(aux, "Choose an option: ");
        option = checkInt(aux);
        executeMainMenu(option, &dataUsers, &dataSpaceship, &dataCrew, stock, &dataVoyage);
    }while(option != 3);

    launch(&dataSpaceship, dataVoyage);

    saveUsers(dataUsers);
    saveSpaceship(dataSpaceship);
    saveCrew(dataCrew);
    saveVoyagesToFile(dataVoyage);

    return 0;
}