// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/Log.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/draw.h>
#include "cinder/audio/Voice.h"
#include <chrono>
#include "CinderImGui.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() = default;

/**
 * sets startup game state, and loads sounds/images.
 */
void MyApp::setup() {
  ImGui::initialize();
  engine.in_menu = true;
  engine.in_game = false;
  engine.in_round = false;
  engine.is_transition = false;
  engine.updated_balance = true;
  engine.is_end_game = false;
  srand(time(nullptr));
  LoadImages();
  LoadSounds();
}

/**
 * makes music play if it stops to continue music loop
 */
void MyApp::update() {
  if (!main_song->isPlaying() && engine.in_game) {
    main_song->start();
  }
}

/**
 * draws the engine's gamestate
 */
void MyApp::draw() {
  cinder::gl::clear();
  ImGui::Begin("Menu");
  ImGui::SetWindowFontScale(1.8);
  if (engine.is_transition) {
    DrawRoundTransition();
  }
  if (engine.in_menu) {
    DrawMenuButton();
  }
  if (engine.in_game && engine.is_betting) {
    DrawGameState();
    DrawStartGameButtons();
  }
  if (engine.in_game && engine.in_round && !engine.is_transition) {
    UpdateScore();
    DrawRoundGUI();
  }
  if (engine.is_end_game) {
    DrawGameOver();
  }
  ImGui::End();
}

/**
 * Draws start button to enter game
 */
void MyApp::DrawMenuButton() {
  if (ui::Button( "Start Game" )) {
    engine.in_menu = false;
    engine.in_game = true;
    engine.is_betting = true;
    main_song->start();
  }
}

void MyApp::DrawExitButton() {
  if (ui::Button("Exit")) {
    single_shuffel_sound->start();
    engine.in_game = false;
    engine.is_betting = false;
    engine.is_transition = false;
    engine.is_end_game = true;
    main_song->stop();
  }
}

/**
 * Draws in round buttons
 */
void MyApp::DrawGameButtons() {
  if (ui::Button("HIT")) {
    engine.RunPlayerHit();
    single_shuffel_sound->start();
  }
  if (ui::Button("STAND")) {
    multiple_chip_sound->start();
    engine.is_transition = true;
    engine.updated_balance = false;
  }
  if (ui::Button("DOUBLE")) {
    single_shuffel_sound->start();
    engine.RunPlayerHit();
    engine.Bet(engine.GetCurrentBet());
    engine.is_transition = true;
    engine.updated_balance = false;
  }
  DrawExitButton();
  DrawScore();
}

/**
 * Draws start of round buttons
 */
void MyApp::DrawStartGameButtons() {
  if (ui::Button("Place Bet")) {
    if (engine.GetCurrentBet() > 0) {
      engine.is_betting = false;
      engine.in_round = true;
      shuffel_sound->start();
    }
  }
  DrawBetButtons();
  DrawExitButton();
}

void MyApp::DrawBetButtons() {
  if (ui::Button("Reset Bet")) {
    button_sound->start();
    engine.ResetBalance();
  }
  if (ui::ImageButton(one_chip_Texture,one_chip_Texture->getSize())) {
    single_chip_sound->start();
    engine.Bet(1);
  }
  if (ui::ImageButton(ten_chip_Texture,ten_chip_Texture->getSize())) {
    single_chip_sound->start();
    engine.Bet(10);
  }
  if (ui::ImageButton(hundred_chip_Texture,
                      hundred_chip_Texture->getSize())) {
    single_chip_sound->start();
    engine.Bet(100);
  }
  if (ui::ImageButton(thousand_chip_Texture,
                      thousand_chip_Texture->getSize())) {
    single_chip_sound->start();
    engine.Bet(1000);
  }
  if (ui::ImageButton(max_chip_Texture,
                      max_chip_Texture->getSize())) {
    single_chip_sound->start();
    engine.Bet(engine.GetBalance());
  }
}

/**
 * Draws player game information during round
 */
void MyApp::DrawGameState() {
  cinder::gl::draw(background_Texture);
  cinder::gl::draw(deck_Texture);
  std::string bal_text = "Balance: "
      + engine.BetToString(engine.GetBalance());
  std::string bet_text = "Current Bet: " 
      + engine.BetToString(engine.GetCurrentBet());
  ui::Text("%s", bal_text.c_str());
  ui::Text("%s", bet_text.c_str());
}

/**
 * Draws cards from engine's player hand vector
 */
void MyApp::DrawPlayerCards() {
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  for (auto & player_card : engine.player_cards) {
    const cinder::vec2 locp = {center.x, center.y + (++row) * 70};
    cinder::gl::draw(GetCardTexture(player_card.value,
        player_card.color), locp);
  }
}

/**
 * draws all dealer cards when revealing round evaluation
 */
void MyApp::DrawDealerCards() {
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  for (auto & dealer_card : engine.dealer_cards) {
    const cinder::vec2 locp = {300, 10 +(++row) * 70};
    cinder::gl::draw(GetCardTexture(dealer_card.value,
        dealer_card.color), locp);
  }
}

/**
 * draws one shown and one hidden dealer card before player stands
 */
void MyApp::DrawInitialDealerCards() {
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  const cinder::vec2 locp = {300, 10 +(++row) * 70};
  const cinder::vec2 locp_two = {300, 10 +(++row) * 70};
  cinder::gl::draw(card_back_Texture, locp);
  cinder::gl::draw(GetCardTexture(engine.dealer_cards[0].value,
      engine.dealer_cards[0].color), locp_two);
}

/**
 * @param value int received from random rank generation
 * @param color int received from random color generation
 * @return card texture for randomly generated card
 */
cinder::gl::Texture2dRef MyApp::GetCardTexture(int value, int color) {
  cinder::gl::Texture2dRef card_texture;
  card_texture = cinder::gl::Texture2d::create( loadImage( 
      loadAsset( engine.BetToString(value) + "_" + 
      engine.BetToString(color) + ".png")));
  return card_texture;
}

/**
 * Drawn if player lost round
 */
void MyApp::DrawPlayerLose() {
  ui::Text("You Lost");
  std::string lost_bet = "- " + engine.BetToString(
      engine.GetCurrentBet());
  ui::Text("%s", lost_bet.c_str());
}

/**
 * Drawn if player won round
 */
void MyApp::DrawPlayerWin() {
  ui::Text("You Won!");
  std::string won_bet = "+ " + engine.BetToString(
      engine.GetCurrentBet());
  ui::Text("%s", won_bet.c_str());
}

/**
 * Button to reset round
 */
void MyApp::DrawNewRoundButton() {
  if (ui::Button("New Round")) {
    button_sound->start();
    engine.ResetRound();
  }
}

/**
 * Draws tie information for player tie
 */
void MyApp::DrawTie() {
  ui::Text("Tie! No Winner");
}

void MyApp::DrawScore() {
  std::string score_text = "Current Score: " 
      + engine.BetToString(engine.GetPlayerScore());
  ui::Text("%s", score_text.c_str());
}

/**
 * Draws evaluation information to screen after
 * round has been played and evaluated
 */
void MyApp::DrawRoundTransition() {
  DrawRoundResult();
  DrawGameState();
  DrawPlayerCards();
  DrawNewRoundButton();
  DrawDealerCards();
  DrawScore();
  DrawDealerScore();
}

/**
 * Draws standard in round game screen for player after bet and before evaluate
 */
void MyApp::DrawRoundGUI() {
  DrawGameState();
  DrawGameButtons();
  DrawPlayerCards();
  DrawInitialDealerCards();
}

/**
 * Updates player and dealer score for GUI
 */
void MyApp::UpdateScore() {
  engine.RunRoundStart();
  engine.SetPlayerScore(engine.EvaluateCardValue(true));
  engine.SetDealerScore(engine.EvaluateCardValue(false));
  if (engine.GetPlayerScore() >= kBlackjack) {
    multiple_chip_sound->start();
    engine.is_transition = true;
    engine.updated_balance = false;
  }
}

/**
 * Checks player balance to determine win or lose screen on player exit
 */
void MyApp::DrawEndGameText() {
  int profit = (engine.GetBalance() - kStartBalance);
  std::string end_game_text;
  if (engine.GetBalance() >= kStartBalance) {
    end_game_text = "Nice, you escaped with: $" + engine.BetToString(profit);
  } else {
    end_game_text = "Loser, you lost: $" + engine.BetToString(profit);
  }
  ui::Text("%s", end_game_text.c_str());
}

void MyApp::DrawDealerScore() {
  std::string score_text = "Dealer Score: " 
      + engine.BetToString(engine.GetDealerScore());
  ui::Text("%s", score_text.c_str());
}

/**
 * Draws End Game Screen
 */
void MyApp::DrawGameOver() {
  DrawEndGameText();
  if (ui::Button("Play Again!")) {
    engine.ResetGame();
  }
}

/**
 * Uses Engine's Evaluate Round function to determine win/lose drawing
 */
void MyApp::DrawRoundResult() {
  if (engine.EvaluateRound() == kPlayerWin) {
    DrawPlayerWin();
  }
  if (engine.EvaluateRound() == kPlayerLose) {
    DrawPlayerLose();
  }
  if (engine.EvaluateRound() == kPlayerTie) {
    DrawTie();
  }
}

/**
 * Loads all sounds needed for gameplay
 */
void MyApp::LoadSounds() {
  ci::audio::SourceFileRef main_source_file = ci::audio::load(
      ci::app::loadAsset( "rawhide.mp3"));
  main_song = ci::audio::Voice::create(main_source_file);

  ci::audio::SourceFileRef shuffle_file = ci::audio::load(
      ci::app::loadAsset( "shuffle.mp3"));
  shuffel_sound= ci::audio::Voice::create(shuffle_file);

  ci::audio::SourceFileRef single_shuffle_file = ci::audio::load(
      ci::app::loadAsset( "single_shuffle.mp3"));
  single_shuffel_sound= ci::audio::Voice::create(single_shuffle_file);

  ci::audio::SourceFileRef button_file = ci::audio::load(
      ci::app::loadAsset( "button_sound.mp3"));
  button_sound= ci::audio::Voice::create(button_file);

  ci::audio::SourceFileRef single_chip_file = ci::audio::load(
      ci::app::loadAsset( "single_chip.mp3"));
  single_chip_sound= ci::audio::Voice::create(single_chip_file);

  ci::audio::SourceFileRef multiple_chip_file = ci::audio::load(
      ci::app::loadAsset( "end_round_chip.mp3"));
  multiple_chip_sound= ci::audio::Voice::create(multiple_chip_file);
}

/**
 * Loads all images needed for game for startup
 */
void MyApp::LoadImages() {
  background_Texture = cinder::gl::Texture2d::create(
      loadImage(
          loadAsset( "background.jpg" )));
  deck_Texture = cinder::gl::Texture2d::create(
      loadImage( loadAsset( "deck.png" )));
  one_chip_Texture = cinder::gl::Texture2d::create(
      loadImage( loadAsset( "1.png" )));
  ten_chip_Texture = cinder::gl::Texture2d::create(
      loadImage( loadAsset( "10.png" )));
  hundred_chip_Texture = cinder::gl::Texture2d::create(
      loadImage( loadAsset( "100.png" )));
  thousand_chip_Texture = cinder::gl::Texture2d::create(
      loadImage( loadAsset( "1000.png" )));
  max_chip_Texture = cinder::gl::Texture2d::create(
      loadImage( loadAsset( "max.png" )));
  card_back_Texture = cinder::gl::Texture2d::create(
      loadImage(
          loadAsset( "cardBack.png" )));
}



}  // namespace myapp
