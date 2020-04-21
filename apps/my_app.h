// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>

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
  std::string BetToString(int value);
  bool inMenu;
  bool inGame;
  cinder::gl::Texture2dRef background_Texture;
  cinder::gl::Texture2dRef deck_Texture;
  cinder::gl::Texture2dRef one_chip_Texture;
  cinder::gl::Texture2dRef hundred_chip_Texture;
  cinder::gl::Texture2dRef thousand_chip_Texture;
  cinder::gl::Texture2dRef ten_chip_Texture;
  
  void DrawGameState();
  void DrawGameButtons();
  void DrawStartGameButtons();
  int balance = 1000;
  int current_bet = 0;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
