.. _sprout-array-array-hash_value:
###############################################################################
hash_value
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N>
  inline SPROUT_CONSTEXPR std::size_t
  hash_value(sprout::array<T, N> const& v);

Returns
========================================

| Equivalent to ``sprout::hash_range(v)``.

Notes
========================================

| ``sprout::to_hash(v)`` is a valid call, because ``hash_value(v)`` ADL callable is defined.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  using type = array<int, 10>;
  SPROUT_STATIC_CONSTEXPR auto input = type{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto h = sprout::to_hash(input);
  static_assert(h, "hash value generated from array.");

Complexity
========================================

| linear in N.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/array/tuple.hpp``
| Convenience header: ``sprout/array.hpp``

