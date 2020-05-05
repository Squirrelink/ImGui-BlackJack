# ImGui BlackJack

This application is a visual game of BlackJack written in C++ using Cinder v0.9.2 and the [Cinder Block ImGui](https://github.com/simongeilfus/Cinder-ImGui). Use [Visual Studio 15](https://visualstudio.microsoft.com/vs/older-downloads/) for the best performance

## Requirements
- [Cinder v0.9.2 or above](https://libcinder.org/download)
- [Visual Studio 2015+](https://visualstudio.microsoft.com/vs/older-downloads/)
- [ImGui Cinder Block (already packaged with Cinder v0.9.3 and above)](https://github.com/simongeilfus/Cinder-ImGui)
- [CMake](https://cmake.org/download/)

## Installation

Note: If using Cinder v0.9.3 ImGui is already included. 
Download [Cinder](https://libcinder.org/download) and make a new folder in the /my-projects directory folder of Cinder. Create the repository into the project folder to run this application. To add ImGui to Cinder, download the [Cinder Block ImGui](https://github.com/simongeilfus/Cinder-ImGui) and put it in the Cinder folders /blocks directory. 
Make sure to change the CMakeLists.txt BLOCKS section to the Cinder-ImGui folder in the /blocks directory if it isn't already.

```bash
ci_make_app(
    APP_NAME    cinder-myapp
    CINDER_PATH ${CINDER_PATH}
    SOURCES     ${SOURCE_LIST}
    LIBRARIES   mylibrary
    BLOCKS      Cinder-ImGui
)
```


## Description 

As you start the game, you enter a casino to the lovely tunes of the Blues Brothers as you prepare to lose your hard-earned 1k paycheck to the dealer. As with any classic BlackJack game, you start by placing your bet, which then begins the round. As a player, you attempt to get as close to a card score of 21 as you can, without going over (bust). A score of 21 automatically wins, but otherwise, you may stand, and wait for the dealer to play his hand. Dealers will always stand on 17 and over. An Ace is worth 11 or 1, in favor of the player's better score. You can also use the double button which will run a single hit and stand but will double your bet and profits if you win. If you lose all your money before you make it big, you can exit at any point and return to the game as if you had never went bankrupt for a chance to rewrite history.

## Controls
| Button | Description |
| --- | --- |
| Start | Starts the user at a BlackJack table |
| Place Bet | Removes current bet from balance and places it up for gamble |
| Reset Bet | Resets current bet and returns it to balance |
| Hit | Adds a single card to player hand |
| Stand | Ends player turn and evaluates the round winner |
| Double | Runs a single player hit then stands for round evaluation. Current bet is doubled |
| New Round | Starts another round of play at betting stage |
| Play Again | Returns the user to menu screen |
| Exit | Exits to end game screen where profits or losses are reported |

## Visuals

The images of the game are drawn using Cinder, while the User Interaction menu is utilizing ImGui for game control
<img width="752" alt="Game3" src="https://user-images.githubusercontent.com/55003777/81023493-de94da80-8e70-11ea-8914-afb1f1ac7a01.PNG">
<img width="753" alt="Game2" src="https://user-images.githubusercontent.com/55003777/81024287-4815e880-8e73-11ea-9d92-3e6e2e0ae642.PNG">
<img width="752" alt="Game1" src="https://user-images.githubusercontent.com/55003777/81024344-74ca0000-8e73-11ea-9d9c-42c50311474a.PNG">




**Author**: John Wachala - [`jwacha4@illinois.edu`](mailto:jwacha4@illinois.edu)
