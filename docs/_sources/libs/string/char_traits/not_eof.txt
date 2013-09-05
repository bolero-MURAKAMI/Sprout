.. _sprout-string-char_traits-not_eof:
###############################################################################
not_eof
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR int_type not_eof(int_type c) SPROUT_NOEXCEPT;

Effects
========================================

| Equivalent to ``std::char_traits<Char>::not_eof(c)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char x = 'H';
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::not_eof(x);
  static_assert(result, "x is not EOF.");

Complexity
========================================

| constant.
| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

