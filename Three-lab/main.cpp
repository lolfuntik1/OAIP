#include <iostream>

using namespace std;

// Структура для представления узла односвязного списка
struct Node {
    int data;         
    Node* next;        

    Node(int data, Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }
};

// Класс для реализации односвязной очереди
class Queue {
private:
    Node* front;     // Указатель на первый элемент
    Node* rear;      // Указатель на последний элемент

public:
    Queue();

    void push_back(int data); // Добавление элемента в конец очереди
    void push_front(int data);
    void pop_front(); // Удаление элемента из начала очереди
    void display(); // Вывод содержимого очереди
    void clear(); // Очистка очереди
    void sort(); // Сортировка очереди методом пузырька
    void addElement(int data); // Добавление элемента в очередь
    void transferElements(); // Перенос элементов между вершиной и максимальным элементом в новую очередь
};

int main() {
    Queue queue;

    while (true) {
        int data;
        int choice;

        cout << "\nВыберите действие:" << endl
            << "1. Создание и заполнение очереди" << endl
            << "2. Вывод содержимого очереди" << endl
            << "3. Очистка очереди" << endl
            << "4. Сортировка очереди" << endl
            << "5. Добавление элемента в очередь" << endl
            << "6. Перенос элементов между вершиной и максимальным элементом" << endl
            << "7. Добавление элемента вначало" << endl
            << "0. Выход" << endl
            << "Введите номер выбранного действия: ";

        cin >> choice; cout << endl;

        switch (choice) {
        case 1:
            cout << "Введите количество элементов: ";
            int numElements;
            cin >> numElements;
            for (int i = 0; i < numElements; i++) {
                cout << "Введите элемент " << i + 1 << ": ";
                cin >> data;
                queue.push_back(data);
            }
            cout << "Очередь создана и заполнена." << endl;
            break;

        case 2:
            queue.display();
            break;

        case 3:
            queue.clear();
            break;

        case 4:
            queue.sort();
            break;

        case 5:
            cout << "Введите элемент для добавления: ";
            cin >> data;
            queue.addElement(data);
            break;

        case 6:
            queue.transferElements();
            break;

        case 7:
            cout << "Введите элемент для добавления: ";
            cin >> data;
            queue.push_front(data);
            break;

        case 0:
            cout << "Всего хорошего." << endl;
            return 0;

        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    }
}

Queue::Queue() {
    front = nullptr;
    rear = nullptr;
}

// Добавление элемента в конец очереди
void Queue::push_back(int data) {
    Node* newNode = new Node(data);
    if (rear == nullptr) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

void Queue::push_front(int data) {
    front = new Node(data, front);
}

// Удаление элемента из начала очереди
void Queue::pop_front() {
    if (front == nullptr)
        return;
    Node* temp = front;

    front = front->next;
    
    if (front == nullptr)
        rear = nullptr;
    delete temp;
}

// Вывод содержимого очереди
void Queue::display() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }
    Node* temp = front;
    cout << "Содержимое очереди: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Очистка очереди
void Queue::clear() {
    while (front != nullptr)
        pop_front();
    cout << "Очередь очищена." << endl;
}

// Сортировка очереди методом пузырька
void Queue::sort() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }
    bool swapped;

    do {
        swapped = false;
        Node* prev = nullptr;
        Node* curr = front;
        Node* next = front->next;
        while (next != nullptr) {
            if (curr->data > next->data) {
                swapped = true;
                if (prev != nullptr) {
                    prev->next = next;
                }
                else {
                    front = next;
                }
                curr->next = next->next;
                next->next = curr;
                Node* temp = next;
                next = curr;
                curr = temp;
            }
            prev = curr;
            curr = next;
            next = next->next;
        }
        rear = curr;

    } while (swapped);
    cout << "Очередь отсортирована." << endl;
}

// Добавление элемента в очередь
void Queue::addElement(int data) {
    push_back(data);
    cout << "Элемент добавлен в очередь." << endl;
}

// Перенос элементов между вершиной и максимальным элементом в новую очередь
void Queue::transferElements() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    int maxElement = front->data;
    Node* temp = front;

    while (temp != nullptr) {
        if (temp->data > maxElement) {
            maxElement = temp->data;
        }
        temp = temp->next;
    }

    Queue newQueue;
    temp = front;
    temp = temp->next;

    while (temp != nullptr) {
        if (temp->data == maxElement) {
            break;
        }
        newQueue.push_back(temp->data);
        temp = temp->next;
    }

    clear(); // Очищаем исходную очередь

    temp = newQueue.front;

    while (temp != nullptr) {
        push_back(temp->data); // Добавляем элементы из новой очереди обратно в исходную очередь
        temp = temp->next;
    }

    cout << "Элементы между вершиной и максимальным элементом перенесены в новую очередь." << endl;
}