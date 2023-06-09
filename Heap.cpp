#include <iostream>
#include <vector>

template <class TKey, class TValue>
class Heap {
private:
	struct Data {
		TKey key = TKey();
		TValue value = TValue();
	};

	std::vector<Data> data;

	int parent(int i) {
		return (i - 1) / 2;
	}
	int leftChild(int i) {
		return (2 * i + 1);
	}
	int rightChild(int i) {
		return (2 * i + 2);
	}
	int child(int i, int k) {
		return 2 * i + k;
	}
	int minChild(int i) {
		int left = leftChild(i);
		int right = rightChild(i);

		if (right >= data.size()) {
			return left;
		}
		else {
			return (data[left].key < data[right].key) ? left : right;
		}
	}
	void diving(int i, int size) {
		int largest = i;
		for (int k = 1; k <= 2; k++) {
			int childIndex = child(i, k);
			if (childIndex < size && data[childIndex].key < data[largest].key) {
				largest = childIndex;
			}
		}

		if (largest != i) {
			std::swap(data[i], data[largest]);
			diving(largest, size);
		}
	}

	void emerson(int i) {
		int j1 = i;
		int j2 = parent(i);
		while (j2 != -1 && data[j2].key > data[j1].key) {
			std::swap(data[j1], data[j2]);
			j1 = j2;
			j2 = parent(j1);
		}
	}

public:
	Heap() {}
	Heap(const std::vector<Data>& temp) {
		data.resize(temp.size());
		for (int count = 0; count < temp.size(); ++count) {
			data[count].key = temp[count].key;
			data[count].value = temp[count].value;
		}
		make_heap();
	}

	bool isEmpty() {
		return data.empty();
	}
	int size() {
		return data.size();
	}
	void insert(TKey key, TValue value) {
		int index = findIndex(key);
		if (index != -1) {
			data[index].value = value;
			return;
		}
		data.push_back({ key,value });
		emerson(data.size() - 1);
	}
	void remove(TKey key) {
		int index = findIndex(key);
		if (index == -1)
			throw std::exception("ERROR: u can't remove element from heap if he is out");
		Data temp = data[index];
		data[index] = data[data.size() - 1];
		data[data.size() - 1] = temp;
		if (index != 0 && data[index].key > data[(index - 1) / 2].key)
			emerson(index);
		else diving(index);
	}
	int findIndex(TKey key) {
		for (int count = 0; count < data.size(); ++count) {
			if (data[count].key == key) {
				return count;
			}
		}
		return -1; // Элемент не найден
	}
	void print() {
		if (isEmpty()) {
			std::cout << "Heap is empty!" << std::endl;
			return;
		}

		int level = 0;
		int count = 0;
		int numNodes = 1;

		while (count < data.size()) {
			std::cout << "Level " << level << ": ";

			for (int i = count; i < count + numNodes && i < data.size(); ++i) {
				std::cout << "(" << data[i].key << ", " << data[i].value << ") ";

				if (i != count + numNodes - 1) {
					std::cout << "-> ";
				}
			}

			std::cout << std::endl;
			count += numNodes;
			numNodes *= 2;
			++level;
		}
	}
	void make_heap() {
		int size = data.size();
		for (int count = size / 2; count >= 0; --count)
			diving(count, size);
	}
	void heap_sort() {
		make_heap();
		int heapSize = data.size();
		for (int count = heapSize - 1; count >= 0; count--) {
			std::swap(data[0], data[count]);
			diving(0, count);
		}
	}
	void printArr() {
		for (int count = 0; count < data.size(); ++count) {
			std::cout << data[count].key << " ";
		}
		std::cout << std::endl;
	}
};

int main() {
	Heap<int, int> h({{1,1},{3,3},{2,1},{6,1},{4,1},{5,1},{8,1},{9,1},{13,1} });
	h.print();
	h.printArr();
	h.heap_sort();
	h.printArr();
}
