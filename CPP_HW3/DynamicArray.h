template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}

	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] _arr;
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }

	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }

	// example iterator implementation:
	// (causes code duplication)
	class iterator
	{
	private:
		DynamicArray* _da;
		int				_i;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(DynamicArray& arr, int i) : _da(&arr), _i(i) {}
		iterator(const iterator& other) : _da(other._da), _i(other._i) {}

		// in const_iterator:	const_iterator(const iterator& other)
		//     					operator=(const iterator& other)

		// const_iterator should also be constructible from regular iterator
		friend class const_iterator;

		const iterator& operator=(const iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		T& operator*() {
			return _da->_arr[_i];
		}
		T* operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		iterator& operator++() {
			++_i;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++_i;
			return temp;
		}
		iterator& operator--() {
			--_i;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--_i;
			return temp;
		}
	};
	// and here we duplicate the 'iterator' class to 'const_iterator'

	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

//	const iterator& erase(const iterator& iter)
//	{
//		iterator itrStart = front();
//		iterator itrCurrent = itrStart, itrPrev = --itrStart;
//		while (itrCurrent != iter)
//		{
//			*itrPrev = *itrCurrent;
//			itrCurrent++;
//		}
//		*itrCurrent = *itrPrev;
//		while (itrCurrent != end())
//		{
//
//			//itrCurrent = itrPrev++;
//		}
//		iterator p = pos;
//		*p = val;
//		++_logicalSize;
//
//	}

//	const iterator& erase(const iterator& first, const iterator& last);

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}
	/*const_iterator begin() const {
		return const_iterator(*this, 0);
	}
	const_iterator end() const {
		return const_iterator(*this, _logicalSize);
	}*/
	/* other iterator methods to implement for collection:
		- cbegin()/cend()		- const iterators
		- rbegin()/rend()		- reverse iterators (end to start)
	*/

	void print() const {
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}

private:
	void resize() {
	    _physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

        delete[] _arr;
        _arr = temp;
    }


	T* _arr;
	int _logicalSize;
	int _physicalSize;
};
