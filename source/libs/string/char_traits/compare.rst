.. _sprout-string-char_traits-compare:

###############################################################################
compare
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR int compare(char_type const* s1, char_type const* s2, std::size_t n);

Returns
========================================

| Equivalent to ``std::char_traits<Char>::compare(s1, s2, n)`` in constant expression.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char const* x = "homuhomu";
  SPROUT_STATIC_CONSTEXPR char const* y = "madocchi";
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::compare(x, y, 8);
  static_assert(result < 0, "x is less than y.");

Complexity
========================================

| linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

