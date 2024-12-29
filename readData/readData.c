#include "readData.h"
#include "../user.h"
#include "../crew.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readData(LongString info, String str, int i){
    int k = 0;
    for(i = i; info[i] != '#' && info[i] != '\0'; i++){
        str[k] = info[i];
        k++;
    }
    str[k] = '\0';
    i++;
    return i;
}

int addUser2(DataUsers* d, User newUser){
    int error = 0;
    User* aux = realloc(d->user, (d->n_users + 1)*sizeof(User));
    if(aux == NULL){
        printf("(ERROR) Memory failed");
        error = 1;
    }else{
        d->user = aux;
        d->user[d->n_users] = newUser;
        d->n_users++;
    }
    return error;
}

int addProject2(DataProjects * d, Project newProject){
    int error = 0;
    Project* aux = realloc(d->project, (d->n_projects + 1)*sizeof(Project));
    if(aux == NULL){
        printf("(ERROR) Memory failed");
        error = 1;
    }else{
        d->project = aux;
        d->project[d->n_projects] = newProject;
        d->n_projects++;
    }
    return error;
}

int addCrew2(Crew_data* d, Crew newCrew) {
    int error = 0;

    // Intenta reasignar memoria para el nuevo usuario
    Crew* aux = NULL;
    aux = realloc(d->crew, (d->n_crew + 1) * sizeof(Crew));

    // Si realloc falla, retorna error sin perder el puntero original
    if (aux == NULL) {
        printf("(ERROR) Memory allocation failed.\n");
        error = 1;
    } else {
        // Si realloc tiene éxito, actualiza el puntero y el número de usuarios
        d->crew = aux;
        d->crew[d->n_crew] = newCrew;
        d->n_crew++;
        if(d->crew == NULL){
            printf("(ERROR) Memory pointers elsewhere\n");
            error = 1;
        }
    }

    return error;
}

int addIdSpaceship2(Crew_data* d, int i, Id_Spaceship newIdSpaceship) {
    int error = 0;

    if (d == NULL || d->crew == NULL) {
        printf("(ERROR) Invalid pointer.\n");
        return 1;
    }

    if (i < 0 || i >= d->n_crew) {
        printf("(ERROR) Index out of bounds.\n");
        return 1;
    }

    // Obtener el puntero a Id_spaceship del miembro Crew
    Id_spaceship* id_spaceship_data = &d->crew[i].id_spaceship;

    // Inicializar id_spaceship si es NULL
    if (id_spaceship_data->id_spaceship == NULL) {
        id_spaceship_data->id_spaceship = malloc(sizeof(Id_Spaceship));
        if (id_spaceship_data->id_spaceship == NULL) {
            printf("(ERROR) Memory allocation failed during initialization.\n");
            return 1;
        }
        id_spaceship_data->n_spaceships = 0;
    }

    // Intentar reasignar memoria para el arreglo de Id_Spaceship
    Id_Spaceship* aux = realloc(id_spaceship_data->id_spaceship, (id_spaceship_data->n_spaceships + 1) * sizeof(Id_Spaceship));

    if (aux == NULL) {
        // Si falla realloc, retornar error sin modificar el puntero original
        printf("(ERROR) Memory allocation failed.\n");
        error = 1;
    } else {
        // Si realloc es exitoso, actualizar el puntero y agregar el nuevo elemento
        id_spaceship_data->id_spaceship = aux;
        id_spaceship_data->id_spaceship[id_spaceship_data->n_spaceships] = newIdSpaceship;
        id_spaceship_data->n_spaceships++;
    }

    return error;
}

DataUsers readUsersData(){
    DataUsers du;
    int i, j, error = 0, n_users;
    LongString info;
    User user;
    String num, aux;
    du.n_users = 0;
    du.user = NULL;
    FILE *f = fopen("..\\textFiles\\RegisterUser.txt", "r");
    if(f == NULL){
        printf("Error opening file - User\n");
    }else{
        fgets(num, 50, f);
        num[strlen(num)-1] = '\0';
        n_users = atoiAux(num);
        for(j = 0; j < n_users; j++) {
            fgets(info, 999, f);
            i = 0;
            i = readData(info, user.name, i);
            i = readData(info, user.email, i);
            i = readData(info, user.password, i);
            user.rol = info[i];
            i += 2;
            i = readData(info, user.pin, i);
            i = readData(info, aux, i);
            user.id = atoiAux(aux);
            error = addUser2(&du, user);
        }
    }
    return du;
}

DataProjects readProjectsData() {
    DataProjects dp;
    int i, j, k, error = 0, n_projects;
    LongString info;
    FILE* f;
    Project project;
    String num, aux;
    dp.n_projects = 0;
    dp.project = NULL;
    f = fopen("..\\textFiles\\Projects.txt", "r");
    if(f == NULL){
        printf("Error opening file - Projects\n");
    }else{
        fgets(num, 50, f);
        num[strlen(num)-1] = '\0';
        n_projects = atoiAux(num);
        for(j = 0; j < n_projects; j++) {
            fgets(info, 999, f);
            i = 0;
            i = readData(info, project.responsible, i);
            i = readData(info, project.title, i);
            i = readData(info, project.description, i);
            i = readData(info, project.status, i);
            i = readData(info, aux, i);
            project.cost = atof(aux);
            i = readData(info, aux, i);
            project.budget = atof(aux);
            i = readData(info, project.goal, i);
            project.design = info[i];
            i += 2;
            i = readData(info, aux, i);
            project.n_members = atoiAux(aux);
            for(k = 0; k < project.n_members; k++){
                i = readData(info, project.team_members[k], i);
            }
            i = readData(info, aux, i);
            project.accepted = atoiAux(aux);
            i = readData(info, aux, i);
            project.posted = atoiAux(aux);
            i = readData(info, aux, i);
            project.id = atoiAux(aux);

            error = addProject2(&dp, project);
        }
        fclose(f);
    }
    return dp;
}

DataSpaceship readSpaceshipsData(DataSpaceship* stock) {
    DataSpaceship ds;
    ds.n_spaceships = 0;
    ds.spaceship = NULL;
    FILE *f = fopen("..\\textFiles\\Spaceships.txt", "r");
    if(f == NULL){
        printf("Error opening file - Spaceships\n");
    }else{
        String num;
        fgets(num, 50, f);
        num[strlen(num) - 1] = '\0';
        int n_spaceships = atoiAux(num);
        for(int j = 0; j < n_spaceships; j++) {
            LongString info;
            String aux;
            Spaceship s;
            fgets(info, 999, f);
            int i = 0;
            i = readData(info, aux, i);
            s.id_spaceship = atoiAux(aux);
            i = readData(info, s.email_user, i);
            i = readData(info, s.name, i);
            i = readData(info, aux, i);
            s.crew_capacity = atoiAux(aux);
            i = readData(info, aux, i);
            s.passenger_capacity = atoiAux(aux);
            i = readData(info, s.communication, i);
            i = readData(info, s.motor, i);
            i = readData(info, aux, i);
            s.broken_motor = atoiAux(aux);
            i = readData(info, s.navigation, i);
            i = readData(info, s.propulsion, i);
            i = readData(info, aux, i);
            s.potency = atoiAux(aux);
            i = readData(info, s.instrumentation, i);
            i = readData(info, aux, i);
            s.module = atoiAux(aux);
            i = readData(info, aux, i);
            s.broken_pieces = atoiAux(aux);
            i = readData(info, aux, i);
            s.launch = atoiAux(aux);
            i = readData(info, aux, i);
            s.indexVoyage = atoiAux(aux);
            i = readData(info, aux, i);
            s.actual_n_crew = atoiAux(aux);

            addSpaceship(&ds, s);
        }
        fclose(f);
        removeStockByData(ds, stock);
    }
    return ds;
}

Crew_data readCrewData() {
    Crew_data dc;
    int i, j, k, error = 0, n_crew;
    LongString info;
    FILE* f;
    Crew crew;
    Id_Spaceship id_spaceship;
    String num, aux;
    dc.n_crew = 0;
    dc.crew = NULL;
    f = fopen("..\\textFiles\\Crew.txt", "r");
    if(f == NULL){
        printf("Error opening file - Crew\n");
    }else{
        fgets(num, 50, f);
        num[strlen(num)-1] = '\0';
        n_crew = atoiAux(num);
        for(j = 0; j < n_crew; j++) {
            fgets(info, 999, f);
            i = 0;
            i = readData(info, aux, i);
            crew.id = atoi(aux);
            i = readData(info, crew.name, i);
            i = readData(info, aux, i);
            crew.age = atoi(aux);
            i = readData(info, crew.rol, i);
            i = readData(info, crew.uniform_color, i);
            i = readData(info, crew.contact_info, i);
            i = readData(info, aux, i);
            crew.support = atoi(aux);
            i = readData(info, aux, i);
            crew.id_spaceship.n_spaceships = atoi(aux);
            crew.id_spaceship.id_spaceship = NULL;
            error = addCrew2(&dc, crew);
            for (k = 0; k < crew.id_spaceship.n_spaceships; k++) {
                i = readData(info, aux, i);
                id_spaceship.id = atoi(aux);
                i = readData(info, aux, i);
                id_spaceship.id_spaceship = atoi(aux);
                addIdSpaceship2(&dc, j, id_spaceship);
            }
        }
        fclose(f);
    }
    return dc;
}

void saveSpaceship(DataSpaceship ds) {
    FILE* f = fopen("..\\textFiles\\Spaceships.txt", "w");
    if(f == NULL){
        printf("Error opening file - Spaceship\n");
    }else{
        fprintf(f, "%d\n", ds.n_spaceships);
        for (int i = 0; i < ds.n_spaceships; i++){
            fprintf(f, "%d#", ds.spaceship[i].id_spaceship);
            fprintf(f, "%s#", ds.spaceship[i].email_user);
            fprintf(f, "%s#", ds.spaceship[i].name);
            fprintf(f, "%d#", ds.spaceship[i].crew_capacity);
            fprintf(f, "%d#", ds.spaceship[i].passenger_capacity);
            fprintf(f, "%s#", ds.spaceship[i].communication);
            fprintf(f, "%s#", ds.spaceship[i].motor);
            fprintf(f, "%d#", ds.spaceship[i].broken_motor);
            fprintf(f, "%s#", ds.spaceship[i].navigation);
            fprintf(f, "%s#", ds.spaceship[i].propulsion);
            fprintf(f, "%d#", ds.spaceship[i].potency);
            fprintf(f, "%s#", ds.spaceship[i].instrumentation);
            fprintf(f, "%d#", ds.spaceship[i].module);
            fprintf(f, "%d#", ds.spaceship[i].broken_pieces);
            fprintf(f, "%d#", ds.spaceship[i].launch);
            fprintf(f, "%d#", ds.spaceship[i].indexVoyage);
            fprintf(f, "%d\n", ds.spaceship[i].actual_n_crew);
        }
        fclose(f);
    }
}

void saveUsersToFile(DataUsers d) {
    FILE* file = fopen("..\\textFiles\\RegisterUser.txt", "w"); // Modo texto para escritura
    if (file == NULL) {
        printf("(ERROR) Could not open file for writing.\n");
        return;
    }

    // Escribir encabezado
    fprintf(file, "ID,Name,Email,Password,Pin,Rol\n");

    // Escribir cada usuario
    for (int i = 0; i < d.n_users; i++) {
        User user = d.user[i];

        // Manejar correctamente el formato, eliminando saltos de línea no deseados
        fprintf(file, "%d,%s,%s,%s,%s,%c\n",
                user.id,
                user.name,
                user.email,
                user.password,
                strlen(user.pin) > 0 ? user.pin : "N/A", // Evitar campos vacíos para PIN
                user.rol);
    }

    fclose(file);
}

void saveCrew(Crew_data dc) {
    FILE* f = fopen("..\\textFiles\\Crew.txt", "w");
    if(f == NULL){
        printf("Error opening file - Crew(W)\n");
    }else{
        fprintf(f, "%d\n", dc.n_crew);
        for (int i = 0; i < dc.n_crew; i++){
            fprintf(f, "%d#", dc.crew[i].id);
            fprintf(f, "%s#", dc.crew[i].name);
            fprintf(f, "%d#", dc.crew[i].age);
            fprintf(f, "%s#", dc.crew[i].rol);
            fprintf(f, "%s#", dc.crew[i].uniform_color);
            fprintf(f, "%s#", dc.crew[i].contact_info);
            fprintf(f, "%d#", dc.crew[i].support);
            fprintf(f, "%d", dc.crew[i].id_spaceship.n_spaceships);
            for (int j = 0; j < dc.crew[i].id_spaceship.n_spaceships; j++) {
                fprintf(f, "#%d#", dc.crew[i].id_spaceship.id_spaceship[j].id);
                fprintf(f, "%d", dc.crew[i].id_spaceship.id_spaceship[j].id_spaceship);
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }
}

void loadAndShowUsersFromTextFile() {
    FILE* file = fopen("..\\textFiles\\users.txt", "r");
    if (file == NULL) {
        printf("(ERROR) Could not open file %s for reading.\n", "C:\\Documentos\\ingenieria informatica\\Segundo_carrera\\Pr Proj\\Proyecto\\prprI2425-A-g1\\users.txt");
        return;
    }

    char line[256]; // Buffer para leer líneas del archivo

    // Leer y descartar la primera línea si tiene encabezado
    if (fgets(line, sizeof(line), file)) {
        // Comprueba si la línea es un encabezado; puede ser opcional según el formato del archivo
        if (strstr(line, "ID,Name,Email,Password,Pin,Rol") != NULL) {
            printf("Leyendo archivo con encabezado: %s\n", line);
        } else {
            rewind(file); // No es un encabezado, volvemos al inicio
        }
    }

    // Leer cada línea y procesarla
    printf("\nUsuarios cargados desde %s:\n", "..\\textFiles\\users.txt");
    while (fgets(line, sizeof(line), file)) {
        User user;
        // Dividir la línea en tokens basados en comas
        char* token = strtok(line, ",");
        if (token != NULL) user.id = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.name, token, sizeof(user.name));

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.email, token, sizeof(user.email));

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.password, token, sizeof(user.password));

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.pin, token, sizeof(user.pin));

        token = strtok(NULL, ",");
        if (token != NULL) user.rol = token[0]; // Primer carácter como rol

        // Imprimir los datos del usuario
        printf("ID: %d\n", user.id);
        printf("Name: %s\n", user.name);
        printf("Email: %s\n", user.email);
        printf("Password: %s\n", user.password);
        printf("Pin: %s\n", user.pin);
        printf("Rol: %c\n", user.rol);
        printf("------------------------\n");
    }

    fclose(file);
}

void saveProject(DataProjects dp){
    int i, j;
    FILE*f;
    f = fopen("..\\textFiles\\Projects.txt", "w");
    if(f == NULL){
        printf("Error opening file - Projects(W)\n");
    }else{
        fprintf(f, "%d\n", dp.n_projects);
        for(i = 0; i < dp.n_projects; i++){
            fprintf(f, "%s#", dp.project[i].responsible);
            fprintf(f, "%s#", dp.project[i].title);
            fprintf(f, "%s#", dp.project[i].description);
            fprintf(f, "%s#", dp.project[i].status);
            fprintf(f, "%.2f#", dp.project[i].cost);
            fprintf(f, "%.2f#", dp.project[i].budget);
            fprintf(f, "%s#", dp.project[i].goal);
            fprintf(f, "%c#", dp.project[i].design);
            fprintf(f, "%d#", dp.project[i].n_members);
            for(j = 0; j < dp.project[i].n_members; j++){
                fprintf(f, "%s#", dp.project[i].team_members[j]);
            }
            fprintf(f, "%d#", dp.project[i].accepted);
            fprintf(f, "%d#", dp.project[i].posted);
            fprintf(f, "%d\n", dp.project[i].id);
        }
        fclose(f);
    }
}

void saveUsers(DataUsers du){
    int i;
    FILE*f;
    f = fopen("..\\textFiles\\RegisterUser.txt", "w");
    if(f == NULL){
        printf("Error opening file - Users(W)\n");
    }else{
        fprintf(f, "%d\n", du.n_users);
        for (i = 0; i < du.n_users; i++) {
            fprintf(f, "%s#", du.user[i].name);
            fprintf(f, "%s#", du.user[i].email);
            fprintf(f, "%s#", du.user[i].password);
            fprintf(f, "%c#", du.user[i].rol);
            fprintf(f, "%s#", du.user[i].pin);
            fprintf(f, "%d\n", du.user[i].id);
        }
        fclose(f);
    }
}


DataUsers loadUsersFromFile() {
    DataUsers d;
    d.n_users = 0;
    d.user = NULL;

    FILE* file = fopen("..\\textFiles\\users.txt", "r"); // Modo texto para lectura
    if (file == NULL) {
        printf("(ERROR) Could not open file %s for reading.\n", "C:\\Documentos\\ingenieria informatica\\Segundo_carrera\\Pr Proj\\Proyecto\\prprI2425-A-g1\\users.txt");
        return d;
    }

    char line[256]; // Buffer para leer líneas

    // Leer y descartar la primera línea si tiene encabezado
    if (fgets(line, sizeof(line), file)) {
        if (strstr(line, "ID,Name,Email,Password,Pin,Rol") != NULL) {
            // Es un encabezado válido, continuar
        } else {
            rewind(file); // No es un encabezado, volver al inicio
        }
    }

    // Leer cada línea y convertir a un objeto `User`
    while (fgets(line, sizeof(line), file)) {
        User user;
        char* token = strtok(line, ",");
        if (token != NULL) user.id = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.name, token, sizeof(user.name) - 1);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.email, token, sizeof(user.email) - 1);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.password, token, sizeof(user.password) - 1);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(user.pin, token, sizeof(user.pin) - 1);
        else strcpy(user.pin, "N/A"); // Manejar campos vacíos para PIN

        token = strtok(NULL, ",");
        if (token != NULL) user.rol = token[0];

        // Eliminar caracteres de nueva línea residuales
        user.name[strcspn(user.name, "\n")] = '\0';
        user.email[strcspn(user.email, "\n")] = '\0';
        user.password[strcspn(user.password, "\n")] = '\0';
        user.pin[strcspn(user.pin, "\n")] = '\0';

        // Agregar el usuario al array dinámico
        d.user = realloc(d.user, (d.n_users + 1) * sizeof(User));
        if (d.user == NULL) {
            printf("(ERROR) Memory allocation failed.\n");
            fclose(file);
            d.n_users = 0;
            return d;
        }

        d.user[d.n_users] = user;
        d.n_users++;
    }

    fclose(file);
    return d;
}
