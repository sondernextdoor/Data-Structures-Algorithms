#include "vector.h"
#include "list.h"
#include <iostream>
#include <iostream>

int main()
{
	abn::vector<int> v( 1, 2, 3, 4, 5, 6, 7, 8, 9 );
	auto pos{ v.search( v.begin(), v.end(), 5 ) };

	std::cout << "Value: " << *pos << std::endl;
	std::cout << "Index: " << ~pos << std::endl;

	//for ( int i = 0; i < n; i++ )
	//{
		//std::cout << v[i] << std::endl;
	//}
	/*

	abn::list<int> linked_list( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 );
	//linked_list.push_back( 11 );
	//linked_list.push_front( 0 );
	linked_list.erase( 0 );

	linked_list.for_each
	( 
		[] ( abn::list_node<int>* node ) -> bool 
		{
			std::cout << node->data << std::endl;
			return false;
		} 
	);*/
}