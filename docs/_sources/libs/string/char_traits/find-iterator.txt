.. _sprout-string-char_traits-find-iterator:

###############################################################################
find
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename ConstInputIterator>
  static SPROUT_CONSTEXPR ConstInputIterator find(ConstInputIterator s, std::size_t n, char_type const& a);

Returns
========================================

| The smallest q in [s,s+n) such that ``eq(*q, a)`` is true, ``s + n`` otherwise.

Remarks
========================================

| Pointer version returns 0 when it not found, but this function returns ``s + n``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/iterator.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto result = char_traits<char>::find(x.begin(), 8, 'm');
  static_assert(sprout::distance(x, result) == 2, "a found position is 2.");

Complexity
========================================

| linear.
| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

