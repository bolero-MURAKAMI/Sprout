.. _sprout-array-array-tuple_get:

###############################################################################
tuple_get
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t I, typename T, std::size_t N>
  inline SPROUT_CONSTEXPR T&
  tuple_get(sprout::array<T, N>& t) SPROUT_NOEXCEPT;
  
  template<std::size_t I, typename T, std::size_t N>
  inline SPROUT_CONSTEXPR T const&
  tuple_get(sprout::array<T, N> const& t) SPROUT_NOEXCEPT;
  
  template<std::size_t I, typename T, std::size_t N>
  inline SPROUT_CONSTEXPR T&&
  tuple_get(sprout::array<T, N>&& t) SPROUT_NOEXCEPT;

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

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(sprout::get<5>(input) == 6, "an element at position 5 is 6.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/tuple.hpp``
| Convenience header: ``sprout/array.hpp``

