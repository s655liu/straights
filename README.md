This is a game I created for the final project of CS 246 (ObjectOriented Programming) using C++. The game is implemented with polymorphism, smart pointers, and observer design pattern. The game status, instructions, and commands are displayed through the command line. due to regulation policies, I will not display any implementatin code.    
Instructions: Lanuch the game on the command line with any integer as the command line argument that indicates the seed for shuffling cards. (ie. ./straights 1)  
The game will have 4 players. The objective is to get the fewest number of points among the players. The game ends when a plyaer reaches 80 points or more, and the player(s) with the lowest score(s) win.  
Straights uses a standard 52 card deck, without the jokers. Each player is dealt 13 cards at the beginning of each round. The Ace is considered to be the lowest card of each suit (rank of 1), while the King is considered to be the highest (rank of 13). 
The program begins by prompting the user to enter 'h' or 'c' to indicate whether the players 1-4 are human or computer. Then, the game begins with the player with the 7 of spades starting. This player must play the 7 of spades on the table. Then, other players will make legal plays in order, with the following constituting as legal plays:
  - A 7 of any suit
  - A card with the same suit and adjacent rank as another card that has already been played. (Ace and King are not considered adjacent ranks)   

If players has no legal plays, then they put a card into their discard pile. They may not discard when having a legal play. 
After all cards have been played or discarded, the score of each player is the sum of the ranks of the player's discards. The cards are reshuffled and dealt to each player if no player has accumulated 80 points. 


Valid Commands:  
play card : plays a card. The card must be entered with the syntax (rank suit ie. 7S), but does not have to be a legal play or valid card. (Note: Ace = A, 10 = T, Jack = J, Queen = Q, King = J)   
discard card : discard a card. The card must be entered with the syntax (rank suit ie. 9C), but does not have to be a legal discard.    
deck : prints the deck    
quit : terminate the program     
ragequit : human player quits and replaced by computer   
