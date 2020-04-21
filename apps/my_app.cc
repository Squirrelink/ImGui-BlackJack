// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include "CinderImGui.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::initialize();
}

void MyApp::update() { }

void MyApp::draw() {
  ImGui::Text("hello");
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
