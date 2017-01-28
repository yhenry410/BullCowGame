#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax similar to Unreal Engine
using FText = std::string;
using int32 = int;

// function prototypes
bool PrintIntro();
void PrintInstructions();
bool AskToPlayGame();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

// entry point for our application
int main() {
	do {
		if (PrintIntro() == true) {
			PrintInstructions();
			AskToPlayGame();
			PlayGame();
		}
		else {
			PlayGame();
		}
	} while (AskToPlayAgain());
	return 0; // exit the application
}

// introduce the game
bool PrintIntro() {
	std::cout << "            Welcome to Bulls and Cows!\n";
	std::cout << std::endl;
	std::cout << "             (___)            ___" << std::endl;
	std::cout << "     ________(O O)           (O O)_______" << std::endl;
	std::cout << "   /|________|\\_/             \\_/|_______|\\" << std::endl;
	std::cout << "  * |        |                   |       | *" << std::endl;
	std::cout << "    ^        ^                   ^       ^" << std::endl;
	std::cout << "Do you want to read the instructions for this game (Y/N)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintInstructions() {
	std::cout << "The goal of this game is to guess the hidden isogram (a word with non-repeating letters)" << std::endl;
	std::cout << "You have a limited number of attempts to guess the word.\n" << std::endl;
	std::cout << "If you guessed the correct letter BUT it is NOT in the correct position, ";
	std::cout << "you get a 'Cow'." << std::endl;
	std::cout << "Whereas, if you guessed the correct letter AND it is in the correct position, you get a 'Bull'.\n" << std::endl;
}

bool AskToPlayGame() {
	std::cout << "Press enter to begin the game. ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return 0;
}

// plays the game until victory or completion
void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter(s) isogram I'm thinking of?\n";
	std::cout << std::endl;

	/* loop asking for guesses while the game i NOT won
	and there are still tries remaining */
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bull = " << BullCowCount.Bull;
		std::cout << " | Cow = " << BullCowCount.Cow << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop contunually until the user gives a valid guess
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Attempt (" << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ")" << std::endl;
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::Ok); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (Y/N)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "GOOD JOB, YOU'VE WON!\n";
	}
	else {
		std::cout << "GAME OVER!\n";
	}
}
