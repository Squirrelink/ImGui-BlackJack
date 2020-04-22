// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/engine.h>
#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>

namespace mylibrary {


int randomValueGenerator() {
  int nr = rand() % 14 + 1;
  return nr;
}

int randomColorGenerator() {
  int nr = rand() % 4 + 1;
  return nr;
}
std::vector<cinder::gl::Texture2dRef> Engine::LoadCards() {
  return std::vector<cinder::gl::Texture2dRef>();
}
std::string Engine::BetToString(int value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}
}  // namespace mylibrary
