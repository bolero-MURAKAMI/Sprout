.. _sprout-string-basic_string-std-tuple_element:

###############################################################################
std::tuple_element
###############################################################################

Interface
========================================
.. sourcecode:: c++

  namespace std {
    template<std::size_t I, typename T, std::size_t N, typename Traits>
    struct tuple_element<I, sprout::basic_string<T, N, Traits> >;
  }
  
  // syntax
  std::tuple_element<I, basic_string<T, N, Traits> >::type

Requires
========================================

| ``I < N``. The program is ill-formed if I is out of bounds.

Value
========================================

| The type T.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <type_traits>
  using namespace sprout;
  
  using type = string<8>;
  using element_type = std::tuple_element<0, type>::type;
  static_assert(std::is_same<element_type, char>::value, "tuple element type of string is char.");

Header
========================================

| ``sprout/string/tuple.hpp``
| Convenience header: ``sprout/string.hpp``

