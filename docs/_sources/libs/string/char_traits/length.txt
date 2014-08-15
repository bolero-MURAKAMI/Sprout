.. _sprout-string-char_traits-length:

###############################################################################
length
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CONSTEXPR std::size_t length(char_type const* s);

Returns
========================================

| Equivalent to ``std::char_traits<Char>::length(s)`` in constant expression.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR char const* x = "homuhomu";
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::length(x);
  static_assert(result == 8, "length of x is 8.");

Complexity
========================================

| linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

