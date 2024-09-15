#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

enum Status 
{
    SUCCESS = 0, 
    ERROR = 1
};

Status readFile (char **buffer, int *strings, long int *size);
Status giveRealAdresses (char *adress[], char *buffer, long int size, int strings);
Status sortStrings (int strings, char *adress[]);
Status compare (char firstSumbol, char secondSumbol);
Status printSortText (char *adress[], int strings);
Status RABOTAUPJPJPJ (char *adress[], int stringNumber);
Status sortToFirstCondition (int strings, char *adress[]);


int main ()
{
    char *buffer = NULL;
    int strings = 0;
    long int size = 0;

    readFile (&buffer, &strings, &size);

    char **adress= (char**)calloc(strings, sizeof(char*));
    assert (*adress == NULL);

    giveRealAdresses (adress, buffer, size, strings);

    sortStrings (strings, adress);

    printSortText (adress, strings);

    sortToFirstCondition (strings, adress);

    printf ("Изначальный вариант текста:\n");
    printSortText (adress, strings);
}

Status readFile (char **buffer, int *strings, long int *size)
{

    FILE * ptrFile = fopen ("text.txt", "rb");
    //assert (ptrFile == NULL);

    fseek (ptrFile, 0, SEEK_END);
    *size = ftell (ptrFile);
    fseek (ptrFile, 0, SEEK_SET);

    *buffer = (char*)calloc (*size+1, sizeof(char));
    //assert (buffer == NULL);

    fread (*buffer, sizeof(char), *size, ptrFile);
    (*buffer) [*size] = '\n';

     for (int number = 0; number < *size; number ++)
    {
        if ((*buffer)[number] == '\n')
        {
            (*strings)++;
        }

        if ((*buffer)[number] == '\r')
        {
            (*buffer)[number] = '\n';
        }
    }

    fclose (ptrFile);

    return SUCCESS;
}

Status giveRealAdresses (char *adress[], char *buffer, long int size, int strings)
{
    adress[0] = buffer;

    int numberString = 1;

    for (int numberSumbol = 0; numberSumbol < size; numberSumbol++)
    {
        if (buffer[numberSumbol] == '\n')
        {
            adress[numberString] = &buffer[numberSumbol+2];

            numberSumbol += 2;
            numberString++;

            if (numberString == strings)
            {
                return SUCCESS;
            }
        }
    }

    return SUCCESS;
}

Status compare (char firstSumbol, char secondSumbol)
{
    if (((isalpha (firstSumbol) != 0 && isalpha (secondSumbol) != 0 &&
        toupper(firstSumbol) > toupper(secondSumbol)) || isalpha (secondSumbol) == 0) ||
        firstSumbol == '\n' || secondSumbol == '\n')
    {
        return SUCCESS;
    }

    return ERROR;
}

Status RABOTAUPJPJPJ (char *adress[], int stringNumber)
{
   for (int sumbolNumber = 0; 
         compare(*(adress[stringNumber] + sumbolNumber), *(adress[stringNumber+1] + sumbolNumber)) == SUCCESS; 
         sumbolNumber++)
    {   
        if (compare (*(adress[stringNumber] + sumbolNumber), *(adress[stringNumber + 1] + sumbolNumber)) == SUCCESS)
        {
            char *variableForCopy = adress[stringNumber];
            adress[stringNumber] = adress[stringNumber + 1];
            adress[stringNumber+1] = variableForCopy;

            return SUCCESS;
        } 
    }

    return SUCCESS;
}

Status sortStrings (int strings, char *adress[])
{

    for (int numberSort = 0; numberSort < strings - 1; numberSort++)
    {
        for (int stringNumber = 0; stringNumber < strings - 1; stringNumber++)
        {
            RABOTAUPJPJPJ (adress, stringNumber);
        }
    }

    return SUCCESS;
}

Status printSortText(char *adress[], int strings)
{
    for (int string = 0; string < strings; string++)
    {
        for (int number = 0; *(adress[string] + number) != '\n'; number++)
        {
            printf ("%c", *(adress[string] + number));
        }

        printf ("\n");
    }

    return SUCCESS;
}

Status sortToFirstCondition (int strings, char *adress[])
{
    for (int numberSort = 0; numberSort < strings - 1; numberSort++)
    {
        for (int stringNumber = 0; stringNumber < strings - 1; stringNumber++)
        {
            if (adress[stringNumber] > adress[stringNumber + 1])
            {
                char *variableForCopy = adress[stringNumber];
                adress[stringNumber] = adress[stringNumber + 1];
                adress[stringNumber+1] = variableForCopy;
            }
        }
    }

    return SUCCESS;
}

