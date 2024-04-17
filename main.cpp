#include <iostream>
using namespace std;

void menu() {
	cout << "(0) shutdown program" << endl;
	cout << "(1) add" << endl;
	cout << "(2) insert" << endl;
	cout << "(3) removeAt" << endl;
	cout << "(4) elementAt" << endl;
	cout << "(5) count" << endl;
	cout << "(6) " << endl;
	cout << "(7) " << endl;
	cout << "(8) clear" << endl;
}
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
	void toFirst() {
		if (!size) return;
		current = head;
		currentIndex = 0;
	}
	void toNext() {
		if (!size) return;
		current = current->next;
		currentIndex++;
	}
	void toPrev() {
		if (!size) return;
		current = current->prev;
		currentIndex--;
	}
	void currentTo(int index) {
		if (!size) return;
		while (index > currentIndex) {
			toNext();
		}
		while (index < currentIndex) {
			toPrev();
		}
	}
	void removeCurrent() {
		if (!size) return;
		Node<T>* delNode = current;
		if ((delNode != head) and (delNode != tail)) {
			delNode->prev->next = delNode->next;
			delNode->next->prev = delNode->prev;
			current = current->next;
		}
		if (delNode == head) {
			head = delNode->next;
			if (delNode->next != nullptr) {
				delNode->next->prev = nullptr;
				current = current->next;
			}
		}
		if (delNode == tail) {
			tail = delNode->prev;
			if (delNode->prev != nullptr) {
				delNode->prev->next = nullptr;
				toPrev();
			}
		}
		delete delNode;
		size--;
		if (!size) current = nullptr;
	}
	void insertBeforeCurrent(T data) {
		if (!size) return;
		Node<T>* newNode = new Node<T>;
		size++;
		currentIndex++;
		newNode->data = data;
		newNode->next = current;
		newNode->prev = current->prev;
		if (current->prev != nullptr) current->prev->next = newNode;
		current->prev = newNode;
		if (current == head) { head = newNode; }
	}

	void add(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
		if (!size) {
			currentIndex = 0;
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
		if ((!size) or (index == size)) {
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
		for (int i = size; i > 0; i--) {
			removeCurrent();
		}
	}
};
void cityCout(city data) {
	cout << "      Name: " << data.name << endl;
	cout << "    Region: " << data.region << endl;
	cout << "Population: " << data.population << endl;
}
city cityCin() {
	city city;
	cout << "      Name: ";
	cin >> city.name;
	cout << "    Region: ";
	cin >> city.region;
	cout << "Population: ";
	cin >> city.population;
	return city;
}
int indexCin(int size) {
	//if (!size) return 0;
	int index;
	do {
		cout << "Index: ";
		cin >> index;
	} while ((index < 0) or (index >= size));
	return index;
}

void main() {
	List<city> list;
	int choice = 0;
	int index = 0;
	while (true) {
		system("cls");
		menu();
		cout << endl;
		cout << "Choice: ";
		cin >> choice;
		switch (choice)
		{
		case (0): {
			return;
		}
		case (1): {
			list.add(cityCin());
			break;
		}
		case (2): {
			index = indexCin(list.count() + 1);
			list.insert(index, cityCin());
			break;
		}
		case (3): {
			if (list.count()) {
				index = indexCin(list.count());
				list.removeAt(index);
			}
			break;
		}
		case (4): {
			if (list.count()) {
				index = indexCin(list.count());
				cityCout(list.elementAt(index));
			}
			break;
		}
		case (5): {
			cout << "Number of cities: " << list.count() << endl;
			break;
		}
		case (6): {

			break;
		}
		case (7): {

			break;
		}
		case (8): {
			list.clear();
			break;
		}
		default: {
			cout << "Unknown command, try again" << endl;
			break;
		}
		}
		system("pause");
	}
}