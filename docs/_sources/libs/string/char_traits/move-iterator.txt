.. _sprout-string-char_traits-move-iterator:
###############################################################################
move
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename OutputIterator, typename ConstInputIterator>
  static OutputIterator move(OutputIterator s1, ConstInputIterator s2, std::size_t n);

Effects
========================================

| For each i in [0,n) performs ``assign(s1[i], p2[i])``.
| Copies correctly even where the ranges [s2,s2+n) and [s1,s1+n) overlap.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");;
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  char_traits<char>::move(x.begin(), y.begin(), 8);
  SPROUT_ASSERT_MSG(x[0] == y[0], "y is copied to x.");

Complexity
========================================

| linear.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

