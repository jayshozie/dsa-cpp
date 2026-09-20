// dsa-cpp - an implementation of some data structures and algorithms in C++.
// Copyright (C)  2026  Emir Baha Yıldırım <jayshozie@gmail.com>
//
// this program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// this program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// you should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
module;

#include <cstddef>
#include <iterator>
#include <utility>
export module dsa.linear.CircularSinglyLinkedList;

export namespace dsa
{

template <typename T>
class CircularSinglyLinkedList {
private:
	struct Node {
		T data;
		Node *next{nullptr};

		Node(const T &value, Node *next) : data(value), next(next)
		{}
		Node(T &&value, Node *next) : data(std::move(value)), next(next)
		{}

		template <typename... Args>
		Node(Node *next, Args &&...args) :
			data(std::forward<Args>(args)...),
			next(next)
		{}
	};

	struct Iterator {
		Node *start_node; // i don't think c++ would set it itself
		Node *current;

		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T *;
		using reference = T &;

		T &operator*()
		{
			return this->current->data;
		}
		Iterator &operator++()
		{
			if (this->current->next == this->start_node) {
				this->current = nullptr;
			} else {
				this->current = this->current->next;
			}
			return *this;
		}
		friend bool operator==(const Iterator &lhs, const Iterator &rhs)
		{
			return (lhs.current == rhs.current);
		}
		friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
		{
			return (lhs.current != rhs.current);
		}
	};

	Node *tail = nullptr; // head is always tail->next
	std::size_t size = 0;

public:
	CircularSinglyLinkedList() = default;
	~CircularSinglyLinkedList()
	{
		this->clear();
	}
	// copy constructor
	CircularSinglyLinkedList(const CircularSinglyLinkedList &rhs)
	{
		if (rhs.isEmpty()) {
			return;
		}
		Node *rhsCurr = rhs.tail->next;
		Node *newHead = new Node(rhsCurr->data, nullptr);
		Node *curr = newHead;
		rhsCurr = rhsCurr->next;
		while (rhsCurr != rhs.tail->next) {
			Node *newNode = new Node(rhsCurr->data, nullptr);
			curr->next = newNode;
			curr = newNode;
			rhsCurr = rhsCurr->next;
		}
		curr->next = newHead;
		this->tail = curr;
		this->size = rhs.size;
	}
	// copy assignment operator
	CircularSinglyLinkedList &operator=(const CircularSinglyLinkedList &rhs)
	{
		if (this != &rhs) {
			CircularSinglyLinkedList tmp(rhs);
			std::swap(this->tail, tmp.tail);
			std::swap(this->size, tmp.size);
		}
		return *this;
	}
	// move constructor
	CircularSinglyLinkedList(CircularSinglyLinkedList &&rhs) noexcept :
		tail(rhs.tail),
		size(rhs.size)
	{
		rhs.tail = nullptr;
		rhs.size = 0;
	}
	// move assignment operator
	CircularSinglyLinkedList &operator=(CircularSinglyLinkedList &&rhs) noexcept
	{
		if (this != &rhs) {
			this->clear();
			this->tail = rhs.tail;
			this->size = rhs.size;
			rhs.tail = nullptr;
			rhs.size = 0;
		}
		return *this;
	}

	[[nodiscard]] std::size_t getSize() const
	{
		return this->size;
	}
	[[nodiscard]] bool isEmpty() const
	{
		return (this->size == 0);
	}
	T &front()
	{
		if (this->isEmpty()) {
			throw std::out_of_range("List is empty.");
		}
		return (this->tail->next->data);
	}
	const T &front() const
	{
		if (this->isEmpty()) {
			throw std::out_of_range("List is empty.");
		}
		return (this->tail->next->data);
	}
	T &back()
	{
		if (this->isEmpty()) {
			throw std::out_of_range("List is empty.");
		}
		return (this->tail->data);
	}
	const T &back() const
	{
		if (this->isEmpty()) {
			throw std::out_of_range("List is empty.");
		}
		return (this->tail->data);
	}
	void pushFront(const T &value)
	{
		Node *newNode = new Node(value, nullptr);
		if (this->isEmpty()) {
			newNode->next = newNode;
			this->tail = newNode;
		} else {
			newNode->next = this->tail->next;
			this->tail->next = newNode;
		}
		this->size++;
	}
	void pushFront(T &&value)
	{
		Node *newNode = new Node(std::move(value), nullptr);
		if (this->isEmpty()) {
			newNode->next = newNode;
			this->tail = newNode;
		} else {
			newNode->next = this->tail->next;
			this->tail->next = newNode;
		}
		this->size++;
	}
	T popFront()
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Cannot pop from an empty list.");
		}
		Node *oldHead = this->tail->next;
		T tmp = std::move(oldHead->data);
		if (this->size == 1) {
			this->tail = nullptr;
		} else {
			Node *newHead = oldHead->next;
			this->tail->next = newHead;
		}
		delete oldHead;
		this->size--;
		return tmp;
	}

	template <typename... Args>
	void emplaceFront(Args &&...args)
	{
		Node *newNode = new Node(this->tail->next, std::forward<Args>(args)...);
		if (this->isEmpty()) {
			newNode->next = newNode;
			this->tail = newNode;
		} else {
			newNode->next = this->tail->next;
			this->tail->next = newNode;
		}
		this->size++;
	}

	void clear()
	{
		if (this->tail) {
			Node *curr = this->tail->next;
			this->tail->next = nullptr; // so that we don't fall into an inf
										// loop
			while (curr != nullptr) {
				Node *next = curr->next;
				delete curr;
				curr = next;
			}
			this->tail = nullptr;
			this->size = 0;
		}
	}

	Iterator begin()
	{
		return Iterator{this->tail->next, this->tail->next};
	}
	Iterator end()
	{
		return Iterator{nullptr};
	}
};
} // namespace dsa
