// dsa-cpp - an implementation of some data structures and algorithms in C++.
// Copyright (C)  2026  Emir Baha Yıldırım <jayshozie@gmail.com>
// Copyright (C)  2026  terra2o <terra2o@protonmail.com>
//
// This program is free software: you can redistribute it and/or modify
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

#include <compare>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

export module dsa.linear.CircularDoublyLinkedList;

export namespace dsa
{

template <typename T>
class CircularDoublyLinkedList {
private:
	struct NodeBase {
		NodeBase *prev{this};
		NodeBase *next{this};
	};
	struct Node : public NodeBase {
		T data;

		template <typename... Args>
		Node(Args &&...args) : data(std::forward<Args>(args)...)
		{}
	};

	template <bool IsConst>
	class IteratorImpl {
	private:
		using NodePtr = std::conditional_t<IsConst, const Node *, Node *>;
		NodePtr current{nullptr};

		template <bool>
		friend class IteratorImpl;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = std::conditional_t<IsConst, const T *, T *>;
		using reference = std::conditional_t<IsConst, const T &, T &>;

		IteratorImpl() = default;

		explicit IteratorImpl(NodePtr node, NodePtr tail = nullptr) :
			current(node)
		{}

		template <bool OtherIsConst>
			requires(IsConst && !OtherIsConst)
		IteratorImpl(const IteratorImpl<OtherIsConst> &other) :
			current(other.current)
		{}

		reference operator*() const
		{
			auto *dataNode =
				static_cast<std::conditional_t<IsConst, const Node *, Node *>>(
					this->current);
			return dataNode->data;
		}
		pointer operator->() const
		{
			auto *dataNode =
				static_cast<std::conditional_t<IsConst, const Node *, Node *>>(
					this->current);
			return &dataNode->data;
		}

		IteratorImpl &operator++()
		{
			this->current = static_cast<NodePtr>(this->current->next);
			return *this;
		}

		IteratorImpl operator++(int)
		{
			IteratorImpl temp = *this;
			++(*this);
			return temp;
		}

		IteratorImpl &operator--()
		{
			this->current = static_cast<NodePtr>(this->current->prev);
			return *this;
		}

		IteratorImpl operator--(int)
		{
			IteratorImpl temp = *this;
			--(*this);
			return temp;
		}

		[[nodiscard]] friend bool operator==(const IteratorImpl &lhs,
											 const IteratorImpl &rhs) noexcept
		{
			return lhs.current == rhs.current;
		}
	};

	NodeBase dummy;
	std::size_t size{0};

public:
	using Iterator = IteratorImpl<false>;
	using ConstIterator = IteratorImpl<true>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CircularDoublyLinkedList() = default;

	CircularDoublyLinkedList(std::initializer_list<T> list)
	{
		for (const auto &item : list) {
			this->pushBack(item);
		}
	}

	~CircularDoublyLinkedList()
	{
		this->clear();
	}

	// dsa::CircularDoublyLinkedList<int> copyConstructed(orig);
	CircularDoublyLinkedList(const CircularDoublyLinkedList &other)
	{
		this->copyFrom(other);
	}

	CircularDoublyLinkedList &operator=(const CircularDoublyLinkedList &other)
	{
		if (this != &other) {
			CircularDoublyLinkedList temp(other);
			this->swap(temp);
		}
		return *this;
	}

	CircularDoublyLinkedList(CircularDoublyLinkedList &&other) noexcept
	{
		this->swap(other);
	}

	CircularDoublyLinkedList &
		operator=(CircularDoublyLinkedList &&other) noexcept
	{
		CircularDoublyLinkedList temp(std::move(other));
		this->swap(temp);
		return *this;
	}

	[[nodiscard]] auto operator<=>(const CircularDoublyLinkedList &rhs) const
		requires std::three_way_comparable<T>
	{
		auto it1 = this->begin();
		auto it2 = rhs.begin();

		while (it1 != this->end() && it2 != rhs.end()) {
			if (auto cmp = *it1 <=> *it2; cmp != 0) {
				return cmp;
			}
			++it1;
			++it2;
		}

		return this->size <=> rhs.size;
	}

	[[nodiscard]] bool operator==(const CircularDoublyLinkedList &rhs) const
	{
		if (this->size != rhs.size) {
			return false;
		}

		auto it1 = this->begin();
		auto it2 = rhs.begin();

		while (it1 != end()) {
			if (!(*it1 == *it2)) {
				return false;
			}
			++it1;
			++it2;
		}

		return true;
	}

	void swap(CircularDoublyLinkedList &other) noexcept
	{
		std::swap(this->dummy.next, other.dummy.next);
		std::swap(this->dummy.prev, other.dummy.prev);
		std::swap(this->size, other.size);

		if (this->size == 0) {
			this->dummy.prev = &this->dummy;
			this->dummy.next = &this->dummy;
		} else {
			this->dummy.prev->next = &this->dummy;
			this->dummy.next->prev = &this->dummy;
		}

		if (other.size == 0) {
			other.dummy.prev = &other.dummy;
			other.dummy.next = &other.dummy;
		} else {
			other.dummy.prev->next = &other.dummy;
			other.dummy.next->prev = &other.dummy;
		}
	}

	T &front()
	{
		Node *head = static_cast<Node *>(this->dummy.next);
		return head->data;
	}
	const T &front() const
	{
		Node *head = static_cast<Node *>(this->dummy.next);
		return head->data;
	}

	T &back()
	{
		Node *tail = static_cast<Node *>(this->dummy.prev);
		return tail->data;
	}
	const T &back() const
	{
		Node *tail = static_cast<Node *>(this->dummy.prev);
		return tail->data;
	}

	template <typename... Args>
	T &emplaceFront(Args &&...args)
	{
		Node *newNode = new Node(std::forward<Args>(args)...);
		NodeBase *left = &this->dummy;
		NodeBase *right = this->dummy.next;
		newNode->prev = left;
		newNode->next = right;
		left->next = newNode;
		right->prev = newNode;
		this->size++;
		return newNode->data;
	}

	template <typename... Args>
	T &emplaceBack(Args &&...args)
	{
		Node *newNode = new Node(std::forward<Args>(args)...);
		NodeBase *left = this->dummy.prev;
		NodeBase *right = &this->dummy;
		newNode->prev = left;
		newNode->next = right;
		left->next = newNode;
		right->prev = newNode;
		this->size++;
		return newNode->data;
	}

	void pushFront(const T &value)
	{
		this->emplaceFront(value);
	}
	void pushFront(T &&value)
	{
		this->emplaceFront(std::move(value));
	}

	void pushBack(const T &value)
	{
		this->emplaceBack(value);
	}
	void pushBack(T &&value)
	{
		this->emplaceBack(std::move(value));
	}

	T popFront()
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Cannot pop from an empty list.");
		}
		NodeBase *target = this->dummy.next;
		NodeBase *left = target->prev;
		NodeBase *right = target->next;
		left->next = right;
		right->prev = left;
		Node *dataNode = static_cast<Node *>(target);
		T result = std::move(dataNode->data);
		delete dataNode;
		this->size--;
		return result;
	}

	T popBack()
	{
		if (this->isEmpty()) {
			throw std::underflow_error("Cannot pop from an empty list.");
		}
		NodeBase *target = this->dummy.prev;
		NodeBase *left = target->prev;
		NodeBase *right = target->next;
		left->next = right;
		right->prev = left;
		Node *dataNode = static_cast<Node *>(target);
		T result = std::move(dataNode->data);
		delete dataNode;
		this->size--;
		return result;
	}

	void clear()
	{
		if (this->isEmpty()) {
			return;
		}
		NodeBase *curr = this->dummy.next;
		while (curr != &this->dummy) {
			NodeBase *next = curr->next;
			Node *target = static_cast<Node *>(curr);
			delete target;
			curr = next;
		}
		this->dummy.prev = &this->dummy;
		this->dummy.next = &this->dummy;
		this->size = 0;
	}

	[[nodiscard]] std::size_t getSize() const noexcept
	{
		return this->size;
	}
	[[nodiscard]] bool isEmpty() const noexcept
	{
		return (this->size == 0);
	}

	Iterator begin()
	{
		return Iterator{static_cast<Node *>(this->dummy.next)};
	}
	Iterator end()
	{
		return Iterator{static_cast<Node *>(&this->dummy)};
	}

	ConstIterator begin() const
	{
		return ConstIterator{static_cast<const Node *>(this->dummy.next)};
	}
	ConstIterator end() const
	{
		return ConstIterator{static_cast<const Node *>(&this->dummy)};
	}

	ConstIterator cbegin() const
	{
		return ConstIterator{static_cast<const Node *>(this->dummy.next)};
	}
	ConstIterator cend() const
	{
		return ConstIterator{static_cast<const Node *>(&this->dummy)};
	}

	ReverseIterator rbegin()
	{
		return ReverseIterator(this->end());
	}
	ReverseIterator rend()
	{
		return ReverseIterator(this->begin());
	}

	ConstReverseIterator rbegin() const
	{
		return ConstReverseIterator(this->cend());
	}
	ConstReverseIterator rend() const
	{
		return ConstReverseIterator(this->cbegin());
	}

	ConstReverseIterator crbegin() const
	{
		return ConstReverseIterator(this->cend());
	}
	ConstReverseIterator crend() const
	{
		return ConstReverseIterator(this->cbegin());
	}

private:
	void copyFrom(const CircularDoublyLinkedList &rhs)
	{
		try {
			for (const auto &data : rhs) {
				this->emplaceBack(data);
			}
		} catch (...) {
			this->clear();
			throw;
		}
	}
};
} // namespace dsa
