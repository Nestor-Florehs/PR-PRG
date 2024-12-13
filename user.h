#ifndef PRUEBA_USER_H
#define PRUEBA_USER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef char String[100];

typedef struct {
    int id;
    String name;
    String email;
    String password;
    String pin;
    char rol;	// A: admin / R: investigador / C: cliente
} User;

typedef struct {
    int n_users;
    User* user;
} DataUsers;

int addUser(DataUsers* d, User newUser);

DataUsers initializeData();

DataUsers registerUser(DataUsers users);

void printUsers(DataUsers d);

DataUsers createReasercher(DataUsers d);

int logIn(DataUsers d);

void showClientData(DataUsers data);

DataUsers removeClient(DataUsers d);

int findUserByMail(DataUsers d);

User findReasercher(DataUsers d);

DataUsers removeResearcher(DataUsers d);

DataUsers modifyResearcher(DataUsers d);

void showResearcherModifications();

User* searchResearcherById(DataUsers d, int id);

User* searchResearcherByName(DataUsers d, String name);

User* searchResearcherByEmail(DataUsers d, String email);

void showResearcherSearch();

User* searchResearcher(DataUsers d);

DataUsers* listResearchers(DataUsers d);

DataUsers initializeData();

void showResearchers(DataUsers d);

DataUsers modifyDataClient(DataUsers data);

DataUsers modifyDataClient(DataUsers data);

#endif