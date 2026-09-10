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

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <utility>
import dsa.linear.ArrayStack;

constexpr uint32_t stackSize = 10;

void fillStack(dsa::ArrayStack<uint32_t> &stack)
{
	stack.clear();
	for (uint32_t i = 0; i < stackSize; i++) {
		stack.push(i);
	}
}

bool checkConstTop(const uint32_t constVal, dsa::ArrayStack<uint32_t> &stack)
{
	return (constVal == stack.pop());
}

int main()
{
	dsa::ArrayStack<uint32_t> stack;
	assert((stack.getSize() == 0) && stack.isEmpty());
	fillStack(stack);
	assert(stack.getSize() == stackSize);

	stack.clear();
	assert(stack.getSize() == 0);

	bool threw = false;
	try {
		stack.pop();
	} catch (std::underflow_error &e) {
		threw = true;
	}

	assert(threw);
	fillStack(stack);
	assert(stack.top() == 9);

	uint32_t testList[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	uint32_t idx = 0;
	while (!stack.isEmpty()) {
		uint32_t tmp = stack.pop();
		assert(testList[idx] == tmp);
		idx++;
	}

	fillStack(stack);
	assert(checkConstTop(std::as_const(stack).top(), stack));

	fillStack(stack);

	// copy constructor - deep copy test
	dsa::ArrayStack<uint32_t> copyStack(stack);
	assert(copyStack.getSize() == stack.getSize());
	assert(copyStack.top() == stack.top());
	copyStack.pop();
	assert((copyStack.top() == stack.top()) == false);
	copyStack.clear();
	dsa::ArrayStack<uint32_t> newCopyArray(copyStack);
	assert(newCopyArray.getSize() == 0);

	// move constructor
	uint32_t stackOldSize = stack.getSize();
	dsa::ArrayStack<uint32_t> moveStack(std::move(stack));
	assert(stack.getSize() == 0);
	assert(stackOldSize == moveStack.getSize());
	assert(stack.isEmpty());
	moveStack.clear();
	dsa::ArrayStack<uint32_t> newMoveStack(std::move(moveStack));
	assert(newMoveStack.getSize() == 0);

	// copy assignment
	fillStack(moveStack);
	dsa::ArrayStack<uint32_t> copyAssignmentStack;
	copyAssignmentStack = moveStack;
	assert(copyAssignmentStack.getSize() == moveStack.getSize());
	uint32_t popped = moveStack.pop();
	assert((copyAssignmentStack.getSize() == moveStack.getSize()) == false);
	assert(copyAssignmentStack.pop() == popped);
	copyAssignmentStack.clear();
	dsa::ArrayStack<uint32_t> newCopyAssignmentList;
	newCopyAssignmentList = copyAssignmentStack;
	assert(newCopyAssignmentList.getSize() == 0);

	// move assignment
	fillStack(copyAssignmentStack);
	uint32_t copyAssignmentOldSize = copyAssignmentStack.getSize();
	dsa::ArrayStack<uint32_t> moveAssignmentStack;
	moveAssignmentStack = std::move(copyAssignmentStack);
	assert(copyAssignmentStack.getSize() == 0);
	assert(moveAssignmentStack.getSize() == copyAssignmentOldSize);
	assert(copyAssignmentStack.isEmpty());
	moveAssignmentStack.clear();
	dsa::ArrayStack<uint32_t> newMoveAssignmentStack;
	newMoveAssignmentStack = std::move(moveAssignmentStack);
	assert(newMoveAssignmentStack.getSize() == 0);

	fillStack(copyAssignmentStack);
	copyAssignmentOldSize = copyAssignmentStack.getSize();
	copyAssignmentStack = copyAssignmentStack;
	assert(copyAssignmentStack.getSize() == copyAssignmentOldSize);

	fillStack(moveAssignmentStack);
	uint32_t moveAssignmentListOldSize = moveAssignmentStack.getSize();
	moveAssignmentStack = std::move(moveAssignmentStack);
	assert(moveAssignmentStack.getSize() == moveAssignmentListOldSize);
}
