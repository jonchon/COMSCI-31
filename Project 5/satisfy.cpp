//
//  main.cpp
//  Project 5
//
//  Created by Jon Chon on 11/15/16.
//  Copyright © 2016 Jon Chon. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

int findWord (char word[], const char doc[], int start);

const int MAX_WORD_LENGTH = 20;

int normalizeRules(char word1[][MAX_WORD_LENGTH+1],
                   char word2[][MAX_WORD_LENGTH+1],
                   int distance[], int nRules)
{
    int alphaTest = 0;                                   //This is to check if any chars are not alpha
    int same = 0;
    int jtemp = -1;
    
    if (nRules < 0)                                 //Treating negative nRules as zero
        nRules = 0;
    
    for (int i = 0; i < nRules; i++)                //Goes thru each word
    {
        for (int j = 0; j < MAX_WORD_LENGTH + 1; j++)   //Changes to lowercase
        {
            word1[i][j] = tolower(word1[i][j]);
            word2[i][j] = tolower(word2[i][j]);
        }
        
        for (int j = 0; j < strlen(word1[i]); j++)  //The next two for statements checks for not alpha
        {
            if (!isalpha(word1[i][j]))
                alphaTest = 1;
        }
        for (int j = 0; j < strlen(word2[i]); j++)
        {
            if (!isalpha(word2[i][j]))
                alphaTest = 1;
        }
        
        //LOOK INTO NEXT PART LATER AND FIX FOR IF THERE ARE THREE OF SAME RULE
        
        for (int j = i-1; j >= 0; j--)              //This checks if there are two of the same rules
        {
            if (!strcmp(word1[i], word1[j]))        //Compares first
                if(!strcmp(word2[i], word2[j]))     //Compares second
                {
                    same = 1;
                    jtemp = j;                      //Save for later
                }
            if (!strcmp(word1[i], word2[j]))        //Compares first to second
                if(!strcmp(word2[i], word1[j]))
                {
                    same = 1;
                    jtemp = j;
                }
        }
        if (same == 1)                              //This part figures out which of the two same rules
        {                                           //has the smaller distance. If the smaller one is to the
            if (distance[jtemp] < distance[i])      //left of the the greater one, it switches the positions
            {                                       //of those two distances so that the smaller one will be
                int temp = distance[jtemp];         //removed
                distance[jtemp] = distance[i];
                distance[i] = temp;
            }
        }

        if (distance[i] < 1 || strlen(word1[i]) == 0 || strlen(word2[i]) == 0 || alphaTest == 1 || same == 1)
        {                           //This checks for not alpha, no entry, nonpositive distance, same rules
            for (int rest = i; rest < nRules - 1; rest++)
            {
                strcpy(word1[rest], word1[rest + 1]);   //Deletes the current column
                strcpy(word2[rest], word2[rest + 1]);
                distance[rest] = distance[rest + 1];
            }
            nRules--;                                   //Makes the amount of words smaller
            i--;                        //Goes back to check the next case, which is now in previous position
            alphaTest = 0;
            same = 0;
        }
    }
    return nRules;
}

int calculateSatisfaction(const char word1[][MAX_WORD_LENGTH+1],
                          const char word2[][MAX_WORD_LENGTH+1],
                          const int distance[], int nRules,
                          const char document[])
{
    int satisfaction = 0;
    char myDoc[201];                //Local version of document[]
    strcpy(myDoc, document);
    
    if (nRules < 0)                 //treating negative nRules as zero
        nRules = 0;
    
    for (int i = 0; i < strlen(myDoc); i++)     //For every char in document
    {
        myDoc[i] = tolower(myDoc[i]);   //everything is lowercase
        
        if (!(isalpha(myDoc[i]) || isspace(myDoc[i])))
        {
            for (int j = i; j < strlen(myDoc); j++)
            {
                myDoc[j] = myDoc[j+1];      //Take out anything thats not a char or a space
            }
            if (i > 0)
                i--;                        //Just in case two nonvalid characters in a row
        }
    }
    
    char tempWord[201];                                     //Initialize variables
    char tempCheckUp[201];
    int k = 0;
    int z = 0;
    int tempj = 0;
    int flag[201];
    
    for (int i = 0; i < 201; i++)                        //Set all values to true
    {
        flag[i] = 1;
    }

    for (int j = 0; j < strlen(myDoc); j+=k)                //Goes through the document
    {
        if(j > strlen(myDoc)) break;
        
        k = findWord (tempWord, myDoc, j);                  //Obtains each word in document
        //cout << endl;
        //cout << tempWord << " TEMP WORD" << endl;
        //cout << k << endl;
        tempj = j;
        
        for (int i = 0; i < nRules; i++)                    //Goes through all the rules
        {
            if (!strcmp(tempWord, word1[i]) && flag[i])                //Compares word with all words in word1
            {
                //cout << "checkpoint 2" << endl << endl;
                strcpy (tempWord, word2[i]);                //Changes word with word2
                //cout << tempWord << " This is tempWord" << endl;
                for (int count = 0; count <= distance[i] && (tempj<strlen(myDoc)); count++)      //looks for words after up to distance
                {
                    if (tempj > strlen(myDoc))
                        break;
                    z = findWord (tempCheckUp, myDoc, tempj);           //gets the word
                    //cout << tempCheckUp << " This is tempCheckUp" << endl;
                    if (!strcmp (tempWord, tempCheckUp))        //Checks if the word is equal to word2
                    {
                        satisfaction++;                         //Adds to satisfaction
                        //cout << "yessss" << endl;
                        flag[i] = false;
                        break;                                  //Breaks out of the loop
                    }
                    memset (tempCheckUp, '\0', 200);            //Makes tempCheckUp null again
                    tempj+=z;
                    //cout << tempj << endl;
                }
            }
            z = 0;
            if (!strcmp(tempWord, word2[i]) && flag[i])    //Does same thing, but if word2 comes before word1
            {
                //cout << "checkpoint 3" << endl << endl;
                strcpy (tempWord, word1[i]);                //Changes word with word1
                //cout << tempWord << " This is tempWord" << endl;
                for (int count = 0; count <= distance[i] && tempj < strlen(myDoc); count++)      //looks for words after up to distance
                {
                    if (tempj > strlen(myDoc))
                        break;
                    z = findWord (tempCheckUp, myDoc, tempj);           //gets the word
                    //cout << tempCheckUp << " This is tempCheckUp" << endl;
                    if (!strcmp (tempWord, tempCheckUp))        //Checks if the word is equal to word2
                    {
                        satisfaction++;                         //Adds to satisfaction
                        //cout << "yessss" << endl;
                        flag[i] = false;
                        break;                                  //Breaks out of the loop
                    }
                    memset (tempCheckUp, '\0', 200);            //Makes tempCheckUp null again
                    tempj+=z;
                }
            }
        }
    }
    return satisfaction;
}

int findWord (char word[], const char doc[], int start)         //A function to find the next word
{
    int j = 0;
    int k = 0;
    int i = start;
    memset (word, '\0', 200);
    while (i > 0 && isalpha(doc[i] && isalpha(doc[i-1])))
    {
        i--;
    }
    while (i < strlen(doc) && !isalpha(doc[i]))                                    //Skips all the white space
    {
        i++;
        k++;                                                    //Remembers how many white spaces were used
    }
    while (i < strlen(doc) && isalpha(doc[i]))                //Puts down the word in a c-string
    {
        word[j] = doc[i];
        j++;
        i++;
    }
    return j+k;       //Returns the length of the c-string and the whitespace before it
}


int main()
{
    char w1[20][MAX_WORD_LENGTH+1] = {"mad", "deranged", "nefarious", "have"};
    char w2[20][MAX_WORD_LENGTH+1] = {"scientist", "robot", "plot", "mad"};
    int distance [20] = {2, 4, 1, 13};

    int r = calculateSatisfaction(w1, w2, distance, 4,
                                  "The mad UCLA scientist unleashed a deranged evil giant robot.");

    cout << r << endl;

}
