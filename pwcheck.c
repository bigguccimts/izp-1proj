// made by xduric06
// 9.5/10

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int strLength(char pword[]) // Checks the length of the password
{
    int counter = 0;
    while (pword[counter] != '\0')
    {
        counter++;
    }
    return counter;
}

bool level1(char pword[])
{
    int counter = 0;
    int upCase = 0;
    int lowCase = 0;
    while (pword[counter] != '\0')
    {
        if ((pword[counter] >= 'a') && (pword[counter] <= 'z'))
        {
            lowCase++;
        }
        else if ((pword[counter] >= 'A') && (pword[counter] <= 'Z'))
        {
            upCase++;
        }
        counter++;
    }

    if ((lowCase > 0) && (upCase > 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool level2(char pword[], int param)
{
    int counter = 0;
    int rulePassedCounter = 0;
    bool nums = false;
    bool special = false;

    if (param > 4)
    {
        param = 4;
    }

    if (level1(pword)) // Checks if password passed level 1. If not, returns false
    {
        rulePassedCounter = 2;
        while (pword[counter] != '\0')
        {

            if (pword[counter] >= '0' && pword[counter] <= '9')
            {
                nums = true;
            }
            else if ((pword[counter] >= ' ' && pword[counter] <= '/') ||
                     (pword[counter] >= ':' && pword[counter] <= '@') ||
                     (pword[counter] >= '[' && pword[counter] <= '`') ||
                     (pword[counter] >= '{' && pword[counter] <= '~'))
            {
                special = true;
            }

            counter++;
        }

        if (nums)
        {
            rulePassedCounter++;
        }
        if (special)
        {
            rulePassedCounter++;
        }

        if (rulePassedCounter >= param)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool level3(char pword[], int param)
{
    if (param == 1)
    {
        return false;
    }

    int sameCharCounter = 1;

    if (level2(pword, param))
    {
        for (int counter = 0; counter < strLength(pword);
             counter++) // Works until the length of the password - 1, so the next code wont try to access out the array
        {
            if (pword[counter] == pword[counter + 1]) // Compares character with the one next to it
            {
                sameCharCounter++;
                if (sameCharCounter == param) // If the count is equal to the parameter, while the cycle is still going,
                                              // returns false. If not continue with the cycle
                {
                    return false;
                }
                else
                {
                    continue;
                }
            }
            else // If the character isnt the same as the one next to it, reset it back to starting value
            {
                sameCharCounter = 1;
            }
        }

        if (sameCharCounter <
            param) // Checks if the amount of the same character is less than the parameter, after the cycle is done
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool level4(char pword[], int param)
{
    int counter = 0;

    if (level3(pword, param))
    {
        for (int i = 0; i <= strLength(pword) - param;
             i++) // Runs the cycle until it reaches the index of lenght of the password minus the parameter value. This
                  // is done to prevent the cycle reaching out of the array
        {
            for (int j = i + 1; j <= strLength(pword) - param + 1; j++)
            {
                while (pword[i + counter] == pword[j + counter])
                {
                    counter++;
                    if (counter == param)
                    {
                        return false;
                    }
                }
            }
            counter = 0;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool statsCheck(char *input)
{
    char stats[8] = "--stats"; // Array with --stats string
    int i = 0;
    while (input[i] != '\0') // Checks if inputted parameter is equal to --stats
    {
        if (input[i] != stats[i])
        {
            return false;
        }
        i++;
    }

    if (input[i] == '\0' && stats[i] == '\0') // Checks if the position of \0 is on the same index. If so returns true
    {
        return true;
    }
    else
    {
        return false;
    }
}

int minLen(char pword[])
{
    int minLength = 0;

    minLength = strLength(pword) - 1;

    return minLength;
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
    {
        fprintf(stderr, "Try using more arguments.\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    int level = strtoul(argv[1], &endptr, 10); // Parses char number into int
    if (endptr[0] != '\0')                     // Checks if letters werent inputted as arguments
    {
        fprintf(stderr, "Input error. Try using numbers only.\n");
        return EXIT_FAILURE;
    }

    if (strLength(argv[2]) >
        3) // Checks if the length of the parameter is longer than 3, if so, shortens the parameter to 3 characters.
           // Because passwords are 100 chars long, any parameter would get shortened to a value that can be handled
    {
        argv[2][3] = '\0';
    }

    int param = strtoul(argv[2], &endptr, 10); // Parses char number into int
    if (endptr[0] != '\0')                     // Checks if letters werent inputted as arguments
    {
        fprintf(stderr, "Input error. Try using numbers only.\n");
        return EXIT_FAILURE;
    }

    if (level <= 0 || level > 4) // Checks if int representing level is between 1 and 4
    {
        fprintf(stderr, "Level value is too low or too high. Try using numbers from interval 1 - 4.\n");
        return EXIT_FAILURE;
    }

    if (param <= 0) // Checks if the inputted parameter isnt 0 and lower
    {

        fprintf(stderr, "Param is lower than 0. Try using numbers larger than 0\n");
        return EXIT_FAILURE;
    }

    if (argc > 4) // Checks if the amount of parameters arguments isnt more than 4
    {
        fprintf(stderr, "Too many arguments.\n");
        return EXIT_FAILURE;
    }

    bool statsCheckVal;
    if (argc ==
        4) // Checks if the amount of arguments is equal to 4, if yes, then checks if the argument on index 3 is --stats
    {

        if (statsCheck(argv[3]))
        {
            statsCheckVal = true;
        }
        else
        {
            fprintf(stderr, "Wrong way of using stats. To display stats use argument --stats.\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        statsCheckVal = false;
    }

    char tmp[97];
    int difChars = 0;
    bool charExists;
    int minLength = 0;
    float avg = 0.0;
    float pwordCounter = 0;
    float pwordsCharCount = 0;
    char pword[102];

    while (fgets(pword, 103, stdin) != NULL) // Loading passwords form txt file, with the length of 103 characters
    {

        pwordCounter++;

        int charCounter = 0;
        while (pword[charCounter] != '\0') // Counts the amount of characters in the password until it reaches \0
        {
            charCounter++;
        }

        if (charCounter > 101) // If the length until \0 is bigger than 101, throws error
        {
            fprintf(stderr, "Password is too long.\n");
            return EXIT_FAILURE;
        }

        if (statsCheckVal) // Checks if the --stats argument was used, if yes, performs --stats
        {
            for (int i = 0; pword[i] != '\n'; i++)
            {
                for (int j = 0; j < difChars; j++)
                {
                    if (pword[i] == tmp[j])
                    {
                        charExists = 1;
                    }
                }
                if (charExists == 0)
                {
                    tmp[difChars] = pword[i];
                    difChars++;
                }
                charExists = false;
            }

            if (minLength == 0)
            {
                minLength = minLen(pword);
            }
            else if (minLen(pword) < minLength)
            {
                minLength = minLen(pword);
            }

            pwordsCharCount += strLength(pword) - 1;
        }
        switch (level) // Based on the inputted level determines which case to use, default is not used, because the
                       // program checks before if the level is between 1 and 4,  that way default case is not necessary
        {
        case 1:

            if (level1(pword))
            {
                printf("%s", pword);
            }

            break;
        case 2:
            if (level2(pword, param))
            {
                printf("%s", pword);
            }

            break;
        case 3:
            if (level3(pword, param))
            {
                printf("%s", pword);
            }

            break;
        case 4:
            if (level4(pword, param))
            {
                printf("%s", pword);
            }
            break;
        }
    }

    avg = pwordsCharCount / pwordCounter;
    if (statsCheckVal) // If argument --stats is used displays the statistics
    {
        printf("Statistika:\n");
        printf("Ruznych znaku: %d\n", difChars);
        printf("Minimalni delka: %d\n", minLength);
        printf("Prumerna delka: %.1f\n", avg);
    }

    return EXIT_SUCCESS;
}
