#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <iostream>

template <class T>
struct Node {
    T value;
    Node<T>* next;

    Node() : next(NULL) {}
    Node(T value) : value(value), next(NULL) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* initial;
    Node<T>* iterator;
    int size;

public:
    LinkedList() : initial(NULL), size(0) {}

    int search(T value) {
        begin();
        for (int i = 0; hasNext(); i++) {
            if (next() == value) {
                return i;
            }
        }

        return -1;
    }

    bool remove(T value) {
        int position = search(value);

        if (position >= 0) {
            return remove(position);
        }

        return false;
    }

	bool remove(int position) {
		if (position >= size) return false;

		Node<T>* obsolete = getNode(position);
		if (position == 0) {
			initial = obsolete->next;
		} else {
			Node<T>* previous = getNode(position - 1);
			previous->next = obsolete->next;
		}

		delete obsolete;
		size--;
		return true;
	}

	bool removeFirst() {
		return remove(0);
	}

	bool removeLast() {
		return remove(size - 1);
	}

    bool insert(T value, int position) {
		if (position > size) return false;

        Node<T>* element = new Node<T>(value);
		if (element == NULL) { //Sem memória
			return false;
		}

        if (position == 0) { //Inserção no início requer caso especial
            element->next = initial;
            initial = element;
        } else {
            Node<T>* previous = getNode(position - 1);

            element->next = previous->next;
            previous->next = element;
        }

        size++;
		return true;
    }

    bool append(T value) {
        return insert(value, size);
    }

    bool prepend(T value) {
        return insert(value, 0);
    }

    void begin() {
        iterator = initial;
    }

    bool hasNext() {
        return iterator != NULL;
    }

    T next() {
        T value = iterator->value;
        iterator = iterator->next;
        return value;
    }

    int getSize() {
        return size;
    }

    Node<T>* getNode(int position) {
		if (position > size) return NULL;

        Node<T>* navigator = initial;
        for (int i = 0; i < position; i++) {
            navigator = navigator->next;
        }

        return navigator;
    }

    T get(int position) {
        return getNode(position)->value;
    }
};

template <class T>
std::ostream& operator<<(std::ostream& out, LinkedList<T>& list) {
    out << "{";
    list.begin();
    while (list.hasNext()) {
        out << list.next();

        if (list.hasNext()) {
			out << ", ";
		}
    }
    out << "}";
    return out;
}

#endif // LINKED_LIST_H_INCLUDED
