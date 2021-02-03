//
//  main.cpp
//  motMystere
//
//  Created by Aurélia Haas on 2020-05-09.
//  Copyright © 2020 Aurélia Haas. All rights reserved.
//

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
// 1 player
#include <fstream>
#include <vector>

using namespace std;

string shuffleLetters(string mysteryWord);
bool player(string mysteryWord, string guess);
string randomWord(vector<string> dictionnary);

int main() {
    //variables
    string mysteryWord, shuffledWord, guessedWord, newGame;
    int attemptsNumber(1), maxAttemps(10);
    int players;
    //1 player
    vector<string> dictionnary; // this tab will contain all the words from the file

    //Game with 1 or 2 players
    cout << "Hello, we are going to play mystery word!\nFirst, are you 1 or 2 players?\n";
    cin >> players;
    cin.ignore();
    
    // create a list with all the words from a file
    if(players == 1){
        //create file
        string const file("/Users/aureliahaas/Desktop/xcode/Dictionnary");
        ifstream flux(file.c_str());

        if(flux){
            // add all words to the dictionnary
            while(!flux.eof()){
                string currentWord;
                getline(flux, currentWord);
                dictionnary.push_back(currentWord);
            }

        }else{
            cout << "Error" << endl;
            goto stop; // if error go to the end
        }
    }

    //Game
    do {
        //how to pick the mystery word
        if (players == 1) //user picks a word
             mysteryWord =randomWord(dictionnary); //pick a random word from the file
        else if(players == 2){ // random word is picked from the dictionnary
            cout << "\n\nEnter the mystery word: " << endl;
            getline(cin, mysteryWord);
        }
    
        //shuffle word
        shuffledWord = shuffleLetters(mysteryWord);

        //play
        cout << shuffledWord << endl << "What's this word? (Attempt 1)" << endl;

        while (!player(mysteryWord, guessedWord) && attemptsNumber < maxAttemps){
            //if(attemptsNumber != 1)
            attemptsNumber++;
            cout << "Wrong. Try again!\n\n(Attempt " << attemptsNumber  << ")\nThe shuffled word is: " << shuffledWord << endl;
        }

        //limited number of attemps, display the right answer
        if(attemptsNumber == maxAttemps)
            cout << "Sorry you did not find the right word.\nIt was: " << mysteryWord<< endl;
        else
            cout << "Congrats! you found the mystery word, which was: " << mysteryWord << endl << endl;

        //new game
        attemptsNumber = 1; //reset attemps number
        cout << "\n\nDo you want to play again? (Y/N)" << endl;
        getline(cin, newGame);
    } while (newGame == "Y");

    stop://goto
    return 0;
}



// Shuffling the letters from the mystery word so we can begin the game.
string shuffleLetters (string mysteryWord){
    string shuffledWord;
    
    while(!mysteryWord.empty()){
        srand(time(0));
        int position = rand() % mysteryWord.size(); // pick a random number between 0 and the size of the mystery word
        
        shuffledWord += mysteryWord[position]; // add each letter in the shuffled word
        mysteryWord.erase(position,1); // erase each letter from the mystery word
    }
    return shuffledWord;
}



// Has the player found the right word
bool player(string mysteryWord, string guessedWord){
    string attempt;
    getline(cin,attempt);
    
    if(attempt == mysteryWord)
        return true;
    return false;
}



// Pick a random word from the file
string randomWord(vector<string> dictionnary){
    srand(time(0));
    int position = rand() % dictionnary.size();
    return dictionnary[position];
}
