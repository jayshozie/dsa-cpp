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

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <utility>

import dsa.linear.SinglyLinkedList;

constexpr uint32_t listSize = 10;

void fillList(dsa::SinglyLinkedList<uint32_t> &list)
{
	for (uint32_t i = listSize; i != 0; i--) {
		list.pushFront(i);
	}
}

bool checkConstFront(const uint32_t constVal,
					 dsa::SinglyLinkedList<uint32_t> &list)
{
	return (constVal == list.popFront());
}

int main()
{
	// dsa::SinglyLinkedList<uint32_t> list{1,2,3,4,5,6,7,8,9,10};
	dsa::SinglyLinkedList<uint32_t> list;
	assert(list.isEmpty());
	fillList(list);
	assert(!list.isEmpty());
	assert(list.getSize() == listSize);

	// popFront threw
	list.clear();
	bool threw = false;
	try {
		list.popFront();
	} catch (std::underflow_error &e) {
		threw = true;
	}
	assert(threw);

	// front threw
	threw = false;
	try {
		list.front();
	} catch (std::out_of_range &e) {
		threw = true;
	}
	assert(threw);

	list.clear();
	fillList(list);
	assert(checkConstFront(std::as_const(list).front(), list));

	list.emplaceFront(1);
	uint32_t front = list.popFront();
	assert(front == 1);

	fillList(list);

	// copy constructor - deep copy test
	dsa::SinglyLinkedList<uint32_t> copyList(list);
	assert(copyList.getSize() == list.getSize());
	assert(copyList.front() == list.front());
	copyList.popFront();
	assert((copyList.front() == list.front()) == false);
	copyList.clear();
	dsa::SinglyLinkedList<uint32_t> newCopyList(copyList);
	assert(newCopyList.getSize() == 0);

	// move constructor
	uint32_t listOldSize = list.getSize();
	dsa::SinglyLinkedList<uint32_t> moveList(std::move(list));
	assert(list.getSize() == 0);
	assert(listOldSize == moveList.getSize());
	assert(list.isEmpty());
	moveList.clear();
	dsa::SinglyLinkedList<uint32_t> newMoveList(std::move(moveList));
	assert(newMoveList.getSize() == 0);

	// copy assignment
	fillList(moveList);
	dsa::SinglyLinkedList<uint32_t> copyAssignmentList;
	copyAssignmentList = moveList;
	assert(copyAssignmentList.getSize() == moveList.getSize());
	uint32_t popped = moveList.popFront();
	assert((copyAssignmentList.getSize() == moveList.getSize()) == false);
	assert(copyAssignmentList.popFront() == popped);
	copyAssignmentList.clear();
	dsa::SinglyLinkedList<uint32_t> newCopyAssignmentList;
	newCopyAssignmentList = copyAssignmentList;
	assert(newCopyAssignmentList.getSize() == 0);
	fillList(copyAssignmentList);

	// move assignment
	fillList(copyAssignmentList);
	uint32_t copyAssignmentOldSize = copyAssignmentList.getSize();
	dsa::SinglyLinkedList<uint32_t> moveAssignmentList;
	moveAssignmentList = std::move(copyAssignmentList);
	assert(copyAssignmentList.getSize() == 0);
	assert(moveAssignmentList.getSize() == copyAssignmentOldSize);
	assert(copyAssignmentList.isEmpty());
	moveAssignmentList.clear();
	dsa::SinglyLinkedList<uint32_t> newMoveAssignmentList;
	newMoveAssignmentList = std::move(moveAssignmentList);
	assert(newMoveAssignmentList.getSize() == 0);
	fillList(moveAssignmentList);

	// self-assignment checks
	copyAssignmentList.clear();
	fillList(copyAssignmentList);
	copyAssignmentOldSize = copyAssignmentList.getSize();
	copyAssignmentList = copyAssignmentList;
	assert(copyAssignmentList.getSize() == copyAssignmentOldSize);

	fillList(moveAssignmentList);
	uint32_t moveAssignmentListOldSize = moveAssignmentList.getSize();
	moveAssignmentList = std::move(moveAssignmentList);
	assert(moveAssignmentList.getSize() == moveAssignmentListOldSize);

	// iterator test
	fillList(list);
	uint32_t idx = 1;
	for (auto val : list) {
		assert(val == idx);
		idx++;
	}
}
