// dsa-cpp - An implementation of some data structures and algorithms in C++.
// Copyright (C)  2026  Emir Baha Yıldırım <jayshozie@gmail.com>
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
#include <stdexcept>
export module dsa.linear.StaticArray;

export namespace dsa
{

template <typename T, std::size_t Capacity>
class StaticArray {
private:
	T items[Capacity]{};

public:
	// Compile-Time Sized Fixed Array
	StaticArray() = default;

	T &at(std::size_t index)
	{
		if (index >= Capacity) {
			throw std::out_of_range("Index out of range.");
		}
		return this->items[index];
	}
	const T &at(std::size_t index) const
	{
		if (index >= Capacity) {
			throw std::out_of_range("Index out of range.");
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
		return this->items[Capacity - 1];
	}
	const T &back() const
	{
		return this->items[Capacity - 1];
	}

	T *data()
	{
		return this->items;
	}
	const T *data() const
	{
		return this->items;
	}

	[[nodiscard]] constexpr std::size_t getSize() const
	{
		return Capacity;
	}
	[[nodiscard]] constexpr bool isEmpty() const
	{
		return (Capacity == 0);
	}
	void fill(const T &value)
	{
		for (std::size_t i = 0; i < Capacity; i++) {
			this->items[i] = value;
		}
	}

	// iterators
	T *begin()
	{
		return this->items;
	}
	const T *begin() const
	{
		return this->items;
	}
	T *end()
	{
		return (this->items + Capacity);
	}
	const T *end() const
	{
		return (this->items + Capacity);
	}
};
}; // namespace dsa
