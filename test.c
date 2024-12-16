#include "spaceship.h"
#include <stdlib.h>

/* int test_addSpaceship(Data1* d, Spaceship new) {
    return 1;
} */

int test_addSpaceship(DataSpaceship* d, Spaceship new) {
    Spaceship* aux = realloc (d->spaceship, (d->n_spaceships + 1) * sizeof(Spaceship));
    d->spaceship = aux;
    d->spaceship[d->n_spaceships] = new;
    d->n_spaceships++;;
    return 0;
}