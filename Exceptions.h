#include <exception>

namespace Game
{
	class IteratorNotDereferenceable
		: public std::exception
	{};

	class IteratorNotDecrementable
		: public std::exception
	{};

	class IteratorNotIncrementable
		: public std::exception
	{};

	class IndexOutOfBounds
		: public std::exception
	{};
}
