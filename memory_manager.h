#pragma once
#include "iterator.h"

namespace abn
{
	template<class T>
	class memory_manager
	{
	private:

		bool allocated{ false };

	public:

		T* memory{ nullptr };
		size_t size{ 0 };
		size_t in_use{ 0 };
		size_t capacity{ 0 };
		const size_t type_size{ sizeof( T ) };
		iterator<T> begin{};
		iterator<T> end{};

		T& grow()
		{
			if ( capacity == 0 )
			{
				allocated = true;
				capacity = 1;
				memory = new T[1]{};
				begin = iterator<T>( memory, 0 );
				end = iterator<T>( memory + type_size, -1 );
				in_use += type_size;
				++size;
				return memory[0];
			}

			if ( size == capacity )
			{
				T* new_memory{ new T[capacity * 2] };

				for ( int i = 0; i < capacity; i++ )
				{
					new_memory[i] = memory[i];
				}

				delete[] memory;
				memory = new_memory;
				capacity *= 2;
			}

			in_use += type_size;
			++end;
			return memory[size++];
		}

		void shrink()
		{
			if ( capacity == 0 )
			{
				return;
			}

			in_use -= type_size;
			--size;
			--end;
			return;
		}

		void free()
		{
			if ( allocated == true )
			{
				allocated = false;
				delete[] memory;
			}

			size = 0;
			capacity = 0;
			in_use = 0;
			begin = iterator<T>( nullptr );
			end = begin;
		}

		memory_manager() {}
		~memory_manager()
		{
			free();
		}
	};
}