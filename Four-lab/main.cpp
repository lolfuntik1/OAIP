#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Структура для узла двусвязной очереди
struct Node {
    int data;           // Данные узла
    Node* prev;         // Указатель на предыдущий узел
    Node* next;         // Указатель на следующий узел
};

// Класс для двусвязной очереди
class Map {
private:
    Node* front;        // Указатель на начало очереди
    Node* rear;         // Указатель на конец очереди
public:
    Map();
    void push_front(int value); // Добавление элемента в начало очереди   
    void push_back(int value); // Добавление элемента в конец очереди 
    void pop_front(); // Удаление элемента с начала очереди 
    void pop_back(); // Удаление элемента с конца очереди 
    void clear(); // Очистка очереди
    void sort(); // Сортировка очереди (сортировка выбором)
    void createAndFillRandom(int count); // Создание и заполнение очереди случайными элементами
    void display(); // Вывод очереди с начала и с конца
    void transferToNewList(); // Перенос элементов между вершиной и максимальным элементом в новый список
};

int main() {
    Map queue;

    while (true) {
        int choice, value;

        cout << "\nВыберите действие:" << endl
            << "1. Создать и заполнить случайными значениями" << endl
            << "2. Отобразить содержимое очереди" << endl
            << "3. Сортировать содержимое очереди" << endl
            << "4. Очистить очередь" << endl
            << "5. Удалить элемент с начала очереди" << endl
            << "6. Удалить элемент с конца очереди" << endl
            << "7. Добавить элемент в начало очереди" << endl
            << "8. Добавить элемент в конец очереди" << endl
            << "9. Перенос элементов между вершиной и максимальным элементом" << endl
            << "0. Выход" << endl
            << "Введите номер выбранного действия: ";
        
        cin >> choice; cout << endl;

        switch (choice) {
        case 1:
            cout << "Введите количество случайных элементов: ";
            cin >> value;
            queue.createAndFillRandom(value);
            break;
        case 2:
            queue.display();
            break;
        case 3:
            queue.sort();
            break;
        case 4:
            queue.clear();
            break;
        case 5:
            queue.pop_front();
            break;
        case 6:
            queue.pop_back();
            break;
        case 7:
            cout << "Введите значение элемента: ";
            cin >> value;
            queue.push_front(value);
            break;
        case 8:
            cout << "Введите значение элемента: ";
            cin >> value;
            queue.push_back(value);
            break;
        case 9:
            queue.transferToNewList();
            break;
        case 0:
            cout << "Программа завершена." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    }
}

Map::Map() {
    front = nullptr;
    rear = nullptr;
}

// Добавление элемента в начало очереди
void Map::push_front(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (front == nullptr) {
        front = rear = newNode;
    }
    else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }

    cout << "Элемент " << value << " успешно добавлен в начало очереди." << endl;
}

// Добавление элемента в конец очереди
void Map::push_back(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newNode;
    }
    else {
        newNode->prev = rear;
        rear->next = newNode;
        rear = newNode;
    }

    cout << "Элемент " << value << " успешно добавлен в конец очереди." << endl;
}

// Удаление элемента с начала очереди
void Map::pop_front() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    Node* temp = front;

    if (front == rear) {
        front = rear = nullptr;
    }
    else {
        front = front->next;
        front->prev = nullptr;
    }

    int value = temp->data;
    delete temp;

    cout << "Элемент " << value << " успешно удален из начала очереди." << endl;
}

// Удаление элемента с конца очереди
void Map::pop_back() {
    if (rear == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    Node* temp = rear;

    if (front == rear) {
        front = rear = nullptr;
    }
    else {
        rear = rear->prev;
        rear->next = nullptr;
    }

    int value = temp->data;
    delete temp;

    cout << "Элемент " << value << " успешно удален из конца очереди." << endl;
}

// Очистка очереди
void Map::clear() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    cout << "Очередь успешно очищена." << endl;
}

// Сортировка очереди (сортировка выбором)
void Map::sort() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    Node* i = front;
    while (i != nullptr) {
        Node* min = i;
        Node* j = i->next;
        while (j != nullptr) {
            if (j->data < min->data) {
                min = j;
            }
            j = j->next;
        }
        if (min != i) {
            int temp = min->data;
            min->data = i->data;
            i->data = temp;
        }
        i = i->next;
    }

    cout << "Очередь успешно отсортирована." << endl;
}

// Создание и заполнение очереди случайными элементами
void Map::createAndFillRandom(int count) {
    srand(time(0)); // Инициализация генератора случайных чисел

    for (int i = 0; i < count; i++) {
        int value = rand() % 100; // Генерация случайного числа от 0 до 99
        push_back(value);
    }

    cout << "Очередь успешно создана и заполнена " << count << " случайными элементами." << endl;
}

// Вывод очереди с начала и с конца
void Map::display() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    Node* current = front;
    cout << "Очередь с начала: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }

    cout << endl;

    current = rear;
    cout << "Очередь с конца: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->prev;
    }

    cout << endl;
}

// Перенос элементов между вершиной и максимальным элементом в новый список
void Map::transferToNewList() {
    if (front == nullptr) {
        cout << "Очередь пуста." << endl;
        return;
    }

    Node* maxNode = front;
    Node* current = front;
    Node* head = front;

    while (current != nullptr) {
        if (current->data > maxNode->data) {
            maxNode = current;
        }
        current = current->next;
    }

    Map newList;
    current = front;
    current = current->next;

    while (current != nullptr) {
        if (current->data == maxNode->data) {
            break;
        } 

        newList.push_back(current->data);
        current = current->next;
    }

    clear(); // Очищаем исходную очередь

    current = newList.front;

    while (current != nullptr) {
        push_back(current->data); // Добавляем элементы из новой очереди обратно в исходную очередь
        current = current->next;
    }

    cout << "Элементы между вершиной и максимальным элементом перенесены в новую очередь." << endl;
}