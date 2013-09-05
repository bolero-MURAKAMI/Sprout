.. _sprout-string-char_traits-compare-iterator:
###############################################################################
compare
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ConstInputIterator>
  static SPROUT_CONSTEXPR int compare(char_type const* s1, ConstInputIterator s2, std::size_t n);
  
  template<typename ConstInputIterator>
  static SPROUT_CONSTEXPR int compare(ConstInputIterator s1, char_type const* s2, std::size_t n);
  
  template<typename ConstInputIterator1, typename ConstInputIterator2>
  static SPROUT_CONSTEXPR int compare(ConstInputIterator1 s1, ConstInputIterator2 s2, std::size_t n);

Returns
========================================

| If for each i in [0,n), ``eq(s1[i], s2[i])`` is true, return zero.
| Otherwise, if for some j in [0,n), ``lt(s1[j], s2[j])`` is true and for each i in [0,j) ``eq(s1[i], s2[i])`` is true, return a negative value.
| Otherwise,  return a positive value.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::compare(x.begin(), y.begin(), 8);
  static_assert(result < 0, "x is less than y.");

Complexity
========================================

| linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

