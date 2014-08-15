.. _sprout-string-basic_string-tuple_get:

###############################################################################
tuple_get
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t I, typename T, std::size_t N, typename Traits>
  inline SPROUT_CONSTEXPR T&
  tuple_get(sprout::basic_string<T, N, Traits>& t) SPROUT_NOEXCEPT;
  
  template<std::size_t I, typename T, std::size_t N, typename Traits>
  inline SPROUT_CONSTEXPR T const&
  tuple_get(sprout::basic_string<T, N, Traits> const& t) SPROUT_NOEXCEPT;
  
  template<std::size_t I, typename T, std::size_t N, typename Traits>
  inline SPROUT_CONSTEXPR T&&
  tuple_get(sprout::basic_string<T, N, Traits>&& t) SPROUT_NOEXCEPT;

Requires
========================================

| ``I < N``. The program is ill-formed if I is out of bounds.

Returns
========================================

| A reference to the Ith element of a, where indexing is zero-based.
| or
| A const reference to the Ith element of a, where indexing is zero-based.
| or
| Equivalent to ``return move(tuple_get<I>(t));``

Notes
========================================

| ``sprout::get<I>(t)`` (same as sprout::tuples::get) is a valid call, because ``tuple_get<I>(t)`` ADL callable is defined.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(sprout::get<4>(input) == 'h', "an element at position 4 is h.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/tuple.hpp``
| Convenience header: ``sprout/string.hpp``

