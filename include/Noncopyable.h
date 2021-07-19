
namespace Boingo {

struct Noncopyable {
  Noncopyable() = default ;
  Noncopyable( const Noncopyable& ) = delete ;
  Noncopyable& operator=( const Noncopyable& ) = delete ;
} ;

} // namespace Boingo