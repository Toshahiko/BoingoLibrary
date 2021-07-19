#include <exception>
#include <iostream>

namespace Boingo {

class ScopeGuardBase {
public:
  ScopeGuardBase() : m_commit(false) {}
  void Commit() const noexcept { m_commit = true ; }
  ScopeGuardBase& operator=(const ScopeGuardBase&) = delete ;

protected:
  ScopeGuardBase( ScopeGuardBase&& other )
  : m_commit(other.m_commit) { other.Commit() ; }
  ~ScopeGuardBase() {} ;
  mutable bool m_commit ;
} ;

template<class Func>
class ScopeGuard : public ScopeGuardBase {
public:
  ScopeGuard( Func&& func ) : m_func(func) {}
  ScopeGuard( const Func& func ) : m_func(func) {}
  ~ScopeGuard() {
    if ( !m_commit ) m_func() ;
  }
  ScopeGuard( ScopeGuard&& other )
  : ScopeGuardBase( std::move( other ) )
  , m_func( other.m_func ) {

  }
private:
  const Func& m_func ;
} ;

template<class Func>
auto MakeGuard( Func&& func ) {
  return ScopeGuard<Func>( std::forward<Func>( func ) )  ;
}

} // namespace Boingo