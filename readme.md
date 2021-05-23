# Highscore Calculator
A simple Highscore Calculator in C++ 

## Features 
1. It displays top 10 highscores
2. It can update itself if new score is greater than existing top 10 highscores
3. It can be used in different games
4. It is very easy to implement in main programs

## Installation 
- Copy the source code 
- Rename "int main()" function to "int highscore(int hscore)"
- Change cin>>score to score = hscore in highscore fucntion and remove cout statement saying enter score
- Paste the whole code into your game file (make sure its above int main())
- Call highscore() function when you want to update highscores by passsing score
- Compile and run to make .exe file
- NOTE : For first time it will print "ERROR !! Unable to read file" (as highcore.txt file is not there ).
         But after first run it will get created and therefore (If things are done correctly it wont give error again)
-Instrustions are there in code too

## Future Plans
Will keep testing this application and improve if needed

## Open Source 
This project is open and if you are willing to contribute for free you are most welcome 

Basic information regarding this program -
1. Made in C++
2. Used standard headers 

## Author
This program is developed by Prabhakar Yadav