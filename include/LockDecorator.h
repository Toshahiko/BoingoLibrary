#include <string>
#include <iostream>
#include <mutex>

namespace Boingo::Debug {
  
template<typename Callable>
class LockDecorator {
public:
  LockDecorator( const Callable& c, std::mutex& m )
    : m_c( c ), m_m( m ) {}

  template<typename ... Args>
  auto operator()( Args&& ... args ) const {
    std::lock_guard<std::mutex> l( m_m ) ;
    return m_c( std::forward<Args>( args ) ... ) ;
  }
private:
  const Callable& m_c ;
  std::mutex& m_m ;
} ;

template <typename Callable>
auto decorate_lock( const Callable& c, std::mutex& m ) {
  return LockDecorator<Callable>( c, m ) ;
}

} // anonymous
/*
int main() {
  auto deb = decorate_debug ( Plus, "Plus " ) ;

  deb( 1, 2 ) ;

  auto deb1 = decorate_debug( []( int& x ) { return x ; }, "x" ) ;
  int x = 4 ;
  deb1( x ) ;

  auto deb2 = decorate_debug( []( int& y ){ return ; }, "y " ) ;
  deb2( 2 ) ;

  std::mutex m ;
  auto safe_f = decorate_debug( decorate_lock( [] ( int x ) { return unsafe_f( x ) ; }, m ), "f(x) " ) ;
  safe_f( 1 ) ;

}
*/