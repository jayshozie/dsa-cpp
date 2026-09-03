// dsa-cpp - An implementation of some data structures and algorithms in C++.
// Copyright (C)  2026      Emir Baha YILDIRIM <jayshozie@gmail.com>
// Copyright (C)  2026      terra2o <terra2o@protonmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.        See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <cassert>
#include <string>

import dsa.linear.LinkedList;

void test_constructors()
{
    dsa::LinkedList<int> empty_list;
    assert(empty_list.empty());
    assert(empty_list.size() == 0);

    dsa::LinkedList<int> list{1, 2, 3, 4, 5};
    assert(!list.empty());
    assert(list.size() == 5);
    assert(list.front() == 1);
}

void test_push_and_pop()
{
    dsa::LinkedList<std::string> list;

    list.pushFront("world");
    list.pushFront("hello");

    assert(list.size() == 2);
    assert(list.front() == "hello");

    auto popped = list.popFront();
    assert(popped.has_value());
    assert(*popped == "hello");
    assert(list.size() == 1);
    assert(list.front() == "world");

    list.popFront();
    assert(list.empty());

    auto empty_pop = list.popFront();
    assert(!empty_pop.has_value());
}

void test_copy_and_move()
{
    dsa::LinkedList<int> original{10, 20, 30};

    dsa::LinkedList<int> copy(original);
    assert(copy.size() == 3);
    assert(copy.front() == 10);

    dsa::LinkedList<int> moved(std::move(copy));
    assert(moved.size() == 3);
    assert(moved.front() == 10);

    dsa::LinkedList<int> assigned;
    assigned = original;
    assert(assigned.size() == 3);

    dsa::LinkedList<int> move_assigned;
    move_assigned = std::move(assigned);
    assert(move_assigned.size() == 3);
}

void test_iteration()
{
    dsa::LinkedList<int> list{1, 2, 3};

    int expected = 1;
    for (int val : list) {
        assert(val == expected++);
    }

    const auto &const_ref = list;
    auto it = const_ref.cbegin();
    assert(*it == 1);
    assert(it == list.begin());
}

int main()
{
    test_constructors();
    test_push_and_pop();
    test_copy_and_move();
    test_iteration();

    return 0;
}
