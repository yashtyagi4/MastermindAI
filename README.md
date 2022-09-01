![Screen Shot 2022-08-31 at 10 09 10 PM](https://user-images.githubusercontent.com/85970478/187823766-04afc2fe-a3fb-4743-9059-29f03a00eb62.png)
#
**AI Solver for Mastermind Game**

**Written In C++ with compiler G++ (MinGW.org GCC-6.3.0-1)**

**NetBeans IDE was used with Cygwin-Windows debugger**

## Game Overview:

Mastermind is a strategic board game where the user has to crack the secret hidden pattern by making guesses. With each guess, the game will tell you that in your guessed pattern, how many colors are in the actual pattern and how many are not.

In this project, AI has been implemented in Mastermind. The player don’t have to do anything, AI will make the smart guesses and will crack the secret hidden pattern using its techniques in the maximum of 13 guesses.


## Game Play:

For Game Play, user has to run the program and the output will be generated in following format:
Total guesses taken<space>Actual code<space>Last guessed code

![image](https://user-images.githubusercontent.com/85970478/187822808-1a99801a-6390-4b07-a9fc-23a355d59f0a.png)

Here in the following screenshot, total guesses are 8, actual secret was 0500 and the last guess was also 0500.

### Strategy:

The strategy is divided into three steps:
1) Start the first guess with 0000 and increment the digits in each guess by 1 until the first digit in the actual code is found (i.e. until right-guess-right-position + right-guess-wrong position = 1).
2) After we found the first digit, fix that digit in our next guess and keep incrementing the other digits by one. Repeating the step 2) with each guess again and again until all the four digits of the actual code are found and fixed (i.e. right-guess-right-position + right-guess-wrong position = 4).
3) Once all the digits are found, the hidden guess must be one of the permutations of the 4 digits that we picked/fixed i.e. one of the 4! = 24 permutations. Now since we have already guessed one of the permutation out of all 24 (on the guess where we
Page 4
got right-guess-right-position + right-guess-wrong position = 4) we got some output data (right-guess-right-position , right-guess-wrong position) for that guess. Out of all the remaining permutations eliminate all the impossible permutations along with the permutation that we had already guessed of the 4-fixed digits based on the fact that a different possible guess/permutation will return the same data (right-guess-right-position , right-guess-wrong position), as our one of the permutations/guess gave, if it was the guess. That’s because the hidden code is unique and the way it will react to each digits of one of the permutations, it should do the same for all other possible permutations. Pick one of the guesses among all permutations that are left possible. Do this elimination process after each guess, until only one possible permutation/guess is remaining (which is the actual code).
