// dsa-cpp - An implementation of some data structures and algorithms in C++.
// Copyright (C)  2026	  Emir Baha YILDIRIM <jayshozie@gmail.com>
// Copyright (C)  2026	  terra2o <terra2o@protonmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	    See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
module;

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory> // std::unique<>()
#include <optional>
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

        template <typename... Args>
        Node(Node *nextPtr, Args &&...args) :
            data(std::forward<Args>(args)...),
            next(nextPtr)
        {
        }
    };

    Node *head_{nullptr};
    std::size_t size_{0};

    // implements both iterator and const_iterator to avoid duplicating logic.
    template <bool IsConst>
    class IteratorImpl {
    private:
        using NodePtr = std::conditional_t<IsConst, const Node *, Node *>;
        NodePtr current_;

        template <bool>
        friend class IteratorImpl;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = std::conditional_t<IsConst, const T *, T *>;
        using reference = std::conditional_t<IsConst, const T &, T &>;

        IteratorImpl() : current_(nullptr)
        {
        }

        explicit IteratorImpl(NodePtr node) : current_(node)
        {
        }

        // implicit conversion from iterator to const_iterator (one-way).
        template <bool OtherIsConst>
            requires(IsConst && !OtherIsConst)
        IteratorImpl(const IteratorImpl<OtherIsConst> &other) :
            current_(other.current_)
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

        // cross-comparison enables comparing non-const iterators against const
        // iterators (e.g. it == cend()).
        template <bool OtherIsConst>
        [[nodiscard]] friend bool
            operator==(const IteratorImpl &lhs,
                       const IteratorImpl<OtherIsConst> &rhs) noexcept
        {
            return lhs.current_ == rhs.current_;
        }
    };

public:
    using Iterator = IteratorImpl<false>;
    using ConstIterator = IteratorImpl<true>;

    LinkedList() = default;

    // iterating in reverse preserves the exact ordering of elements when using
    // pushFront.
    LinkedList(std::initializer_list<T> list)
    {
        for (auto it = std::rbegin(list); it != std::rend(list); ++it) {
            pushFront(*it);
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
        size_(std::exchange(other.size_, 0))
    {
    }

    LinkedList &operator=(LinkedList &&other) noexcept
    {
        LinkedList temp(std::move(other));
        swap(temp);
        return *this;
    }

    void swap(LinkedList &other) noexcept
    {
        std::swap(head_, other.head_);
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

    template <typename... Args>
    T &emplaceFront(Args &&...args)
    {
        // construct node directly with raw pointer
        head_ = new Node(head_, std::forward<Args>(args)...);
        ++size_;
        return head_->data;
    }

    void pushFront(const T &value)
    {
        emplaceFront(value);
    }
    void pushFront(T &&value)
    {
        emplaceFront(std::move(value));
    }

    std::optional<T> popFront()
    {
		if (head_ == nullptr) {
			return std::nullopt;
		}

		Node *oldHead = head_;
		head_ = head_->next;

		// move data out before cleanup
		T result = std::move(oldHead->data);
		delete oldHead;
		--size_;

		return result;
    }

    void clear()
    {
        while (head_) {
            Node *temp = head_;
            head_ = head_->next;
            delete temp;
        }
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
        return Iterator(head_);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    ConstIterator begin() const
    {
        return ConstIterator(head_);
    }
    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

    ConstIterator cbegin() const
    {
        return ConstIterator(head_);
    }
    ConstIterator cend() const
    {
        return ConstIterator(nullptr);
    }

private:
    // basic exception safety: cleans up partially allocated nodes if node
    // instantiation throws mid-copy.
    void copyFrom(const LinkedList &other)
    {
        if (!other.head_)
            return;

        head_ = new Node(nullptr, other.head_->data);
        Node *currentNew = head_;
        Node *currentOld = other.head_->next;

        try {
            while (currentOld) {
                currentNew->next = new Node(nullptr, currentOld->data);
                currentNew = currentNew->next;
                currentOld = currentOld->next;
            }
        } catch (...) {
            clear();
            throw;
        }
        size_ = other.size_;
    }
};

} // namespace dsa
