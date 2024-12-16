#ifndef VOYAGE_H
#define VOYAGE_H

#include "spaceship.h"
#include "user.h"

typedef char String[100];

typedef char LongString[1000];

typedef struct{
    int minutes;
    int hour;
    int day;
    int month;
    int year;
}Date;


typedef struct {
    int id_voyage;
    int id_passenger;
    Date date;
    int rating;
    LongString comment;
}Ticket;

typedef struct {
    char start[100];
    char end[100];
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
} VoyageData;



struct tm dateToTm(Date date);
Date tmToDate(struct tm tm_date);
Date stringToDate(String fecha);
void splitItinerary(char in[],String out[],char separator);
void buyTicket(VoyageData data);
int addVoyage(VoyageData* v, Voyage newVoyage);
VoyageData createVoyage(VoyageData data,DataSpaceship spaceships);
VoyageData filterVoyages(VoyageData data, FilterCriteria criteria);
VoyageData filterVoyagesBySeats(VoyageData data, int min_seats);
int isDateBeforeOrEqual(Date date1, Date date2);
int isDateInRange(Date date, Date start_date, Date end_date);
void splitDate(String date_str, int* day, int* month, int* year, int* hour, int* minutes);
int isDateBeforeOrEqual(Date date1, Date date2);
int isDateInRange(Date date, Date start_date, Date end_date);
VoyageData rateVoyage(VoyageData dv, DataUsers du, int idx_user, Date actualDate);

#endif// VOYAGE_H