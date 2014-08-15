.. _sprout-string-basic_string-u32string:

###############################################################################
u32string
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N>
  using u32string = sprout::basic_string<char32_t, N>;

Examples
========================================
.. sourcecode:: c++

  #include <type_traits>
  #include <sprout/string.hpp>
  using namespace sprout;
  
  using type = u32string<8>;
  static_assert(std::is_same<type::value_type, char32_t>::value, "element type of u32string is char32_t.");

Header
========================================

| ``sprout/string/alias.hpp``
| Convenience header: ``sprout/string.hpp``

