.. _sprout-string-basic_string-std-tuple_size:
###############################################################################
std::tuple_size
###############################################################################

Interface
========================================
.. sourcecode:: c++

  namespace std {
    template<typename T, std::size_t N, typename Traits>
    struct tuple_size<sprout::basic_string<T, N, Traits> >;
  }
  
  // syntax
  std::tuple_size<basic_string<T, N, Traits> >::value

Return type
========================================

| integral constant expression.

Value
========================================

| N.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  using type = string<8>;
  SPROUT_STATIC_CONSTEXPR auto n = std::tuple_size<type>::value;
  static_assert(n == 8, "tuple size of string is 8.");

Header
========================================

| ``sprout/string/tuple.hpp``
| Convenience header: ``sprout/string.hpp``

