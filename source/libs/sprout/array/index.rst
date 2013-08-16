.. _sprout-array:
###############################################################################
Sprout.Array
###############################################################################

.. toctree::
    :hidden:

    array/index

Interface
========================================
.. sourcecode:: c++

  template <typename T, std::size_t N>
  class array;
  
  template<typename T, std::size_t N>
  inline void swap(sprout::array<T, N>& lhs, sprout::array<T, N>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)));
  
  template<typename T, std::size_t N>
  inline SPROUT_CONSTEXPR sprout::array<T, N> to_array(T const (& arr)[N]);

Classes
========================================

* :doc:`array <./array/index>`

Non-member functions
========================================

* :doc:`swap <./swap>`
* :doc:`to_array <./to_array>`

Header
========================================

``sprout/array.hpp``

