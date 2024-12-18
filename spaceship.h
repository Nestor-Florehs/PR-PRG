#ifndef SPACESHIP_H
#define SPACESHIP_H

struct voyageData;

typedef char String[100];

typedef struct {
    int id_spaceship;
    int id_user;
    String name;
    int crew_capacity;
    int passenger_capacity;
    String communication;
    String motor;
    int broken_motor;
    String navigation;
    String propulsion;
    int potency;
    String instrumentation;
    int module;
    int broken_pieces;
    int launch;
    int actual_n_crew;
} Spaceship;

typedef struct {
    int n_spaceships;
    Spaceship* spaceship;
} DataSpaceship;

DataSpaceship buySpaceship(DataSpaceship d, DataSpaceship* stock, int id);

DataSpaceship readSpaceship();

void printSpaceship(DataSpaceship data, int i);

DataSpaceship removeSpaceship (DataSpaceship data);

DataSpaceship modifySpaceship(DataSpaceship data, DataSpaceship stock);

void filterSpaceship(DataSpaceship data);

DataSpaceship repairSpaceship(DataSpaceship data);

int atoiAux(String str);

void addSpaceship(DataSpaceship* d, Spaceship newSpaceship);

void removeStockByData(DataSpaceship d, DataSpaceship* stock);

DataSpaceship readStock();

void showSpaceship(DataSpaceship data, int id);

int searchSpaceshipByName(String str, DataSpaceship data);

#endif
