//
// Main module file for the Black Jack game. This module will coordinate the game by 
// instantiating the "BlackJackGame" class which contains all the necessary objects
// as well as game logic needed to play a game between a dealer and a single player. 
//
// Goal of this module is to conduct the game from start to finish when the user de-
// cides to quit the game
//
// Design pattern used: None 
//
// Modified on: 04/15/2021
//

/****************************************************************************************/
/*					Imports						*/
/****************************************************************************************/
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <string>
#include <fstream> 
#include <sstream> 
#include <iostream>
#include <exception>

#include "Shoe.h"
#include "Dealer.h"
#include "Player.h"
#include "DiscardTray.h"
#include "BlackJackGame.h"
#include "MiscFunctions.h"

using namespace std; 

/****************************************************************************************/
/*				     Globals						*/
/****************************************************************************************/
ifstream iFileBJ, iFileCards, 
		iFileGameMenu, iFileStartMenu, 
		iFilePlayerWon, iFilePlayerLost,
		iFileTieMsg, iFileReshuffleShoe;

/****************************************************************************************/
/*				Function declarations					*/
/****************************************************************************************/
bool get_user_choice();

void open_file(ifstream& iFile, const string& FileName);
void close_file(ifstream& iFile);

void prepare_new_round(BlackJackGame* BJG);
void pause_game(const unsigned short& Delay);
void play_game(BlackJackGame* BJG, Dealer* dealer, Player& player, 
	       DiscardTray* discardTray, Shoe* shoe, bool FirstRound = true);

void print_game_menu();
void print_game_msg(ifstream& iFile);
void print_player_result(const stringstream& GameResult);
void print_game_output(BlackJackGame* BJG, ifstream& iFile, const unsigned short& delay);
void print_start_menu(ifstream& iFileBJ, ifstream& iFileCards, ifstream& iFileStartMenu);

/****************************************************************************************/
/*					Main						*/
/****************************************************************************************/
int main() {

	//
	// Local variables used for playing 
	// the game 
	// 
	Player player; 
	Shoe* shoe (Shoe::get_instance()); 
	Dealer* dealer = Dealer::get_instance(); 
	DiscardTray* discardTray = DiscardTray::get_instance(); 
	BlackJackGame* BJG = BlackJackGame::get_instance(dealer->get_instance(), 
							 player, 
							 shoe->get_instance(), 
							 discardTray->get_instance());
	bool UserChoice; 	// used to keep track the input of the player 

	//
	// Local variables used to manage all the 
	// menu files used during the game 
	// 

	//
	// Map data structure to map the ifstream objects 
	// to the text file names that correspond to them
	map<string, ifstream&> InputFiles = {
		{"Card.txt", iFileCards},
		{"BlackJack.txt", iFileBJ},
		{"Menu.txt", iFileStartMenu},
		{"TieMessage.txt", iFileTieMsg},
		{"GameMenu.txt", iFileGameMenu},
		{"PlayerWon.txt", iFilePlayerWon},
		{"PlayerLost.txt", iFilePlayerLost}
	};


	/* Open all the text files needed for the game */
	try {
		for (auto it = InputFiles.begin(); it != InputFiles.end(); ++it){
			open_file(it->second, it->first);
		} 

	} catch(std::runtime_error& e) {
		cerr << "Terminating the app : " << e.what() << endl;
		exit(1);
	}


	/* Display the menu */
	print_start_menu(iFileBJ, iFileCards, iFileStartMenu);

	/* Get user's choice */
	UserChoice = get_user_choice();

	/* Check if game needs to be terminated prematurely */
	if(!UserChoice) {
	
		/* Terminate the game */
		exit(0);
	} 
	else {
		/* Start a game session */
		play_game(BJG, dealer, player, discardTray, shoe, true);

	}

	/* Close the menu files */
	for (auto it = InputFiles.begin(); it != InputFiles.end(); ++it){
		close_file(it->second);
	}

	/* Terminate the app */
	return 0; 
}

/****************************************************************************************/
/*				Function definitions					*/
/****************************************************************************************/

//
// Function to pause the game. Mostly used to give the user 
// time to read the displayed contents 
//
void pause_game(const unsigned short& Delay) {

	std::this_thread::sleep_for(std::chrono::seconds(Delay));
}

//
// Function to prepare the game for a new round 
// 
void prepare_new_round(BlackJackGame* BJG) {
	
	/* Set up the new round */
	BJG->set_up_new_round();
}

//
// Core function which will coordinate the entire play from start to finish
//
void play_game(BlackJackGame* BJG, Dealer* dealer, Player& player, DiscardTray* discardTray, Shoe* shoe, bool FirstRound) {

	//
	// Local variables 
	// 
	char UserChoice; 
	unsigned short DealerTotal{};
	unsigned short PlayerTotal{}; 

	//
	// Cut the shoe 
	// 
	StartOfNewGame:		// Label used for control flow 
	BJG->cut_shoe();
	
	//
	// Main do while loop to play the game as long as the player doesn't quit
	//
	StartOfRound:
	do {
		//
		// Clear the terminal 
		// Deal round 
		// Each participant is being dealt two cards
		// followed by validation for an early termination
		//
		system("clear");
		BJG->the_deal(FirstRound);
		BJG->set_DealRound(false);

		/* Display participants hands */
		BJG->display_participants_cards(BJG->get_RevealDealerCards());		

		/* Determine whether there is a need to check for naturals */
		if(dealer->get_HasAce() || player.get_HasAce()) {
		
			/* Check for naturals */
			if(BJG->check_naturals()) {
			/* Detemine the winner */
			if(dealer->get_Hit21()) {
				print_game_output(BJG, iFilePlayerLost, 1);
			}
			else {
				print_game_output(BJG, iFilePlayerWon, 1);
			}
			/* Jump to the end of the loop */
			goto PlayAnotherRound;
			}
		}
		/****************************************************************/
		/*` Player's play						*/
		/*` Have player continue playing until they chose to stand 	*/
		/****************************************************************/
		do {

			/* Ask player whether they want to stand at this point */
			cout << "Enter choice! \n\n";
			cout << "'S' : Stand \n'H' : Hit\n'Q' : Quit\n'N' : New Game\n\n";
			
			/* Capture player's input */
			cin >> UserChoice;
			cin.ignore();
			//pause_game(1);

			/* Process based on user input */ 
			switch(UserChoice) {
				case 'S': 
				case 's': player.set_StandFlag(true); 
					continue;
				case 'H': 
				case 'h': break; 
				case 'N':
				case 'n': BJG->set_up_new_game();
					  goto StartOfNewGame;
				default: cout << "Terminating the game!\n";
					return;
			}

			//
			// Hit the player with a card and display the updated hand
			//
			// Second parameter is hard coded to false as by this point 
			// the game is past the deal round 
			//
			BJG->deal_participant(player, false);
			BJG->display_participants_cards(BJG->get_RevealDealerCards());
			
			/* Check whether player reached 21 */
			if(player.get_Hit21()) {				
				print_game_output(BJG, iFilePlayerWon, 1);
				goto PlayAnotherRound;
			}

			/* Check whether player went over 21 */
			if(player.get_GotBusted()) {
				print_game_output(BJG, iFilePlayerLost, 1);
				goto PlayAnotherRound;				
			}

		} while(!player.get_StandFlag() || player.get_Hit21());

		/********************************************************************************/
		/* Dealer's play								*/
		/* Dealer's hidden card will be revealed and the dealer continues to get a card */
		/* dealt until dealer hits the minimum which is set at 17			*/								
		/********************************************************************************/
		BJG->set_RevealDealerCards(true); 
		BJG->display_participants_cards(BJG->get_RevealDealerCards());

		/* Have dealer play until they hit the minimum at which they must stand */
		while(!dealer->get_StandFlag() || dealer->get_Hit21()) {

			/* Check dealer's total and stand if condition is met */
			if(dealer->get_TotalCardValues() >= BJG->get_DealereMustStand()) {
				dealer->set_StandFlag(true);
			} 
			else {
				/* Dealer deals a new card */
				BJG->deal_participant(*dealer, false);
				BJG->display_participants_cards(BJG->get_RevealDealerCards());
				pause_game(1);
			}

			/* Check whether dealer hit 21 */
			if(dealer->get_Hit21()) {
				print_game_output(BJG, iFilePlayerLost, 1);
				goto PlayAnotherRound;
			}

			/* Check whether dealer got busted */
			if(dealer->get_GotBusted()) {
				print_game_output(BJG, iFilePlayerWon, 1);
				goto PlayAnotherRound;
			}
		}

		//
		// Compare the count of cards and determine which of the three possible three 
		// outcomes occured (Player wont, Player lost, tie)
		//
		DealerTotal = dealer->get_TotalCardValues();
		PlayerTotal = player.get_TotalCardValues();
		if( DealerTotal > PlayerTotal) {
			print_game_msg(iFilePlayerLost);
		}
		else if (DealerTotal == PlayerTotal) {
			print_game_msg(iFileTieMsg);
		}
		else {
			print_game_msg(iFilePlayerWon);
		}

		//
		// Ask for player's input 
		// 
		PlayAnotherRound:	// Label used for control flow
		cout << "Want to play another round? \n\n";
		cout << "Y : Yes\n";
		cout << "N : No\n";

		cin >> UserChoice;
		cin.ignore();

		//
		// If player wants to continue playing, then set up a 
		// new round 
		// 
		if(UserChoice == 'Y' || UserChoice == 'y') {

			//
			// Start new round 
			//
			prepare_new_round(BJG);

			//
			// Reset participants counts
			//
			DealerTotal = 0;
			PlayerTotal = 0;

		}
		else {
			break;
		}

		//
		// Check if any available cards are still left
		// 
		if (!BJG->get_PlayableCardsLeft()) {
			print_game_msg(iFileReshuffleShoe);
			BJG->refill_shoe(discardTray, shoe);
			shoe->set_available_cards();
			goto StartOfRound;
		}

	} while(true);

	/* Return so the game can be terminated */
	return;
}

//
// Function to open a file 
//
void open_file(ifstream& iFile, const string& FileName) {

	//// 
	//// Try to open the file
	////
	//try {
	//	iFile.open(FileName);
	//}
	//catch (std::exception& e) {
	//	std::cerr << "Exception opening/reading file\n";
	//	exit(1);
  	//}

	//
	// Try to open the file, if it doesn't exist then throw a
	// runtime exception
	// 
	iFile.open(FileName);

	/* Check whether the file was successfully opened */
	if(!iFile)
		throw std::runtime_error("Could not open: " + FileName);
}

//
// Function to close the file
//
void close_file(ifstream& iFile) {

	/* close the file */
	iFile.close();
}

//
// Function to print the game output 
// 
void print_game_output(BlackJackGame* BJG, ifstream& iFile, const unsigned short& delay) {

	//
	// Reveal all the participants cards (including the hidden card from the dealer)
	// At this point the dealer's cards need to be revealed
	// hence the hard coded boolean value
	// Wait for a while for a user to be able to read the output 
	// Print the message indicating the game outcome 
	//
	BJG->set_RevealDealerCards(true); 	 
	BJG->display_participants_cards(true);	
	std::this_thread::sleep_for(std::chrono::seconds(delay));
	print_game_msg(iFile);

}

//
// Function to display the outcome fo the current round 
// 
void print_game_msg(ifstream& iFile) {

	//
	// Local variables 
	//
	string LineToDisplay{};

	//
	// Print each line of the file 
	//
	while(getline(iFile, LineToDisplay)) {
		cout << LineToDisplay << NEW_LINE;
	}

	cout << NEW_LINE;

	//
	// Go back to the beginning of the file so that the next run 
	// can print the output again 
	//
	iFile.clear();
	iFile.seekg(0);
}

//
// Function to display the main menu to the user 
// 
void print_start_menu(ifstream& iFileBJ, ifstream& iFileCards, ifstream& iStartMenu) {

	//
	// Local variables
	//
	string LineToDisplay; 
	
	//
	// Print the contents of the files to the console
	//
	
	while(getline(iFileBJ, LineToDisplay)) {
		cout << LineToDisplay << NEW_LINE;
	}
	cout << NEW_LINE << NEW_LINE;
	
	while(getline(iFileCards, LineToDisplay)) {
		cout << LineToDisplay << NEW_LINE;
	}

	cout << NEW_LINE << NEW_LINE;

	while(getline(iStartMenu, LineToDisplay)) {
		cout << LineToDisplay << NEW_LINE;
	}

	cout << NEW_LINE;
}

//
// Function to get the user input for the main menu 
//
bool get_user_choice() {

	//
	// Local variables 
	// 
	char UserChoice;

	//
	// Capture the user choice and validate that it's correct
	//
	while (true) {
	
		cin >> UserChoice;
		cin.ignore();
	
		if(tolower(UserChoice) == 'p') {
			return true;
		}
		else if(tolower(UserChoice) == 'q') {
			return false; 
		}
		else {
			cout << "Enter 'P' or 'Q' only !\n";
		}
	}
}