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
  bool inMenu;
  bool inGame;
  cinder::gl::Texture2dRef background;
  void DrawGameState();
  void DrawGameButtons();
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
