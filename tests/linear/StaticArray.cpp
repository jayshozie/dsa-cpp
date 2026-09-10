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
import dsa.linear.StaticArray;

constexpr uint32_t cap = 128;

void fillArray(dsa::StaticArray<uint32_t, cap> &arr)
{
	for (uint32_t i = 0; i < cap; i++) {
		arr[i] = i;
	}
}

int main()
{
	dsa::StaticArray<uint32_t, cap> arr;
	assert(arr.getSize() == cap);
	assert(!arr.isEmpty());
	fillArray(arr);

	assert(arr.at(0) == 0);
	assert(arr.at(1) == 1);
	assert(std::as_const(arr).at(2) == 2);

	assert(arr.front() == 0);
	assert(std::as_const(arr).front() == 0);
	assert(arr.back() == 127);
	assert(std::as_const(arr).back() == 127);

	assert(arr[0] == 0);
	assert(std::as_const(arr)[1] == 1);

	assert(arr.data()[10] == 10);
	assert(std::as_const(arr).data()[13] == 13);

	bool threw = false;
	std::size_t invalidIdx = static_cast<std::size_t>(cap) * 2;
	try {
		arr.at(invalidIdx);
	} catch (std::out_of_range &e) {
		threw = true;
	}
	assert(threw);

	arr.fill(cap);
	for (uint32_t i = 0; i < cap; i++) {
		assert(arr.at(i) == cap);
	}
	for (uint32_t i : arr) {
		assert(i == cap);
	}
}
