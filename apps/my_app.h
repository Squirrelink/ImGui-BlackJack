// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/engine.h>
#include "cinder/audio/Voice.h"
#include <chrono>

namespace myapp {
const int kBlackjack = 21;
const int kPlayerWin = 1;
const int kPlayerLose = 2;
const int kPlayerTie = 3;
const int kStartBalance = 1000;

class MyApp : public cinder::app::App {
 private:
  mylibrary::Engine engine;
  cinder::gl::Texture2dRef GetCardTexture(int value, int color);
  void DrawGameState();
  void DrawGameButtons();
  void DrawBetButtons();
  void DrawStartGameButtons();
  void DrawNewRoundButton();
  void DrawPlayerWin();
  void DrawTie();
  void DrawScore();
  void DrawDealerScore();
  void DrawPlayerCards();
  void DrawDealerCards();
  void DrawInitialDealerCards();
  void DrawPlayerLose();
  void DrawGameOver();
  void DrawRoundResult();
  void DrawRoundTransition();
  void DrawRoundGUI();
  void UpdateScore();
  void DrawEndGameText();
  void DrawExitButton();
  void MenuButton();
  void LoadImages();
  void LoadSounds();
  ci::audio::VoiceRef main_song;
  ci::audio::VoiceRef shuffel_sound;
  ci::audio::VoiceRef single_shuffel_sound;
  ci::audio::VoiceRef button_sound;
  ci::audio::VoiceRef single_chip_sound;
  ci::audio::VoiceRef multiple_chip_sound;
  cinder::gl::Texture2dRef background_Texture;
  cinder::gl::Texture2dRef deck_Texture;
  cinder::gl::Texture2dRef one_chip_Texture;
  cinder::gl::Texture2dRef hundred_chip_Texture;
  cinder::gl::Texture2dRef thousand_chip_Texture;
  cinder::gl::Texture2dRef ten_chip_Texture;
  cinder::gl::Texture2dRef max_chip_Texture;
  cinder::gl::Texture2dRef card_back_Texture;
  void setup() override;
  void update() override;
  void draw() override;
  
 public:
  MyApp();
};
}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
