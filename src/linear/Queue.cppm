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
#include <utility>
export module dsa.linear.Queue;
import dsa.linear.LinkedList;

export namespace dsa
{

template <typename T>
class Queue {
private:
	dsa::LinkedList<T> items;

public:
	Queue() = default;
	~Queue() = default;
	Queue(const Queue &) = default;
	Queue &operator=(const Queue &) = default;
	Queue(Queue &&) noexcept = default;
	Queue &operator=(Queue &&) noexcept = default;

	void push(const T &value)
	{
		this->items.pushBack(value);
	}
	void push(T &&value)
	{
		this->items.pushBack(std::move(value));
	}
	T pop()
	{
		return this->items.popFront();
	}
	template <typename... Args>
	void emplace(Args &&...args)
	{
		this->items.emplaceBack(std::forward<Args>(args)...);
	}

	[[nodiscard]] std::size_t getSize() const
	{
		return this->items.getSize();
	}
	[[nodiscard]] bool isEmpty() const
	{
		return (this->items.getSize() == 0);
	}

	void clear()
	{
		this->items.clear();
	}
	T &front()
	{
		return this->items.front();
	}
	const T &front() const
	{
		return this->items.front();
	}
	T &back()
	{
		return this->items.back();
	}
	const T &back() const
	{
		return this->items.back();
	}
};
} // namespace dsa
