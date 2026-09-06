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

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
export module dsa.linear.RTFixedArray;

export namespace dsa
{
template <typename T>
class RTFixedArray {
private:
	std::unique_ptr<T[]> items;
	std::size_t capacity;

public:
	// Runtime Sized Fixed Array
	RTFixedArray(std::size_t capacity) :
		capacity(capacity),
		items(std::make_unique<T[]>(capacity))
	{}
	~RTFixedArray() = default;

	// copy constructor: needed because of smart pointers
	RTFixedArray(const RTFixedArray &rhs) :
		capacity(rhs.capacity),
		items(std::make_unique<T[]>(rhs.capacity))
	{
		for (std::size_t i = 0; i < this->capacity; i++) {
			this->items[i] = rhs.items[i];
		}
	}

	// copy assignment operator: needed because of smart pointers
	RTFixedArray &operator=(const RTFixedArray &rhs)
	{
		if (this == &rhs) { // self-assignment
			return *this;
		}
		RTFixedArray tmp(rhs);
		std::swap(this->capacity, tmp.capacity);
		std::swap(this->items, tmp.items);
		return *this;
	}

	// move constructor
	RTFixedArray(RTFixedArray &&rhs) noexcept :
		capacity(std::exchange(rhs.capacity, 0)),
		items(std::move(rhs.items))
	{}

	// move assignment operator
	RTFixedArray &operator=(RTFixedArray &&rhs) noexcept
	{
		if (this == &rhs) { // self-assignment
			return *this;
		}
		std::swap(this->capacity, rhs.capacity);
		std::swap(this->items, rhs.items);
		return *this;
	}

	T &at(std::size_t index)
	{
		if (index >= this->capacity) {
			throw std::out_of_range("Index out of range");
		}
		return this->items[index];
	}
	const T &at(std::size_t index) const
	{
		if (index >= this->capacity) {
			throw std::out_of_range("Index out of range");
		}
		return this->items[index];
	}

	T &operator[](std::size_t index)
	{
		return this->items[index];
	}
	const T &operator[](std::size_t index) const
	{
		return this->items[index];
	}

	T &front()
	{
		return this->items[0];
	}
	const T &front() const
	{
		return this->items[0];
	}
	T &back()
	{
		return this->items[this->capacity - 1];
	}
	const T &back() const
	{
		return this->items[this->capacity - 1];
	}

	T *data()
	{
		return (this->items.get());
	}
	const T *data() const
	{
		return (this->items.get());
	}

	[[nodiscard]] std::size_t getSize() const
	{
		return this->capacity;
	}
	[[nodiscard]] bool isEmpty() const
	{
		return (this->capacity == 0);
	}
	void fill(const T &value)
	{
		for (std::size_t i = 0; i < this->capacity; i++) {
			this->items[i] = value;
		}
	}

	// iterators
	T *begin()
	{
		return (this->items.get());
	}
	const T *begin() const
	{
		return (this->items.get());
	}
	T *end()
	{
		return (this->items.get() + this->capacity);
	}
	const T *end() const
	{
		return (this->items.get() + this->capacity);
	}
};
}; // namespace dsa
