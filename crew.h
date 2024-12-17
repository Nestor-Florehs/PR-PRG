#ifndef CREW_H
#define CREW_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "user.h"
#include "auxiliar.h"
#include "spaceship.h"

typedef char String[100];

typedef struct {
    int id;
    int id_spaceship;
} Id_Spaceship;

typedef struct {
    int n_spaceships;
    Id_Spaceship* id_spaceship;
} Id_spaceship;

typedef struct {
    int id;
    String name;
    int age;
    String rol;
    String uniform_color;
    String contact_info;
    int support;
    Id_spaceship id_spaceship;
} Crew;

typedef struct {
    int n_crew;
    Crew* crew;
} Crew_data;

Crew_data menuCrew(Crew_data data, DataSpaceship data_spaceship);

Crew_data initializeCrewData(Crew_data data);

#endif