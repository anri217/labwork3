#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

template <typename T>
class List
{
public:
	List() { size = 0; }
	void push_back(T newvalue) {
		Node<T>* newNode = new Node<T>(newvalue);
		if (firstNode == nullptr) {
			firstNode = newNode;
			lastNode = newNode;
			lastNode->setPNext(firstNode);
		}
		else {
			lastNode->setPNext(newNode);
			newNode->setPNext(firstNode);
			lastNode = newNode;
		}
		++size;
	}
	int length() { return size; }
	bool empty() {
		if (size == 0) return true;
		else return false;
	}
	T& operator [](int val) {
		int i = 0;
		Node<T>* rNode = firstNode;
		while (i < val) {
			rNode = rNode->pnext();
			++i;
		}
		return rNode->getData();
	}
	~List<T>() {
		for (size_t i = 0; i < size; ++i) {
			Node<T>* newN = firstNode;
			delete firstNode;
			firstNode = newN;
		}
	}
private:
	template <typename T>
	class Node
	{
	public:
		Node(T value) { data = value; }
		void setData(T value) { data = value; }
		void setPNext(Node<T>* value) { next = value; }
		T& getData() { return data; }
		Node<T>* pnext() { return next; }
	private:
		Node<T>* next;
		T data;
	};
	Node<T>* firstNode;
	Node<T>* lastNode;
	int size = 0;
};

template <typename T>
void qSort3(List <T> &lis, int left, int right) {
	if (right <= left)
		return;
	T m = lis[(right + left) >> 1];
	swap(lis[right], lis[(right + left) >> 1]);
	int l = left;
	int r = right;
	int i = l;
	int j = r - 1;
	int p = l - 1;
	int q = r;
	while (i <= j) {
		while (lis[i] < m && i < r)
			i++;
		while (lis[j] > m && j > l)
			j--;
		if (i >= j)
			break;
		swap(lis[i], lis[j]);
		if (lis[i] == m) {
			p++;
			swap(lis[p], lis[i]);
		}
		i++;
		if (lis[j] == m) {
			q--;
			swap(lis[q], lis[j]);
		}
		j--;
	}
	swap(lis[i], lis[r]);
	j = i - 1;
	i++;
	for (int k = l; k <= p; k++, j--)
		swap(lis[k], lis[j]);
	for (int k = r - 1; k >= q; k--, i++)
		swap(lis[k], lis[i]);
	qSort3(lis, l, j);
	qSort3(lis, i, r);
}

void randomList(List<int>& lis, int num)
{
	int i = lis.length();
	while (i < num) {
		lis.push_back(rand());
		++i;
	}
}

void almostSortList(List<int>& lis, int num)
{
	randomList(lis, num);
	bool good = true;
	for (size_t i = 0; i < lis.length() - 1; ++i) {
		if (lis[i] > lis[i + 1]) {
			good = false;
			break;
		}
		else good = true;
	}
	if (!good) {
		qSort3(lis, lis[0], lis[lis.length() - 1]);
	}
	int n = lis[(lis.length() / 2) + 1];
	lis[lis.length() / 2] = lis[(lis.length() / 2) + 1];
	lis[lis.length() / 2] = n;
}

void reverseSortList(List<int>& lis, int num)
{
	randomList(lis, num); bool good = true;
	for (size_t i = 0; i < lis.length() - 1; ++i) {
		if (lis[i] > lis[i + 1]) {
			good = false;
			break;
		}
		else good = true;
	}
	if (!good) {
		qSort3(lis, lis[0], lis[lis.length() - 1]);
	}
	for (size_t i = 0; i < lis.length() / 2; ++i) {
		int num = lis[i];
		lis[i] = lis[lis.length() - 1 - i];
		lis[lis.length() - 1 - i] = num;
	}
}

double timer(List<int>& lis)
{
	double time = 0;
	time -= clock();
	qSort3(lis, 0, lis.length() - 1);
	time += clock();
	return time / CLOCKS_PER_SEC;
}

void sortingTime(List<int>& lis, int i)
{
	randomList(lis, i);
	cout << "Sorting time of random list, list size " << i << ": " << timer(lis) << endl;
	almostSortList(lis, i);
	cout << "Sorting time of almost sort list, list size " << i << ": " << timer(lis) << endl;
	reverseSortList(lis, i);
	cout << "Sorting time of reverse sort list, list size " << i << ": " << timer(lis) << endl;
}

int main()
{
	List <int> lis;

	sortingTime(lis, 1000);
	cout << endl << endl;
	sortingTime(lis, 5000);
	cout << endl << endl;
	sortingTime(lis, 10000);

	system("pause");
	return 0;
}