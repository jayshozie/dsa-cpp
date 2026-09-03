// dsa-cpp - An implementation of some data structures and algorithms in C++.
// Copyright (C)  2026  Emir Baha YILDIRIM <jayshozie@gmail.com>
// Copyright (C)  2026  terra2o <terra2o@protonmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
module;

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <utility>

export module dsa.linear.DynamicArray;

export namespace dsa
{
#define NOT_ENOUGH_SPACE ((this->count) == (this->capacity))
#define TOO_MUCH_SPACE ((this->count) < ((this->capacity) / 4))
template <typename T>
class DynamicArray {
private:
	// T *items;
	std::size_t count = 0;
	std::size_t capacity = 1;
	std::unique_ptr<T[]> items = std::make_unique<T[]>(1);

	void reallocate(size_t capacity)
	{
		std::unique_ptr<T[]> items = std::make_unique<T[]>(capacity);
		for (size_t i = 0; i < this->count; i++) {
			items[i] = std::move(this->items[i]);
		}
		this->items = std::move(items);
		this->capacity = capacity;
	}
	void grow()
	{
		std::size_t new_capacity = 0;
		if (this->capacity == 1) {
			new_capacity = 2;
		} else {
			new_capacity = this->capacity + (this->capacity >> 1);
		}
		this->reallocate(new_capacity);
	}
	void shrink()
	{
		if (this->capacity < 2) {
			return;
		}
		std::size_t new_capacity = (this->capacity >> 1);
		this->reallocate(new_capacity);
	}

public:
	// default constructor
	DynamicArray() = default;

	// destructor
	~DynamicArray() = default;

	// copy constructor
	DynamicArray(const DynamicArray &rhs) :
		count(rhs.count),
		capacity(rhs.capacity),
		items(std::make_unique<T[]>(rhs.capacity))
	{ // wip
		for (size_t i = 0; i < rhs.count; i++) {
			this->items[i] = rhs.items[i];
		}
	}

	// copy assignment operator
	DynamicArray &operator=(const DynamicArray &rhs)
	{
		if (this == &rhs) { // self-assignment
			return *this;
		}
		std::unique_ptr<T[]> tmp = std::make_unique<T[]>(rhs.capacity);
		for (size_t i = 0; i < rhs.count; i++) {
			tmp[i] = rhs.items[i];
		}
		this->count = rhs.count;
		this->capacity = rhs.capacity;
		std::swap(this->items, tmp);
		return *this;
	}

	// move constructor
	DynamicArray(DynamicArray &&rhs) noexcept = default;

	// move assignment operator
	DynamicArray &operator=(DynamicArray &&rhs) noexcept = default;

	// getters
	size_t getLength()
	{
		return this->count;
	}
	size_t getCapacity()
	{
		return this->capacity;
	}
	bool isEmpty()
	{
		return (this->count == 0);
	}
	T &get(std::size_t index)
	{
		if (index < this->count) {
			return this->items[index];
		}
		throw std::out_of_range("Index out of bounds.");
	}

	void pushBack(T value)
	{
		if (this->capacity == this->count) {
			this->grow();
		}
		this->items[this->count++] = std::move(value);
	}
	T popBack()
	{
		if (this->count == 0) {
			throw std::out_of_range("Cannot pop from an empty array.");
		}
		T return_val = std::move(this->items[this->count - 1]);
		this->items[--this->count] = T{};
		if (TOO_MUCH_SPACE && (this->capacity >= 2)) {
			this->shrink();
		}
		return return_val;
	}

	// void insertAt(T value, std::size_t index)
	// {
	// 	if (NOT_ENOUGH_SPACE) {
	// 		this->grow();
	// 	}
	//
	// }

	/*
	 * public:
	 * -------
	 * getLength() // DONE
	 * getCapacity() // DONE
	 * isEmpty() // DONE
	 * get(index) // DONE
	 * pushBack(value)
	 * popBack()
	 * insertAt(index, value) // may be removed
	 * removeAt(index, value) // may be removed
	 * contains(value)
	 *
	 * private:
	 * --------
	 * grow() // double the capacity
	 * shrink() // halve the capacity
	 */
};
} // namespace dsa
