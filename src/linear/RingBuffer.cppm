// dsa-cpp - An implementation of some data structures and algorithms in C++.
// Copyright (C)  2026  Emir Baha Yıldırım <jayshozie@gmail.com>
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
#include <utility>
export module dsa.linear.RingBuffer;
import dsa.linear.StaticArray;

export namespace dsa
{

template <typename T, std::size_t Capacity>
class RingBuffer {
private:
	static_assert(((Capacity > 0) && ((Capacity & (Capacity - 1)) == 0)),
				  "Ring Buffer capacity must be a power of 2.");
	dsa::StaticArray<T, Capacity> buffer;
	std::size_t head = 0;
	std::size_t tail = 0;

public:
	RingBuffer() = default;
	~RingBuffer() = default;
	RingBuffer(const RingBuffer &) = default;
	RingBuffer &operator=(const RingBuffer &) = default;
	RingBuffer(RingBuffer &&) noexcept = default;
	RingBuffer &operator=(RingBuffer &&) noexcept = default;

	[[nodiscard]] std::size_t getSize() const
	{
		return ((this->tail - this->head) & (Capacity - 1));
	}
	[[nodiscard]] constexpr std::size_t getCapacity() const
	{
		return Capacity;
	}
	[[nodiscard]] bool isEmpty() const
	{
		return (this->tail == this->head);
	}
	[[nodiscard]] bool isFull() const
	{
		return (((this->tail + 1) & (Capacity - 1)) == this->head);
	}

	T &front()
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Ring Buffer is empty.");
		}
		return (this->buffer[this->head]);
	}
	const T &front() const
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Ring Buffer is empty.");
		}
		return (this->buffer[this->head]);
	}
	T &back()
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Ring Buffer is empty.");
		}
		return (this->buffer[(this->tail - 1) & (Capacity - 1)]);
	}
	const T &back() const
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Ring Buffer is empty.");
		}
		return (this->buffer[(this->tail - 1) & (Capacity - 1)]);
	}

	void push(const T &value)
	{
		if (this->isFull()) {
			throw std::overflow_error("Ring Buffer is full.");
		}
		this->buffer[this->tail++] = value;
		this->tail &= (Capacity - 1);
	}
	void push(T &&value)
	{
		if (this->isFull()) {
			throw std::overflow_error("Ring Buffer is full.");
		}
		this->buffer[this->tail++] = std::move(value);
		this->tail &= (Capacity - 1);
	}
	T pop()
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Ring Buffer is empty.");
		}
		T tmp = std::move(this->buffer[this->head++]);
		this->head &= (Capacity - 1);
		return tmp;
	}
	void clear()
	{
		this->head = 0;
		this->tail = 0;
	}
};
} // namespace dsa
