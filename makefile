#########################################################################################
#				Final object file					#
#########################################################################################

#Main object file creation 
BlackJack: Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o BlackJackGame.o BlackJack_Driver.o
	g++ Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o BlackJackGame.o BlackJack_Driver.o -o BlackJack

#Testing the BlackJackGame_Driver
#BlackJack: Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o 
#	g++ Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o

#Testing the dealer driver 
#BlackJack: Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o Dealer_Driver.o
#	g++ Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o Dealer_Driver.o -o BlackJack

#Testing the player driver 
#BlackJack: Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o Player_Driver.o 
#	g++ Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o Player_Driver.o -o BlackJack

#Testing the card deck driver 
#BlackJack: Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o CardDeck_Driver.o
#	g++ Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o CardDeck_Driver.o -o BlackJack

#Testing the card driver 
#BlackJack: Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o Card_Driver.o
#	g++ Card.o CardDeck.o Shoe.o DiscardTray.o MiscFunctions.o Player.o Dealer.o BlackJackParticipant.o Card_Driver.o -o BlackJack 


#########################################################################################
#				Driver object files					#
#########################################################################################
BlackJack_Driver.o: BlackJack_Driver.cpp
	g++ -c BlackJack_Driver.cpp 

#Card_Driver.o: Card_Driver.cpp
#	g++ -c Card_Driver.cpp

#CardDeck_Driver.o: CardDeck_Driver.cpp
#	g++ -c CardDeck_Driver.cpp

#Player_Driver.o: Player_Driver.cpp
#	g++ -c Player_Driver.cpp 

#Dealer_Driver.o: Dealer_Driver.cpp
#	g++ -c Dealer_Driver.cpp 


#########################################################################################
#				Core object files					#
#########################################################################################
BlackJackGame.o: BlackJackGame.cpp
	g++ -c BlackJackGame.cpp

MiscFunctions.o: MiscFunctions.cpp
	g++ -c MiscFunctions.cpp

Dealer.o: Dealer.cpp
	g++ -c Dealer.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

BlackJackParticipant.o: BlackJackParticipant.cpp
	g++ -c BlackJackParticipant.cpp

DiscardTray.o: DiscardTray.cpp 
	g++ -c DiscardTray.cpp

Shoe.o: Shoe.cpp 
	g++ -c Shoe.cpp

CardDeck.o: CardDeck.cpp
	g++ -c CardDeck.cpp

Card.o: Card.cpp
	g++ -c Card.cpp
clean: 
	rm*.o BlackJack
