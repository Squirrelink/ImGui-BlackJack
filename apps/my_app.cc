// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Log.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/draw.h>
#include "CinderImGui.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::initialize();
  inMenu = true;
  inGame = false;
  LoadImages();
}

void MyApp::update() {
}

void MyApp::draw() {
  cinder::gl::clear();
  ImGui::Begin("Menu");
  if (inMenu) {
    MenuButton();
  }
  if (inGame) {
    DrawGameState();
    DrawGameButtons();
  }
  
  ImGui::End();
}


void MyApp::keyDown(KeyEvent event) { }
void MyApp::MenuButton() {
  
  if (ui::Button( "Start Game" )) {
    inMenu = false;
    inGame = true;
  }
}
void MyApp::LoadImages() {
  background = cinder::gl::Texture2d::create( loadImage( loadAsset( "background.jpg" )));
}
void MyApp::DrawGameState() {
  cinder::gl::draw(background);
}
void MyApp::DrawGameButtons() {
  ui::Button("HIT");
  ui::Button("STAND");
  ui::Button("10");
  ui::Button("100");
  ui::Button("1000");
  ui::Button("MAX");
}

}  // namespace myapp
