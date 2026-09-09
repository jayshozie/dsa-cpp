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
import dsa.linear.ListQueue;

constexpr uint32_t queueSize = 100;

void fillQueue(dsa::ListQueue<uint32_t> &queue)
{
	queue.clear();
	for (uint32_t i = 0; i < queueSize; i++) {
		queue.push(i);
	}
}

int main()
{
	dsa::ListQueue<uint32_t> queue;
	assert(queue.isEmpty());
	assert(queue.getSize() == 0);
	fillQueue(queue);
	assert(!queue.isEmpty());
	assert(queue.getSize() != 0);

	assert(queue.front() == 0);
	assert(std::as_const(queue).front() == 0);
	assert(queue.back() == 99);
	assert(std::as_const(queue).back() == 99);

	assert(queue.pop() == 0);
	assert(queue.pop() == 1);

	bool threw = false;
	queue.clear();
	try {
		queue.pop();
	} catch (std::underflow_error &e) {
		threw = true;
	}
	assert(threw);

	// copy constructor - deep copy test
	fillQueue(queue);
	dsa::ListQueue<uint32_t> copyQueue(queue);
	assert(copyQueue.getSize() == queue.getSize());
	assert(copyQueue.front() == queue.front());
	copyQueue.pop();
	assert((copyQueue.front() == queue.front()) == false);
	copyQueue.clear();
	dsa::ListQueue<uint32_t> newCopyQueue(copyQueue);
	assert(newCopyQueue.getSize() == 0);

	// move constructor
	uint32_t queueOldSize = queue.getSize();
	dsa::ListQueue<uint32_t> moveQueue(std::move(queue));
	assert(queue.getSize() == 0);
	assert(queueOldSize == moveQueue.getSize());
	assert(queue.isEmpty());
	moveQueue.clear();
	dsa::ListQueue<uint32_t> newMoveQueue(std::move(moveQueue));
	assert(newMoveQueue.getSize() == 0);

	// copy assignment
	fillQueue(moveQueue);
	dsa::ListQueue<uint32_t> copyAssignmentQueue;
	copyAssignmentQueue = moveQueue;
	assert(copyAssignmentQueue.getSize() == moveQueue.getSize());
	uint32_t popped = moveQueue.pop();
	assert((copyAssignmentQueue.getSize() == moveQueue.getSize()) == false);
	assert(copyAssignmentQueue.pop() == popped);
	copyAssignmentQueue.clear();
	dsa::ListQueue<uint32_t> newCopyAssignmentQueue;
	newCopyAssignmentQueue = copyAssignmentQueue;
	assert(newCopyAssignmentQueue.getSize() == 0);
	fillQueue(copyAssignmentQueue);

	// move assignment
	fillQueue(copyAssignmentQueue);
	uint32_t copyAssignmentOldSize = copyAssignmentQueue.getSize();
	dsa::ListQueue<uint32_t> moveAssignmentQueue;
	moveAssignmentQueue = std::move(copyAssignmentQueue);
	assert(copyAssignmentQueue.getSize() == 0);
	assert(moveAssignmentQueue.getSize() == copyAssignmentOldSize);
	assert(copyAssignmentQueue.isEmpty());
	moveAssignmentQueue.clear();
	dsa::ListQueue<uint32_t> newMoveAssignmentQueue;
	newMoveAssignmentQueue = std::move(moveAssignmentQueue);
	assert(newMoveAssignmentQueue.getSize() == 0);
	fillQueue(moveAssignmentQueue);

	// self-assignment checks
	copyAssignmentQueue.clear();
	fillQueue(copyAssignmentQueue);
	copyAssignmentOldSize = copyAssignmentQueue.getSize();
	copyAssignmentQueue = copyAssignmentQueue;
	assert(copyAssignmentQueue.getSize() == copyAssignmentOldSize);

	fillQueue(moveAssignmentQueue);
	uint32_t moveAssignmentQueueOldSize = moveAssignmentQueue.getSize();
	moveAssignmentQueue = std::move(moveAssignmentQueue);
	assert(moveAssignmentQueue.getSize() == moveAssignmentQueueOldSize);
}
