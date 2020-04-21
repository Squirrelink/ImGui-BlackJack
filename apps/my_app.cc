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
  ImGui::SetWindowFontScale(1.8);
  if (inMenu) {
    MenuButton();
  }
  if (inGame) {
    DrawGameState();
    DrawStartGameButtons();
//    DrawGameButtons();
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
  background_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "background.jpg" )));
  deck_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "deck.png" )));
  one_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "1.png" )));
  ten_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "10.png" )));
  hundred_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "100.png" )));
  thousand_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "1000.png" )));
}
void MyApp::DrawGameState() {
  cinder::gl::draw(background_Texture);
  cinder::gl::draw(deck_Texture);
  std::string balText = "Balance: " + BetToString(balance);
  std::string betText = "Current Bet: " + BetToString(current_bet);
  ui::Text(balText.c_str());
  ui::Text(betText.c_str());
}

void MyApp::DrawGameButtons() {
  ui::Button("HIT");
  ui::Button("STAND");
  ui::Button("10");
  ui::Button("100");
  ui::Button("1000");
  ui::Button("MAX");
}

void MyApp::DrawStartGameButtons() {
  ui::Button("Place Bet");
  if (ui::Button("Reset Bet")) {
    balance+= current_bet;
    current_bet = 0;
  }
  if (ui::ImageButton(one_chip_Texture,one_chip_Texture->getSize())) {
    bet(1);
  }
  if (ui::ImageButton(ten_chip_Texture,ten_chip_Texture->getSize())) {
    bet(10);
  }
  if (ui::ImageButton(hundred_chip_Texture,hundred_chip_Texture->getSize())) {
    bet(100);
  }
  if (ui::ImageButton(thousand_chip_Texture,thousand_chip_Texture->getSize())) {
    bet(1000);
  }
}

std::string MyApp::BetToString(int value) { 
  std::stringstream ss;
  ss << value;
  return ss.str();
}
void MyApp::bet(int value) {
  current_bet += value;
  balance -= value;
}

}  // namespace myapp
