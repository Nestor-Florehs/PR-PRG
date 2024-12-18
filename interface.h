#ifndef PRUEBA_INTERFACE_H
#define PRUEBA_INTERFACE_H

#include "user.h"
#include "project.h"
#include "spaceship.h"
#include "crew.h"
#include "voyage.h"

void executeAdminMenu(int choice, DataUsers* d, DataSpaceship* ds, Crew_data* dc, DataSpaceship stock, int id,VoyageData* voyage_data);

void showAdminMenu();

void showInvestigatorMenu();

void executeInvestigatorMenu(int choice, DataUsers d, DataProjects dp, int userIndex);

void executeClientMenu(int option,DataUsers* data_users, VoyageData* voyage_data, DataSpaceship stock);

void showClientMenu(DataUsers* data_users, VoyageData* voyage_data);
#endif