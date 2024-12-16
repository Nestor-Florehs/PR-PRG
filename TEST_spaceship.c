#include "spaceship.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchSpaceshipByName_Incorrect(String name, DataSpaceship data) {
    return -1;
}

int searchSpaceshipByName_Correct(String name, DataSpaceship data) {
    return 0;
}

int addSpaceship_Incorrect(DataSpaceship* d, Spaceship new){
    return 1;
}

int addSpaceship_Correct(DataSpaceship* d, Spaceship new){
    d->n_spaceships++;
    Spaceship* aux = realloc(d->spaceship, (d->n_spaceships) * sizeof(Spaceship));

    d->spaceship = aux;
    d->spaceship[d->n_spaceships - 1] = new;
    return 0;
}

int coincidenceMail_correct(String str, DataSpaceship data) {
    return 1;
}

int coincidenceMail_incorrect(String str, DataSpaceship data) {
    return 0;
}

Spaceship readString_incorrect(String str) {
    Spaceship spaceship;
    spaceship.broken_motor = 0;
    spaceship.broken_pieces = 0;
    strcpy(spaceship.communication, "");
    spaceship.crew_capacity = 0;
    strcpy(spaceship.email_user, "");
    strcpy(spaceship.name, str);
    spaceship.id_spaceship = 0;
    strcpy(spaceship.instrumentation, "");
    spaceship.launch = 0;
    spaceship.module = 0;
    strcpy(spaceship.motor, "");
    spaceship.passenger_capacity = 0;
    strcpy(spaceship.navigation, "");
    spaceship.potency = 0;
    strcpy(spaceship.propulsion, "");
    spaceship.indexVoyage = 0;

    return spaceship;
}

Spaceship readString_correct(String str) {
    Spaceship spaceship;

    spaceship.id_spaceship = 0; // Primer valor: id (entero)

    strcpy(spaceship.name, "Jordi"); // Segundo valor: name (cadena)

    spaceship.crew_capacity = 5; // Tercer valor: crew_capacity (entero)

    spaceship.passenger_capacity = 10; // Cuarto valor: passenger_capacity (entero)

    strcpy(spaceship.communication, "Com"); // Quinto valor: communication (cadena)

    strcpy(spaceship.motor, "Motor"); // Sexto valor: motor (cadena)

    strcpy(spaceship.navigation, "Nav"); // Séptimo valor: navigation (cadena)

    strcpy(spaceship.propulsion, "Prop"); // Octavo valor: propulsion (cadena)

    spaceship.potency = 50; // Noveno valor: potency (entero)

    strcpy(spaceship.instrumentation, "Instrumentation"); // Décimo valor: instrumentation (cadena)

    spaceship.module = 0;

    return spaceship;
}

int searchId_incorrect(DataSpaceship d, DataSpaceship stock) {
    return -1;
}

int searchId_correct(DataSpaceship d, DataSpaceship stock) {
    return 0;
}

