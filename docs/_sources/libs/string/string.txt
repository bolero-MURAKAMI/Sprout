.. _sprout-string-basic_string-string:

###############################################################################
string
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N>
  using string = sprout::basic_string<char, N>;

Examples
========================================
.. sourcecode:: c++

  #include <type_traits>
  #include <sprout/string.hpp>
  using namespace sprout;
  
  using type = string<8>;
  static_assert(std::is_same<type::value_type, char>::value, "element type of string is char.");

Header
========================================

| ``sprout/string/alias.hpp``
| Convenience header: ``sprout/string.hpp``

