#include <include/pch.h>
#include "src/HelloFunc.h"
#include <src/SettingManager.h>
#include <include/Debugger.h>
#include <include/Vector3D.h>
#include <matplot/matplot.h>

namespace {
  void FourierTransform() {
  }
}

int main() {
  Boingo::HelloFunc() ;

  Boingo::App::SettingManager::Instance().SetBGColor( 0, 255, 255 ) ;

  const auto anony = Boingo::Debug::decorate_debug( [](){ return 0 ;}, "anonymous" ) ;

  Boingo::Math::Vector3D vec ;
  const auto vec2 = -vec ;

  anony();
  std::vector<int> a ;

  using namespace matplot;
    auto [x, y, z] = peaks();
    surf(x, y, z);
    // save("img/peaks.gif");
    // save("img/peaks.eps");
    show();
  return 0 ;
}