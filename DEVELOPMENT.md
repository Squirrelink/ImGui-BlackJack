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
- Added Timer and transition state to game engine
- Attmpted to implement timed transition state upon user bust

**4/27/2020** Changed Gameflow Design
- Changed timer during transition to be a button for new round
- implemented A reset function in engine to reset game state for new round
- looked into bug where game crashes when code is added

**4/28/2020** Implemented Game Flow For Bust
- Added gameflow button where player goes over 21 by hitting
- fixed bug where player Ace and 10 value card didn't equal blackjack

---
