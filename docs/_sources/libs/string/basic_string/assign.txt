.. _sprout-string-basic_string-assign:
###############################################################################
assign
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N2>
  basic_string& assign(basic_string<T, N2, Traits> const& str);

Effects
========================================

| Equivalent to ``assign(str, 0, npos)``.

Returns
========================================

| ``*this``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  int main() {
    x.assign(y);
    SPROUT_ASSERT_MSG(x == y, "y is assigned to x.");
  }

----

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N2>
  basic_string& assign(basic_string<T, N2, Traits> const& str, size_type pos, size_type n);

Requires
========================================

| ``pos <= str.size()``.

Effects
========================================

| Determines the effective length rlen of the string to assign as the smaller of n and ``str.size() - pos`` and calls ``assign(str.data() + pos, rlen)``.

Returns
========================================

| ``*this``.

Throws
========================================

| std::out_of_range if ``pos > str.size()``.

----

Interface
========================================
.. sourcecode:: c++

  basic_string& assign(value_type const* s, size_type n);

Requires
========================================

| s points to an array of at least n elements of value_type.

Effects
========================================

| Replaces the string controlled by *this with a string of length n whose elements are a copy of those pointed to by s.

Returns
========================================

| ``*this``.

Throws
========================================

| std::length_error if ``n > max_size()``.

----

Interface
========================================
.. sourcecode:: c++

  basic_string& assign(value_type const* s);

Requires
========================================

| s points to an array of at least ``traits_type::length(s) + 1`` elements of value_type.

Effects
========================================

| Calls ``assign(s, traits_type::length(s))``.

Returns
========================================

| ``*this``.

----

Interface
========================================
.. sourcecode:: c++

  basic_string& assign(size_type n, value_type c);

Effects
========================================

| Equivalent to ``assign(basic_string(n, c))``.

Returns
========================================

| ``*this``.

----

Interface
========================================
.. sourcecode:: c++

  template<typename InputIterator>
  basic_string& assign(InputIterator first, InputIterator last);

Effects
========================================

| Equivalent to ``assign(basic_string(first, last))``.

Returns
========================================

| ``*this``.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

