/* 
 * File:   main.cpp
 * Author: Yash Tyagi
 * Created on 12/01/19
 * Purpose:  Mastermind AI
 * Version: 2
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
    //Define helper functions here
    void (*print)(string [],char [],char [],int,int)=
        [] (string g[],char r[],char w[],int nb,int ne){ 
            for(int i=nb;i<=ne;i++){
                cout<<g[i]<<" "
                    <<static_cast<int>(r[i])<<" "
                    <<static_cast<int>(w[i])<<endl;
            }
    };
    
    //Save the historical values of guesses and results
    const int        size = 4;             //Code Size
    static int       guess=0;              //Increment the guess number
    static const int SIZE=10000;           //How many guesses to save
    static string    aGuess[SIZE];         //Save the guesses
    static char      grr[SIZE];            //Save right guess in right spot
    static char      grw[SIZE];            //Save right guess in wrong spot
    static string    sGuess="0000";        //Size the guest string
    static char      pickdgt[size];        //Pick Fix digit
    static char      pickidx = 0;          //Pickdgt array index
    static char      cnt = 0;              //Count to check something
    static int       nGuess = 0;           //Number of Guesses
    
    //Store the results from the last guess
    grr[nGuess]=rr;
    grw[nGuess]=rw;
    
    //Test the helper function
    if(rr==4)print(aGuess,grr,grw,
            nGuess-10>0?nGuess-10:0,nGuess);
    
    //Calculate the guess
    if(nGuess != 0)
    {
       if(static_cast<int>(cnt) != -1)
        {
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
        {  pickdgt[i] = sGuess[i];
        }
        }
        pickidx = (rr+rw);
        
        //Storing the guess from the pickdgt up till it's index,
        //and after that updating other previous digits by 1
        for(int i=0;i<pickidx;i++)    sGuess[i] = pickdgt[i];
        for(int i=pickidx;i<size;i++) sGuess[i] = sGuess[i]+1;
        if((rr+rw) == 4) cnt = -1;
        
        //Updating Guess
        guess = stoi(sGuess);
        }
        else{
        //Incrementing guess by 1
            int n1000=(guess-guess%1000)/1000;
            int n100=(guess-guess%100)/100-10*n1000;
            int n10=(guess%100-guess%10)/10;
            int n1=guess%10;
            sGuess[0]=n1000+'0';
            sGuess[1]=n100+'0';
            sGuess[2]=n10+'0';
            sGuess[3]=n1+'0';
       }
    }
    aGuess[++nGuess]=sGuess;//Save the result
    guess++;
    
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