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
