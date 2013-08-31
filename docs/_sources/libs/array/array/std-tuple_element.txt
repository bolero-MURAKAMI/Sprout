.. _sprout-array-array-std-tuple_element:
###############################################################################
std::tuple_element
###############################################################################

Interface
========================================
.. sourcecode:: c++

  namespace std {
    template<std::size_t I, typename T, std::size_t N>
    struct tuple_element<I, sprout::array<T, N> >;
  }
  
  // syntax
  std::tuple_element<I, array<T, N> >::type

Requires
========================================

| ``I < N``. The program is ill-formed if I is out of bounds.

Value
========================================

| The type T.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  #include <type_traits>
  using namespace sprout;
  
  using type = array<int, 10>;
  using element_type = std::tuple_element<0, type>::type;
  static_assert(std::is_same<element_type, int>::value, "tuple element type of array is int.");

Header
========================================

| ``sprout/array/tuple.hpp``
| Convenience header: ``sprout/array.hpp``

