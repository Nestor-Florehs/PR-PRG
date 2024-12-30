#ifndef PRUEBA_PROJECT_H
#define PRUEBA_PROJECT_H

#include "user.h"

typedef char String[100];
typedef char LongString[1000];

typedef struct {
    int accepted;   // 0 = pending / 1 = accepted / -1 = denied
    int id;
    String title;
    String responsible;
    String status;
    LongString description;
    float cost;
    float budget;
    int n_members;
    String team_members[20];
    String goal;
    char design;   // T = trip / S = ship
    int posted;
} Project;

typedef struct {
    int n_projects;
    Project* project;
} DataProjects;

DataProjects createProject(DataProjects dp, DataUsers du, int user_idx);

int addProject(DataProjects * d, Project newProject);

void showProjectDetails(DataProjects dp);

DataProjects validateProject(DataProjects dp);

DataProjects updateProject(DataProjects dp, int idx_user, DataUsers du);

DataProjects deleteProject(DataProjects dp, int idx_user, DataUsers du);

DataProjects postProject(DataProjects dp);

DataProjects reviewProject(DataProjects dp, int idx_user, DataUsers du);

#endif