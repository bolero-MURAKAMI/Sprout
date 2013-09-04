.. _sprout-string-basic_string-operator-plus:
###############################################################################
operator+
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N, typename Traits>
  inline SPROUT_CONSTEXPR sprout::basic_string<T, N + 1, Traits>
  operator+(sprout::basic_string<T, N, Traits> const& lhs, T const& rhs);
  
  template<typename T, std::size_t N, typename Traits>
  inline SPROUT_CONSTEXPR sprout::basic_string<T, 1 + N, Traits>
  operator+(T const& lhs, sprout::basic_string<T, N, Traits> const& rhs);
  
  template<typename T, std::size_t N, typename Traits, std::size_t M>
  inline SPROUT_CONSTEXPR sprout::basic_string<T, N + (M - 1), Traits>
  operator+(sprout::basic_string<T, N, Traits> const& lhs, T const (& rhs)[M]);
  
  template<typename T, std::size_t N, typename Traits, std::size_t M>
  inline SPROUT_CONSTEXPR sprout::basic_string<T, (M - 1) + N, Traits>
  operator+(T const (& lhs)[M], sprout::basic_string<T, N, Traits> const& rhs);
  
  template<typename T, std::size_t N1, std::size_t N2, typename Traits>
  inline SPROUT_CONSTEXPR sprout::basic_string<T, N1 + N2, Traits>
  operator+(sprout::basic_string<T, N1, Traits> const& lhs, sprout::basic_string<T, N2, Traits> const& rhs);

Returns
========================================

| A concatenated string.

Remarks
========================================

| String buffer length of the result, become the largest number that can be stored of the concatenated argument.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<4>("mado");
  SPROUT_STATIC_CONSTEXPR auto y = string<4>("homu");
  SPROUT_STATIC_CONSTEXPR auto z = x + y;
  static_assert(z == "madohomu", "A concatenated string is madohomu.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/concat.hpp``
| Convenience header: ``sprout/string.hpp``

