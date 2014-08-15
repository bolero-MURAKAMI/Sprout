.. _sprout-string-basic_string-operator-not_equal_to:

###############################################################################
operator!=
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N1, std::size_t N2, typename Traits>
  inline SPROUT_CONSTEXPR bool
  operator!=(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs);

Returns
========================================

| true if the contents of the containers are not equivalent, false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  static_assert(x != y, "x is not equal to y.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

Header
========================================

| ``sprout/string/comparison.hpp``
| Convenience header: ``sprout/string.hpp``

