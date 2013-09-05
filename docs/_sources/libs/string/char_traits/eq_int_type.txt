.. _sprout-string-char_traits-eq_int_type:
###############################################################################
eq_int_type
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR bool eq_int_type(int_type c1, int_type c2) SPROUT_NOEXCEPT;

Effects
========================================

| Equivalent to ``std::char_traits<Char>::eq_int_type(c1, c2)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR int x = 'H';
  SPROUT_STATIC_CONSTEXPR int y = 'H';
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::eq_int_type(x, y);
  static_assert(result, "x is equal to y.");

Complexity
========================================

| constant.
| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

