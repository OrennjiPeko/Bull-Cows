/*This is the console executable, that makes use of the bullcow class
this acts as the view in a MVC pattern and is responsible for all 
user interaction. For the game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include<string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText=std::string;
using int32 = int32;

//function prototypes as outside a class
void Printro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; //Instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{
	std::cout << BCGame.GetCurrentTry();
	bool bPlayAgain = false;
	do
	{
		Printro();
		PlayGame();
		
		bPlayAgain= AskToPlayAgain();
	} 
	while (bPlayAgain);
	
	return 0; // exit the application

}


void Printro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenLength();
	std::cout << " letter isogram I'm Thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game to complection 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries= BCGame.GetMaxTries();
	
	//loop asking for guesses while the game 
	//is NOT won and there are still tries remaining 
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	{
		FText Guess = GetValidGuess();

		//sumbit vaild guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".  Cows =  " << BullCowCount.Cows << "\n\n";
	}
	
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invaild;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		getline(std::cin, Guess);
		
		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			//assume the guess is vaild 
			break;
		}
	} while (Status != EGuessStatus::Ok);//keep looping until we get no errors.

	return Guess;


}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done - You Win!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word  Y/N? ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}