#pragma once

namespace Boingo {

template <class T>
class SingletonBase
{
protected:
  SingletonBase() {}
public:
  SingletonBase( SingletonBase const& ) = delete ;
  SingletonBase& operator=(SingletonBase const&) = delete ;
  static T& Instance()
  {
    static T single;
    return single;
  }
} ;

} // namespace Boingo