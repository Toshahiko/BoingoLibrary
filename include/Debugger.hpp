#pragma once

#include <iostream>
#include <typeinfo>
#include <utility>
#include <functional>
#include <chrono>

namespace Boingo::Debug {

template<typename T>
void PrintTypeof ( const T& ) ;

template<typename T>
void PrintTypeof( const T& x ) {
  std::cout << typeid( x ).name() << std::endl ;
}

template<typename Callable, typename... Args>
decltype(auto) call( Callable&& op, Args&&... args ) {

  struct cleanup {
    cleanup() : m_stt( std::chrono::system_clock::now() ) {
      const auto time_stamp = std::chrono::system_clock::to_time_t( m_stt ) ;
      std::cout << std::ctime( &time_stamp ) ;
    }
    ~cleanup() {
      const auto end = std::chrono::system_clock::now() ;
      std::cout << "Time : " << std::chrono::duration_cast<std::chrono::milliseconds>( m_stt - end ).count() << "ms" << std::endl ;
    }

    std::chrono::system_clock::time_point m_stt ;
  } dummy ;
  return std::invoke( std::forward<Callable>( op ),
                      std::forward<Args>( args )... ) ;
}

template<typename Callable>
class DebugDecorator {
public :
  DebugDecorator( const Callable& c, const char* s )
  : m_c( c ), m_s( s ) {}
  
  template<typename ... Args>
  auto operator()( Args&& ... args ) const {
    std::cout << "Invoking: " << m_s << std::endl ;
    auto res = call( m_c, std::forward<Args>( args ) ... ) ; // 戻り値がvoidの場合は別途処理が必要
    std::cout << "Result: " << res << std::endl ;
    return res ;
  }

private :
  const Callable& m_c ;
  const std::string m_s ;
} ;

template<typename Callable>
auto decorate_debug( const Callable& c, const char* s ) {
  return DebugDecorator<Callable>( c, s ) ;
}

}