#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

enum Status 
{
    SUCCESS = 0, 
    ERROR = 1
};

const int NUMBER_SUMBOLS_IN_STRING = 16;

char text [][NUMBER_SUMBOLS_IN_STRING] = {{"io"}, 
                                          {"evropa"}, 
                                          {"ganimed"}, 
                                          {"calisto"}};

const int STRINGS_NUMBER = sizeof (text)/sizeof (text[0]);

Status sortStrings (char *adress[]);
Status giveRealAdresses (char *adress[]);
Status printSortText (char *adress[]);

int main ()
{
    char *adress [STRINGS_NUMBER];

    giveRealAdresses (adress);

    sortStrings (adress);

    printSortText (adress);

    return SUCCESS;
}

Status sortStrings (char *adress[])
{
    for (int sortNumber = 0; sortNumber < STRINGS_NUMBER-1; sortNumber++)
    {
        for (int string = 0; string < STRINGS_NUMBER-1; string++)
        {
            for (int sumbolNumber = 0; sumbolNumber < NUMBER_SUMBOLS_IN_STRING; sumbolNumber++)
            {
                if (isalpha (text[string][sumbolNumber]) != 0 && isalpha (text[string+1][sumbolNumber]) != 0 &&
                    toupper(text[string][sumbolNumber]) > toupper(text[string+1][sumbolNumber]))
                {
                    char *variableForCopy = adress[string];
                    adress[string] = adress[string + 1];
                    adress[string+1] = variableForCopy;
                }
            }
        }
    }

    return SUCCESS;
}

Status giveRealAdresses (char *adress[])
{
    for (int string = 0; string < STRINGS_NUMBER; string++)
    {
        adress[string] = &text[string][0];

        printf ("%p\n", adress[string]);
    }

    return SUCCESS;
}

Status printSortText(char *adress[])
{
    for (int string = 0; string < STRINGS_NUMBER; string++)
    {
        puts (adress[string]);
    }

    return SUCCESS;
}