.. _sprout-string-char_traits-copy-iterator:
###############################################################################
copy
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename OutputIterator, typename ConstInputIterator>
  static SPROUT_CXX14_CONSTEXPR OutputIterator copy(OutputIterator s1, ConstInputIterator s2, std::size_t n);

Pre-condition
========================================

| s2 not in [s1,s1+n).

Effects
========================================

| For each i in [0,n) performs ``assign(s1[i], s2[i])``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");;
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  int main() {
    char_traits<char>::copy(x.begin(), y.begin(), 8);
    SPROUT_ASSERT_MSG(x[0] == y[0], "y is copied to x.");
  }

Complexity
========================================

| linear.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

