#include <iostream>

#include <vector>
#include <iomanip>      // setw() для форматирования

using namespace std;

// Определение узла дерева
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

/* ************************************ */

// выводит значения узлов дерева в порядке возрастания
void printInOrder(Node* node, int depth = 0, char branch = ' ') {
    if (node == NULL) {
        return;
    }

    printInOrder(node->right, depth + 1, '|');
    cout << setw(depth * 4) << branch << node->data << endl;
    printInOrder(node->left, depth + 1, '|');
}

// выводит значения узлов дерева в прямом порядке: сначала значение корневого узла, затем значения всех его левых поддеревьев, а затем значения всех его правых поддеревьев
void printPreOrder(Node* node, int depth = 0, char branch = ' ') {
    if (node == NULL) {
        return;
    }

    cout << setw(depth * 4) << branch << node->data << endl;

    printPreOrder(node->right, depth + 1, '|');
    printPreOrder(node->left, depth + 1, '|');
}

// выводит значения узлов дерева в обратном порядке: сначала значения всех левых поддеревьев, затем значения всех правых поддеревьев и в конце значение корневого узла
void printPostOrder(Node* node, int depth = 0, char branch = ' ') {
    if (node == NULL) {
        return;
    }

    printPostOrder(node->right, depth + 1, '|');
    printPostOrder(node->left, depth + 1, '|');

    cout << setw(depth * 4) << branch << node->data << endl;
}

Node* insert(Node* root, int value); // Функция для добавления узла в дерево
Node* arrayToBST(vector<int>& arr, int start, int end); // Функция для внесения информации из массива в дерево
int countChars(Node* root); // Функция для подсчета количества символов во всех строках дерева 
void getSortedArray(Node* root, vector<int>& arr); // Функция для получения списка значений дерева в порядке возрастания
Node* balanceBST(Node* root); // Функция для балансировки дерева
Node* search(Node* root, int value); // Функция для поиска узла в дереве
Node* deleteNode(Node* root, int value); // Функция для удаления узла из дерева

/* ************************************ */

int main() {
    Node* root = NULL;
    Node* ads = NULL;   // для search();
    int choice = 1;

    while (choice != 0) {
        cout << "\n\nВыберите действие: \n"
            << "1. [Добавить] узел в дерево\n"
            << "2. [Добавить] массив в дерево\n"
            << "3. Функция для подсчета количества символов во всех строках дерева\n"
            << "4. Получение списка значений дерева в порядке возрастания\n"
            << "5. * [Печать] значений дерева в порядке возрастания\n"
            << "6. * [Печать] значений дерева в прямом порядке\n"
            << "7. * [Печать] значений дерева в обратном порядке\n"
            << "8. Балансировка дерева\n"
            << "9. Поиск узла в дереве\n"
            << "10. Удаление узла из дерева\n"
            << "0. Выход\n\n"
            << "> Введите номер выбранного действия: ";

        cin >> choice; cout << endl;

        vector<int> ar;
        int value = 0;

        cout << "*******************************\n";
        switch(choice) {
            case 1: // добавить узел
                cout << "Введите значение узла, которое нужно добавить: ";
                cin >> value;
                root = insert(root, value);

                cout << "Дерево в порядке возрастания\n";
                printInOrder(root);
                break;

            case 2: // добавить массив
                int numberElements;

                do {
                    cout << "Введите желаемое количество элементов в массиве: ";
                    cin >> numberElements;
                } while (numberElements == 0);

                for (int i=0; i<numberElements; i++) {
                    cout << "Введите " << i+1 << " элемент массива: ";
                    cin >> value;
                    root = insert(root, value);
                }

                cout << "Дерево в порядке возрастания\n";
                printInOrder(root);
                break;

            case 3: // 
                int count;
                count = countChars(root);
                cout << "Во всех строках дерева находится " << count << " символов\n";
                break;

            case 4: // вывести отсортированный массив
                ar.clear();
                getSortedArray(root, ar);
                for (int i=0; i<ar.size(); i++) cout << ar[i] << ' ';
                cout << endl;
                break;

            case 5: // вывести в порядке возрастания
                if (root == NULL) {
                    cout << "Нечего печатать." << endl;
                    continue;
                }

                printInOrder(root);
                break;

            case 6: // вывести в прямом порядке
                if (root == NULL) {
                    cout << "Нечего печатать." << endl;
                    continue;
                }

                printPreOrder(root);
                break;

            case 7: // вывести в обратном порядке
                if (root == NULL) {
                    cout << "Нечего печатать." << endl;
                    continue;
                }

                printPostOrder(root);
                break;

            case 8: // сбалансировать
                root = balanceBST(root);

                cout << "Дерево в порядке возрастания\n";
                printInOrder(root);
                break;

            case 9: // найти
                cout << "Введите значение узла, которое нужно найти: ";
                cin >> value;
                ads = search(root, value);

                if (ads != NULL) {
                    cout << "[YES] Действительно, узел " << ads->data << " есть в дереве" << endl;
                } else {
                    cout << "[NO] Узел не найден" << endl;
                }
                break;

            case 10: // удалить
                cout << "Введите значение узла, которое нужно удалить: ";
                cin >> value;
                root = deleteNode(root, value);

                cout << "Дерево в порядке возрастания\n";
                printInOrder(root);
                break;
        }
        cout << "*******************************";
    }
    return 0;
}

// Функция для добавления узла в дерево
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return new Node(value);
    }

    if (value == root->data) { // проверяем на равенство
        return root; // возвращаем указатель на текущий узел
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}


// Функция для поиска узла в дереве
Node* search(Node* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search(root->left, value);
    }

    return search(root->right, value);
}



// Функция для удаления узла из дерева
Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Найден узел, который нужно удалить
        if (root->left == NULL) {
            Node* temp = root->right;

            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;

            delete root;
            return temp;
        }

        // Если у узла есть оба потомка
        Node* temp = root->right;

        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Функция для внесения информации из массива в дерево
Node* arrayToBST(vector<int>& arr, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;

    Node* root = new Node(arr[mid]);

    root->left = arrayToBST(arr, start, mid - 1);
    root->right = arrayToBST(arr, mid + 1, end);

    return root;
}

// Функция для получения списка значений дерева в порядке возрастания
void getSortedArray(Node* root, vector<int>& arr) {
    if (root == NULL) {
        return;
    }
    getSortedArray(root->left, arr);
    arr.push_back(root->data);
    getSortedArray(root->right, arr);
}

// Функция для балансировки дерева
Node* balanceBST(Node* root) {
    vector<int> arr;
    getSortedArray(root, arr);
    return arrayToBST(arr, 0, arr.size() - 1);
}

int countChars(Node* node) {
    if (node == NULL) {
        return 0;
    }

    int length = std::to_string(node->data).length();
    int sum = length + countChars(node->left) + countChars(node->right);

    return sum;
}