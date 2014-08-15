.. _sprout-string-basic_string-compare:

###############################################################################
compare
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N2>
  SPROUT_CONSTEXPR int compare(basic_string<T, N2, Traits> const& str) const;

Effects
========================================

| Determines the effective length rlen of the strings to compare as the smallest of ``size()`` and ``str.size()``.
| The function then compares the two strings by calling ``traits_type::compare(data(), str.data(), rlen)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  SPROUT_STATIC_CONSTEXPR auto result = x.compare(y);
  static_assert(result < 0, "x is less than y.");

Complexity
========================================

| Recursive function invocations in *O(logN)* (logarithmic) depth.

.. note::
  The current implementation is incomplete. *O(N)* (linear) depth.

----

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N2>
  SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str) const;

Returns
========================================

| ``basic_string(*this, pos1, n1).compare(str)``.

----

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N2>
  SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, basic_string<T, N2, Traits> const& str, size_type pos2, size_type n2) const;

Returns
========================================

| ``basic_string(*this, pos1, n1).compare(basic_string<T, N2, Traits>(str, pos2, n2))``.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR int compare(value_type const* s) const;

Returns
========================================

| ``compare(basic_string(s))``.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, value_type const* s) const;

Returns
========================================

| ``basic_string(*this, pos, n1).compare(basic_string(s))``.

----

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR int compare(size_type pos1, size_type n1, value_type const* s, size_type n2) const;

Returns
========================================

| ``basic_string(*this, pos, n1).compare(basic_string(s, n2))``.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

