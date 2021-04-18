//
// Class declaration file for the "BlackJackGame" class. This class is the main driver
// of the game where all the game logic is being implemented.
// 
// Design pattern used: Singleton  
//
// Modified on: 03/31/2021
//

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include "Dealer.h"
#include "Player.h"
#include "Shoe.h"
#include "DiscardTray.h"
#include "MiscFunctions.h"

/****************************************************************************************/
/*			    "BlackJackGame" class declaration				*/
/****************************************************************************************/
class BlackJackGame final {

	//
	// Static variable used for the singleton pattern
	//
	static BlackJackGame* _instance;

private: 

	//
	// Private variables
	// The actual objects will be passed by the calling function from the driver
	// These pointers will be used to actually operate on those objects
	//
	Shoe* bjShoe; 
	Player* bjPlayer; 
	Dealer* bjDealer; 
	DiscardTray* bjDiscardTray; 

	bool DealRound 	= true; 
	bool PlayableCardsLeft = true;
	bool RevealDealerCards = false;

	const unsigned short DealerMustStand = 17;

	//
	// Constructor
	//
	BlackJackGame(Dealer* dealer, Player& player, 
		      Shoe* shoe, DiscardTray* discardTray);

public: 

	//
	// Singleton member method 
	//
	static BlackJackGame* get_instance(Dealer* dealer, Player& player, 
					   Shoe* shoe, DiscardTray* discarTray);

	//
	// Desctructor
	//
	~BlackJackGame() = default; 

	//
	// Delete copy constructor as well as assignment operator 
	//
	BlackJackGame(const BlackJackGame&) 	= delete;
	Dealer& operator=(const BlackJackGame&) = delete; 
	
	//
	// Functions that will be used throughout the game
	//
	bool check_naturals();
	
	void cut_shoe();
	void collect_participants_cards();
	void the_deal(const bool& FirstRound);
	void refill_shoe(DiscardTray* bjDiscardTray, Shoe* bjShoe); 
	void display_participants_cards(const bool& RevealDealerCards);
	void deal_participant(BlackJackParticipant& Participant, const bool& FirstRound);

	/****************************************************************************************/
	/*			    		Setters						*/
	/****************************************************************************************/	
	void set_up_new_game();
	void set_up_new_round();
	void update_playable_cards_left();
	void set_DealRound(bool dealRound) 				{ this->DealRound = dealRound;}
	void set_RevealDealerCards(bool revealDealerCards) 		{ this->RevealDealerCards = revealDealerCards; }

	/****************************************************************************************/
	/*			    		Getters						*/
	/****************************************************************************************/
	bool get_DealRound() 				{ return this->DealRound; }
	bool get_RevealDealerCards()			{ return this->RevealDealerCards; }
	bool get_PlayableCardsLeft()			{ return this->PlayableCardsLeft; }
	unsigned short get_DealereMustStand() 		{ return this->DealerMustStand; }
};