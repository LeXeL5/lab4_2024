#include <iostream>
using namespace std;

void menu() {
	cout << "(0) shutdown program" << endl;
	cout << "(1) add" << endl;
	cout << "(2) insert" << endl;
	cout << "(3) removeAt" << endl;
	cout << "(4) elementAt" << endl;
	cout << "(5) count" << endl;
	cout << "(6) regionOutputByPopulation" << endl;
	cout << "(7) removeCitiesByRegion" << endl;
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
	void toLast() {
		if (!size) return;
		current = tail;
		currentIndex = count() - 1;
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
		if ((currentIndex - index) > index) {
			toFirst();
		}
		if ((count() - 1 - index) < (index - currentIndex)) {
			toLast();
		}
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
	Node<T>* getCurrent(int index) {
		currentTo(index);
		return current;
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
void regionOutputByPopulation(List<city>& list) {
	struct region {
		string name = "";
		int population = 0;
	};
	List<region> regionList;
	for (int i = 0; i < list.count(); i++) {
		bool isInRegionList = false;
		for (int t = 0; t < regionList.count(); t++) {
			if (list.elementAt(i).region == regionList.elementAt(t).name) {
				region  temp;
				temp.population = regionList.elementAt(t).population + list.elementAt(i).population;
				temp.name = regionList.elementAt(t).name;
				regionList.add(temp);
				regionList.removeAt(t);
				isInRegionList = true;
				break;
			}
		}
		if (!isInRegionList) {
			region newRegion;
			newRegion.name = list.elementAt(i).region;
			newRegion.population = list.elementAt(i).population;
			regionList.add(newRegion);
		}
	}
	for (int i = 0; i < regionList.count() - 1; i++) {
		for (int t = 0; t < regionList.count() - i - 1; t++) {
			if (regionList.elementAt(t).population < regionList.elementAt(t + 1).population) {
				regionList.insert(t, regionList.elementAt(t + 1));
				regionList.removeAt(t + 2);
			}
		}
	}
	cout << "Region:\t\tPopulation:" << endl;
	for (int i = 0; i < regionList.count(); i++) {
		cout << regionList.elementAt(i).name << "\t\t" << regionList.elementAt(i).population << endl;
	}
}
void removeCitiesByRegion(string region, List<city>& list) {
	if (!list.count()) return;
	list.toFirst();
	for (int i = 0; i < list.count(); i++) {
		if (list.elementAt(i).region == region) {
			list.removeCurrent();
			i--;
		}
	}
}
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
	string region;
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
			regionOutputByPopulation(list);
			break;
		}
		case (7): {
			cout << "Region: ";
			cin >> region;
			removeCitiesByRegion(region, list);
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
