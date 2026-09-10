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
#include <utility>

export module dsa.linear.ArrayStack;
import dsa.linear.DynamicArray;

export namespace dsa
{

template <typename T>
class ArrayStack {
private:
	dsa::DynamicArray<T> container;

public:
    ArrayStack() = default;
    ~ArrayStack() = default;

    ArrayStack(const ArrayStack &rhs) = default;
    ArrayStack &operator=(const ArrayStack &rhs) = default;

    ArrayStack(ArrayStack &&rhs) noexcept = default;
    ArrayStack &operator=(ArrayStack &&rhs) noexcept = default;

    void push(T value)
    {
        this->container.pushBack(std::move(value));
    }

    T pop()
    {
        if (this->isEmpty()) {
            throw std::underflow_error("Cannot pop from an empty stack.");
        }
        return this->container.popBack();
    }

    [[nodiscard]] T &top()
    {
        if (this->isEmpty()) {
            throw std::out_of_range("Stack is empty.");
        }
        return this->container.back();
    }

    [[nodiscard]] const T &top() const
    {
        if (this->isEmpty()) {
            throw std::out_of_range("Stack is empty.");
        }
        return this->container.back();
    }

    [[nodiscard]] std::size_t getSize() const
    {
        return this->container.getLength();
    }

    [[nodiscard]] bool isEmpty() const
    {
        return this->container.isEmpty();
    }

    void clear()
    {
        this->container.clear();
    }
};
} // namespace dsa
