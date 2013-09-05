.. _sprout-string-char_traits-lt:
###############################################################################
lt
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR bool lt(char_type c1, char_type c2) SPROUT_NOEXCEPT;

Returns
========================================

| Equivalent to ``std::char_traits<Char>::lt(c1, c2)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char x = 'H';
  SPROUT_STATIC_CONSTEXPR char y = 'M';
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::lt(x, y);
  static_assert(result, "x is less than y.");

Complexity
========================================

| constant.
| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

