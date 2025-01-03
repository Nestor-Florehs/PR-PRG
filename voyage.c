#include "voyage.h"
#include "user.h"
#include "auxiliar.h"

#include <time.h>

struct tm dateToTm(Date date) {
    struct tm tm_date = {0};  // Inicializa la estructura a ceros
    tm_date.tm_mday = date.day;
    tm_date.tm_mon = date.month - 1; // tm_mon empieza desde 0 (enero = 0)
    tm_date.tm_year = date.year - 1900; // tm_year es desde 1900
    tm_date.tm_hour = date.hour;
    tm_date.tm_min = date.minutes;

    return tm_date;
}

Date tmToDate(struct tm tm_date) {
    Date date = {0};
    date.day = tm_date.tm_mday;
    date.month = tm_date.tm_mon + 1;
    date.year = tm_date.tm_year + 1900;
    date.hour = tm_date.tm_hour;
    date.minutes = tm_date.tm_min;
    return date;
}

void splitItinerary(char in[],String out[],char separator) {
    int j=0;
    int o=0;
    for(int i=0;in[i]!='\0';i++) {
        out[j][o] = in[i];
        o++;
        if(in[i]==separator) {
            out[j][o-1] = '\0';
            j++;
            o=0;
        }
    }
    out[j][o]='\0';
}

int addVoyage(VoyageData* v, Voyage newVoyage){
    int error = 0;
    Voyage* aux = realloc(v->voyages, (v->num_voyages + 1)*sizeof(Voyage));
    if(aux == NULL){
        printf("(ERROR) Memory failed");
        error = 1;
    }else{
        v->voyages = aux;
        v->voyages[v->num_voyages] = newVoyage;
        v->num_voyages++;
        v->voyages[v->num_voyages-1].id = v->num_voyages + 1;
    }
    return error;
}


void buyTicket(VoyageData data){
    int i, id, option;
    String code;
    VoyageData filteredData = filterVoyagesBySeats(data,1);
    for(i=0;i < filteredData.num_voyages;i++){
        printf("Voyage %d: %s - %s\n",filteredData.voyages[i].id,filteredData.voyages[i].start,filteredData.voyages[i].end);
    }
    printf("Insert the id of the voyage you want to buy a ticket for: ");
    scanf("%d",&id);
    if(id>0 && id<=filteredData.num_voyages){
        data.voyages[id-1].tickets=realloc(data.voyages[id-1].tickets,(data.voyages[id-1].num_tickets+1)*sizeof(Ticket));
        data.voyages[id-1].tickets[data.voyages[id-1].num_tickets].id_voyage=id;
        printf("Select payment method:\n\t1.Bank transfer\n\t2.Visa\n\t3.Mastercard");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            printf("Insert the bank transfer code: ");
            scanf("%s",code);

            break;
        case 2:
            printf("Insert the visa code: ");
            scanf("%s",code);
            break;
        case 3:
            printf("Insert the mastercard code: ");
            scanf("%s",code);
            break;
        default:
            printf("Error invalid option\n");
            break;
        }
        printf("Insert the id of the passenger you want to buy the ticket for: ");
        scanf("%s",&id);
        data.voyages[id-1].tickets[data.voyages[id-1].num_tickets].id_passenger=id;
        data.voyages[id-1].num_tickets++;
        printf("Ticket bought successfully!\n");

    }else{
        printf("Error this voyage does not exist\n");
    }
}

// Función para comparar dos fechas (retorna true si date1 <= date2)
int isDateBeforeOrEqual(Date date1, Date date2) {
    if (date1.year < date2.year) return 1;
    if (date1.year > date2.year) return 0;
    if (date1.month < date2.month) return 1;
    if (date1.month > date2.month) return 0;
    return date1.day <= date2.day;
}


// Función para verificar si una fecha está entre dos fechas
int isDateInRange(Date date, Date start_date, Date end_date) {
    return isDateBeforeOrEqual(start_date, date) && isDateBeforeOrEqual(date, end_date);
}

// Función principal para filtrar los viajes según los criterios
 VoyageData filterVoyages(VoyageData data, FilterCriteria criteria) {
    VoyageData filteredData;
    filteredData.voyages = NULL;
    filteredData.num_voyages = 0;

    for (int i = 0; i < data.num_voyages; i++) {
        Voyage v = data.voyages[i];
        int matches = 1;

        // Filtrar por lugar de salida (si se especifica)
        if (strlen(criteria.start) > 0 && strcmp(v.start, criteria.start) != 0) {
            matches = 0;
        }

        // Filtrar por lugar de destino (si se especifica)
        if (strlen(criteria.end) > 0 && strcmp(v.end, criteria.end) != 0) {
            matches = 0;
        }

        // Filtrar por precio máximo (si se especifica)
        if (criteria.max_price > 0 && v.price > criteria.max_price) {
            matches = 0;
        }

        // Filtrar por duración (si se especifica)
        if ((criteria.min_duration > 0 && v.duration < criteria.min_duration) ||
            (criteria.max_duration > 0 && v.duration > criteria.max_duration)) {
            matches = 0;
        }

        // Filtrar por fecha de viaje (si se especifica)
        if (criteria.start_date.year > 0 && criteria.end_date.year > 0) {
            int dateMatch = 0;
            for (int j = 0; j < v.duration; j++) {  // Asumiendo un arreglo de fechas de duración del viaje



            if (isDateInRange(v.startDate, criteria.start_date, criteria.end_date)) {
                    dateMatch = 1;
                    break;
                }
            }
            if (!dateMatch) matches = 0;
        }

        // Si el viaje coincide con todos los criterios, se añade a filteredData
        if (matches) {
            filteredData.num_voyages++;
            filteredData.voyages = realloc(filteredData.voyages, filteredData.num_voyages * sizeof(Voyage));
            filteredData.voyages[filteredData.num_voyages - 1] = v;
        }
    }

    return filteredData;
}

VoyageData filterVoyagesBySeats(VoyageData data, int min_seats) {
    VoyageData filteredData;
    filteredData.voyages = NULL;
    filteredData.num_voyages = 0;

    for (int i = 0; i < data.num_voyages; i++) {
        Voyage v = data.voyages[i];

        // Calcula la capacidad total de la nave para este viaje
        int total_seats = v.spaceship.crew_capacity + v.spaceship.passenger_capacity;

        // Verifica si la nave cumple con el número mínimo de asientos
        if (total_seats >= min_seats) {
            // Agrega el viaje al array de viajes filtrados
            filteredData.num_voyages++;
            filteredData.voyages = realloc(filteredData.voyages, filteredData.num_voyages * sizeof(Voyage));
            if (filteredData.voyages == NULL) {
                printf("Error al asignar memoria para los viajes filtrados.\n");
                exit(1);  // Termina el programa si falla la asignación de memoria
            }
            filteredData.voyages[filteredData.num_voyages - 1] = v;
        }
    }

    return filteredData;
}

void splitDate(String date_str, int* day, int* month, int* year, int* hour, int* minutes) {
         if (sscanf(date_str, "%d/%d/%d %d:%d",day, month, year, &hour, &minutes) != 5) {
        fprintf(stderr, "Error: El formato de la cadena no es válido. Debe ser 'dd/mm/yyyy hh:mm'.\n");
        exit(EXIT_FAILURE);
    }
}


VoyageData createVoyage(VoyageData data,DataSpaceship spaceships){

    Voyage new_voyage;
    char itinerary[400];
    String spaceship,launch_date,arrival_date;
    int error,i,index;
    int found=0;

    printf("Insert name of the ship: ");
    fgets(spaceship,100,stdin);
    deleteLinespace(spaceship);
    for(i=0;i<spaceships.n_spaceships;i++){
        if(!strcmp(spaceships.spaceship[i].name,spaceship)){
            found=1;
            index=i;
        }
    }
    if(found==0){
        printf("Error this ship is not in the database");
    }else{
        new_voyage.spaceship = spaceships.spaceship[index];
        printf("Insert exit point: ");
        fgets(new_voyage.start,100,stdin);
        deleteLinespace(new_voyage.start);
        printf("Insert itinerary (every place must be separated by '-'): ");
        fgets(itinerary,400,stdin);
        deleteLinespace(itinerary);
        splitItinerary(itinerary,new_voyage.itinerary,'-');
        printf("Where does the voyage end?\n");
        fgets(new_voyage.end,100,stdin);
        deleteLinespace(new_voyage.end);
        printf("Imput launch date in the next format: dd/mm/yyyy hh:mm");
        fgets(launch_date,100,stdin);
        deleteLinespace(launch_date);
        printf("Imput arrival date in the next format: dd/mm/yyyy hh:mm");
        fgets(arrival_date,100,stdin);
        deleteLinespace(arrival_date);
        splitDate(launch_date,&new_voyage.startDate.day,&new_voyage.startDate.month,&new_voyage.startDate.year,&new_voyage.startDate.hour,&new_voyage.startDate.minutes);
        splitDate(arrival_date,&new_voyage.endDate.day,&new_voyage.endDate.month,&new_voyage.endDate.year,&new_voyage.endDate.hour,&new_voyage.endDate.minutes);
        error = addVoyage(&data,new_voyage);
        if(!error) {
            printf("Register successful!\n");
        }
    }
    return data;
}

int compareVoyageId(int id, int voyageId){
    int found = 0;
    if(id == voyageId){
        found = 1;
    }
    return found;
}

int findPassengerId(VoyageData dv, int userId, int i){
    int found = 0, j;
    for(j = 0; j < dv.voyages[i].num_tickets && !found; j++){
        if(dv.voyages[i].tickets[j].id_passenger == userId){
            j--;
            found = 1;
        }
    }
    if(!found){
        j = -1;
    }
    return j;
}

VoyageData rateVoyage(VoyageData dv, DataUsers du, int idx_user, Date actualDate){
    int id, found = 0, i, j, rating;
    LongString comment;
    String aux;

    askForString(aux, "Enter the ID of the voyage: ");
    id = checkInt(aux);
    for(i = 0; i < dv.num_voyages && !found; i++){
        found = compareVoyageId(id, dv.voyages[i].id);
        if(found == 1){
            i--;
        }
    }
    if(found == 0){
        printf("This voyage ID does not exist\n");
    }else{
        j = findPassengerId(dv, du.user[idx_user].id, i);
        if(j == -1){
            found = 0;
        }
        if(found == 0){
            printf("You have not bought any ticket of this voyage\n");
        }else{
            if(isDateBeforeOrEqual(dv.voyages[i].tickets[j].date, actualDate)){
                askForString(aux, "Add your rating from 0 (bad) to 5 (very good): ");
                int rating = checkInt(aux);
                dv.voyages[i].tickets[j].rating = rating;
                askForString(aux, "Enter the word 'comment' to enter a comment for the voyage\n");
                if(strcmp(aux, "comment") == 0) {
                    askForLongString(comment, "Enter your comment with a maximum of 1000 characters: ");
                    strcpy(dv.voyages[i].tickets[j].comment, comment);
                    printf("Your rating and comment have been successfully uploaded");
                }else{
                    printf("Your rating has been successfully uploaded");
                }
            } else {
                printf("Your ticket date has not been expired yet\n");
            }
        }
    }
    return dv;
}

void cancelTicket(VoyageData data, int current_day) {
    int id_passenger,id_voyage;
    printf("Insert the id of the passanger of the ticket you want to cancel: ");
    scanf("%d",&id_passenger);
    printf("insert the id of the voyage: ");
    scanf("%d",&id_voyage);
    if(data.voyages[id_voyage-1].tickets[data.voyages[id_voyage-1].num_tickets-1].id_passenger==id_passenger){
        if(id_voyage>0 && id_voyage<=data.voyages[id_voyage-1].num_tickets && current_day-data.voyages[id_voyage-1].startDate.day > 2){
            for(int i=0;i<data.voyages[id_voyage-1].num_tickets;i++){
                if(data.voyages[id_voyage-1].tickets[i].id_passenger==id_passenger){
                    data.voyages[id_voyage-1].num_tickets--;
                    printf("Ticket cancelled successfully!\n");
                }
                else{
                    printf("Error this ticket does not exist\n");
                }
            }
        }else{
            printf("Error this ticket does not exist\n");
        }
    }
}