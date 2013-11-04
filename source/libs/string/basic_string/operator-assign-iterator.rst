.. _sprout-string-basic_string-operator-assign-iterator:
###############################################################################
operator=
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename StringConstIterator>
  SPROUT_CXX14_CONSTEXPR basic_string& operator=(StringConstIterator rhs);

Requires
========================================

| ``std::is_same<StringConstIterator, const_iterator>::value || std::is_same<StringConstIterator, iterator>::value``.

Effects
========================================

| Equivalent to ``assign(rhs)``.

Returns
========================================

| ``*this``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");
  SPROUT_STATIC_CONSTEXPR auto y = string<8>("madocchi");
  int main() {
    x = y.begin();
    SPROUT_ASSERT_MSG(x == y, "y is assigned to x.");
  }

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

