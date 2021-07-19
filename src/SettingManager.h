#pragma once
#include "include/SingletonBase.h"
#include "include/smartmemory.h"

namespace Boingo::App {

using R = uint8_t ;
using G = uint8_t ;
using B = uint8_t ;
class SettingManager : public Boingo::SingletonBase<SettingManager>
{
private:
  SettingManager() ;
  ~SettingManager() ;
  friend class Boingo::SingletonBase<SettingManager> ;
public:
  void Display() ;
  void SetBGColor( R red, G green, B blue ) ;
private:
  struct Impl ;
  SMART_PTR_IMPL( Impl )
  Impl_up m_pImpl ;
} ;

}