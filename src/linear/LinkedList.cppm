// dsa-cpp - an implementation of some data structures and algorithms in C++.
// copyright (C) 2026 Emir Baha YILDIRIM <jayshozie@gmail.com>
// copyright (C) 2026 terra2o <terra2o@protonmail.com>
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

#include <compare>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

export module dsa.linear.LinkedList;

export namespace dsa
{

template <typename T>
class LinkedList {
private:
	struct Node {
		T data;
		Node *next{nullptr};
		Node *prev{nullptr};

		template <typename... Args>
		Node(Node *nextPtr, Node *prevPtr, Args &&...args) :
			data(std::forward<Args>(args)...),
			next(nextPtr),
			prev(prevPtr)
		{
		}
	};

	Node *head_{nullptr};
	Node *tail_{nullptr};
	std::size_t size_{0};

	// single iterator implementation handling both const and non-const variants
	template <bool IsConst>
	class IteratorImpl {
	private:
		using NodePtr = std::conditional_t<IsConst, const Node *, Node *>;
		NodePtr current_{nullptr};
		NodePtr tail_{nullptr};

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
			current_(node),
			tail_(tail)
		{
		}

		// allows implicit conversion from mutable to const iterator
		template <bool OtherIsConst>
			requires(IsConst && !OtherIsConst)
		IteratorImpl(const IteratorImpl<OtherIsConst> &other) :
			current_(other.current_),
			tail_(other.tail_)
		{
		}

		reference operator*() const
		{
			return current_->data;
		}
		pointer operator->() const
		{
			return &current_->data;
		}

		IteratorImpl &operator++()
		{
			current_ = current_->next;
			return *this;
		}

		IteratorImpl operator++(int)
		{
			IteratorImpl temp = *this;
			current_ = current_->next;
			return temp;
		}

		IteratorImpl &operator--()
		{
			if (current_) {
				current_ = current_->prev;
			} else {
				current_ = tail_;
			}
			return *this;
		}

		IteratorImpl operator--(int)
		{
			IteratorImpl temp = *this;
			--(*this);
			return temp;
		}

		// relies on implicit conversion from mutable to const iterator
		[[nodiscard]] friend bool operator==(const IteratorImpl &lhs,
						     const IteratorImpl &rhs) noexcept
		{
			return lhs.current_ == rhs.current_;
		}
	};

public:
	using Iterator = IteratorImpl<false>;
	using ConstIterator = IteratorImpl<true>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	LinkedList() = default;

	LinkedList(std::initializer_list<T> list)
	{
		for (const auto &item : list) {
			pushBack(item);
		}
	}

	~LinkedList()
	{
		clear();
	}

	LinkedList(const LinkedList &other)
	{
		copyFrom(other);
	}

	LinkedList &operator=(const LinkedList &other)
	{
		if (this != &other) {
			LinkedList temp(other);
			swap(temp);
		}
		return *this;
	}

	LinkedList(LinkedList &&other) noexcept :
		head_(std::exchange(other.head_, nullptr)),
		tail_(std::exchange(other.tail_, nullptr)),
		size_(std::exchange(other.size_, 0))
	{
	}

	LinkedList &operator=(LinkedList &&other) noexcept
	{
		LinkedList temp(std::move(other));
		swap(temp);
		return *this;
	}

	[[nodiscard]] auto operator<=>(const LinkedList &rhs) const
		requires std::three_way_comparable<T>
	{
		auto it1 = begin();
		auto it2 = rhs.begin();

		while (it1 != end() && it2 != rhs.end()) {
			if (auto cmp = *it1 <=> *it2; cmp != 0) {
				return cmp;
			}
			++it1;
			++it2;
		}

		return size_ <=> rhs.size_;
	}

	[[nodiscard]] bool operator==(const LinkedList &rhs) const
	{
		if (size_ != rhs.size_) {
			return false;
		}

		auto it1 = begin();
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

	void swap(LinkedList &other) noexcept
	{
		std::swap(head_, other.head_);
		std::swap(tail_, other.tail_);
		std::swap(size_, other.size_);
	}

	T &front()
	{
		return head_->data;
	}
	const T &front() const
	{
		return head_->data;
	}

	T &back()
	{
		return tail_->data;
	}
	const T &back() const
	{
		return tail_->data;
	}

	template <typename... Args>
	T &emplaceFront(Args &&...args)
	{
		Node *newNode = new Node(head_, nullptr, std::forward<Args>(args)...);
		if (head_) {
			head_->prev = newNode;
		} else {
			tail_ = newNode;
		}
		head_ = newNode;
		++size_;
		return head_->data;
	}

	template <typename... Args>
	T &emplaceBack(Args &&...args)
	{
		Node *newNode = new Node(nullptr, tail_, std::forward<Args>(args)...);
		if (tail_) {
			tail_->next = newNode;
		} else {
			head_ = newNode;
		}
		tail_ = newNode;
		++size_;
		return tail_->data;
	}

	void pushFront(const T &value)
	{
		emplaceFront(value);
	}
	void pushFront(T &&value)
	{
		emplaceFront(std::move(value));
	}

	void pushBack(const T &value)
	{
		emplaceBack(value);
	}
	void pushBack(T &&value)
	{
		emplaceBack(std::move(value));
	}

	T popFront()
	{
		if (head_ == nullptr) [[unlikely]] {
			throw std::out_of_range("popFront called on empty list");
		}

		Node *oldHead = head_;
		T result = std::move(oldHead->data);

		head_ = head_->next;
		if (head_) {
			head_->prev = nullptr;
		} else {
			tail_ = nullptr;
		}

		delete oldHead;
		--size_;

		return result;
	}

	T popBack()
	{
		if (tail_ == nullptr) [[unlikely]] {
			throw std::out_of_range("popBack called on empty list");
		}

		Node *oldTail = tail_;
		T result = std::move(oldTail->data);

		tail_ = tail_->prev;
		if (tail_) {
			tail_->next = nullptr;
		} else {
			head_ = nullptr;
		}

		delete oldTail;
		--size_;

		return result;
	}

	void clear()
	{
		Node *current = head_;
		while (current) {
			Node *next = current->next;
			delete current;
			current = next;
		}
		head_ = nullptr;
		tail_ = nullptr;
		size_ = 0;
	}

	[[nodiscard]] std::size_t size() const noexcept
	{
		return size_;
	}
	[[nodiscard]] bool empty() const noexcept
	{
		return size_ == 0;
	}

	Iterator begin()
	{
		return Iterator(head_, tail_);
	}
	Iterator end()
	{
		return Iterator(nullptr, tail_);
	}

	ConstIterator begin() const
	{
		return ConstIterator(head_, tail_);
	}
	ConstIterator end() const
	{
		return ConstIterator(nullptr, tail_);
	}

	ConstIterator cbegin() const
	{
		return ConstIterator(head_, tail_);
	}
	ConstIterator cend() const
	{
		return ConstIterator(nullptr, tail_);
	}

	ReverseIterator rbegin()
	{
		return ReverseIterator(end());
	}
	ReverseIterator rend()
	{
		return ReverseIterator(begin());
	}

	ConstReverseIterator rbegin() const
	{
		return ConstReverseIterator(cend());
	}
	ConstReverseIterator rend() const
	{
		return ConstReverseIterator(cbegin());
	}

	ConstReverseIterator crbegin() const
	{
		return ConstReverseIterator(cend());
	}
	ConstReverseIterator crend() const
	{
		return ConstReverseIterator(cbegin());
	}

private:
	void copyFrom(const LinkedList &other)
	{
		try {
			for (Node *curr = other.head_; curr != nullptr; curr = curr->next) {
				emplaceBack(curr->data);
			}
		} catch (...) {
			clear();
			throw;
		}
	}
};

} // namespace dsa
