#ifndef PRUEBA_READDATA_H
#define PRUEBA_READDATA_H
#include "../project.h"
#include "../spaceship.h"

int readData(LongString info, String str, int i);

DataUsers readUsersData();

DataProjects readProjectsData();

DataSpaceship readSpaceshipsData(DataSpaceship *stock);

void saveSpaceship(DataSpaceship data);

void saveProject(DataProjects dp);

void saveUsers(DataUsers data);

#endif //PRUEBA_READDATA_H
