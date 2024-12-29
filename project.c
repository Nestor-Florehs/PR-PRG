#include "project.h"
#include "auxiliar.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int addProject(DataProjects * d, Project newProject){
    int error = 0;
    Project* aux = realloc(d->project, (d->n_projects + 1)*sizeof(Project));
    if(aux == NULL){
        printf("(ERROR) Memory failed");
        error = 1;
    }else{
        d->project = aux;
        d->project[d->n_projects] = newProject;
        d->n_projects++;
    }
    return error;
}

DataProjects createProject(DataProjects dp, DataUsers du, int user_idx){
    Project newProject;
    int error = 0, quit = 0, found, j;
    char aux;
    String cost, budget, design, member;

    newProject.n_members = 0;
    newProject.accepted = 0;
    newProject.posted = 0;
    strcpy(newProject.status, "-");
    strcpy(newProject.responsible, du.user[user_idx].email);
    askForString(newProject.title, "Enter the title: ");
    askForLongString(newProject.description, "Enter the description: ");
    askForString(cost, "Enter the cost: ");
    newProject.cost = checkDecimal(cost);

    if(newProject.cost != -1){
        askForString(budget, "Enter the budget: ");
        newProject.budget = checkDecimal(budget);
        if(newProject.budget != -1) {
            askForString(newProject.goal, "Enter the goal: ");

            askForString(design, "Enter your design: [T]rip or [S]hip: ");
            newProject.design = toupper(design[0]);
            if(newProject.design != 'T' && newProject.design != 'S') {
                printf("(ERROR) This design does not exist\n");
                error = 1;
            }
            if(!error){
                printf("Investigators available: \n");
                for(int i = 0; i < du.n_users; i++){
                    if(du.user[i].rol == 'R' && i != user_idx){
                        printf("\t-%s\n", du.user[i].email);
                    }
                }
                j = 0;
                do {
                    found = 0;
                    askForString(member, "Enter a member email or introduce 'Q' for quit:");
                    if(toupper(member[0]) == 'Q' && (member[1] == ' ' || member[1] == '\0')){
                        quit = 1;
                    }else{
                        for(int i = 0; i < du.n_users && !found; i++){
                            if(strcmp(du.user[i].email, member) == 0 && du.user[i].rol == 'R'){
                                found = 1;
                                strcpy(newProject.team_members[j], member);
                                j++;
                                newProject.n_members++;
                                printf("Investigator added!\n");
                            }
                        }
                        if(!found){
                            printf("This investigator does not exist\n");
                        }
                    }
                }while(quit == 0);
                if(dp.n_projects == 0){
                    newProject.id = 1;
                }else{
                    newProject.id = dp.project[dp.n_projects-1].id + 1;
                }
                error = addProject(&dp, newProject);
                if(!error){
                    printf("Project created!\n");
                    printf("Your project id is (%d)\n", newProject.id);
                }
            }
        }else{
            printf("(ERROR) Enter a valid number.\n");
        }
    }else{
        printf("(ERROR) Enter a valid number.\n");
    }
    return dp;
}

void showProjectDetails(DataProjects dp){
    String idStr;
    int id, i, j, found = 0;
    askForString(idStr, "Enter the ID of the project: ");
    id = checkInt(idStr);
    if(id != -1){
        for(i = 0; i < dp.n_projects && !found; i++){
            if(id == dp.project[i].id){
                printf("Project #%d: %s\n", dp.project[i].id, dp.project[i].title);
                printf("  Responsible: %s\n", dp.project[i].responsible);
                printf("  Description: %s\n", dp.project[i].description);
                printf("  Goal: %s\n", dp.project[i].goal);
                printf("  Cost: %.2f || Budget: %.2f\n", dp.project[i].cost, dp.project[i].budget);
                if(dp.project[i].design == 'S'){
                    printf("  Type of design: Ship\n");
                }else{
                    printf("  Type of design: Trip\n");
                }
                printf("  Status: %s\n", dp.project[i].status);
                printf("  Team members(%d): \n", dp.project[i].n_members);
                for(j = 0; j < dp.project[i].n_members; j++){
                    printf("\t-%s \n", dp.project[i].team_members[j]);
                }
                switch (dp.project[i].accepted) {
                    case -1:
                        printf("  This project has been denied\n");
                        break;
                    case 0:
                        printf("  This project is pending approval\n");
                        break;
                    case 1:
                        printf("  This project has been approved\n");
                        break;
                }
                found = 1;
            }
        }
        if(!found){
            printf("This ID project does not exist\n");
        }
    }else{
        printf("(ERROR) Enter a valid number\n");
    }
}

DataProjects validateProject(DataProjects dp){
    String idStr, validation;
    int id, i, j, found = 0;
    askForString(idStr, "Enter the ID of the project: ");
    id = checkInt(idStr);

    if(id != -1){
        for(i = 0; i < dp.n_projects && !found; i++){
            if(dp.project[i].id == id){
                found = 1;
                if(dp.project[i].accepted == 0) {
                    printf("%s\n", dp.project[i].title);
                    askForString(validation, "Enter 'Y' for accept or 'N' for deny: ");
                    if (toupper(validation[0]) == 'Y' && validation[1] == '\0') {
                        printf("The project has been approved\n");
                        strcpy(dp.project[i].status, "TO DO");
                        dp.project[i].accepted = 1;
                    } else {
                        if (toupper(validation[0]) == 'N' && validation[1] == '\0') {
                            printf("The project has been denied\n");
                            dp.project[i].accepted = -1;
                        } else {
                            printf("(ERROR) Enter a valid option\n");
                        }
                    }
                }else{
                    printf("This project is not pending approval\n");
                }
            }
        }
        if(!found){
            printf("This ID project does not exist\n");
        }
    }else{
        printf("(ERROR) Enter a valid number\n");
    }
    return dp;
}

int checkID(int idProject, int id){
    int check = 0;
    if(idProject == id){
        check = 1;
    }
    return check;
}

int checkAccepted(int accepted){
    int check = 0;
    if(accepted == 1){
        check = 1;
    }
    return check;
}

DataProjects updateProject(DataProjects dp, int idx_user, DataUsers du){
    int num, id, i, found = 0;
    String idStr;

    askForString(idStr, "Enter the ID of the project: ");
    id = checkInt(idStr);

    if(id != -1) {
        for (i = 0; i < dp.n_projects && !found; i++) {
            if (checkID(dp.project[i].id, id)) {
                found = 1;
                if(!strcmp(dp.project[i].responsible, du.user[idx_user].email)) {
                    if(dp.project[i].accepted == 1) {
                        if (strcmp(dp.project[i].status, "DONE")) {
                            srand(time(NULL));
                            num = rand() % (100 + 1);
                            printf("To update the project you need 50 points\n");
                            printf("\tYour project has obtained %d points\n", num);
                            if (num >= 50) {
                                if (!strcmp(dp.project[i].status, "TO DO")) {
                                    strcpy(dp.project[i].status, "IN PROGRESS");
                                } else {
                                    if (!strcmp(dp.project[i].status, "IN PROGRESS")) {
                                        strcpy(dp.project[i].status, "IN REVIEW");
                                    } else {
                                        if (!strcmp(dp.project[i].status, "IN REVIEW")) {
                                            strcpy(dp.project[i].status, "DONE");
                                        }
                                    }
                                }
                                printf("Your project has been updated to '%s'\n", dp.project[i].status);
                            } else {
                                printf("Your project has not been updated\n");
                            }
                        } else {
                            printf("Your project is already fully updated\n");
                        }
                    }else{
                        printf("Your project must be accepted for updates\n");
                    }
                }else{
                    printf("You're not the responsible of this project\n");
                }
            }
        }
        if(!found){
            printf("This project ID does not exist\n");
        }
    }else{
        printf("(ERROR) Enter a valid number\n");
    }
    return dp;
}

int removeProject(DataProjects* dp, int index){
    int error = 0;
    if(dp->n_projects < 1){
        printf("Memory is already empty");
    }else{
        memmove(&dp->project[index], &dp->project[index+1], (dp->n_projects-(index+1))* sizeof(Project));
        Project* aux = realloc(dp->project, (dp->n_projects-1)*sizeof(Project));
        if(aux == NULL){
            error = 1;
            printf("(ERROR) Memory failed");
        }else{
            dp->project = aux;
            dp->n_projects--;
        }
    }
    return error;
}

int checkResponsible(String responsible, String email){
    int check = 0;
    if(!strcmp(responsible, email)){
        check = 1;
    }
    return check;
}

DataProjects deleteProject(DataProjects dp, int idx_user, DataUsers du){
    int num, id, i, found = 0, error;
    String idStr;

    askForString(idStr, "Enter the project ID: ");
    id = checkInt(idStr);

    if(id != -1) {
        for (i = 0; i < dp.n_projects && !found; i++) {
            if (dp.project[i].id == id) {
                found = 1;
                if(checkResponsible(dp.project[i].responsible, du.user[idx_user].email)) {
                    if(dp.project[i].accepted == -1) {
                        error = removeProject(&dp, i);
                        if(!error){
                            printf("Your project has been deleted\n");
                        }
                    }else{
                        printf("Your project must be denied for deleting\n");
                    }
                }else{
                    printf("You're not the responsible of this project\n");
                }
            }
        }
        if(!found){
            printf("This project ID does not exist\n");
        }
    }else{
        printf("(ERROR) Enter a valid number\n");
    }
    return dp;
}

int checkDone(String responsible){
    int check = 0;
    if(!strcmp(responsible, "DONE")){
        check = 1;
    }
    return check;
}

void savePostedProject(DataProjects dp){
    int i, j;
    FILE*f;
    f = fopen("C:\\Users\\ggpp8\\OneDrive\\Escritorio\\La Salle Enginyeria\\2n curs\\ProjectesDeProg\\Prog_I\\P1\\prueba\\textFiles\\PostedProjects.txt", "w");
    if(f == NULL){
        printf("error opening file");
    }else{
        for(i = 0; i < dp.n_projects; i++){
            if(dp.project[i].posted == 1) {
                fprintf(f, "%s#", dp.project[i].responsible);
                fprintf(f, "%s#", dp.project[i].title);
                fprintf(f, "%s#", dp.project[i].description);
                fprintf(f, "%s#", dp.project[i].status);
                fprintf(f, "%.2f#", dp.project[i].cost);
                fprintf(f, "%.2f#", dp.project[i].budget);
                fprintf(f, "%s#", dp.project[i].goal);
                fprintf(f, "%c#", dp.project[i].design);
                fprintf(f, "%d#", dp.project[i].n_members);
                for (j = 0; j < dp.project[i].n_members; j++) {
                    fprintf(f, "%s#", dp.project[i].team_members[j]);
                }
                fprintf(f, "%d#", dp.project[i].accepted);
                fprintf(f, "%d#", dp.project[i].posted);
                fprintf(f, "%d\n", dp.project[i].id);
            }
        }
        fclose(f);
    }
}

DataProjects postProject(DataProjects dp){
    int num, id, i, found = 0;
    String idStr;

    askForString(idStr, "Enter the project ID: ");
    id = checkInt(idStr);

    if(id != -1) {
        for (i = 0; i < dp.n_projects && !found; i++) {
            if (checkID(dp.project[i].id, id)) {
                found = 1;
                if(dp.project[i].accepted == 1) {
                    if (checkDone(dp.project[i].status)) {
                        dp.project[i].posted = 1;
                        savePostedProject(dp);
                        printf("Your project has been posted on a file\n");
                    } else {
                        printf("Your project hasn't finished\n");
                    }
                }else{
                    printf("Your project must be accepted for updates\n");
                }
            }else{
                printf("You're not the responsible of this project\n");
            }
        }
        if(!found){
            printf("This project ID does not exist\n");
        }
    }else{
        printf("(ERROR) Enter a valid number\n");
    }
    return dp;
}

void showDataToModify(){
    printf("Data to modify:\n");
    printf("\t1. Title\n");
    printf("\t2. Description\n");
    printf("\t3. Cost\n");
    printf("\t4. Budget\n");
    printf("\t5. Goal\n");
}

DataProjects modifyOption(int option, DataProjects dp, int i){
    String newTitle, newGoal, budgetChar, costChar;
    LongString newDescription;
    float newBudget, newCost;

    switch(option){
        case 1:
            askForString(newTitle, "\nEnter a new title: ");
            strcpy(dp.project[i].title, newTitle);
            break;
        case 2:
            askForLongString(newDescription, "Enter a new description: ");
            strcpy(dp.project[i].description, newDescription);
            break;
        case 3:
            askForString(costChar, "Enter a new cost: ");
            newCost = checkInt(costChar);
            dp.project[i].cost = newCost;
            break;
        case 4:
            askForString(budgetChar, "Enter a new budget: ");
            newBudget = checkInt(budgetChar);
            dp.project[i].budget = newBudget;
            break;
        case 5:
            askForString(newGoal, "Enter a new goal: ");
            strcpy(dp.project[i].goal, newGoal);
            break;
        default:
            printf("Please enter a valid option\n");
    }
    return dp;
}

DataProjects reviewProject(DataProjects dp, int idx_user, DataUsers du){
    int option, id, i, found = 0;
    String idStr, opt, newTitle, newGoal, budgetChar, costChar;
    LongString newDescription;
    float newBudget, newCost;

    askForString(idStr, "Enter the project ID to review: ");
    id = checkInt(idStr);

    if(id != -1) {
        for (i = 0; i < dp.n_projects && !found; i++) {
            if (checkID(dp.project[i].id, id)) {
                found = 1;
                if(!strcmp(dp.project[i].responsible, du.user[idx_user].email)) {
                    if(dp.project[i].posted == 1) {
                        showDataToModify();
                        askForString(opt, "Choose an option: ");
                        option = checkInt(opt);
                        if(option != -1){
                            dp = modifyOption(option, dp, i);
                        }else{
                            printf("(ERROR) Enter a valid number\n");
                        }
                    }else{
                        printf("Your project must be accepted for updates\n");
                    }
                }else{
                    printf("You're not the responsible of this project\n");
                }
            }
        }
        if(!found){
            printf("This project ID does not exist\n");
        }
    }else{
        printf("(ERROR) Enter a valid number\n");
    }
    return dp;
}