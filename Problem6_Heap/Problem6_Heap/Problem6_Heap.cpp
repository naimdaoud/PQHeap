#include <iostream>
#include <iomanip>

using namespace std;

struct NODE {
	int ID;
	int duration;
	int priority;
};

struct HEAP {
	int Max;
	int N;
	NODE* a;
};

HEAP* initialize(int Max) {
	HEAP* h;
	h = new HEAP;
	/* Allocate the array plus one extra for sentinel */
	h->a = new NODE[Max + 1];
	h->Max = Max;
	h->N = 0;
	return h;
}

int isEmpty(HEAP* h) {
	return h->N == 0;
}
int isFull(HEAP* h) {
	return h->N == h->Max;
}

void displayHeapArray(HEAP* h) {
	for (int i = 1; i <= h->N; i++) {
		cout << h->a[i].ID << " ";
	}
	cout << endl;
}

void displayHeapTree(HEAP* h) {
	int k;
	if (isEmpty(h)) {
		cout << "Heap is empty!" << endl;
		return;
	}
	cout << "The heap is: " << endl;
	cout << setw(5) << h->a[1].ID;
	k = 2;
	for (int i = 2; i <= h->N; i++) {
		if (i == k) {
			cout << endl;
			k *= 2;
		}
		cout << setw(5) << h->a[i].ID;
	}
	cout << endl;
}

void swap(NODE* a, int i, int j) {
	NODE tmp;
	tmp = a[i]; a[i] = a[j]; a[j] = tmp;
}

void swim(HEAP* h, int k)
{
	while (k > 1 && h->a[k].priority < h->a[k / 2].priority)
	{
		swap(h->a, k, k / 2);
		k = k / 2;
	}
}

void sink(HEAP* h, int k)
{
	while (2 * k <= h->N)
	{
		int j = 2 * k;
		if (j < h->N && h->a[j].priority < h->a[j + 1].priority) j++;
		if (h->a[k].priority >= h->a[j].priority) break;
		swap(h->a, k, j);
		k = j;
	}
}

void insert(HEAP* h, int ID, int duration, int priority)
{
	int x = ++h->N;
	NODE* tmp = new NODE;
	tmp->ID = ID;
	tmp->duration = duration;
	tmp->priority = priority;

	if (isFull(h)) {
		cout << "Priority queue is full";
		return;
	}
	h->a[x] = tmp;
	swim(h, h->N);
}

int deleteMax(HEAP* h)
{
	NODE max;
	if (isEmpty(h))
		return -1;
	max = h->a[1];
	h->a[1] = h->a[h->N--];
	sink(h, 1);
	return max.ID;
}

int main()
{
	int MAX = 10;
	HEAP* h;
	h = initialize(MAX);

	insert(h,1,5,5);
	insert(h,2,4,3);
	insert(h,3,6,2);

	displayHeapArray(h);
	displayHeapTree(h);
}