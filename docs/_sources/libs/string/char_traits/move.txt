.. _sprout-string-char_traits-move:
###############################################################################
move
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static char_type* move(char_type* s1, char_type const* s2, std::size_t n);

Effects
========================================

| Equivalent to ``std::char_traits<Char>::move(s1, s2, n)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  char x[] = "homuhomu";
  SPROUT_STATIC_CONSTEXPR char const* y = "madocchi";
  char_traits<char>::move(x, y, 8);
  SPROUT_ASSERT_MSG(x[0] == y[0], "y is copied to x.");

Complexity
========================================

| linear.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

