//
// Class declaration file for the "Card" class which will simulate a standard playing
// card which can be used for any card game
// 
// Design pattern used: None 
//
// Modified on: 03/23/2021
//

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <iostream>
#include <string>
#include <map>

using namespace std;

/****************************************************************************************/
/*				"Card" class declaration				*/
/****************************************************************************************/
class Card final {
private:

	//
	// Member and friend declarations
	//
	string FaceValue; 
	string Suit;
	friend class Deck;
	friend class Player;
	friend class Dealer;
	
public: 

	//
	// Static class members
	//
	static const short MAX_CARDS_PER_SUIT = 13;
	static const short MAX_SUITS = 4;
	static const map<string, short> CardMap;
	static const map<short, string> CardSuit; 
	static const string CardFaceValues[MAX_CARDS_PER_SUIT];

	//
	// Constructors and destructors
	//
	Card() = delete;
	Card(string face_val, string suit);
	~Card() = default;

	//
	// Getters
	//
	inline const string get_face_value() { return FaceValue; }
	inline const string get_card_suit() { return Suit; }
	inline const string get_card_suit_unicode() { return Card::CardSuit.at(stoi(Suit)); }
	
	//
	// Setters
	//
	inline void set_FaceValue(string fv) { FaceValue = fv; }
	inline void set_card_suit(string cs) { Suit = cs; }

	//
	// Functions for debugging purposes
	//
	void print_card(); 
};