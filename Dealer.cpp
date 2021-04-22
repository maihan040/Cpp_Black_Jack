//
// Implementation file for the "Dealer" class 
//

/****************************************************************************************/
/*					Imports				  		*/
/****************************************************************************************/
#include "HeaderFiles/Dealer.h"

/****************************************************************************************/
/*				    Method definitions					*/
/****************************************************************************************/

//
// Initialize the instance to nullptr, since this is a singleton class and it will be 
// created on demand 
//
Dealer* Dealer::_instance = nullptr;

//
// Constructor 
//
Dealer::Dealer() {}

//
// Static implementation
//

Dealer* Dealer::get_instance() {
	//
	// Check whether a prior instance of this class already exists if not, then 
	// go ahead and create a new single instance 
	//
	if (_instance == nullptr) {
		_instance = new Dealer(); 
	}

	//
	// Return the new instance 
	//
	return _instance; 
}

//
// Implementation for the "Player" member 
//
void Dealer::hit(Card new_card, bool deal_round) {
	//
	// Add the new card to the "hand" 
	//
	this->append_card(new_card);

	//
	// Add the current card value to the total in the current "hand"  
	//
	this->add_new_card_val(new_card.CardMap.at(new_card.FaceValue));

	//
	// Check whether the "Dealer" has hit 17 in which case the "Dealer" has to stand 
	//
	if (this->get_TotalCardValues() == 17)
		this->set_StandFlag(true);

	//
	// Check whether 21 has been hit
	//
	if (this->get_TotalCardValues() == 21) {

		/* Check whether 21 was hit during the deal round */
		if (deal_round == true)
			this->set_HitBlackJack(true);
			
		/* Mark that 21 has been hit */
		this->set_Hit21(true);
	}
}

//
// Method to print the dealer's current hand to the terminal OVERIDDEN method, as the first 
// card of the dealer remains hidden initially 
//
// Modify the string stream to hide the first card of the dealer
//
// Below is a representation of how the cards for the dealer will look initially. 
//
// Implementation: Replace the contents of the first card with those of "HIDDEN" (see below)
//
//    '┌─────────┐' '┌─────────┐' line1	
//    '│░░░░░░░░░│' '│ K       │' line2
//    '│░░░░░░░░░│' '│ ♠       │' line3
//    '│░░░░░░░░░│' '│         │' line4
//    '│░░░░░░░░░│' '│    ♠    │' line5
//    '│░░░░░░░░░│' '│         │' line6
//    '│░░░░░░░░░│' '│       ♠ │' line7
//    '│░░░░░░░░░│' '│       K │' line8
//    '└─────────┘' '└─────────┘' line9
//	HIDDEN 	      REGULAR
//
void Dealer::display_current_hand() {

	//
	// Local variables 
	//
	int NumCards = BlackJackParticipant::get_HandSize();

	/* Line 1 */
	for(int i = 0; i < NumCards; ++i) {
		cout << BlackJackParticipant::top_line;
	}
	cout << NEW_LINE; 

	/* Line 2 */
	/* Print hidden line first */
	cout << BlackJackParticipant::hidden_line;
	for(int i = 1; i < NumCards; ++i) {
		cout << "| " << setw(2) << left << CardContents[0].at(i) << "       |  ";
	}
	cout << NEW_LINE;

	/* Line 3 */
	/* Print hidden line first */
	cout << BlackJackParticipant::hidden_line;
	for(int i = 1; i < NumCards; ++i) {
		cout << "| " << CardContents[1].at(i) << "        |  ";
	}
	cout << NEW_LINE;

	/* Line 4 */
	/* Print hidden line first */
	cout << BlackJackParticipant::hidden_line;
	for(int i = 1; i < NumCards; ++i) {
		cout << BlackJackParticipant::filler_line;
	}
	cout << NEW_LINE;

	/* Line 5 */
	/* Print hidden line first */
	cout << BlackJackParticipant::hidden_line;
	for(int i = 1; i < NumCards; ++i) {
		cout << "|    " << setw(2) << right << CardContents[0].at(i) << "    |  ";
	}
	cout << NEW_LINE;

	/* Line 6 */
	/* Print hidden line first */
	cout << BlackJackParticipant::hidden_line;
	for(int i = 1; i < NumCards; ++i) {
		cout << BlackJackParticipant::filler_line;
	}
	cout << NEW_LINE;

	/* Line 7 */
	/* Print hidden line first */
	cout << BlackJackParticipant::hidden_line;
	for(int i = 1; i < NumCards; ++i) {
		cout << "|        " << CardContents[1].at(i) << " |  ";
	}
	cout << NEW_LINE;

	/* Line 8 */
	/* Print hidden line first */
	cout << BlackJackParticipant::hidden_line;
	for(int i = 1; i < NumCards; ++i) {
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
// Reveal the entire hand, including the hidden card
//
void Dealer::reveal_hand(){

	//
	// Clear the terminal and simply call the parent method for displaying the entire hand 
	//
	BlackJackParticipant::display_current_hand();
}
