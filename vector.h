#pragma once
#include "memory_manager.h"

namespace abn
{
	template<class T>
	class vector
	{
	private:

		memory_manager<T>* _memory_manager{ new memory_manager<T>() };

	public:

		static constexpr size_t npos{ static_cast<size_t>( -1 ) };

		T& at( size_t index ) const
		{
			return _memory_manager->memory[index];
		}

		void push_back( T value ) const
		{
			_memory_manager->grow() = value;
		}

		void pop_back() const
		{
			_memory_manager->shrink();
		}

		void insert( size_t index, T value )
		{
			size_t n{ size() };

			if ( index == n )
			{
				return;
			}

			if ( index == n - 1 )
			{
				push_back( value );
				return;
			}

			_memory_manager->grow();

			for ( ; n > index; --n )
			{
				at( n ) = at( n - 1 );
			}

			at( n ) = value;
		}

		void assign( size_t index, T value ) const
		{
			at( index ) = value;
		}

		void resize( size_t new_size ) const
		{
			if ( new_size == _memory_manager->size )
			{
				return;
			}

			while ( _memory_manager->size != new_size )
			{
				if ( new_size < _memory_manager->size )
				{
					_memory_manager->shrink();
				}
				else
				{
					_memory_manager->grow();
				}
			}
		}

		void erase( iterator<T> it )
		{
			while ( it != _memory_manager->end )
			{
				auto& value{ *it };
				++it;
				value = *it;
			}

			_memory_manager->shrink();
		}

		void erase( size_t index )
		{
			if ( index >= _memory_manager->size )
			{
				return;
			}

			while ( index + 1 != _memory_manager->size )
			{
				_memory_manager->memory[index] = _memory_manager->memory[index + 1];
				++index;
			}

			--_memory_manager->size;
			_memory_manager->in_use -= _memory_manager->type_size;
		}

		void erase( size_t index, size_t last_index )
		{
			if ( index >= _memory_manager->size
				|| last_index >= _memory_manager->size
				|| last_index < index )
			{
				return;
			}

			if ( index == 0 && last_index == _memory_manager->size - 1 )
			{
				clear();
				return;
			}

			while ( last_index + 1 != _memory_manager->size )
			{
				_memory_manager->memory[index] = _memory_manager->memory[last_index + 1];
				++index;
				++last_index;
			}

			--_memory_manager->size -= last_index - index;
			_memory_manager->in_use = _memory_manager->type_size * _memory_manager->size;
		}

		iterator<T> search( iterator<T> first, iterator<T> last, T value )
		{
			size_t left{ ~first };
			size_t right{ last == _memory_manager->end ? _memory_manager->size - 1 : ~last };

			if ( *first == value )
			{
				return first;
			}

			if ( last != _memory_manager->end && *last == value)
			{
				return last;
			}

			while ( left != right )
			{
				size_t mid{ ( left + right ) / 2 };
				T& mid_value{ _memory_manager->memory[mid] };

				if ( mid_value == value )
				{
					return iterator<T>( &mid_value, mid );
				}

				if ( mid_value > value )
				{
					right = mid - 1;
				}
				else
				{
					left = mid + 1;
				}
			}

			return _memory_manager->end;
		}

		void clear() const
		{
			_memory_manager->free();
		}

		T* data() const
		{
			return _memory_manager->memory;
		}

		size_t size() const
		{
			return _memory_manager->size;
		}

		size_t capacity() const
		{
			return _memory_manager->capacity;
		}

		bool empty() const
		{
			return _memory_manager->in_use == 0;
		}

		T& front() const
		{
			return _memory_manager->memory[0];
		}

		T& back() const
		{
			return _memory_manager->memory[size() - 1];
		}

		iterator<T> begin() const
		{
			return _memory_manager->begin;
		}

		iterator<T> end() const
		{
			return _memory_manager->end;
		}

		T& operator [] ( size_t index )
		{
			return _memory_manager->memory[index];
		}

		vector<T>& operator = ( const vector<T>& v )
		{
			clear();

			for ( T& val : v )
			{
				push_back( val );
			}

			return *this;
		}

		template <typename... args> 
		void initialize( T value ) 
		{ 
			_memory_manager->grow() = value; 
		}

		template<typename... args> 
		void initialize( T value, args... data )
		{
			_memory_manager->grow() = value;
			initialize( data... );
		}

		template<typename... args> 
		vector( T value, args... data )
		{
			initialize( value, data... );
		}

		vector() = default;

		~vector()
		{
			delete _memory_manager;
		}
	};
}