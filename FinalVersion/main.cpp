/* 
 * File:   main.cpp
 * Author: Yash Tyagi
 * Created on 12/3/19
 * Purpose:  Mastermind AI
 * Version: 4
 * Version Highlight: AI that solves the Mastermind game in 13 guesses maximum
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
string AI(char,char);
bool eval(string,string,char &,char &);
string set();

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code to break, and current guess
    char rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses
    
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;
    
    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw));
    //Check evaluation
    cout<<nGuess<<" "<<code<<" "<<guess<<endl;
    guess=AI(rr,rw);
    /*cout<<code<<endl;
    for(int i=0;i<10000;i++){
        guess=AI(0,0);
        eval(code,guess,rr,rw);
        cout<<setw(5)<<code<<setw(5)<<guess
                <<setw(2)<<static_cast<int>(rr)
                <<setw(2)<<static_cast<int>(rw)<<endl;
    }*/
    
    //Exit the program
    return 0;
}

string AI(char rr,char rw){  
    //Find all combinations
    void (*allComb)(string ,string[]) =
     [](string update,string next[])
    {   
    const int SIZE=4;
    string temp = "    ";
    int count = 0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(i==j)continue;
            for(int k=0;k<SIZE;k++){
                if(i==k||j==k)continue;
                for(int l=0;l<SIZE;l++){
                    if(i==l||j==l||k==l)continue;
                         temp[0] = update[i];
                         temp[1] = update[j];
                         temp[2] = update[k];
                         temp[3] = update[l];
                         next[count] = "    ";
                         next[count] = temp;
                         count++;
                }
            }
        }
    }
    };
    
    //Save the historical values of guesses and results
    const int        size = 4;                //Code Size
    const int        tComb = 24;              //All Possible Combinations (4!) when rr = 4
    static const int SIZE=10000;              //How many guesses to save
    static string    tGuess[tComb] = {"\0"};  //Keep all the possible guesses when final digits are picked
    static int       guess=0;                 //Increment the guess number
    static string    sGuess="0000";           //Size the guess string
    static char      pickdgt[size];           //Pick Fix digit
    static char      pickidx = 0;             //Pickdgt array index
    static char      cnt = 0;                 //Count to check something
    static short     elipos[tComb] = {0};     //Eliminate unwanted guesses
    static short     elimax;                  //Max index of elipos
    
    //Variable Declaration
    char             rrTemp;                  //Temporary right color-right position
    char             rwTemp;                  //Temporary right color-wrong position
    string           tempG;                   //Temporary Guess
    bool             check;                   //To check something

    //Calculate the guess
    if(guess != 0)
    {
    if( (rr+rw) != 4){
     //---Step 1: Find the first fix digit---
      cnt = 0;
      for(int i=1;i<size;i++){
        if(sGuess[i] == sGuess[i-1])
            cnt++;}
        if(cnt == 3){   //Checking if all the digits of the guess are same
            if(rr>0){
                //Storing as many digits that are in real code in pickdgt array
                for(int i=0;i<rr;i++){
                    pickdgt[i] = sGuess[i];
                    pickidx++;
                } 
            }            
        }
    
    //---Step 2: Find all the fix digits---
    if(pickidx>0 && ((rr+rw) > pickidx) ){
        //Updating the pickdgt array with all the new found fix digits
        for(int i=pickidx;i<(rr+rw);i++)
        {  
            pickdgt[i] = sGuess[i];
        }
    }
    pickidx = (rr+rw);
    
    //Storing the guess from the pickdgt up till it's index,
    //and after that updating other previous digits by 1
    for(int i=0;i<pickidx;i++)    sGuess[i] = pickdgt[i];
    for(int i=pickidx;i<size;i++) sGuess[i] = sGuess[i]+1;
    cnt = guess;
    }
    
    //---Step 3: Stepping through each combination of the found fix digits and guessing---
    else{
        //Finding all the possible (4!) combinations 
        if(cnt == (guess-1))
        { 
            allComb(sGuess,tGuess);
            cnt = 1; 
        }
        
        //Eliminating the previous guess position
        for(int i=0;i<tComb;i++)
        {
            if(tGuess[i] == sGuess) 
                elipos[elimax++] = i;
        }
        
        //Eliminating all unwanted guesses that have rr+rw = 4 based on previous guess
        for(int i=0;i<tComb;i++)
        {
            rrTemp = 0; rwTemp = 0;
            
            //Picking a combination
            tempG = tGuess[i];
            
            //Finding out if the picked guess position is already blocked or not
            check = false;
            for(int j=0;j<elimax;j++)
            if(elipos[j] == i) check = true;
            
            //Proceeding only if the position isn't blocked
            if(check == false){
                //Checking if the combination is a possible guess
                check = eval(sGuess,tempG,rrTemp,rwTemp);
                if((rrTemp != rr) || (rwTemp != rw))
                    elipos[elimax++] = i;
            }
        }
        
        //Picking the next guess
        for(int i=0;i<tComb;i++){
            check = false;
        for(int j=0;j<elimax;j++)
            if(i == elipos[j]) check = true;
        if(check == false){
            sGuess = tGuess[i];
            break;
        }
        }
    }

    }
    
    //Updating the guess
    ++guess;

    //Return the result
    return sGuess;
}

bool eval(string code,string guess,char &rr,char &rw){
    string check="    ";
    rr=0,rw=0;
    //Check how many are right place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Found or not
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}