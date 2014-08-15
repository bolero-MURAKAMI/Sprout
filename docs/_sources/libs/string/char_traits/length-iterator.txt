.. _sprout-string-char_traits-length-iterator:

###############################################################################
length
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ConstInputIterator>
  static SPROUT_CONSTEXPR std::size_t length(ConstInputIterator s);

Returns
========================================

| The smallest i such that ``eq(s[i], char_type())`` is true.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::length(x.begin());
  static_assert(result == 8, "length of x is 8.");

Complexity
========================================

| linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

