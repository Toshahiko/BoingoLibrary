#include <include/pch.h>
#include "src/HelloFunc.h"
#include <src/SettingManager.h>
#include <include/Debugger.hpp>

int main() {
  Boingo::HelloFunc() ;

  Boingo::App::SettingManager::Instance().SetBGColor( 0, 255, 255 ) ;

  const auto anony = Boingo::Debug::decorate_debug( [](){ return 0 ;}, "anonymous" ) ;

  anony();
  std::vector<int> a ;
  return 0 ;
}