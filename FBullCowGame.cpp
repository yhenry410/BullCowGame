#pragma once

#include "FBullCowGame.h"
#include <map>
#include <time.h>

// Unreal Engine friendly syntax
#define TMap std::map
using int32 = int;

// this constructor overwrites the the values in the header (this is RunTime)
FBullCowGame::FBullCowGame() {Reset();}

void FBullCowGame::Reset() {
	FString WordBank[] = {"planet", "earth", "have", "lead", "align", "lead", "helix",
	"cat", "isogram", "foam", "major", "paris", "storm", "macro", "ransom", "random","image"};

	srand(time(NULL));
	int32 randomWord = rand() % 9;
	const FString HIDDEN_WORD = WordBank[randomWord]; // this hidden word must be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}

bool FBullCowGame::IsGameWon() const {return bGameIsWon;}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	// if the guess isn't an isogram, return an error
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isn't all lowercase, return an error
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong, return an error
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	//otherwise, return OK
	else {
		return EGuessStatus::Ok;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++) {
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then..
			if (Guess[j] == MyHiddenWord[i]) { 
				if (i == j) { // if they're in the same place
					BullCowCount.Bull++; // increment bulls
				}
				else {
					BullCowCount.Cow++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bull == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {return true;}

	TMap<char, bool> LetterSeen; // setting up our map
	for (char Letter : Word) { // for all letters of the word
		Letter = tolower(Letter); // handle mixed cases
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

