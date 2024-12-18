#include "interface.h"
#include "project.h"
#include "user.h"
#include "readData/readData.h"
#include "auxiliar.h"
#include "crew.h"
#include "spaceship.h"
#include "voyage.h"


void showAdminProjectsMenu() {
    printf("\nAdmin projects functions:");
    printf("\n\t1. Show project details\n");
    printf("\t2. Validate a project\n");
    printf("\t3. Exit\n");
}


DataUsers executeAdminProjectsMenu(int choice, DataUsers d, DataProjects dp) {
    switch (choice) {
        case 1:
            showProjectDetails(dp);
            saveProject(dp);
            break;
        case 2:
            dp = validateProject(dp);
            saveProject(dp);
            break;
        case 3:
            printf("Back to the previous screen.\n");
            break;
        default:
            printf("Invalid Choice\n");
    }
    return d;
}

void showAdminMenu() {
    printf("\nAdmin functions:");
    printf("\n\t1. Manage client\n");
    printf("\t2. Manage researcher\n");
    printf("\t3. Manage spaceship\n");
    printf("\t4. Manage crew\n");
    printf("\t5. Manage project\n");
    printf("\t6. Create travel\n");
    printf("\t7. Exit\n");
}

void showAdminSpaceshipMenu() {
    printf("\nManage Spaceship:");
    printf("\n\t1. Buy Spaceship\n");
    printf("\t2. Modify Spaceship\n");
    printf("\t3. Repair Spaceship\n");
    printf("\t4. Delete Spaceship\n");
    printf("\t5. List Spaceship\n");
    printf("\t7. Filter Spaceship\n");
    printf("\t8. Exit\n");
}

DataSpaceship runManageSpaceship(DataSpaceship ds, DataSpaceship *stock, int id, VoyageData voyages) {
    int option = 0;
    do {
        String aux;
        showAdminSpaceshipMenu();
        askForString(aux, "Enter option: ");
        option = checkInt(aux);
        switch (option) {
            case 1:
                ds = buySpaceship(ds, stock, id);
            break;
            case 2:
                ds = modifySpaceship(ds, *stock);
            break;
            case 3:
                repairSpaceship(ds);
                break;
            case 4:
                ds = removeSpaceship(ds);
                break;
            case 5:
                showSpaceship(ds, id);
                break;
            case 6:
                filterSpaceship(ds);
                break;
            case 7:
                printf("Exit\n");
                launch(&ds, voyages);
                break;
            default:
                printf("Invalid option");
                break;
        }
    } while (option != 8);

    return ds;
}

void showManageClientMenu() {
    printf("\nManage Clients:");
    printf("\n\t1. Show clients\n");
    printf("\t2. Modify client\n");
    printf("\t3. Delete client\n");


    printf("\t4. Exit\n");

    printf("Choose: ");
}


DataUsers executeManageClientMenu(int choice, DataUsers d) {
    switch (choice) {
        case 1:
            showClientData(d);
            break;
        case 2:
            d = modifyDataClient(d);
            break;
        case 3:
            d = removeClient(d);
            break;
        case 4:
            break;
        default:
            printf("Invalid Choice\n");
    }
    return d;
}

DataUsers runManageClient(DataUsers data_users) {
    int option = 0;
    char aux;
    do {
        showManageClientMenu();
        scanf("%d", &option);
        scanf("%c", &aux);
        data_users = executeManageClientMenu(option, data_users);
    }while(option != 4);

    return data_users;
}

void showManageResearcherMenu() {
    printf("\nManage Researchers:");
    printf("\n\t1. Add Researcher\n");
    printf("\t2. Modify Researcher\n");
    printf("\t3. Delete Researcher\n");
    printf("\t4. Filter Researcher\n");
    printf("\t5. Exit\n");
    printf("Choose: ");
}


//FIXME
DataUsers executeManageResearcherMenu(int option, DataUsers data_users) {
    switch (option) {
        case 1:
            data_users = createReasercher(data_users);
        break;
        case 2:
            data_users = modifyResearcher(data_users);
        break;
        case 3:
            data_users = removeResearcher(data_users);
            data_users.n_users--;
            break;
        case 4:
            User* user = searchResearcher(data_users);
        if (user != NULL) {
            printf("\nUser %d\n", user->id);
            printf("\tName: %s\n", user->name);
            printf("\tEmail: %s\n", user->email);
            printf("\tRol: %c\n", user->rol);
        }
        break;
        case 5:
            break;
        default:
            printf("Invalid Choice\n");
    }

    return data_users;
}

DataUsers runManageResearcher(DataUsers data_users) {
    int option = 0;
    char aux;
    do {
        showManageResearcherMenu();
        scanf("%d", &option);
        scanf("%c", &aux);
        data_users = executeManageResearcherMenu(option, data_users);
    }while(option != 5);

    return data_users;
}

void executeAdminMenu(int choice, DataUsers* d, DataSpaceship* ds, Crew_data* dc, DataSpaceship stock, int id,VoyageData* voyage_data) {
    int projectOption = 0;
    DataProjects dp;
    String option;
    switch (choice) {
        case 1:
            *d = runManageClient(*d);
            break;
        case 2:
            *d = runManageResearcher(*d);
            break;
        case 3:
            *ds = runManageSpaceship(*ds, &stock, id, *voyage_data);
            break;
        case 4:
            *dc = menuCrew(*dc, *ds);
            break;
        case 5:
            do {
                showAdminProjectsMenu();
                askForString(option, "Enter option: ");
                projectOption = checkInt(option);
                if(projectOption != -1) {
                    dp = readProjectsData();
                    *d = executeAdminProjectsMenu(projectOption, *d, dp);
                }else {
                    printf("Please enter a valid option!");
                }
            }while(projectOption != 3);
            break;
        case 6:
            *voyage_data = createVoyage(*voyage_data,stock);

            break;
        case 7:
            break;
        default:
            printf("Invalid Choice\n");
    }

}

void showInvestigatorMenu() {
    printf("\nInvestigator functions:");
    printf("\n\t1. Create project\n");
    printf("\t2. Show project details\n");
    printf("\t3. Update a project\n");
    printf("\t4. Delete a project\n");
    printf("\t5. Post a project\n");
    printf("\t6. Review a project\n");
    printf("\t7. Exit\n");
}

void executeInvestigatorMenu(int choice, DataUsers du, DataProjects dp, int indexUser) {
    switch (choice) {
        case 1:
            dp = createProject(dp, du, indexUser);
            saveProject(dp);
            break;
        case 2:
            showProjectDetails(dp);
            break;
        case 3:
            dp = updateProject(dp, indexUser, du);
            saveProject(dp);
            break;
        case 4:
            dp = deleteProject(dp, indexUser, du);
            saveProject(dp);
            break;
        case 5:
            dp = postProject(dp);
            saveProject(dp);
        case 6:
            dp = reviewProject(dp, indexUser, du);
            saveProject(dp);
            break;
        case 7:
            printf("Exit\n");
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void showClientMenu(DataUsers* data_users, VoyageData* voyage_data) {
    printf("\nClient functions:");
    printf("\n\t1. Modify user data\n");
    printf("\t2. Delete account\n");
    printf("\t3. List voyages by avaliability\n");
    printf("\t4. Filter voyages\n");
    printf("\t5. Buy ticket\n");
    printf("\t6. Rate voyage\n");
    printf("\t7. Cancel ticket\n");
    printf("\t8. Exit\n");
}

void executeClientMenu(int option,DataUsers* data_users, VoyageData* voyage_data, DataSpaceship stock) {
    VoyageData filtered_data;
    FilterCriteria filter_criteria;
    switch (option) {
    case 1:

        break;
    case 2:
        break;
    case 3:
        filtered_data=filterVoyagesBySeats(*voyage_data,0);
        showVoyages(filtered_data);
        break;
    case 4:
        filter_criteria = askFilterCritera();
        filtered_data = filterVoyages(*voyage_data,filter_criteria);
        showVoyages(filtered_data);
        break;
    case 5:
        *voyage_data=buyTicket(*voyage_data);
        break;
    case 6:
        //rateVoyage(*voyage_data,*data_users,1,date);
        break;
     case 7:
         break;
     case 8:
         break;
     default:
         printf("Invalid Choice\n");
        break;
    }
}