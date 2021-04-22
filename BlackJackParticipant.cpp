//
// Implementation file for the "HitBlackJack_Participant" class.
//

/******************************************************************************************/
/*					Imports						  */
/******************************************************************************************/
#include <iomanip>
#include <iostream>
#include "HeaderFiles/BlackJackParticipant.h"
#include "HeaderFiles/Card.h"
using namespace std;

/******************************************************************************************/
/*				 Static member initializations				  */
/******************************************************************************************/
const string BlackJackParticipant::top_line    = "┌──────────┐  ";
const string BlackJackParticipant::filler_line = "|          |  ";
const string BlackJackParticipant::bottom_line = "└──────────┘  ";
const string BlackJackParticipant::hidden_line = "│░░░░░░░░░░│  ";	// used to hide card

/******************************************************************************************/
/*				    Method definitions					  */
/******************************************************************************************/

//
// Default constructor 
//
BlackJackParticipant::BlackJackParticipant() : 
HitBlackJack(false), 
StandFlag(false), 
GotBusted(false),
//HasAce(false), 
Hit21(false), 
TotalCardValues(0)
{}

//
// Discard cards, collect used cards to be put in the "Discard_Tray" Utilizes move semantics
//
vector<Card> BlackJackParticipant::discard_cards() {
	return move(Hand); 
}

//
// Reset all the flags to start a new game round or complete new game session 
//
void BlackJackParticipant::reset() {

	//
	// Clear the current "Hand"
	//
	Hand.clear();

	//
	// Reset the variables holding the current state of the participant
	//
	AceCount 	= 0; 
	TotalCardValues = 0;

	Hit21		= false; 
	StandFlag    	= false; 
	GotBusted    	= false;
	HitBlackJack 	= false;

	CardContents[0].clear();
	CardContents[1].clear();
}

//
// Add a new card to the current Hand 
//
void BlackJackParticipant::append_card(Card new_card) {

	//
	// Add new card to the vector that simulates the participant's hand
	//
	Hand.push_back(move(new_card));

	//
	// Also add the card to the "CardContents" array stream object
	//
	add_to_card_contents(new_card);
}

//
// Add new card value to the current Hand
//
void BlackJackParticipant::add_new_card_val(int NewCardVal) {

	/* Check if card is an ace and take note of it*/
	if(NewCardVal == 11) {
		++AceCount;
	}

	/* Accumulate the total values */ 
	TotalCardValues += NewCardVal;

	/* Check for a possible win */
	if(TotalCardValues == 21)
		this->Hit21 = true; 

	/* Check for a possible bust and deal Aces in the current hand */
	if(TotalCardValues > 21 && AceCount == 0) {
		this->GotBusted = true; 
	}
	/* Went over 21 but since there is an Ace in the keep deducting 
	/* for all the aces */
	else {
		while(TotalCardValues > 21) {
			--AceCount;
			TotalCardValues -= 10;
		}
	}
}

//
// Method to print the current hand to the terminal 
// 
// Card should be presented in a pleasant way to closely look like a card
// one would see at a Casino. A King of Spade would like follows: 
//
//    '┌─────────┐' line1	
//    '│ K       │' line2
//    '│ ♠       │' line3
//    '│         │' line4
//    '│    ♠    │' line5
//    '│         │' line6
//    '│       ♠ │' line7
//    '│       K │' line8
//    '└─────────┘' line9
//
void BlackJackParticipant::display_current_hand(){

	//
	// Local variables 
	//
	int NumCards = Hand.size();

	/* Line 1 */
	for(int i = 0; i < NumCards; ++i) {
		cout << BlackJackParticipant::top_line;
	}
	cout << NEW_LINE; 

	/* Line 2 */
	for(int i = 0; i < NumCards; ++i) {
		cout << "| " << setw(2) << left << CardContents[0].at(i) << "       |  ";
	}
	cout << NEW_LINE;

	/* Line 3 */
	for(int i = 0; i < NumCards; ++i) {
		cout << "| " << CardContents[1].at(i) << "        |  ";
	}
	cout << NEW_LINE;

	/* Line 4 */
	for(int i = 0; i < NumCards; ++i) {
		cout << BlackJackParticipant::filler_line;
	}
	cout << NEW_LINE;

	/* Line 5 */
	for(int i = 0; i < NumCards; ++i) {
		cout << "|    " << setw(2) << right << CardContents[0].at(i) << "    |  ";
	}
	cout << NEW_LINE;

	/* Line 6 */
	for(int i = 0; i < NumCards; ++i) {
		cout << BlackJackParticipant::filler_line;
	}
	cout << NEW_LINE;

	/* Line 7 */
	for(int i = 0; i < NumCards; ++i) {
		cout << "|        " << CardContents[1].at(i) << " |  ";
	}
	cout << NEW_LINE;

	/* Line 8 */
	for(int i = 0; i < NumCards; ++i) {
		cout << "|       " << setw(2) << right << CardContents[0].at(i) << " |  ";
	}
	cout << NEW_LINE;

	/* Line 9 */
	for(int i = 0; i < NumCards; ++i) {
		cout << BlackJackParticipant::bottom_line; 
	}
	cout << NEW_LINE;
}

//
// Function to keep track of the current "card"'s face value as well as the suit character.
// This will be used in order to print the card itself later in the game 
//
void BlackJackParticipant::add_to_card_contents(Card card) {

	/* Note down the face value of the new card */
	CardContents[0].emplace_back(card.get_face_value());
	
	/* Note down the suit type of the new card */
	CardContents[1].emplace_back(card.get_card_suit());
}
