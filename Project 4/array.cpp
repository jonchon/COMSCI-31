//
//  main.cpp
//  Project 4
//
//  Created by Jon Chon on 11/1/16.
//  Copyright © 2016 Jon Chon. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value)
{
    if (n < 0)                      //Tests if n is negative
        return -1;
    for (int i = 0; i < n; i++)
    {
        a[i] += value;              //Adds the value to the end of the string
    }
    
    return n;
}

int lookup(const string a[], int n, string target)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)         //Finds if any part of the array matches target
        {
            return i;
        }
    }
    return -1;                      //If target never appears
}

int positionOfMax(const string a[], int n)
{
    string tempMax = "";            //String to temporarily hold the max.
    int i;
    int k = -1;
    for (i = 0; i < n; i++)
    {
        if (a[i] > tempMax)
        {
            tempMax = a[i];
            k = i;                  //Saves the location of the max.
        }
    }
    return k;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0)
        return -1;
    string tempLeft = a[pos];       //Saves the leftmost string
    int i = pos;
    while (i < n - 1)               //Minus one so that theres no error with a[i+1]
    {
        a[i] = a[i + 1];
        i++;
    }
    a[i] = tempLeft;
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    int i = 0;
    int count = 0;
    string current = "";
    while (i < n)
    {
        if (a[i] != current)        //If the string is not equal to the string before it.
        {
            current = a[i];
            count++;
        }
        i++;
    }
    return count;
}

int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    string temp = "";
    int i = 0;
    while (i < n/2)                 //Only need half since flipping
    {
        temp = a[i];
        a[i] = a[n-1-i];            //Setting the first one as the last one
        a[n-1-i] = temp;            //Setting last one as the first one
        i++;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    int i = 0;
    while ((i < n1) && (i < n2))    //While both n1 and n2 are not reached
    {
        if (a1[i] != a2[i])         //Finds where they are not equal
            return i;
        i++;
    }
    if (n1 < n2)                    //If they are equal up to n1 or n2, return lower one
        return n1;
    else if (n1 > n2)
        return n2;
    return n1;                      //if n1 and n2 are equal, return either one of them
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    for (int i = 0; i < n1; i++)
    {
        if (a1[i] == a2[0])                             //If the first of a2 even comes up
        {
            for (int j = 0; j < n2; j++)
            {
                if ((i+j <= n1) && (a1[i+j] == a2[j]))  //Makes sure its in bound and in order
                {
                    if (j == n2 - 1)                    //Once the loop is done
                    {
                        return i;                       //Since i is the starting position
                    }
                }
            }
        }
    }
    return -1;                                          //Default case
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    for (int i = 0; i < n1; i++)                        //Loop for a1
    {
        for (int j = 0; j < n2; j++)                    //Loop for a2
        {
            if (a1[i] == a2[j])                         //Goes through all of a2 to see if equal
                return i;
        }
    }
    return -1;                                          //Default case
}

int separate(string a[], int n, string separator)
{
    if (n < 0)
        return -1;
    string temp;
    int count = 0;
    for (int i = 0; i < n; i++)                         //To make sure there's enough iterations
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j+1])                          //Organizes alphabetically
            {
                temp = a[j];
                a[j] = a[j+1];                          //Switches two at a time
                a[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)                         //This is just for the return value
    {
        if (a[i] < separator)
            count++;
    }

    if (count == 0)                                     //Also for return value]
        return n;
    return count;
}


int main()
{
}
