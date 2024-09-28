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
    ERROR = 1,
    SECONDSUCCESS = 2
};

struct Text
{
    char *buffer = NULL;
    int strings = 0;
    long int size = 0;
};



typedef Status(*CompareFunction)(const void *firstSumbol, const void *secondSumbol);
typedef Status(*ExchangeFunction)(void *adressStrings[], int stringNumber);

Status compareStrings(const void *firstSumbol, const void *secondSumbol);
Status exchangeStrings (void *adressStrings[], int stringNumber);
Status readFile (Text *text);
Status removeNewLines (char *adressStrings[], Text text);
Status printSortText (char *adressStrings[], int strings);
Status sortToFirstCondition (int strings, char *adressStrings[]);
Status initStringsArray (int strings, char ***adressStrings);
void mySort (void *adressStrings[], CompareFunction compareFunction, int strings, ExchangeFunction exchangeFunction);

int main ()
{
    Text text;

    if (readFile (&text) == ERROR)
    {
        return ERROR;
    }
 
    char **adressStrings = NULL;
    initStringsArray (text.strings, &adressStrings);

    removeNewLines (adressStrings, text);

    mySort ((void**)adressStrings, compareStrings, text.strings, exchangeStrings);

    printSortText (adressStrings, text.strings);

    sortToFirstCondition (text.strings, adressStrings);

    printf ("\n \n \n");
    printf ("Изначальный вариант текста:\n");
    printSortText (adressStrings, text.strings);
}

Status initStringsArray (int strings, char ***adressStrings)
{
    *adressStrings = (char**)calloc(strings, sizeof(char*));
    if (*adressStrings == NULL)
    {
        return ERROR;
    }

    return SUCCESS;
}

Status readFile (Text *text)
{
    FILE * ptrFile = fopen ("text.txt", "rb");
    if (ptrFile == NULL)
    {
        return ERROR;
    }

    fseek (ptrFile, 0, SEEK_END);
    text -> size = ftell (ptrFile);
    fseek (ptrFile, 0, SEEK_SET);

    text -> buffer = (char*)calloc (text -> size +1, sizeof(char));
    if (text -> buffer == NULL)
    {
        return ERROR;
    }

    fread (text -> buffer, sizeof(char), text -> size, ptrFile);
    (text -> buffer) [text -> size] = '\n';

    for (int number = 0; number < text -> size; number ++)
    {
        if ((text -> buffer)[number] == '\n')
        {
            (text -> strings)++;
        }

        if ((text -> buffer)[number] == '\r')
        {
            (text -> buffer)[number] = '\n';
        }
    }

    fclose (ptrFile);

    return SUCCESS;
}

Status removeNewLines (char *adressStrings[], Text text)
{
    adressStrings[0] = text.buffer;

    int numberString = 1;

    for (int numberSumbol = 0; numberSumbol < text.size; numberSumbol++)
    {
        if (text.buffer[numberSumbol] == '\n')
        {
            adressStrings[numberString] = &text.buffer[numberSumbol+2];

            numberSumbol += 2;
            numberString++;

            if (numberString == text.strings)
            {
                return SUCCESS;
            }
        }
    }

    return SUCCESS;
}

Status compareStrings (const void *firstSumbol, const void *secondSumbol)
{
    if (((isalpha (*(const char*)firstSumbol) != 0 && isalpha (*(const char*)secondSumbol) != 0 &&
        toupper(*(const char*)firstSumbol) > toupper(*(const char*)secondSumbol)) || isalpha (*(const char*)secondSumbol) == 0) ||
        *(const char*)firstSumbol == '\n' || *(const char*)secondSumbol == '\n')
    {
        return SUCCESS;
    } else if (((isalpha (*(const char*)firstSumbol) != 0 && isalpha (*(const char*)secondSumbol) != 0 &&
        toupper(*(const char*)firstSumbol) < toupper(*(const char*)secondSumbol)) || isalpha (*(const char*)secondSumbol) == 0) ||
        *(const char*)firstSumbol == '\n' || *(const char*)secondSumbol == '\n')
    {
        return SECONDSUCCESS;
    }

    return ERROR;
}

Status exchangeStrings (void *adressStrings[], int stringNumber)
{
    char *variableForCopy = *((char**)adressStrings + stringNumber);
    *((char**)adressStrings + stringNumber) = *((char**)adressStrings + stringNumber + 1);
    *((char**)adressStrings + stringNumber + 1) = variableForCopy;

    return SUCCESS;
}

Status printSortText(char *adressStrings[], int strings)
{
    for (int string = 0; string < strings; string++)
    {
        for (int number = 0; *(adressStrings[string] + number) != '\n'; number++)
        {
            printf ("%c", *(adressStrings[string] + number));
        }

        printf ("\n");
    }

    return SUCCESS;
}

Status sortToFirstCondition (int strings, char *adressStrings[])
{
    for (int numberSort = 0; numberSort < strings - 1; numberSort++)
    {
        for (int stringNumber = 0; stringNumber < strings - 1; stringNumber++)
        {
            if (adressStrings[stringNumber] > adressStrings[stringNumber + 1])
            {
                char *variableForCopy = adressStrings[stringNumber];
                adressStrings[stringNumber] = adressStrings[stringNumber + 1];
                adressStrings[stringNumber+1] = variableForCopy;
            }
        }
    }

    return SUCCESS;
}

void mySort (void *adressStrings[], CompareFunction compareFunction, int strings, ExchangeFunction exchangeFunction)
{
    for (int numberSort = 0; numberSort < strings - 1; numberSort++)
    {
        for (int stringNumber = 0; stringNumber < strings - 1; stringNumber++)
        {
            for (int sumbolNumber = 0, end = 0; 
                 *((char*)(*((char**)adressStrings + stringNumber) + sumbolNumber)) != '\0' && 
                 *((char*)(*((char**)adressStrings + stringNumber+1) + sumbolNumber)) != '\0' && 
                 end != 1; 
                 sumbolNumber++)
            {   
                if (compareFunction ((const void*)(((char*)(*((char**)adressStrings + stringNumber) + sumbolNumber))), 
                    (const void*)(((char*)(*((char**)adressStrings + stringNumber + 1) + sumbolNumber)))) == SUCCESS)
                {
                    exchangeFunction (adressStrings, stringNumber);
                    end = 1;
                } else if (compareFunction ((const void*)(((char*)(*((char**)adressStrings + stringNumber) + sumbolNumber))), 
                    (const void*)(((char*)(*((char**)adressStrings + stringNumber + 1) + sumbolNumber)))) == SECONDSUCCESS)
                {
                    end = 1;
                }
            }
        }
    }
}
