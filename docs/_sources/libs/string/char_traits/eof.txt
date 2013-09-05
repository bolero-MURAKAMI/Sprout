.. _sprout-string-char_traits-eof:
###############################################################################
eof
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR int_type eof() SPROUT_NOEXCEPT;

Effects
========================================

| Equivalent to ``std::char_traits<Char>::eof()``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <cstdio>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char x = char_traits<char>::eof();
  static_assert(x == EOF, "x is equivalent to EOF.");

Complexity
========================================

| constant.
| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

