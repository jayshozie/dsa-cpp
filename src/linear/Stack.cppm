#include <cstddef>
#include <stdexcept>
#include <utility>

export module dsa.linear.Stack;

import dsa.linear.DynamicArray;

export namespace dsa
{
template <typename T>
class Stack {
private:
    DynamicArray<T> container;

public:
    Stack() = default;
    ~Stack() = default;

    Stack(const Stack &rhs) = default;
    Stack &operator=(const Stack &rhs) = default;

    Stack(Stack &&rhs) noexcept = default;
    Stack &operator=(Stack &&rhs) noexcept = default;

    void push(T value)
    {
        this->container.pushBack(std::move(value));
    }

    T pop()
    {
        if (this->isEmpty()) {
            throw std::out_of_range("Cannot pop from an empty stack.");
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
