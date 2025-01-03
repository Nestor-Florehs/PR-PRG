#ifndef PRUEBA_READDATA_H
#define PRUEBA_READDATA_H
#include "../project.h"
#include "../spaceship.h"
#include "../crew.h"
#include "../voyage.h"

int readData(LongString info, String str, int i);

DataUsers readUsersData();

DataProjects readProjectsData();

DataSpaceship readSpaceshipsData(DataSpaceship *stock);

Crew_data readCrewData();

void saveSpaceship(DataSpaceship data);

void saveProject(DataProjects dp);

void saveCrew(Crew_data dc);

void saveUsers(DataUsers data);

void saveVoyagesToFile(VoyageData data);
VoyageData readVoyagesFromFile(char* filename);

#endif //PRUEBA_READDATA_H
