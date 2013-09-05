.. _sprout-string-char_traits-find:
###############################################################################
find
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR char_type const* find(char_type const* s, std::size_t n, char_type const& a);

Returns
========================================

| Equivalent to ``std::char_traits<Char>::find(s, n, a)`` in constant expression.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/iterator.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char const* x = "homuhomu";
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::find(x, 8, 'm');
  static_assert(sprout::distance(x, result) == 2, "a found position is 2.");

Complexity
========================================

| linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

