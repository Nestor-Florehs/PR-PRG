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
    String name;
    int age;
    String rol;
    String uniform_color;
    String contact_info;
    int support;
    Spaceship* spaceship;
} Crew;

typedef struct {
    int n_crew;
    Crew* crew;
} Crew_data;

Crew_data removeCrew(Crew_data data);

Crew_data hireCrew(Crew_data data, int support_crew_member);

void viewCrew(Crew_data data);

#endif