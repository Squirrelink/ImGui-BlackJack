# Development
**4/19/2020** Attempted to set up SFML with Cinder
- tried to use MinGw compiler along with sfml download

**4/20/2020** Learned using Cinder and SFML won't be optimal
- Looked for new GUI for game compatible with cinder

**4/21/2020** Set up ImGui as cinder block
- set up a small window with buttons and played around with how the Gui behaved

**4/22/2020** Implemented Betting System
- Added menu to the game that transitions to game
- Added betting system to control bets and balance functionality
- Added engine class to run game functions
- Added card texture Loader To load image of card to GUI

**4/23/2020** Implemented Card Dealing
- Moved betting system into engine class
- Implemented card dealing to start game
- Implemented hit button to give player more cards
- Draws player and dealer cards on the screen for GUI
- Added score counter for player

**4/25/2020** Started Adding Gameflow
- Attempted to add SQLite database for leaderboard
- Added Timer and transition state to game engine
- Attmpted to implement timed transition state upon user bust


**4/27/2020** Changed Gameflow Design
- Changed timer during transition to be a button for new round
- implemented A reset function in engine to reset game state for new round
- looked into bug where game crashes when code is added

**4/28/2020** Implemented Game Flow For Bust
- Added gameflow button where player goes over 21 by hitting
- fixed bug where player Ace and 10 value card didn't equal blackjack

**4/29/2020** Implemented Game flow
- Added full implementation for gameflow with an Evaluation Method
  and transition state.
- found and fixed the crashing bug which was from RNG generating a value that
  didn't exist in asset folder.
- Added Dealer AI to run for the dealer hit if losing and/or under 17 points

**4/30/2020** Added More Game Features
- Fixed evaluations to correctly handle the order of the scoring process
- Added functionality to the double button to double the bet and run a single hit
- started modifying dealing functions to incoporate unique card drawing per round to
  avoid duplicate card draws.
  
**5/1/2020** Added Sounds and Unique Card functionality
- Added sounds to button presses along with in game music
- Added recursive functionality to dealing cards to make sure 
  each card generated hasn't already been played during the round.
- Added an end game screen to allow for a full game loop. End game
  screen tells player their losses or profits before allowing to play again.
 
**5/2/2020** Improved Design
- Separated repetetive code into helper functions
- Added private section for engine and myApp
- Made setters and getters for engine variables

**5/3/2020** Organized Code
- Fixed naming syntax
- Removed unused code
- Added unit tests for public methods

**5/4/2020** Readme
- Wrote Readme for game functionality
- Finalized design 
- Gave appropriate access to class methods


---
