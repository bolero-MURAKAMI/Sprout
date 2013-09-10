.. _sprout-array-array-std-tuple_size:
###############################################################################
std::tuple_size
###############################################################################

Interface
========================================
.. sourcecode:: c++

  namespace std {
    template<typename T, std::size_t N>
    struct tuple_size<sprout::array<T, N> >;
  }
  
  // syntax
  std::tuple_size<array<T, N> >::value

Return type
========================================

| integral constant expression.

Value
========================================

| N.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  using type = array<int, 10>;
  SPROUT_STATIC_CONSTEXPR auto n = std::tuple_size<type>::value;
  static_assert(n == 10, "tuple size of array is 10.");

Header
========================================

| ``sprout/array/tuple.hpp``
| Convenience header: ``sprout/array.hpp``

