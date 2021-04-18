//
// Class declaration file for the "Dealer" class this class will simulate the dea-
// ler object of the game 
// 
// Design pattern used: Singleton  
//
// Modified on: 03/20/2021
//

#pragma once

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <memory>
#include <iomanip>
#include <iostream>
#include "MiscFunctions.h"
#include "BlackJackParticipant.h"

/****************************************************************************************/
/*				"Dealer" class declaration				*/
/****************************************************************************************/
class Dealer : public BlackJackParticipant {
private:

	//
	// Singleton member variables/construtor 
	//
	static Dealer* _instance;
	Dealer();
	
public:

	//
	// Singleton member method 
	//
	static Dealer* get_instance();

	//
	// Delete copy constructor as well as assign-
	// ment operator 
	//
	Dealer(const Dealer& ) = delete; 
	Dealer& operator=(const Dealer&) = delete; 

	//
	// Destructor
	//
	~Dealer() = default; 

	//
	// Virtual functions that are overridden 
	//
	virtual void hit(Card new_card, bool deal_round) override;
	virtual void display_current_hand() override;

	//
	// Reveal entire hand
	//
	void reveal_hand();
 };
