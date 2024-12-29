#ifndef PRUEBA_INTERFACE_H
#define PRUEBA_INTERFACE_H

#include "user.h"
#include "project.h"
#include "spaceship.h"
#include "crew.h"

void executeAdminMenu(int choice, DataUsers* d, DataSpaceship* ds, Crew_data* dc, DataSpaceship stock, String mail);

void showAdminMenu();

void showInvestigatorMenu();

void executeInvestigatorMenu(int choice, DataUsers d, DataProjects dp, int userIndex);

#endif
