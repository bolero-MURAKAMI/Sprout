.. _sprout-array-array-std-hash:

###############################################################################
std::hash
###############################################################################

Interface
========================================
.. sourcecode:: c++

  namespace std {
    template<typename T, std::size_t N>
    struct hash<sprout::array<T, N> >;
  }

Description
========================================

| Meet the requirements of class template hash.

Member functions
----------------------------------------

======================================== ===============================================================================
function                                 definition
======================================== ===============================================================================
operator()                               Equivalent to ``sprout::hash_range(v)``.
======================================== ===============================================================================

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  using type = array<int, 10>;
  SPROUT_STATIC_CONSTEXPR auto input = type{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto h = std::hash<type>()(input);
  static_assert(h, "hash value generated from array.");

Header
========================================

| ``sprout/array/hash.hpp``
| Convenience header: ``sprout/array.hpp``

