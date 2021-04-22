//
// Class declaration file for the "HitBlackJack_Participant" class this class will be 
// the base class from which "Player" and "Dealer" will be created from 
// 
// Design pattern used: None 
//
// Modified on: 03/17/2021
//

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <map>
#include <vector>
#include <string>
#include "Card.h"
#include "MiscFunctions.h"

using namespace std; 

/****************************************************************************************/
/*			"BlackJackParticipant" class declaration			*/
/****************************************************************************************/
class BlackJackParticipant {
	
protected:

	//
	// Private static members
	//
	static const string top_line;    
	static const string filler_line;
	static const string bottom_line;
	static const string hidden_line;	// Only used by the "Dealer"'s object
	
	static const int MAX_LINES = 9;		// Number of lines required to print 
						// the cards 
	static const int DATA_LINES = 2; 	// Indicates the numbers of rows whe-
						// re there is data on the face of a 
						// card. I.e. face value and suit. To 
						// be used for the printing feature
	
	//
	// Protected members of the class 
	//
	vector<string> CardContents[DATA_LINES];	// Keeps track of all the face values 
							// and card suits ( in order they we-
							// re dealt) of the participant current 
							// hand. IDX 0 is for the face values 
							// IDX 1 is for the card suits

private: 
	//
	// Private members
	//
	vector<Card> Hand; 
	
	unsigned short TotalCardValues{};
	unsigned short AceCount{};		// Keep track of how many aces the participant got
	
	bool HitBlackJack 	= false;	// Flag to check if 21 was hit in the deal round
	bool Hit21		= false; 	// Flag to check if 21 was hit during play 
	bool StandFlag		= false;	// Flag to check if participant wants to stand
	bool GotBusted		= false; 	// Flag to check if participant go busted (over 21)

public: 

	//
	// Constructors and destructor
	//
	BlackJackParticipant(); 
	BlackJackParticipant(const BlackJackParticipant&) = default;
	virtual ~BlackJackParticipant() = default; 

	//
	// Operational member functions 
	//
	void reset();			// resets all the local variables 
	void append_card(Card new_card);
	void add_new_card_val(int NewCardVal);
	
	vector<Card> discard_cards();	// used to collect cards from 
					// participants during game

	//
	// Virtual member methods 
	//
	virtual void hit(Card new_card, bool deal_round) = 0;
	virtual void display_current_hand();		// Prints card in current hand
	virtual void add_to_card_contents(Card card); 	// helper method for above 
							// method 
							
	//
	// Setters 
	//
	void set_Hit21(bool Hit21) 		{ this->Hit21 = Hit21; }
	void set_StandFlag(bool stand) 		{ this->StandFlag = stand; }
	void set_Hand(vector<Card> Hand)       	{ this->Hand = Hand; }
	void set_GotBusted(bool GotBusted) 	{ this->GotBusted = GotBusted; }
	void set_HitBlackJack(bool blkJck) 	{ this->HitBlackJack = blkJck; }
	void set_TotalCardValues(int totalVal) 	{ this->TotalCardValues = totalVal; }

	//
	// Getters
	//
	vector<Card> get_Hand() 	{ return std::move(Hand);}
	
	int get_HandSize() 		{ return Hand.size(); }
	int get_TotalCardValues()	{ return TotalCardValues; }
	
	bool get_Hit21() 		{ return Hit21; }
	bool get_StandFlag() 		{ return StandFlag; }
	bool get_GotBusted() 		{ return GotBusted; }
	bool get_HitBlackJack() 	{ return HitBlackJack; }
	bool get_HasAce() 		{ return ((AceCount > 0) ? true: false); }

};