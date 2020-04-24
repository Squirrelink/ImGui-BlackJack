// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/engine.h>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void MenuButton();
  void LoadImages();
  bool inMenu;
  bool inGame;
  bool inRound;
  cinder::gl::Texture2dRef background_Texture;
  cinder::gl::Texture2dRef deck_Texture;
  cinder::gl::Texture2dRef one_chip_Texture;
  cinder::gl::Texture2dRef hundred_chip_Texture;
  cinder::gl::Texture2dRef thousand_chip_Texture;
  cinder::gl::Texture2dRef ten_chip_Texture;
  cinder::gl::Texture2dRef max_chip_Texture;
  cinder::gl::Texture2dRef card_back_Texture;
  bool isBetting;
  void DrawGameState();
  void DrawGameButtons();
  void DrawBetButtons();
  void DrawStartGameButtons();
  mylibrary::Engine engine;
  void DrawPlayerCards();
  void DrawDealerCards();
  void DrawInitialDealerCards();
  cinder::gl::Texture2dRef GetCardTexture(int value, int color);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
