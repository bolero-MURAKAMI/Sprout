.. _sprout-string-char_traits-to_int_type:

###############################################################################
to_int_type
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR int_type to_int_type(char_type c) SPROUT_NOEXCEPT;

Returns
========================================

| Equivalent to ``std::char_traits<Char>::to_int_type(c)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR int x = 'H';
  SPROUT_STATIC_CONSTEXPR auto y = char_traits<char>::to_char_type(x);
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::to_int_type(y);
  static_assert(char_traits<char>::eq_int_type(result, x), "a value that converted from x to char type and re-converted to int type is equal to the original x.");

Complexity
========================================

| constant.
| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

