.. _sprout-string-basic_string-assign-iterator:

###############################################################################
assign
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename StringConstIterator>
  SPROUT_CXX14_CONSTEXPR basic_string& assign(StringConstIterator s, size_type n);

Requires
========================================

| s points to an array of at least n elements of value_type.

Effects
========================================

| Replaces the string controlled by ``*this`` with a string of length n whose elements are a copy of those pointed to by s.

Returns
========================================

| ``*this``.

Throws
========================================

| std::length_error if ``n > max_size()``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  int main() {
    x.assign(y.begin(), 8);
    SPROUT_ASSERT_MSG(x == y, "y is assigned to x.");
  }

----

Interface
========================================
.. sourcecode:: c++

  template<typename StringConstIterator>
  basic_string& assign(StringConstIterator s);

Requires
========================================

| s points to an array of at least ``traits_type::length(s) + 1`` elements of value_type.

Effects
========================================

| Calls ``assign(s, traits_type::length(s))``.

Returns
========================================

| ``*this``.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

