// dsa-cpp - An implementation of some data structures and algorithms in C++.
// Copyright (C)  2026  Emir Baha YILDIRIM <jayshozie@gmail.com>
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
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <stdexcept>
import dsa.linear.DynamicArray;

int main()
{
	// initialization
	dsa::DynamicArray<uint_fast64_t> arr;
	// isEmpty
	assert(arr.isEmpty());
	// getCapacity - default
	assert(arr.getCapacity() == 1);

	// core i/o
	uint_fast64_t random1 = std::rand();
	// pushBack
	arr.pushBack(random1);
	// get
	assert(random1 == arr.get(0));
	// popBack
	arr.popBack();
	assert(arr.isEmpty());

	const uint_fast64_t random2 = std::rand();
	arr.pushBack(random2);
	assert(random2 == arr.get(0));
	assert(arr.contains(random2));
	arr.popBack();

	// capacity scaling
	for (uint_fast8_t i = 0; i < 100; i++) {
		arr.pushBack(std::rand());
	}
	assert(arr.getLength() == 100);
	assert(!arr.isEmpty());

	// arbitrary position mutation
	// insertAt
	arr.insertAt(random1, 69);
	assert(random1 == arr.get(69));
	// front
	assert(arr.front() == arr.get(0));
	// back
	assert(arr.back() == arr.get(arr.getLength() - 1));

	uint_fast64_t random3 = arr.removeAt(69);
	assert(random3 == random1);

	// bounds checking & exception safety
	dsa::DynamicArray<double> should_throw;
	bool threw = false;

	try {
		should_throw.popBack();
	} catch (const std::out_of_range &) {
		threw = true;
	}
	assert(threw);

	threw = false;
	try {
		should_throw.get(UINT_FAST64_MAX);
	} catch (const std::out_of_range &) {
		threw = true;
	}
	assert(threw);

	threw = false;
	try {
		should_throw.insertAt(std::numbers::pi, UINT_FAST32_MAX);
	} catch (const std::out_of_range &) {
		threw = true;
	}
	assert(threw);

	threw = false;
	try {
		should_throw.removeAt(UINT_FAST16_MAX);
	} catch (const std::out_of_range &) {
		threw = true;
	}
	assert(threw);

	// iterators
	dsa::DynamicArray<int> iter_arr;
	iter_arr.pushBack(10);
	iter_arr.pushBack(20);
	iter_arr.pushBack(30);

	int expected[] = {10, 20, 30};
	size_t iter_idx = 0;

	for (int val : iter_arr) {
		// iterator check
		assert(val == expected[iter_idx]);
		// operator[]
		assert(iter_arr[iter_idx] == expected[iter_idx]);
		iter_idx++;
	}
	// whether it stops at the correct time
	assert(iter_idx == 3);

	// copy semantics (deep copy verification)
	dsa::DynamicArray<uint_fast64_t> arr_copy(arr);
	assert(arr_copy.getLength() == arr.getLength());
	assert(arr_copy.get(0) == arr.get(0));

	arr_copy.get(0) = 9999;
	assert(arr.get(0) != 9999);

	dsa::DynamicArray<uint_fast64_t> arr_assign;
	arr_assign = arr;
	assert(arr_assign.getLength() == arr.getLength());
	assert(arr_assign.get(0) == arr.get(0));

	arr_assign.get(0) = 8888;
	assert(arr.get(0) != 8888);

	// move semantics
	std::size_t expected_length = arr_copy.getLength();
	dsa::DynamicArray<uint_fast64_t> arr_moved(std::move(arr_copy));

	assert(arr_moved.getLength() == expected_length);
	assert(arr_moved.get(0) == 9999);
	assert(arr_copy.getLength() == 0);

	expected_length = arr_assign.getLength();
	dsa::DynamicArray<uint_fast64_t> arr_move_assign;
	arr_move_assign = std::move(arr_assign);

	assert(arr_move_assign.getLength() == expected_length);
	assert(arr_assign.getLength() == 0);

	// reserve
	std::size_t MiB = 1024 * 1024;
	arr.reserve(MiB);
	assert(arr.getCapacity() == MiB);

	// clear check
	arr.clear();
	assert(arr.isEmpty());

	return 0;
}
