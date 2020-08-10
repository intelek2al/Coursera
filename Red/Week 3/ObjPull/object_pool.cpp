#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate() {
		T *p = TryAllocate();
		if (p == nullptr)
		{
			p = new T;
			objs.insert(p);
		}
		return p;
	}
	T* TryAllocate() {
		if (!free.empty()) {
			objs.insert(free.front());
			T *p = free.front();
			free.pop();
			return p;
		}
		return nullptr;
	}

	void Deallocate(T* object) {
		auto o = objs.find(object);
		if (o == objs.end()) {
			throw invalid_argument("Invaliv pointer");
		}
		else
		{
			free.push(*o);
			objs.erase(o);
		}

	}

	~ObjectPool() {
		while (!free.empty()) {
			delete free.front();
			free.pop();
		}
		for (auto &o:objs) {
			delete o;
		}
	}

private:
	queue<T *> free;
	set<T *> objs;
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}
