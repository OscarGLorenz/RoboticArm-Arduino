#ifndef QUEUE_H_
#define QUEUE_H_

template<class T> class Node {
public:
	Node(T param) {
		object = param;
		next = nullptr;
	}
	T object;
	Node<T> * next;
};

template<class T> class Queue {
public:
	Queue() {
		first = nullptr;
		last = nullptr;
		lenght = 0;
	}

	void pushBack(T param) {
		if (first == nullptr) {
			first = new Node<T>(param);
			last = first;
		} else {
			last->next = new Node<T>(param);
			last = last->next;
		}
		lenght++;
	}

	T getFront() {
		return first->object;
	}

	T getBack() {
		return last->object;
	}

	void popFront() {
		if (first != nullptr) {
			if (last != first) {
				Node<T> * aux = first->next;
				free(first);
				first = aux;
			} else {
				free(first);
				first = nullptr;
				last = nullptr;
			}
			lenght--;
		}
	}

	int size() {
		return lenght;
	}

	bool isEmpty() {
		return lenght == 0;
	}
private:
	Node<T> * first;
	Node<T> * last;
	int lenght;
};

#endif
