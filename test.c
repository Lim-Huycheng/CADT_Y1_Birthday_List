/*
    Use "bd.c" as starting point.
    Create your function in "test.c", so that in case something goes wrong
    just make another copy from "bd.c" and try again.

    DESCRIPTION
    ==========================================================================
    This program read text from "bdList.txt" and does this and that (which you
    don't need to care about for now) to get last names, first names, birthday
    and birth place and store it in lastNames[] array, firstNames[] array, 
    birthday[] array and birth place array[] respectively.

    'lineIndex' is the number of lines in "bdList.txt". This variable
    also represent the current number of people in the list.
    **hint**: use this variable to work with arrays

    For example, we from our list we have:
    LIM,IEANGZORNG,02-06-2002,KRATIE
    LIM,HUYCHENG,23-05-2004,KOH KONG

    When the progam is compiled and run, the value of arrays is:

    lastNames[0] = "LIM" 
    firstName[0] = "IEANGZORNG"
    birthday[0] = "02-06-2002"
    birthPlace[0] = "KRATIE"

    lastNames[1] = "LIM" 
    firstName[1] = "HUYCHENG"
    birthday[1] = "23-05-2004"
    birthPlace[1] = "KOH KONG"
    =========================================================================

    Tasks
    - create a function to add another person's information
    - create a functon to edit a person's information in the list
    - create a funciotn to remove a person from the list
    - create a function to search a person int the list
    - create a function to show upcoming BDs in a month

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 100
#define MAXLEN 200
#define DATALEN 50

//load file as text stream and split it into line
void loadLine(FILE * fp);
//split each line into data, 4 datas -> 4 splits
void splitLine();

void display();
void add();
void edit();
void f_remove();
void save(FILE * fp);


int lineIndex = 0;
char line[MAXLINE][MAXLEN];
char lastNames[MAXLINE][DATALEN];
char firstNames[MAXLINE][DATALEN];
char birthday[MAXLINE][DATALEN];
char birthPlace[MAXLINE][DATALEN];

int main()
{
    FILE * fp;
    char option;
    char fileName[100] = "bdList.txt";

    fp = fopen(fileName, "r");
    if (fp == NULL){
        printf("Error: file not found\n");
        return 0;
    }
    loadLine(fp);
    printf("Loaded: %s\n", fileName);
    printf("Test loaded line\n");
    fclose(fp);
    splitLine();
    while(1){
        printf("\n==============================================\n");
        printf("Options:\n");
        printf("1. Add\n");
        printf("2. Edit\n");
        printf("3. Remove\n");
        printf("4. Display\n");
        printf("5. Search\n");
        printf("6. Show upcomings\n");
        printf("7. Exit\n");
        printf("Select an option: ");
        scanf("%c", &option);
        fflush(stdin);
        // if(!isdigit(option))
        //     continue;
        switch (option)
        {
            case '1':{
                add();
                break;
            }
            case '2':{
                // option 2 edit
                break;
            }
            case '3':{
                // option 3 remove
                break;
            }
            case '4':{
                display();
                break;
            }
            case '5': {
                // option 5: search by name
                break;
            }
            case '6': {
                // option 6: show upcoming BDs
            }
            case '7':{
                fp = fopen(fileName, "w");
                save(fp);
                fclose(fp);
                return 0;
                break;
            }
            default :{
                printf("Error: invalid option\n");
                break;
            }
        }
    }
    
    return 0;
}

void add()
{
    if (lineIndex >= MAXLINE){
        printf("list is full\n");
        return;
    }
    printf("Enter lastname: ");
    scanf("%s", lastNames[lineIndex]);
    printf("Enter first name: ");
    scanf("%s", firstNames[lineIndex]);
    printf("Enter birthday: ");
    scanf("%s", birthday[lineIndex]);
    printf("Enter birth place: ");
    scanf("%s", birthPlace[lineIndex]);
    lineIndex++;
}


void save(FILE * fp)
{
    for(int i = 0; i < lineIndex; i++)
        if(i != lineIndex-1)
            fprintf(fp, "%s,%s,%s,%s\n", lastNames[i], firstNames[i], birthday[i], birthPlace[i]);
        else
            fprintf(fp, "%s,%s,%s,%s", lastNames[i], firstNames[i], birthday[i], birthPlace[i]);
}

void display()
{
    if( lineIndex == 0)
        printf("Empty list\n");
    else
        printf("No. Last name First name  birthday\n");
        for (int i = 0; i < lineIndex; i++){
            printf("%-3d %-10s%-14s%10s%10s\n", i, lastNames[i], firstNames[i], birthday[i], birthPlace[i]);
        }
}

// load the whole file as stream and splitting it into lines
void loadLine(FILE * fp)
{
    printf("Initiate loadLine...\n");
    char str[10000];
    char * token;
    char * delimChar = "\n";
    int c, i = 0;
    
    while ((c = fgetc(fp)) != EOF){
        str[i++] = c;
    }

    token = strtok(str, delimChar);
    while (token != NULL){
        strcpy(line[lineIndex], token);
        token = strtok(NULL, delimChar);
        lineIndex++;
    }
    printf("finish loadLine...\n");
}

// the process of splitting line also destroys the line
void splitLine()
{
    printf("Initiate splitLine...\n");
    char * delimChar = ",";
    char * token;
   
    for(int i = 0; i < lineIndex; i++){
        token = strtok(line[i], delimChar);
        strcpy(lastNames[i], token);

        token = strtok(NULL, delimChar);
        strcpy(firstNames[i], token);

        token = strtok(NULL, delimChar);
        strcpy(birthday[i], token);

        token = strtok(NULL, delimChar);
        strcpy(birthPlace[i], token);
    }
    token = NULL;
    printf("Finished splitLine...\n");
}