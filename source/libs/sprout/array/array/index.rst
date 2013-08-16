.. _sprout-array-array:
###############################################################################
Class template array
###############################################################################

.. toctree::
    :hidden:

Interface
========================================
.. sourcecode:: c++

  template <typename T, std::size_t N>
  class array {
  	// types:
  	typedef T& reference;
  	typedef T const& const_reference;
  	typedef /*implementation-defined*/ iterator;
  	typedef /*implementation-defined*/ const_iterator;
  	typedef std::size_t size_type;
  	typedef std::ptrdiff_t difference_type;
  	typedef T value_type;
  	typedef T* pointer;
  	typedef T const* const_pointer;
  	typedef sprout::reverse_iterator<iterator> reverse_iterator;
  	typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator;
  
  	// constants:
  	SPROUT_STATIC_CONSTEXPR size_type static_size = N;
  
  	T elems[N ? N : 1]; // exposition only
  
  	// construct/copy/destroy:
  	template<typename T2>
  	array& operator=(array<T2, N> const& rhs);
  	template<typename T2>
  	array& operator=(array<T2, N>&& rhs);
  
  	// modifiers:
  	void fill(const_reference u);
  	SPROUT_CONSTEXPR array fill(const_reference value) const;
  	void assign(const_reference value);
  	SPROUT_CONSTEXPR array assign(const_reference value) const;
  	void swap(array&) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>())));
  
  	// iterators:
  	iterator begin() SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT;
  	iterator end() SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT;
  	reverse_iterator rbegin() SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT;
  	reverse_iterator rend() SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT;
  
  	// capacity:
  	SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT;
  
  	// element access:
  	reference operator[](size_type n);
  	SPROUT_CONSTEXPR const_reference operator[](size_type n) const;
  	reference at(size_type n);
  	SPROUT_CONSTEXPR const_reference at(size_type n) const;
  	reference front();
  	SPROUT_CONSTEXPR const_reference front() const;
  	reference back();
  	SPROUT_CONSTEXPR const_reference back() const;
  	pointer data() SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT;
  	pointer c_array() SPROUT_NOEXCEPT;
  	SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT;
  };


Description
========================================

Member functions
----------------------------------------

(initializer)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* :doc:`(initializer) <./array/initializer->`

construct/copy/destroy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* :doc:`operator= <./array/operator-assign>`

modifiers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* :doc:`fill <./array/fill>`
* :doc:`assign <./array/assign>`

iterators
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* :doc:`begin <./array/begin>`
* :doc:`end <./array/end>`
* :doc:`rbegin <./array/rbegin>`
* :doc:`rend <./array/rend>`
* :doc:`cbegin <./array/cbegin>`
* :doc:`cend <./array/cend>`
* :doc:`crbegin <./array/crbegin>`
* :doc:`crend <./array/crend>`

capacity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* :doc:`size <./array/size>`
* :doc:`max_size <./array/max_size>`
* :doc:`empty <./array/empty>`

element access
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* :doc:`operator[] <./array/operator-subscript>`
* :doc:`at <./array/at>`
* :doc:`front <./array/front>`
* :doc:`back <./array/back>`
* :doc:`data <./array/data>`
* :doc:`c_array <./array/c_array>`

Header
========================================

``sprout/array/array.hpp``

Convenience header: ``sprout/array.hpp``

