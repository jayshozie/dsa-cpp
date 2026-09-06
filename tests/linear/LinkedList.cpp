#include <string>
#include <utility>
#include <memory>
#include <stdexcept>
#include <cassert>

import dsa.linear.LinkedList;

namespace
{

struct Point {
	int x{0};
	int y{0};
};

void testDefaultConstructionAndCapacity()
{
	dsa::LinkedList<int> list;
	assert(list.empty());
	assert(list.getSize() == 0);
	assert(list.begin() == list.end());
}

void testInitializerListAndAccess()
{
	dsa::LinkedList<int> list{10, 20, 30};
	assert(!list.empty());
	assert(list.getSize() == 3);
	assert(list.front() == 10);
	assert(list.back() == 30);

	list.front() = 15;
	list.back() = 35;
	assert(list.front() == 15);
	assert(list.back() == 35);

	const dsa::LinkedList<int> constList{1, 2, 3};
	assert(constList.front() == 1);
	assert(constList.back() == 3);
}

void testPushAndEmplace()
{
	dsa::LinkedList<std::string> list;

	list.pushBack("world");
	list.pushFront("hello");
	assert(list.getSize() == 2);
	assert(list.front() == "hello");
	assert(list.back() == "world");

	std::string s1 = "foo";
	std::string s2 = "bar";
	list.pushFront(std::move(s1));
	list.pushBack(std::move(s2));
	assert(list.front() == "foo");
	assert(list.back() == "bar");
	assert(list.getSize() == 4);

	list.emplaceFront("first");
	list.emplaceBack("last");
	assert(list.front() == "first");
	assert(list.back() == "last");
	assert(list.getSize() == 6);
}

void testPopOperationsAndExceptions()
{
	dsa::LinkedList<int> list{1, 2, 3};

	assert(list.popFront() == 1);
	assert(list.getSize() == 2);

	assert(list.popBack() == 3);
	assert(list.getSize() == 1);

	assert(list.popFront() == 2);
	assert(list.empty());

	try {
		(void)list.popFront();
		assert(false);
	} catch (const std::out_of_range &) {
	}

	try {
		(void)list.popBack();
		assert(false);
	} catch (const std::out_of_range &) {
	}
}

void testCopyAndMoveSemantics()
{
	dsa::LinkedList<int> orig{1, 2, 3};

	dsa::LinkedList<int> copyConstructed(orig);
	assert(copyConstructed == orig);

	dsa::LinkedList<int> copyAssigned;
	copyAssigned = orig;
	assert(copyAssigned == orig);

	dsa::LinkedList<int> moveSrc{4, 5, 6};
	dsa::LinkedList<int> moveConstructed(std::move(moveSrc));
	assert(moveConstructed.getSize() == 3);
	assert(moveConstructed.front() == 4);
	assert(moveSrc.empty());

	dsa::LinkedList<int> moveDst;
	moveDst = std::move(moveConstructed);
	assert(moveDst.getSize() == 3);
	assert(moveDst.front() == 4);
	assert(moveConstructed.empty());
}

void testIteratorsAndOperators()
{
	dsa::LinkedList<Point> points{{10, 20}, {30, 40}};

	auto it = points.begin();
	assert(it->x == 10 && it->y == 20);

	auto oldIt = it++;
	assert(oldIt->x == 10);
	assert(it->x == 30);

	dsa::LinkedList<int> list{10, 20, 30, 40};

	int expected = 10;
	for (auto iter = list.begin(); iter != list.end(); ++iter) {
		assert(*iter == expected);
		expected += 10;
	}

	// verifying --end() steps back to tail node
	auto endIt = list.end();
	--endIt;
	assert(*endIt == 40);
	endIt--;
	assert(*endIt == 30);

	for (auto &val : list) {
		val *= 2;
	}
	assert(list.front() == 20);
	assert(list.back() == 80);

	// implicit conversion from mutable to const iterator
	dsa::LinkedList<int>::ConstIterator cit = list.begin();
	assert(*cit == 20);
}

void testReverseIterators()
{
	dsa::LinkedList<int> list{1, 2, 3, 4};

	int expected = 4;
	for (auto rit = list.rbegin(); rit != list.rend(); ++rit) {
		assert(*rit == expected);
		--expected;
	}

	const dsa::LinkedList<int> constList{10, 20};
	auto crit = constList.crbegin();
	assert(*crit == 20);
	++crit;
	assert(*crit == 10);
}

void testComparisons()
{
	dsa::LinkedList<int> a{1, 2, 3};
	dsa::LinkedList<int> b{1, 2, 3};
	dsa::LinkedList<int> c{1, 2, 4};
	dsa::LinkedList<int> d{1, 2};

	assert(a == b);
	assert(a != c);
	assert((a <=> b) == 0);
	assert((a <=> c) < 0);
	assert((a <=> d) > 0);
}

void testMoveOnlyTypes()
{
	dsa::LinkedList<std::unique_ptr<int>> list;

	list.pushBack(std::make_unique<int>(10));
	list.emplaceFront(std::make_unique<int>(5));

	assert(*list.front() == 5);
	assert(*list.back() == 10);

	auto ptr = list.popFront();
	assert(*ptr == 5);
	assert(list.getSize() == 1);
}

void testClearAndSwap()
{
	dsa::LinkedList<int> list1{1, 2, 3};
	dsa::LinkedList<int> list2{10, 20};

	list1.swap(list2);
	assert(list1.getSize() == 2 && list1.front() == 10);
	assert(list2.getSize() == 3 && list2.front() == 1);

	list1.clear();
	assert(list1.empty());
	assert(list1.begin() == list1.end());
}

} // namespace

int main()
{
	testDefaultConstructionAndCapacity();
	testInitializerListAndAccess();
	testPushAndEmplace();
	testPopOperationsAndExceptions();
	testCopyAndMoveSemantics();
	testIteratorsAndOperators();
	testReverseIterators();
	testComparisons();
	testMoveOnlyTypes();
	testClearAndSwap();

	return 0;
}
