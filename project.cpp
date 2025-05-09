#include <iostream>
#include <memory>  // For smart pointers
#include <algorithm>  // For std::sort

using namespace std;

const int MAX_SIZE = 100;

class Stack {
private:
    int arr[MAX_SIZE];
    int top;
public:
    Stack() { top = -1; }

    void push(int element) {
        if (top >= MAX_SIZE - 1) {
            cout << "Stack Overflow!\n";
        } else {
            arr[++top] = element;
            cout << element << " pushed to stack.\n";
        }
    }

    void pop() {
        if (top == -1) {
            cout << "Stack Underflow!\n";
        } else {
            cout << arr[top--] << " popped from stack.\n";
        }
    }

    void peek() {
        if (top == -1) {
            cout << "Stack is empty.\n";
        } else {
            cout << "Top element is " << arr[top] << endl;
        }
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_SIZE - 1;
    }

    void display() {
        if (top == -1) {
            cout << "Stack is empty.\n";
        } else {
            cout << "Stack contents: ";
            for (int i = top; i >= 0; i--) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
};

class Queue {
private:
    int arr[MAX_SIZE];
    int front, rear;
public:
    Queue() { front = -1; rear = -1; }

    void enqueue(int element) {
        if (rear == MAX_SIZE - 1) {
            cout << "Queue is full!\n";
        } else {
            if (front == -1) front = 0;  // First element insertion
            arr[++rear] = element;
            cout << element << " enqueued to queue.\n";
        }
    }

    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue Underflow!\n";
        } else {
            cout << arr[front++] << " dequeued from queue.\n";
        }
    }

    void frontElement() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty.\n";
        } else {
            cout << "Front element is " << arr[front] << endl;
        }
    }

    void rearElement() {
        if (rear == -1) {
            cout << "Queue is empty.\n";
        } else {
            cout << "Rear element is " << arr[rear] << endl;
        }
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    bool isFull() {
        return rear == MAX_SIZE - 1;
    }

    void display() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty.\n";
        } else {
            cout << "Queue contents: ";
            for (int i = front; i <= rear; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
};

class LinkedList {
private:
    struct Node {
        int data;
        std::unique_ptr<Node> next;  // Smart pointer to handle dynamic memory
    };

    std::unique_ptr<Node> head;

public:
    LinkedList() : head(nullptr) {}

    void insertAtEnd(int data) {
        std::unique_ptr<Node> newNode = std::make_unique<Node>();
        newNode->data = data;
        newNode->next = nullptr;

        if (!head) {
            head = std::move(newNode);
        } else {
            Node* temp = head.get();
            while (temp->next) {
                temp = temp->next.get();
            }
            temp->next = std::move(newNode);
        }
        cout << data << " inserted at the end.\n";
    }

    void display() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head.get();
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next.get();
        }
        cout << endl;
    }

    void reverse() {
        std::unique_ptr<Node> prev = nullptr;
        Node* curr = head.get();
        Node* next = nullptr;

        while (curr) {
            next = curr->next.release();  // Release ownership of next node
            curr->next.reset(prev.release());  // Reverse the link and move prev
            prev.reset(curr);
            curr = next;
        }
        head.reset(prev.release());  // Set head to the new first node
        cout << "List reversed.\n";
    }

    void search(int key) {
        Node* temp = head.get();
        while (temp) {
            if (temp->data == key) {
                cout << "Element " << key << " found in the list.\n";
                return;
            }
            temp = temp->next.get();
        }
        cout << "Element " << key << " not found in the list.\n";
    }
};

// Array class to handle array operations
class Array {
private:
    int arr[MAX_SIZE];
    int size;

public:
    Array() : size(0) {}

    void traverse() {
        if (size == 0) {
            cout << "Array is empty.\n";
            return;
        }
        cout << "Array elements: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void insert(int index, int value) {
        if (index < 0 || index > size) {
            cout << "Invalid index!\n";
            return;
        }
        for (int i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        size++;
        cout << value << " inserted at index " << index << ".\n";
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!\n";
            return;
        }
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
        cout << "Element at index " << index << " removed.\n";
    }

    void search(int value) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                cout << "Element " << value << " found at index " << i << ".\n";
                return;
            }
        }
        cout << "Element " << value << " not found.\n";
    }

    void update(int index, int newValue) {
        if (index < 0 || index >= size) {
            cout << "Invalid index!\n";
            return;
        }
        arr[index] = newValue;
        cout << "Element at index " << index << " updated to " << newValue << ".\n";
    }

    int getSize() const {
        return size;
    }

    // Sorting Algorithms
    void bubbleSort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        cout << "Array sorted using Bubble Sort.\n";
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

    int partition(int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void mergeSort(int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            mergeSort(low, mid);
            mergeSort(mid + 1, high);
            merge(low, mid, high);
        }
    }

    void merge(int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int left[n1], right[n2];

        for (int i = 0; i < n1; i++) left[i] = arr[low + i];
        for (int i = 0; i < n2; i++) right[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }
        while (i < n1) arr[k++] = left[i++];
        while (j < n2) arr[k++] = right[j++];
    }

    void selectionSort() {
        for (int i = 0; i < size - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            swap(arr[minIdx], arr[i]);
        }
        cout << "Array sorted using Selection Sort.\n";
    }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        cout << "Array sorted using Insertion Sort.\n";
    }
};

int main() {
    Stack s;
    Queue q;
    LinkedList l;
    Array a;
    int choice, value, index;

    while (true) {
        cout << "\nChoose an option:\n";
        cout << "1. Stack Operations\n2. Queue Operations\n3. LinkedList Operations\n4. Array Operations\n0. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:  // Stack operations
                while (true) {
                    cout << "\nStack Operations:\n";
                    cout << "1. Push\n2. Pop\n3. Peek\n4. Display Stack\n5. Exit\n";
                    cin >> choice;
                    switch (choice) {
                        case 1:
                        cout << "Enter element to push: ";
                        cin >> value;
                        s.push(value);
                        break;
                    case 2:
                        s.pop();
                        break;
                    case 3:
                        s.peek();
                        break;
                    case 4:
                        s.display();
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Invalid choice\n";
                }
                if (choice == 5) break;
            }
            break;

        case 2:  // Queue operations
            while (true) {
                cout << "\nQueue Operations:\n";
                cout << "1. Enqueue\n2. Dequeue\n3. Front Element\n4. Rear Element\n5. Display Queue\n6. Exit\n";
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "Enter element to enqueue: ";
                        cin >> value;
                        q.enqueue(value);
                        break;
                    case 2:
                        q.dequeue();
                        break;
                    case 3:
                        q.frontElement();
                        break;
                    case 4:
                        q.rearElement();
                        break;
                    case 5:
                        q.display();
                        break;
                    case 6:
                        break;
                    default:
                        cout << "Invalid choice\n";
                }
                if (choice == 6) break;
            }
            break;

        case 3:  // LinkedList operations
            while (true) {
                cout << "\nLinkedList Operations:\n";
                cout << "1. Insert at End\n2. Display List\n3. Reverse List\n4. Search\n5. Exit\n";
                cin >> choice;
                switch (choice) {
                    case 1:
                        cout << "Enter element to insert: ";
                        cin >> value;
                        l.insertAtEnd(value);
                        break;
                    case 2:
                        l.display();
                        break;
                    case 3:
                        l.reverse();
                        break;
                    case 4:
                        cout << "Enter element to search: ";
                        cin >> value;
                        l.search(value);
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Invalid choice\n";
                }
                if (choice == 5) break;
            }
            break;

        case 4:  // Array operations
            while (true) {
                cout << "\nArray Operations:\n";
                cout << "1. Traverse Array\n2. Insert Element\n3. Remove Element\n4. Search Element\n5. Update Element\n6. Sort Array\n7. Exit\n";
                cin >> choice;
                switch (choice) {
                    case 1:
                        a.traverse();
                        break;
                    case 2:
                        cout << "Enter index and value: ";
                        cin >> index >> value;
                        a.insert(index, value);
                        break;
                    case 3:
                        cout << "Enter index to remove: ";
                        cin >> index;
                        a.remove(index);
                        break;
                    case 4:
                        cout << "Enter element to search: ";
                        cin >> value;
                        a.search(value);
                        break;
                    case 5:
                        cout << "Enter index and new value: ";
                        cin >> index >> value;
                        a.update(index, value);
                        break;
                    case 6:
                        cout << "Choose sorting algorithm:\n";
                        cout << "1. Bubble Sort\n2. Quick Sort\n3. Merge Sort\n4. Selection Sort\n5. Insertion Sort\n";
                        cin >> choice;
                        switch (choice) {
                            case 1:
                                a.bubbleSort();
                                break;
                            case 2:
                                a.quickSort(0, a.getSize() - 1);
                                break;
                            case 3:
                                a.mergeSort(0, a.getSize() - 1);
                                break;
                            case 4:
                                a.selectionSort();
                                break;
                            case 5:
                                a.insertionSort();
                                break;
                            default:
                                cout << "Invalid choice\n";
                        }
                        break;
                    case 7:
                        break;
                    default:
                        cout << "Invalid choice\n";
                }
                if (choice == 7) break;
            }
            break;

        case 0:
            return 0;

        default:
            cout << "Invalid choice\n";
    }
}

return 0;
}
