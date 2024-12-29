#ifndef READDATA_H
#define READDATA_H
#include "../project.h"
#include "../spaceship.h"
#include "../crew.h"

int readData(LongString info, String str, int i);

DataUsers readUsersData();

DataProjects readProjectsData();

DataSpaceship readSpaceshipsData(DataSpaceship *stock);

Crew_data readCrewData();

void saveSpaceship(DataSpaceship data);

void saveProject(DataProjects dp);

void saveCrew(Crew_data dc);

void saveUsers(DataUsers data);

#endif //READDATA_H
