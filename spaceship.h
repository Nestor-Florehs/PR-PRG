#ifndef SPACESHIP_H
#define SPACESHIP_H

struct voyageData;

typedef char String[100];

typedef struct {
    int id_spaceship;
    String email_user;
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
    int indexVoyage;
} Spaceship;

typedef struct {
    int n_spaceships;
    Spaceship* spaceship;
} DataSpaceship;

DataSpaceship buySpaceship(DataSpaceship d, DataSpaceship* stock, String email);

DataSpaceship readSpaceship();

DataSpaceship removeSpaceship (DataSpaceship data);

void showSpaceship(DataSpaceship data, String mail);

DataSpaceship modifySpaceship(DataSpaceship data, DataSpaceship stock);

void filterSpaceship(DataSpaceship data);

//DataSpaceship launchSpaceship(DataSpaceship data, struct VoyageData voyage);

DataSpaceship repairSpaceship(DataSpaceship data);

int atoiAux(String str);

void addSpaceship(DataSpaceship* d, Spaceship newSpaceship);

void removeStockByData(DataSpaceship d, DataSpaceship* stock);

#endif
