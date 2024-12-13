#ifndef PRUEBA_INTERFACE_H
#define PRUEBA_INTERFACE_H

#include "user.h"
#include "project.h"
#include "spaceship.h"

void executeAdminMenu(int choice, DataUsers* d, DataSpaceship* ds, DataSpaceship stock, String mail);

void showAdminMenu();

void showInvestigatorMenu();

void executeInvestigatorMenu(int choice, DataUsers d, DataProjects dp, int userIndex);

#endif
