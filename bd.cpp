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
    birthday[1] = "23-05-2006"
    birthPlace[1] = "KOH KONG"
    =========================================================================

    Tasks
    - create a function to add another person's information
    - create a functon to edit a person's information in the list
    - create a funciotn to remove a person from the list
    - create a function to search a person int the list
    - create a function to show upcoming BDs in a month

*/

#include <cstdio>  // <stdio.h>
#include <cstring>
#include <cstdlib>
#include <ctype.h>
#include <time.h>

#define MAXLINE 100
#define MAXLEN 200
#define DATALEN 50



void c_loadLine(FILE * fp);
void c_splitLine();

void c_display();
void c_add();
void c_edit();
void c_remove();
void c_search();
void c1_showUpcoming();   // to do: show up coming within 30 days from current date
void c_getDate();
void c_save(FILE * fp);

void strToLower(char [], char []);
int dayOfYear(int year, int month, int day);

int lineIndex = 0;
char line[MAXLINE][MAXLEN];

class Person {
    public:
        char lastNames[DATALEN];
        char firstNames[DATALEN];
        char birthday[DATALEN];
        char birthPlace[DATALEN];
        char month[10];
        char day[10];
        char year[10];
};

Person person[MAXLINE];

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
    c_loadLine(fp);
    fclose(fp);
    c_splitLine();
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
        switch (option)
        {
            case '1':{
                c_add();
                break;
            }
            case '2':{
                c_edit();
                break;
            }
            case '3':{
                c_remove();
                break;
            }
            case '4':{
                c_display();
                break;
            }
            case '5': {
                // option 5: search by name
                c_search();
                break;
            }
            case '6': {
                c_getDate();
                c1_showUpcoming();
                break;
            }
            case '7':{
                fp = fopen(fileName, "w");
                c_save(fp);
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


void c_add()
{
    if (lineIndex >= MAXLINE){
        printf("list is full\n");
        return;
    }
    printf("Enter lastname: ");
    scanf("%[^\n]", person[lineIndex].lastNames);
    fflush(stdin);
    printf("Enter first name: ");
    scanf("%[^\n]", person[lineIndex].firstNames);
    fflush(stdin);
    printf("Enter birthday (dd-mm-yyyy): ");
    scanf("%[^\n]", person[lineIndex].birthday);
    fflush(stdin);
    printf("Enter birth place: ");
    scanf("%[^\n]", person[lineIndex].birthPlace);
    lineIndex++;
    fflush(stdin);
}

void c_edit()
{
    int selectIndex;
    printf("Choose an index to edit: ");
    scanf("%d", &selectIndex);
    fflush(stdin);

    if(selectIndex > lineIndex){
        printf("Error: Invalid index selection\n");
        return;
    }
    printf("Edit last name: ");
    scanf("%[^\n]", person[selectIndex].lastNames);
    fflush(stdin);
    printf("Edit first name: ");
    scanf("%[^\n]", person[selectIndex].firstNames);
    fflush(stdin);
    printf("Edit birthday (dd-mm-yyyy): ");
    scanf("%[^\n]", person[selectIndex].birthday);
    fflush(stdin);
    printf("Edit birth place: ");
    scanf("%[^\n]", person[selectIndex].birthPlace);
    fflush(stdin);
}

void c_remove()
{
    int selectIndex, i;
    printf("Choose and index to remove: ");
    scanf("%d", &selectIndex);
    fflush(stdin);

    if(selectIndex < 0 || selectIndex >= lineIndex){
        printf("Error: invalid selection\n");
        return;
    }
    //shifting all indexes above by 1 down ward
    for(i = selectIndex; i < lineIndex; i++){
        strcpy(person[i].lastNames, person[i+1].lastNames);
        strcpy(person[i].firstNames, person[i+1].firstNames);
        strcpy(person[i].birthday, person[i+1].birthday);
        strcpy(person[i].birthPlace, person[i+1].birthPlace);
    }
    strcpy(person[i].lastNames, "");
    strcpy(person[i].firstNames, "");
    strcpy(person[i].birthday, "");
    strcpy(person[i].birthPlace, "");
    lineIndex--;
}

void c_save(FILE * fp)
{
    for(int i = 0; i < lineIndex; i++)
        if(i != lineIndex-1)
            fprintf(fp, "%s,%s,%s,%s\n", person[i].lastNames, person[i].firstNames, person[i].birthday, person[i].birthPlace);
        else
            fprintf(fp, "%s,%s,%s,%s", person[i].lastNames, person[i].firstNames, person[i].birthday, person[i].birthPlace);
}

void c_display()
{
    if( lineIndex == 0)
        printf("Empty list\n");
    else
        printf("No. Last name First name  Birthday   Birth place\n");
        for (int i = 0; i < lineIndex; i++){
            printf("%-3d %-10s%-14s%10s%10s\n", i, person[i].lastNames, person[i].firstNames, person[i].birthday, person[i].birthPlace);
        }
}

// load the whole file as stream and splitting it into lines

void c_loadLine(FILE * fp)
{   
    char str[10000];
    char * token;
    char * delimChar = "\n";
    int c, i = 0;
    if ((c = fgetc(fp)) == EOF){
        printf("File is empty\n");
        return;
    }
    
    while (c != EOF){
        str[i++] = c;
        c = fgetc(fp);
    }

    token = strtok(str, delimChar);
    while (token != NULL){
        strcpy(line[lineIndex], token);
        token = strtok(NULL, delimChar);
        lineIndex++;
    }
}

void strToLower(char output[], char input[])
{
    strcpy(output, input);
    int i = 0;
    while (output[i] != '\0'){
        output[i] = tolower(output[i]);
        i++;
    }
}

void c_getDate()
{
    //strtok will break the string that it split.
    //to avoid that make a copy of birthday and split that copy
    char temp[DATALEN];
    char * token;
    char * delim = "-";

    for (int i = 0; i < lineIndex; i++){
        strcpy(temp, person[i].birthday);
        token = strtok(temp, delim);
        strcpy(person[i].day, token);
        token = strtok(NULL, delim);
        strcpy(person[i].month, token);
        token = strtok(NULL, delim);
        strcpy(person[i].year, token);
        //printf("index %d, day = %s ,month = %s, year = %s \n", i, person[i].day, person[i].month, person[i].year);
    }
}

void c1_showUpcoming()
{
    int dayOfYear(int year, int month, int day);
    time_t c_time;
    c_time = time(NULL);
    struct tm nowTime = *localtime(&c_time);
    int i, found = 0;
    int tempDay, tempMon, tempYear, dateDif, today;
    printf("Current date: %d-%d-%d\n", nowTime.tm_mday, nowTime.tm_mon + 1, nowTime.tm_year + 1900);
    printf("Upcoming birthdays within 30 days:\n");
    for(i = 0; i < lineIndex; i++){
        tempDay = atoi(person[i].day);
        tempMon = atoi(person[i].month);
        tempYear = atoi(person[i].year);
        today = dayOfYear(nowTime.tm_year + 1900, nowTime.tm_mon + 1, nowTime.tm_mday);
        dateDif = dayOfYear(tempYear, tempMon, tempDay) - today;
        //printf("%d, day = %d, month = %d,dateDif = %d\n", i, tempDay, tempMon,dateDif);
        if(dateDif >= 0 && dateDif <= 30){
            printf("index %d, %s %s %s\n", i, person[i].lastNames, person[i].firstNames, person[i].birthday);
            found = 1;
        }
    }
    if (found == 0)
        printf("There are no birthday in the next 30 days\n");
}

// the process of splitting line also destroys the line
void c_splitLine()
{
    printf("Initiate splitLine...\n");
    char * delimChar = ",";
    char * token;
   
    for(int i = 0; i < lineIndex; i++){
        token = strtok(line[i], delimChar);
        strcpy(person[i].lastNames, token);

        token = strtok(NULL, delimChar);
        strcpy(person[i].firstNames, token);

        token = strtok(NULL, delimChar);
        strcpy(person[i].birthday, token);

        token = strtok(NULL, delimChar);
        strcpy(person[i].birthPlace, token);
    }
    token = NULL;
    printf("Finished splitLine...\n");
}

void c_search(){
    char fn[30], tempFn[30], tempFirstNames[30];
    char ln[30], tempLn[30], tempLastNames[30];
    printf("Enter Last name : ");
    scanf("%[^\n]" ,ln);
    fflush(stdin);
    printf("Enter First name : ");
    scanf("%[^\n]" ,fn);
    fflush(stdin);
    for( int i =0; i<lineIndex ; i++){
        strToLower(tempFn, fn);
        strToLower(tempLn, ln);
        strToLower(tempFirstNames, person[i].firstNames);
        strToLower(tempLastNames, person[i].lastNames);
        if( (strcmp(tempFirstNames, tempFn) == 0) && (strcmp(tempLastNames,tempLn) == 0)){
            printf("%s %s , found in Index %d\n ", fn , ln , i);
            return;
        }
    }
    printf("%s %s Not Found", fn,ln);
}


int dayOfYear(int year, int month, int day)
{
    int i, leap;

    int dayTab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    };

    leap = ( year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
    for (i = 1; i < month; i++)
        day += dayTab[leap][i];
    return day;
}