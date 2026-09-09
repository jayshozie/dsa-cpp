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
#include <stdexcept>
#include <utility>
export module dsa.linear.SinglyLinkedList;

export namespace dsa
{

template <typename T>
class SinglyLinkedList {
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
			this->current = this->current->next;
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

	Node *head = nullptr;
	std::size_t size = 0;

public:
	// default constructor
	SinglyLinkedList() = default;
	// default destructor
	~SinglyLinkedList()
	{
		this->clear();
	}
	// SinglyLinkedList(std::initializer_list<T> list)
	// {
	// 	// we need to reverse
	// 	for (auto val : list) {
	// 		this->pushFront(val);
	// 	}
	// }
	// copy constructor
	SinglyLinkedList(const SinglyLinkedList &rhs)
	{
		if (rhs.head == nullptr) {
			return;
		}
		this->head = new Node(rhs.head->data, nullptr);
		Node *curr = this->head;
		Node *next = rhs.head->next;
		while (next != nullptr) {
			Node *newNode = new Node(next->data, nullptr);
			curr->next = newNode;
			curr = newNode;
			next = next->next;
		}
		this->size = rhs.size;
	}
	// copy assignment operator
	SinglyLinkedList &operator=(const SinglyLinkedList &rhs)
	{
		if (this != &rhs) {
			SinglyLinkedList tmp(rhs);
			std::swap(this->head, tmp.head);
			std::swap(this->size, tmp.size);
		}
		return *this;
	}
	// move constructor
	SinglyLinkedList(SinglyLinkedList &&rhs) noexcept
	{
		this->head = rhs.head;
		rhs.head = nullptr;
		this->size = rhs.size;
		rhs.size = 0;
	}
	// move assignment operator
	SinglyLinkedList &operator=(SinglyLinkedList &&rhs) noexcept
	{
		if (this != &rhs) {
			this->clear();
			this->head = rhs.head;
			this->size = rhs.size;
			rhs.head = nullptr;
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
		return this->head->data;
	}
	const T &front() const
	{
		if (this->isEmpty()) {
			throw std::out_of_range("List is empty.");
		}
		return this->head->data;
	}

	void pushFront(const T &value)
	{
		Node *newNode = new Node(value, this->head);
		this->head = newNode;
		this->size++;
	}
	void pushFront(T &&value)
	{
		Node *newNode = new Node(std::move(value), this->head);
		this->head = newNode;
		this->size++;
	}
	T popFront()
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Cannot pop from an empty list.");
		}
		T tmp = std::move(this->head->data);
		Node *oldHead = this->head;
		Node *newHead = oldHead->next;
		this->head = newHead;
		delete oldHead;
		this->size--;
		return tmp;
	}
	template <typename... Args>
	void emplaceFront(Args &&...args)
	{
		Node *newNode = new Node(this->head, std::forward<Args>(args)...);
		this->head = newNode;
		this->size++;
	}

	void clear()
	{
		Node *curr = this->head;
		while (curr != nullptr) {
			Node *next = curr->next;
			delete curr;
			curr = next;
		}
		this->head = nullptr;
		this->size = 0;
	}

	Iterator begin()
	{
		return Iterator{head};
	}
	Iterator end()
	{
		return Iterator{nullptr};
	}
};
} // namespace dsa
