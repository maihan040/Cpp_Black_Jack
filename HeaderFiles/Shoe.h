// 
// Class declaration file for the "Shoe" class this class will simulate the shoe for the 
// black jack game which will hold 1, 2, 4, 6, or 8 decks for a single game session (st-
// andard game containing six decks). 
// 
// Design pattern used: singleton 
//
// Modified on: 03/12/2021
// 

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <deque>
#include <vector>
#include <memory>
#include <algorithm>
#include "CardDeck.h"
using namespace std; 

/****************************************************************************************/
/*				"Card" class declaration				*/
/****************************************************************************************/
class Shoe final{
private:

	//
	// Static and constant variables for this class
	//
	static const int MIN_DECKS = 4;
	static const int MAX_DECKS = 8; 
	static const int CARDS_PER_DECK = 52;
	static constexpr float CUT_CARD_MIN = .2; 	// % values used to determine max 
							// position of the cut card
	static constexpr float CUT_CARD_MAX = .25;	// % values used to determine min 
							// position of the cut card
	static bool RESHUFFLE; 

	//
	// Singleton variables/constructor 
	//
	static Shoe* _instance;
	Shoe(int Num);		// Single arg constructor which will create six decks of 
				// cards by default. 	 

	//
	// Remaining member variables 
	//
	deque<Card> GameDeck;	// Will hold all the decks used to play the game (6 decks 
				// will be the default, Casinos limit the decks to 8)
	int CutCardPos;		// Used to indicates when all the cards need to be gather-
				// ed and reshuffled again(in real games the last 20/25 %
				// of cards are not used in order to make card counting 
				// difficult)
	int AvailableCards;	// Tracker to indicate how many cards can still be dealt 
				// from the shoe until the "Cut Card" has been reached
	int NumOfDecks; 	// Indicates how many number of playing decks are used in
				// the game (usually it will vary between 6-8)

	//
	// Friend declarations
	//
	friend class DiscardTray;	// Allows the "DiscardTray" class to move its con-
					// tents back to the "Shoe" class in order to set
					// up a new session 

	//
	// Alias definitions
	//
	using ShoeIterator = deque<Card>::iterator;
	
public: 

	//
	// Singleton member method 
	//
	static Shoe* get_instance(int NumOfDecks = MIN_DECKS);
	
	//
	// Deleted special member methods  
	//
	Shoe() = delete;
	Shoe(const Shoe& ) 		= delete; 
	Shoe& operator=(const Shoe&) 	= delete; 
    	Shoe& operator=(const Shoe&&) 	= delete;

	//
	// Default destrutor
	//
	~Shoe() = default; 

	//
	// Core member methods 
	//
	Card deal_card();			// Used to deal a card to both player/s 
						// and dealer
	void clear_shoe();			// Clear the remaining cards from the 
						// shoe to reshuffle and play again
	void build_shoe(int NumOfDecks); 	// Function to build the shoe after the
						// contents have been cleared 
	void shuffle_shoe();			// Function to shuffle all the cards in-
						// side the shoe 
	
	//
	// Setter methods
	//
	void set_cut_card_pos();
	void set_available_cards();
	
	//
	// Getter methods
	//
	int get_cut_card_pos()		{return CutCardPos;}
	int get_available_cards() 	{return AvailableCards;}

	//
	// Print contents of the shoe (used for debugging)
	//
	void print_shoe();
};