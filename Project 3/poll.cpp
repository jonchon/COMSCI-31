#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool hasCorrectSyntax(string pollData);                         //stating all functions I use
int countVotes(string pollData, char party, int& voteCount);
bool isValidUppercaseStateCode(string stateCode);
bool hasZero(string pollData);
int prediction(string pollData, char party);

int main()
{
}

bool hasCorrectSyntax(string pollData)
{
    int i = 0;
    string stateCode;
    string upperPollData;
    while (i < pollData.size())
    {
        upperPollData += toupper(pollData[i]);      //Changes the characters to uppercase for isValidUpper
        i++;
    }
    
    i = 0;
    
    while (i < pollData.size())
    {
        if (pollData.size() < i + 4)                //If the size of the pollData is too short, return false
        {
            return false;
        }
        
        if (isdigit(pollData[i+3]) && pollData.size() < i + 5)  //Same thing as ^^, but for double digit
        {
            return false;
        }
        
        stateCode = upperPollData[i];               //Capitalizes the state code
        stateCode += upperPollData[i+1];
        
        if (!isValidUppercaseStateCode(stateCode))  //checks if it is a state code
        {
            return false;
        }
        
        if (!isdigit(pollData[i+2]))            //This checks if first is not a digit
        {
            return false;
        }
        
        if (!isdigit(pollData[i+3]))
        {                                       //This one checks if the first is digit and second is not
            if (!isalpha(pollData[i+3]))
            {
                return false;
            }
            i+=4;                               //If first is digit but not second, the length of the string
        }                                       //is 4, so add 4 to i to go to next stateCode.
        
        else if (isdigit(pollData[i+3]) && !isalpha(pollData[i+4]))
        {                                       //Checks if the last thing in the string is a letter
            return false;
        }
        
        else if (isdigit(pollData[i+3]) && isalpha(pollData[i+4]))
        {
            i+=5;                               //If it is a double digit, the length of a string is 5
        }
    }
    return true;                                //Default returns true
}

int countVotes(string pollData, char party, int& voteCount)
{
    
    if (!hasCorrectSyntax(pollData))            //Checks for correct syntax
    {
        return 1;
    }
    else if (hasZero(pollData))                      //Checks if any of the states have zero votes for a party
    {
        return 2;
    }
    else if (!isalpha(party))                        //Checks if the party is even valid
    {
        return 3;
    }
    
    else
    {
        voteCount = prediction(pollData, party);
        return 0;                                   //Everything is fine
    }
}

int prediction(string pollData, char party)
{
    int total = 0;
    int i = 0;
    
    while (i < pollData.size())
    {
        if (toupper(pollData [i+3]) == toupper(party))                //Checks for single digit case
        {
            total+= stoi(pollData.substr(i+2,1));   //If it is a single digit, convert to int and add
            i+=4;                                   //Go to next state code
        }
        
        else if (isalpha(pollData [i+3]))
        {
            i+=4;
        }

        else
        {
            if (toupper(pollData[i+4]) == toupper(party))         //If right party
            {
                total+= stoi(pollData.substr(i+2,2));   //convert to int and add
            }
            i+=5;                               //Go to next state code
        }
    }
    return total;
}

bool hasZero(string pollData)
{
    int i = 0;
    while (i < pollData.size())
    {
        if (pollData[i+2] == '0' && pollData[i+3] == '0') //checks the case its a double digit zero
        {
            return true;
        }
        
        if (pollData[i+2] == '0' && isalpha(pollData[i+3])) //checks the case its a single digit zero
        {
            return true;
        }
        
        if (!isdigit(pollData[i+3]))            //if it was a single digit number, add 4 to go to next state
        {
            i+=4;
        }
        
        else if (isdigit(pollData[i+3]))        //if it was a double digit number, add 5 to go to next state
        {
            i+=5;
        }
    }
    return false;
}

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
    "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC."
    "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
