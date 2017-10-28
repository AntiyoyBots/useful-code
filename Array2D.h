#include "Exceptions.h"

namespace Game
{
	template<class T, const int H, const int W>
	class Array2D
	{
	private:
		T Arr[H, W];

	public:					 
		class Const_Iterator
		{
		private:
			int X;
			int Y;
			T** Array;

		public:
			Const_Iterator()
				: X(0)
				, Y(0)
				, Arr(nullptr)
			{}

			Const_Iterator(const int x, const int y, const T** arr)
				: X(x)
				, Y(y)
				, Array(arr)
			{}

			Const_Iterator(const Const_Iterator& iterator)
				: X(iterator.X)
				, Y(iterator.Y)
				, Arr(iterator.Array)
			{}

			Const_Iterator& operator=(const Const_Iterator& iterator)
			{
				if(this != &iterator)
				{
					X = iterator.X;
					Y = iterator.Y;
					Array = iterator.Array;
				}
				return *this;
			}

			const T* operator->() const
			{
				if(X >= W || X <= 0 || Y >= H || Y <= 0 || Array == nullptr)
					throw IteratorNotDereferenceable();
				return &(Array[Y, X]);
			}

			const T& operator*() const
			{
				if(X >= W || X <= 0 || Y >= H || Y <= 0 || Array == nullptr)
					throw IteratorNotDereferenceable();
				return Array[Y, X];
			}

			Const_Iterator& operator++()
			{
				if(X >= W && Y >= H)
					throw IteratorNotIncrementable();
				++X;
				if(X >= W)
				{
					Y += X / W;
					X %= W;
				}
			}

			Const_Iterator operator++(int)
			{
				Const_Iterator tmp(*this);
				operator++();
				return tmp;
			}

			Const_Iterator& operator--()
			{
				if(X <= 0 && Y <= 0)
					throw IteratorNotDecrementable();
				--X;
				if(X <= 0)
				{
					Y += X / W;
					X %= W;
				}
			}

			Const_Iterator operator--(int)
			{
				Const_Iterator tmp(*this);
				operator--();
				return tmp;
			}

			Const_Iterator left()
			{
				if(X <= 0)
					throw IteratorNotDecrementable();
				Const_Iterator tmp(*this);
				--X;
				return
			}

			Const_Iterator right()
			{
				if(X >= W)
					throw IteratorNotIncrementable();
				Const_Iterator tmp(*this);
				++X;
				return
			}

			Const_Iterator up()
			{
				if(Y <= 0)
					throw IteratorNotDecrementable();
				Const_Iterator tmp(*this);
				--Y;
				return
			}

			Const_Iterator down()
			{
				if(Y >= H)
					throw IteratorNotIncrementable();
				Const_Iterator tmp(*this);
				++Y;
				return
			}

			bool operator==(const Const_Iterator& iterator) const
			{
				return Array == iterator.Array && X == iterator.X && Y == iterator.Y;
			}

			bool operator!=(const Const_Iterator& iterator) const
			{
				return !(*this == iterator);
			}

			friend class Array2D<T, H, W>;
		};

		class Iterator
			: public Const_Iterator
		{
		public:
			Iterator()
				: Const_Iterator()
			{}

			Iterator(const int x, const int y, const T** arr)
				: Const_Iterator(x, y, arr)
			{}

			Iterator(const Iterator& iterator)
				: Const_Iterator(iterator)
			{}

			Iterator& operator=(const Iterator& iterator)
			{
				if(this != &iterator)
				{
					X = iterator.X;
					Y = iterator.Y;
					Array = iterator.Array;
				}
				return *this;
			}

			Iterator& operator++()
			{
				if(X >= W && Y >= H)
					throw IteratorNotIncrementable();
				++X;
				if(X >= W)
				{
					Y += X / W;
					X %= W;
				}
			}

			Iterator operator++(int)
			{
				Iterator tmp(*this);
				operator++();
				return tmp;
			}

			Iterator& operator--()
			{
				if(X <= 0 && Y <= 0)
					throw IteratorNotDecrementable();
				--X;
				if(X <= 0)
				{
					Y += X / W;
					X %= W;
				}
			}

			Iterator operator--(int)
			{
				Iterator tmp(*this);
				operator--();
				return tmp;
			}

			Iterator left()
			{
				if(X <= 0)
					throw IteratorNotDecrementable();
				Iterator tmp(*this);
				--X;
				return
			}

			Iterator right()
			{
				if(X >= W)
					throw IteratorNotIncrementable();
				Iterator tmp(*this);
				++X;
				return
			}

			Iterator up()
			{
				if(Y <= 0)
					throw IteratorNotDecrementable();
				Iterator tmp(*this);
				--Y;
				return
			}

			Iterator down()
			{
				if(Y >= H)
					throw IteratorNotIncrementable();
				Iterator tmp(*this);
				++Y;
				return
			}
		};

		Array2D()
			: Arr()
		{}

		Array2D(const std::initializer_list<T>& list)
			: Array2D()
		{
			int size = H * W;
			int i = 0;
			for(T& elem : list)
			{
				Arr[i / W, i % W] = elem;
				++i;
				if(i >= size)
					break;
			}
			for(; i < size; ++i)
				Arr[i / W, i % W] = T();		      
		}

		~Array2D() = default;

		Iterator begin()
		{
			return Iterator(0, 0, Arr);
		}

		Iterator begin() const
		{
			return Iterator(0, 0, Arr);
		}

		Iterator end()
		{
			return Iterator(H, W + 1, Arr);
		}

		Iterator end() const
		{
			return Iterator(H, W + 1, Arr);
		}

		const T& front() const
		{
			return Arr[0, 0];
		}

		T& front()
		{
			return Arr[0, 0];
		}

		const T& back() const
		{
			return Arr[H - 1, W - 1];
		}

		T& back()
		{
			return Arr[H - 1, W - 1];
		}

		const T& operator[](const int x, const int y) const
		{
			return Arr[y, x];
		}

		T& operator[](const int x, const int y)
		{
			return Arr[y, x];
		}

		const T& at(const int x, const int y) const
		{
			if(x < 0 || x >= W || y < 0 || y > H)
				return Arr[y, x];
			else throw IndexOutOfBounds();
		}

		T& at(const int x, const int y)
		{
			if(x < 0 || x >= W || y < 0 || y > H)
				return Arr[y, x];
			else throw IndexOutOfBounds();
		}

		Iterator get_iter(const int x, const int y)
		{
			return Iterator(x, y, Arr);
		}

		Iterator get_iter(const int x, const int y) const
		{
			return Iterator(x, y, Arr);
		}

		Const_Iterator get_citer(const int x, const int y) const
		{
			return Const_Iterator(x, y, Arr);
		}
	};
}
