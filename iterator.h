#pragma once

namespace abn
{
	template <class T>
	class iterator
	{

	private:

		T* data{};
		size_t index{};

	public:

		static constexpr size_t npos{ static_cast<size_t>( -1 ) };

		iterator() {}

		iterator( T* data, size_t index = -1 )
		{
			this->data = data;
			this->index = index;
		}

		iterator<T> operator = ( iterator<T> it )
		{
			data = it.data;
			index = it.index;
			return *this;
		}

		iterator<T>& operator ++ ()
		{
			++data;

			if ( index != npos )
			{
				++index;
			}

			return *this;
		}

		iterator<T>& operator -- ()
		{
			--data;

			if ( index != npos )
			{
				--index;
			}

			return *this;
		}

		iterator<T> operator + ( long long value )
		{
			iterator<T> it( data + value, ( index != npos ? index + value : index ) );
			return it;
		}

		iterator<T> operator - ( long long value )
		{
			iterator<T> it( data - value, ( index != npos ? index - value : index ) );
			return it;
		}

		iterator<T> operator += ( long long value )
		{
			data += value;

			if ( index != npos )
			{
				index += value;
			}

			return *this;
		}

		iterator<T> operator -= ( long long value )
		{
			data -= value;

			if ( index != npos )
			{
				index -= value;
			}

			return *this;
		}

		T& operator * ()
		{
			return *data;
		}

		size_t operator ~ ()
		{
			return index;
		}

		bool operator == ( iterator<T> it )
		{
			return data == it.data && index == it.index;
		}

		bool operator != ( iterator<T> it )
		{
			return data != it.data && index != it.index;
		}

		bool operator > ( iterator<T> it )
		{
			return data > it.data && index > it.index;
		}

		bool operator < ( iterator<T> it )
		{
			return data < it.data&& index < it.index;
		}

		bool operator >= ( iterator<T> it )
		{
			return data >= it.data && index >= it.index;
		}

		bool operator <= ( iterator<T> it )
		{
			return data <= it.data && index <= it.index;
		}
	};
}