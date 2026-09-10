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
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>
import dsa.linear.HeapArray;

constexpr std::size_t capacity = 100;
constexpr uint32_t randomInt = 42;

void fillArray(dsa::HeapArray<uint32_t> &arr)
{
	for (uint32_t i = 0; i < capacity; i++) {
		arr[i] = i;
	}
}

int main()
{
	dsa::HeapArray<uint32_t> arr(capacity);
	assert(arr.getSize() == capacity);
	assert(!arr.isEmpty());
	fillArray(arr);

	bool threw = false;
	try {
		arr.at(capacity * capacity);
	} catch (std::out_of_range &e) {
		threw = true;
	}
	assert(threw);

	assert(arr.at(0) == 0);
	assert(std::as_const(arr).at(0) == 0);
	assert(arr[0] == 0);
	assert(std::as_const(arr)[0] == 0);
	assert(arr.front() == 0);
	assert(std::as_const(arr).front() == 0);
	assert(arr.back() == 99);
	assert(std::as_const(arr).back() == 99);
	assert(arr.data()[0] == 0);
	assert(std::as_const(arr).data()[0] == 0);
	arr.fill(randomInt);
	for (uint32_t num : arr) {
		assert(num == randomInt);
	}

	// copy constructor - deep copy test
	dsa::HeapArray<uint32_t> copyArr(arr);
	assert(copyArr.getSize() == arr.getSize());
	assert(copyArr.front() == arr.front());
	copyArr.at(0) = UINT32_MAX;
	assert((copyArr.front() == arr.front()) == false);

	// move constructor
	uint32_t arrOldSize = arr.getSize();
	dsa::HeapArray<uint32_t> moveArr(std::move(arr));
	assert(arr.getSize() == 0);
	assert(arrOldSize == moveArr.getSize());
	assert(arr.isEmpty());

	// copy assignment
	fillArray(moveArr);
	dsa::HeapArray<uint32_t> copyAssignmentArr(0);
	copyAssignmentArr = moveArr;
	assert(copyAssignmentArr.getSize() == moveArr.getSize());
	dsa::HeapArray<uint32_t> newCopyAssignmentArr(0);
	newCopyAssignmentArr = copyAssignmentArr;

	// move assignment
	fillArray(copyAssignmentArr);
	uint32_t copyAssignmentOldSize = copyAssignmentArr.getSize();
	dsa::HeapArray<uint32_t> moveAssignmentArr(0);
	moveAssignmentArr = std::move(copyAssignmentArr);
	assert(copyAssignmentArr.getSize() == 0);
	assert(moveAssignmentArr.getSize() == copyAssignmentOldSize);
	assert(copyAssignmentArr.isEmpty());
	dsa::HeapArray<uint32_t> newMoveAssignmentArr(0);
	newMoveAssignmentArr = std::move(moveAssignmentArr);
	fillArray(moveAssignmentArr);

	// self-assignment checks
	copyAssignmentOldSize = copyAssignmentArr.getSize();
	copyAssignmentArr = copyAssignmentArr;
	assert(copyAssignmentArr.getSize() == copyAssignmentOldSize);

	fillArray(moveAssignmentArr);
	uint32_t moveAssignmentArrOldSize = moveAssignmentArr.getSize();
	moveAssignmentArr = std::move(moveAssignmentArr);
	assert(moveAssignmentArr.getSize() == moveAssignmentArrOldSize);
}
