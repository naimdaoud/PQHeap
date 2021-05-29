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

void insert(HEAP* h, int ID, int duration, int priority)
{
	int x = ++h->N;
	if (isFull(h)) {
		cout << "Priority queue is full";
		return;
	}
	h->a[x].ID = ID ;
	h->a[x].duration = duration;
	h->a[x].priority = priority;
	swim(h, h->N);
}

void sinkMinHeap(HEAP* h, int k) {
	while (2 * k <= h->N) {
		int j = 2 * k;
		if (j < h->N && h->a[j].priority > h->a[j + 1].priority) j++;
		if (h->a[k].priority <= h->a[j].priority) break;
		swap(h->a, k, j);
		k = j;
	}
}

NODE deleteMin(HEAP* h)
{
	NODE min;
	/*if (isEmpty(h))
		return NULL;*/
	min = h->a[1];
	h->a[1] = h->a[h->N--];
	sinkMinHeap(h, 1);
	return min;
}

void heapsort3(HEAP* h, NODE* a, int n) {
	for (int i = 0; i < n; i++)
		a[i] = deleteMin(h);
}

int GetDuration(HEAP* h, NODE* a, int ID) { // Use heapsort and then calculate the duration.
	int x = 0;
	int size = h->N;
	int total = 0;
	NODE* tmp = new NODE[h->N];
	heapsort3(h, a, h->N);
	for (int i = 0; i <= size; i++) {
		while (x != ID) {
			total = total + a[i].duration;
			x = a[i].ID;
			break;
		}
	}
	return total;
}

int main()
{
	int MAX = 10;
	NODE* min = new NODE[6];
	HEAP* h;
	int ID = 30;
	h = initialize(MAX);

	insert(h, 100, 3, 2);
	insert(h, 40 ,4 ,5);
	insert(h, 20, 2, 1);
	insert(h, 30, 5, 4);
	insert(h, 200, 4, 5);
	insert(h, 50, 4, 3);

	displayHeapArray(h);
	displayHeapTree(h);
	 
	cout << "The duration to complete the task with ID " << ID << " is: " << GetDuration(h, min, ID) << endl;

}