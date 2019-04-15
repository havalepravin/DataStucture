#include <assert.h>

#include "priorityqueue.h"

void TestPriorityQueue() {
	priorityqueue q;
	int values[31] = { 16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 14, 18, 22, 26, 30, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31 };
	for(int i = 0; i < 31; i++)
		q.push(values[i]);
	for(int i = 31; i >0; i--) {
		assert(i == q.top());
		q.pop();
	}
}
int main() {
	TestPriorityQueue();
}