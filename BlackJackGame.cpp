//
// Implementation file for the "BlackJackGame" class.
// 
// Modified on: 03/30/2021
//

#include <iomanip>
#include <iostream>
#include "HeaderFiles/BlackJackGame.h"

using namespace std; 

/******************************************************************************************/
/*				Static definitions					  */
/******************************************************************************************/
static const string BANNER = "♠ ♡ ♣ ♢ ♦ ♤ ♥ ♧ ♠ ♡ ♣ ♢ ♦ ♤ ♥ ♧ ♠ ♡ ♣ ♢ ♦ ♤ ♥ ♧ ♠ ♡ ♣ ♢\n";

/******************************************************************************************/
/*				Local helper definitions				  */
/******************************************************************************************/

//
// Method to print the header to display participants cards
//
void print_banner(const char* participant) {

	cout << BANNER; 
	cout << "\n\t\t" << participant << "'s hand\n\n"; 
	cout << BANNER; 
	cout << NEW_LINE;
}

/******************************************************************************************/
/*				Method definitions					  */
/******************************************************************************************/
//
// Initialize the instance to null, since this is a singleton class and it will be created 
// on demand 
//
BlackJackGame* BlackJackGame::_instance = nullptr;

//
// Constructor
//
BlackJackGame::BlackJackGame(Dealer* dealer, Player& player,
			     Shoe* shoe, DiscardTray* discardTray) : 
	bjDealer	{ dealer }, 
	bjPlayer	{ &player },
	bjShoe		{ shoe }, 
	bjDiscardTray	{ discardTray } {

}

//
// Static implementation
//
BlackJackGame* BlackJackGame::get_instance(Dealer* dealer, Player& player, 
					   Shoe* shoe, DiscardTray* discardTray) {
	
	//
	// Check whether a prior instance of this 
	// class already exist if not, then go a-
	// head and create a new single instance 
	//
	if (_instance == nullptr) {
		_instance = new BlackJackGame(dealer, player, shoe, discardTray);
	}

	//
	// Return the instance 
	//
	return _instance;
}

//
// Method to cut the shoe
//
void BlackJackGame::cut_shoe() {

	//
	// Call the  "set_cut_card_pos()" 
	// method from the "Shoe" class
	//
	bjShoe->set_cut_card_pos();
}

//
// Method to play the deal round 
//
void BlackJackGame::the_deal(const bool& FirstRound) {

	//
	// Hand player and dealer two cards keep in mind since the dealer object is a singleton
	// a pointer is used to refer to its instance 
	//
	// Also, since this is the deal round the second paramter for the be
	// low function calls are hard coded to true to indicate this
	//
	for (int i = 0; i < 2; ++i) {
		this->deal_participant(*bjDealer, FirstRound);
		this->deal_participant(*bjPlayer, FirstRound);
	}
}

//
// Method to check whether the dealer or player 21 during the deal round
//
bool BlackJackGame::check_naturals() {

	//
	// Check wehther any participant has hit a black jack
	//
	if (this->bjDealer->get_HitBlackJack() || this->bjPlayer->get_HitBlackJack()) {
		return true; 
	}
	else {
		return false; 
	}
}

//
// Method to display the players cards
//
void BlackJackGame::display_participants_cards(const bool& RevealDealerCards) {

	system("clear");

	//
	// Display the curent hand of the dealer Reveal the cards as determiend by the bool 
	//
	print_banner("Dealer");
	

	/* Call the display method from the "BlackJackParticipant" class */
	if(RevealDealerCards) {
		this->bjDealer->reveal_hand();
	} 
	else {
		this->bjDealer->display_current_hand();
	}
	cout << NEW_LINE;

	//
	// Display player's hand 
	//
	print_banner("Player");

	/* Call the display method from the "BlackJackParticipant" class */
	this->bjPlayer->display_current_hand();
	cout << NEW_LINE;

	//
	// Display player's total of their current hand 
	//
	cout << "Your total: " << setw(3) << this->bjPlayer->get_TotalCardValues() << NEW_LINE;
}

//
// Check whether there are still playable cards in the shoe
//
void BlackJackGame::update_playable_cards_left() {

	this->PlayableCardsLeft = (this->bjShoe->get_available_cards() > 0);
}

//
// Collect the participants cards and place them in the discard tray 
// 
void BlackJackGame::collect_participants_cards() {

	//
	// Collect dealer and players cards from their current hand and place them in 
	// the discard tray 
	// 
	this->bjDiscardTray->collect_participants_cards(this->bjDealer->discard_cards());
	this->bjDiscardTray->collect_participants_cards(this->bjPlayer->discard_cards());
}

//
// Collect the cards from "DiscardTray" to refill the "Shoe"
// 
void BlackJackGame::refill_shoe(DiscardTray* bjDiscardTray, Shoe* bjShoe) {

	//
	// Call the "empty_tray" on the "DiscardTray" object and pass the 
	// "Shoe" instance to this method so it can populate the "Shoe" 
	// to have the game continue followed by shuffling the "Shoe"
	//
	bjDiscardTray->empty_Tray(bjShoe);
	bjShoe->shuffle_shoe();
}

//
// Method to set up a new round 
// 
void BlackJackGame::set_up_new_round() {
	
	//
	// Following steps need to happen in order for a new session to start
	//
	// 1. collect participants cards
	// 2. clear participants flags 
	// 3. mark the "DealRound" flag back to true
	//

	this->collect_participants_cards();
	this->bjDealer->reset();
	this->bjPlayer->reset();
	this->DealRound = true;
	this->RevealDealerCards = false;
}

// 
// Reset method to start another round 
// 
void BlackJackGame::set_up_new_game() {

	//
	// Following steps need to happen in order for a new game to start 
	//
	// 1.collect participants cards
	// 2.clear participants flags 
	// 3.empty discard tray 
	// 4.re-shuffle shoe 
	//
	// Note: steps 1 and 2 can be delegated to the "set_up_new_round()" function as those 
	// steps are identical 
	//

	//
	// Steps 1 and 2
	//
	this->set_up_new_round();

	//
	// Step 3
	// Empty the "DiscardTray" container contents to the shoe
	//
	this->bjDiscardTray->empty_Tray(this->bjShoe);

	//
	// Step 4
	//
	this->bjShoe->shuffle_shoe();
}

//
// Deal participant a new card 
//
void BlackJackGame::deal_participant(BlackJackParticipant& Participant, const bool& FirstRound) {

	//
	// Participant can either be a Dealer/Player depending on what's being passed to this
	// method
	//
	Participant.hit(this->bjShoe->deal_card(), FirstRound);

	//
	// Check whether there are any playable cards left in the shoe
	// 
	if(this->bjShoe->get_available_cards() <= 0) {
		this->PlayableCardsLeft = false; 
	}

}
