#ifndef VOYAGE_H
#define VOYAGE_H

#include "spaceship.h"
#include "user.h"
#include <time.h>
#include <stdio.h>

typedef char String[100];
typedef char LongString[1000];

typedef struct{
    int minutes;
    int hour;
    int day;
    int month;
    int year;
    long unsigned int date;
}Date;



typedef struct {
    int id_voyage;
    int id_passenger;
    Date date;
    int rating;
    LongString comment;

}Ticket;

typedef struct {
    String start;
    String end;
    float max_price;
    Date start_date;
    Date end_date;
    int min_duration;
    int max_duration;
} FilterCriteria;

typedef struct {
    int id;
    int duration;
    float price;
    String itinerary[10];
    int itinerary_stops;
    String start;
    String end;
    Date startDate;
    Date endDate;
    Spaceship spaceship;
    Ticket* tickets;
    int num_tickets;
}Voyage;

typedef struct {
    Voyage* voyages;
    int num_voyages;
}VoyageData;



struct tm dateToTm(Date date);
Date tmToDate(struct tm tm_date);
Date stringToDate(String fecha);
void splitItinerary(char in[],String out[],char separator);
VoyageData buyTicket(VoyageData data);
int addVoyage(VoyageData* v, Voyage newVoyage);
VoyageData createVoyage(VoyageData data,DataSpaceship spaceships);
VoyageData filterVoyages(VoyageData data, FilterCriteria criteria);
VoyageData filterVoyagesBySeats(VoyageData data, int min_seats);
int isDateBeforeOrEqual(Date date1, Date date2);
int isDateInRange(Date date, Date start_date, Date end_date);
void splitDate(String date_str, int* day, int* month, int* year, int* hour, int* minutes);
void showVoyages(VoyageData data);
FilterCriteria askFilterCritera();
VoyageData rateVoyage(VoyageData dv, DataUsers du, int idx_user, Date actualDate);
int findPassengerId(VoyageData dv, int userId, int i);
int compareVoyageId(int id, int voyageId);
void showVoyages(VoyageData data);
FilterCriteria askFilterCritera();
int findSpaceshipIndex(int id,DataSpaceship data);
int findVoyageIndex(int id,VoyageData data);
Date UTILS_getCurrentDate();
long unsigned int UTILS_toMinutes(Date date);


#endif// VOYAGE_H