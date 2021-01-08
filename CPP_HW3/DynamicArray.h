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

	class iterator
	{
	private:
		DynamicArray* _da;
		int				_i;
        bool _reverse;
    public:
		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

        iterator(DynamicArray& arr, int i, bool reverse = false) : _da(&arr), _i(i), _reverse(reverse) {}

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
            if(_reverse) --_i;
            else ++_i;
			return *this;
		}

		iterator operator++(int) {
            iterator temp(*this);
            if(_reverse) --_i;
            else ++_i;
			return temp;
		}

		iterator& operator--() {
            if(_reverse) ++_i;
            else --_i;
			return *this;
		}

		iterator operator--(int) {
			iterator temp(*this);
            if(_reverse) ++_i;
            else --_i;
			return temp;
		}

        int getIndex() { return _i; }
        int getIndex() const{ return _i; }
	};

    class const_iterator
    {
    private:
        const DynamicArray* _da;
        int				_i;
        bool _reverse;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        // other options exist, e.g., std::forward_iterator_tag
        using different_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        const_iterator(const DynamicArray& arr, int i, bool reverse = false) : _da(&arr), _i(i), _reverse(reverse) {}

        const_iterator(const const_iterator& other) : _da(other._da), _i(other._i) {}

        bool operator==(const iterator& other) const {
            return (_da == other._da) && (_i == other._i);
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        T* operator->() {
            return &_da->_arr[_i];
        }

        iterator operator++(int) {
            iterator temp(*this);
            if(_reverse) --_i;
            ++_i;
            return temp;
        }

        iterator operator--(int) {
            iterator temp(*this);
            if(_reverse) ++_i;
            --_i;
            return temp;
        }
    };

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

    const iterator& erase(iterator pos) {
        if (pos == end()) return end();
        iterator curr = pos;
        while (curr != --end()) {
            *curr = this->_arr[curr.getIndex() + 1];
            ++curr;
        }
        --_logicalSize;
        return --pos;
    }

	const iterator& erase(iterator first, iterator last)
	{
        iterator itrCurrent = last, itrInstead=first;
		while (itrCurrent != end())
		{
			*itrInstead = *itrCurrent;
			itrInstead++; itrCurrent++;
		}
		_logicalSize -= (last.getIndex() - first.getIndex());
		return --first;
	}

	iterator begin() {
		return iterator(*this, 0);
	}

	iterator end() {
		return iterator(*this, _logicalSize);
	}

    iterator rbegin() {
        return iterator(*this, _logicalSize-1, true);
    }
    iterator rend() {
        return iterator(*this, -1, true);
    }
	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}
	const_iterator cend() const {
		return const_iterator(*this, _logicalSize);
	}

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



