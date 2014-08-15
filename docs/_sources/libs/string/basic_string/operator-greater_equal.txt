.. _sprout-string-basic_string-operator-greater_equal:

###############################################################################
operator>=
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N1, std::size_t N2, typename Traits>
  inline SPROUT_CONSTEXPR bool
  operator>=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs);

Returns
========================================

| true if the contents of the lhs are lexicographically greater than or equal the contents of rhs, false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  static_assert(y >= x, "y is greater than or equal to x.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/comparison.hpp``
| Convenience header: ``sprout/string.hpp``

