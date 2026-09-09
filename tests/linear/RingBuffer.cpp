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
#include <string>
#include <utility>
import dsa.linear.RingBuffer;

constexpr uint32_t cap = 128;
constexpr uint32_t realCap = 127;

void fillBuffer(dsa::RingBuffer<uint32_t, cap> &buf)
{
	buf.clear();
	for (uint32_t i = 0; i < realCap; i++) {
		buf.push(i);
	}
}

bool testPushOverflow(dsa::RingBuffer<uint32_t, cap> &buf)
{
	bool threw = false;
	buf.clear();
	try {
		for (uint32_t i = 0; i < (cap*cap); i++) {
			buf.push(i);
		}
	} catch (std::overflow_error &e) {
		threw = true;
	}
	return threw;
}

bool testMovePushOverflow(dsa::RingBuffer<std::string, cap> &buf)
{
	bool threw = false;
	std::string str = "long string to test";
	try {
		for (uint32_t i = 0; i < (cap*cap); i++) {
			buf.push(std::move(str));
		}
	} catch (std::overflow_error &e) {
		threw = true;
	}
	return threw;
}

bool testPopUnderflow(dsa::RingBuffer<uint32_t, cap> &buf)
{
	bool threw = false;
	buf.clear();
	try {
		buf.pop();
	} catch (std::underflow_error &e) {
		threw = true;
	}
	return threw;
}

bool testMovePopUnderflow(dsa::RingBuffer<std::string, cap> &buf)
{
	bool threw = false;
	std::string str = "long string to test";
	buf.clear();
	buf.push(std::move(str));
	try {
		for (uint32_t i = 0; i < (cap*cap); i++) {
			buf.pop();
		}
	} catch (std::underflow_error &e) {
		threw = true;
	}
	return threw;
}


bool testFrontUnderflow(dsa::RingBuffer<uint32_t, cap> &buf)
{
	bool threw = false;
	buf.clear();
	try {
		buf.front();
	} catch (std::underflow_error &e) {
		threw = true;
	}
	return threw;
}

bool testBackUnderflow(dsa::RingBuffer<uint32_t, cap> &buf)
{
	bool threw = false;
	buf.clear();
	try {
		buf.back();
	} catch (std::underflow_error &e) {
		threw = true;
	}
	return threw;
}

int main()
{
	dsa::RingBuffer<uint32_t, cap> buf;
	assert(buf.getSize() == 0);
	assert(buf.getCapacity() == cap);
	assert(buf.isEmpty());

	fillBuffer(buf);
	assert(buf.getSize() == realCap);
	assert(!buf.isEmpty());
	assert(buf.isFull());

	assert(testPushOverflow(buf));
	dsa::RingBuffer<std::string, cap> bufStr;
	assert(testMovePushOverflow(bufStr));

	assert(testPopUnderflow(buf));
	assert(testMovePopUnderflow(bufStr));

	assert(testFrontUnderflow(buf));
	assert(testBackUnderflow(buf));

    fillBuffer(buf);
    for (uint32_t i = 0; i < 50; i++) {
        buf.pop();
    }
    for (uint32_t i = 0; i < 50; i++) {
        buf.push(i);
    }
	assert(buf.front() == 50);
    assert(buf.isFull());
    assert(buf.getSize() == realCap);

	dsa::RingBuffer<uint32_t, cap> copyBuf(buf);
    assert(copyBuf.getSize() == buf.getSize());
    assert(copyBuf.front() == buf.front());
}
