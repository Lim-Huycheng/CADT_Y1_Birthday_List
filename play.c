#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void strToLower(char output[], char input[])
{
    strcpy(output, input);
    int i = 0;
    while (output[i] != '\0'){
        output[i] = tolower(output[i]);
        i++;
    }
}


void getMonth(char str[], char month[])
{
    int i = 0;
    char * token;
    char * delim = "-";

    token = strtok(str, delim);
    token = strtok(NULL, delim);
    strcpy(month, token);
}
int main()
{ 
    int a = 5;
    int b;
    char str[20] = "05";

    b = atoi(str);

    if(a == b)
        printf("This is a: %d, this is b: %d\n", a,b);

    printf("This is str: %s\n", str);

    return 0;
}