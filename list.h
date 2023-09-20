#pragma once 

namespace abn
{
	template <class T>
	class list_node
	{
	public:

		T data{};
		list_node* next;
		list_node* previous;

		list_node() {}
		list_node( T& data )
		{
			this->data = data;
		}

		list_node<T> operator ++ ()
		{
			return *( this = this->next );
		}

		list_node<T> operator -- ()
		{
			return *( this = this->previous );
		}

		bool operator != ( list_node<T> _node )
		{
			return
			(
				this->data != _node.data
				&& this->next != _node.next
				&& this->previous != _node.previous
			);
		}

		bool operator == ( list_node<T> _node )
		{
			return
			(
				this->data == _node.data
				&& this->next == _node.next
				&& this->previous == _node.previous
			);
		}
	};

	template <class T>
	class list
	{
	private:

		list_node<T>* head{ new list_node<T>() };
		list_node<T>* tail{ nullptr };
		list_node<T>* working_node{ head };
		size_t count{};

	public:

		void clear()
		{
			while ( head )
			{
				working_node = head->next;
				delete head;
				head = working_node;
			}

			count = 0;
			tail = nullptr;
		}

		void push_front( T data )
		{
			head->previous = new list_node<T>( data );
			head->previous->next = head;
			head = head->previous;
			++count;
		}

		void push_back( T data )
		{
			tail->next = new list_node<T>( data );
			tail->next->previous = tail;
			tail = tail->next;
			++count;
		}

		void pop_front()
		{
			working_node = head;
			head = head->next;
			head->previous = nullptr;
			delete working_node;
			--count;
		}

		void pop_back()
		{
			working_node = tail;
			tail->previous->next = nullptr;
			tail = tail->previous;
			delete working_node;
			--count;
		}

		void erase( size_t index )
		{
			if ( index == 0 )
			{
				return pop_front();
			}

			if ( index == count - 1 )
			{
				return pop_back();
			}

			working_node = head;

			for ( size_t i = 0; i < index; i++ )
			{
				working_node = working_node->next;
			}

			working_node->previous->next = working_node->next;
			working_node->next->previous = working_node->previous;
			delete working_node;
			--count;
		}

		size_t size()
		{
			return count;
		}

		list_node<T> begin() const
		{
			return *head;
		}

		list_node<T> end() const
		{
			return *tail;
		}

		template <class Ty = bool( * )( list_node<T>* )>
		void for_each( Ty callback )
		{
			working_node = head;

			while ( working_node )
			{
				if ( callback( working_node ) == true )
				{
					return;
				}

				working_node = working_node->next;
			}
		}

		template <typename... args> 
		void initialize( T value )
		{
			working_node->data = value;
			working_node->previous = tail;
			tail = working_node;
			++count;
		}

		template<typename... args> 
		void initialize( T value, args... data )
		{
			working_node->data = value;
			working_node->previous = tail;
			tail = working_node;
			working_node->next = new list_node<T>();
			working_node = working_node->next;
			++count;
			initialize( data... );
		}

		template<typename... args>
		list( T value, args... data )
		{
			initialize( value, data... );
		}

		list() = default;

		~list()
		{
			clear();
		}
	};
}