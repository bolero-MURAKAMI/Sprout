.. _sprout-string-basic_string-std-hash:
###############################################################################
std::hash
###############################################################################

Interface
========================================
.. sourcecode:: c++

  namespace std {
    template<typename T, std::size_t N, typename Traits>
    struct hash<sprout::basic_string<T, N, Traits> >;
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

  #include <sprout/string.hpp>
  using namespace sprout;
  
  using type = string<8>;
  SPROUT_STATIC_CONSTEXPR auto input = type("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto h = std::hash<type>()(input);
  static_assert(h, "hash value generated from string.");

Header
========================================

| ``sprout/string/hash.hpp``
| Convenience header: ``sprout/string.hpp``

