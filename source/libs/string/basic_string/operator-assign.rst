.. _sprout-string-basic_string-operator-assign:
###############################################################################
operator=
###############################################################################

Interface
========================================
.. sourcecode:: c++

  basic_string& operator=(basic_string const& rhs);
  
  template<std::size_t N2, typename Enable = typename std::enable_if<(N2 != N)>::type>
  basic_string& operator=(basic_string<T, N2, Traits> const& rhs);
  
  basic_string& operator=(value_type const* rhs);

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
  x = y;
  SPROUT_ASSERT_MSG(x == y, "y is assigned to x.");

----

Interface
========================================
.. sourcecode:: c++

  basic_string& operator=(value_type rhs);

Effects
========================================

| Equivalent to ``assign(1, rhs)``.

Returns
========================================

| ``*this``.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

