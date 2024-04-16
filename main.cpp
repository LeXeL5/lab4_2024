#include <iostream>
using namespace std;

struct city {
	string name = "";
	string region = "";
	int population = 0;
};

template <typename T>
struct Node {
	T data;
	Node* next = nullptr;
	Node* prev = nullptr;
};

template <typename T>
struct List {
	int size = 0;
	int currentIndex = 0;
	Node<T>* current = nullptr;
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	bool isEmpty() {
		return !size;
	}
	void toFirst() {
		if (isEmpty()) return;
		current = head;
		currentIndex = 0;
	}
	void toNext() {
		if (isEmpty()) return;
		current = current->next;
		currentIndex++;
	}
	void toPrev() {
		if (isEmpty()) return;
		current = current->prev;
		currentIndex--;
	}
	void currentTo(int index) {
		if (isEmpty()) return;
		while (index > currentIndex) {
			toPrev();
		}
		while (index < currentIndex) {
			toNext();
		}
	}
	void removeCurrent() {
		if (isEmpty()) return;
		if (current == head) {
			head = current->next;
			if (current->next != nullptr) current->next->prev = nullptr;
		}
		else if (current == tail) {
			tail = current->prev;
			if (current->prev != nullptr) current->prev->next = nullptr;
			currentIndex--;
		}
		else {
			current->prev->next = current->next;
			current->next->prev = current->prev;
		}
		Node<T>* temp = current->next;
		delete current;
		current = temp;
		size--;
	}
	void insertBeforeCurrent(T data) {
		if (isEmpty()) return;
		Node<T>* newNode = new Node<T>;
		size++;
		currentIndex++;
		newNode->data = data;
		newNode->next = current;
		newNode->prev = current->prev;
		if (current == head) { head = newNode; }
	}

	void add(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
		if (isEmpty()) {
			current = newNode;
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		size++;
	}
	void insert(int index, T data) {
		if ((isEmpty()) or (index == size)) {
			add(data);
		}
		else {
			currentTo(index);
			insertBeforeCurrent(data);
		}
	}
	void removeAt(int index) {
		currentTo(index);
		removeCurrent();
	}
	T elementAt(int index) {
		currentTo(index);
		return current->data;
	}
	int count() {
		return size;
	}
	void clear() {
		if (isEmpty()) return;
		toFirst();
		for (int i = size; i > 0; i--) {
			removeCurrent();
		}
	}
};

void cityOutput(city data) {
	cout << "Name: " << data.name << endl;
	cout << "Region: " << data.region << endl;
	cout << "Population: " << data.population << endl;
}
city cityInput() {
	city city;
	cout << "Name: ";
	cin >> city.name;
	cout << endl;
	cout << "Region: ";
	cin >> city.region;
	cout << endl;
	cout << "Population: ";
	cin >> city.population;
	cout << endl;
	return city;
}

void main() {
	int index = 0;
	List<city> list;
	list.add(cityInput());
	cityOutput(list.elementAt(index));
}