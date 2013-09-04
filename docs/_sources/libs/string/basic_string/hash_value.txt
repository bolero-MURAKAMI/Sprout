.. _sprout-string-basic_string-hash_value:
###############################################################################
hash_value
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N, typename Traits>
  inline SPROUT_CONSTEXPR std::size_t
  hash_value(sprout::basic_string<T, N, Traits> const& v);

Returns
========================================

| Equivalent to ``sprout::hash_range(v)``.

Notes
========================================

| ``sprout::to_hash(v)`` is a valid call, because ``hash_value(v)`` ADL callable is defined.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  using type = string<8>;
  SPROUT_STATIC_CONSTEXPR auto input = type("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto h = sprout::to_hash(input);
  static_assert(h, "hash value generated from string.");

Complexity
========================================

| linear in N.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/hash.hpp``
| Convenience header: ``sprout/string.hpp``

