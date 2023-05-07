#include <iostream>     // для cout и cin
#include <fstream>      // для файлов
#include <cstdio>       // для remove()

using namespace std;

struct Student {    // информация о студенте
    string surname;
    string nameTeam;
    string nameCountry;
    int age;
    int gameNumber;
    int height;
    int weight;
};

/*
ФИО игрока, игровой номер, возраст, рост, вес, наименование страны, название команды
*/

/* ************************************ */
string openFile();
void loadOutFile(Student [], int&, string);   // загрузить записи из файла в массив
void delFile();

void addStudent(Student [], int&);
void viewStudents(Student [], int);
void solveTask(Student [], int);
void saveToFile(Student [], int, string);
void editStudents(Student [], int);

void quickSortByAge(Student [], int, int);
void selectionSort(Student [], int);
Student* searchByKey(Student arr[], int n, int key);

void clearFile(string);

/*
организовать сортировку методами прямого выбора и QuickSort по ключу
организовать поиск по ключу
key = age
Вывести информацию о самой молодой команде.
*/

void nullCount();
/* ************************************ */

int main() {
    Student students[100];
    int count = 0;
    int choice;
    string fileName;
    
    system("open ."); // DEBUG
    
    do {
        cout << endl;
        cout << "1. Open file" << endl;
        cout << "2. Delete file" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                fileName = openFile();
                do {
                    cout << endl;
                    cout << "1. Add profile" << endl;
                    cout << "2. View all profiles" << endl;
                    cout << "3. Solve task" << endl;
                    cout << "4. * Save to file" << endl;
                    cout << "5. * Read from file" << endl;
                    cout << "6. Edit the profile" << endl;
                    cout << "7. Quick Sort" << endl;
                    cout << "8. Selection Sort" << endl;
                    cout << "9. Search by Age" << endl;
                    cout << "10. * Clear file" << endl;
                    cout << "0. Exit" << endl;

                    cout << "Enter your choice: ";
                    cin >> choice;
                    
                    switch (choice) {
                        case 10:
                            clearFile(fileName);
                            break;
                        case 0:
                            cout << "Exiting program..." << endl;
                            break;

                        case 1:
                            addStudent(students, count);
                            break;
                            
                        case 2:
                            if (count == 0) {
                                nullCount();
                            } else {
                                viewStudents(students, count);
                            }
                            break;
                            
                        case 3:
                            if (count == 0) {
                                nullCount();
                            } else {
                                solveTask(students, count);
                            }
                            break;
                            
                        case 4:
                            if (count == 0) {
                                nullCount();
                            } else {
                                saveToFile(students, count, fileName);
                            }
                            break;
                            
                        case 5:
                            loadOutFile(students, count, fileName);
                            break;
                            
                        case 6:
                            if (count == 0) {
                                nullCount();
                            } else {
                                editStudents(students, count);
                            }
                            break;

                        case 7:
                            quickSortByAge(students, 0, count - 1);
                            break;

                        case 8:
                            selectionSort(students, count);
                            break;

                        case 9:
                            int key;
                            cout << "Enter key (age)" << endl;
                            cin >> key;
                            
                            Student* person = searchByKey(students, count, key);
                            if (person != NULL) {
                                cout << "Found: " << person->age << " " << person->surname << endl;
                            } else {
                                cout << "Not found." << endl;
                            }

                            break;
                    }
                } while (choice != 0);
                break;
                
            case 2:
                delFile();
                break;
                
            case 3:
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
        

    } while (choice != 3);
    
}

string openFile() {
    string fileName;
    
    cout << "Enter file name: ";
    cin >> fileName;
    
    fstream file(fileName, ios_base::app);
    
    if (!file.is_open()) {
        cout << "**** file opening error ****" << endl;
        perror("open the file");
    }
    
    cout << "File with name " << fileName << " opened successfully." << endl;
    file.close();
    
    return fileName;
}

void delFile() {
    char fileName[80];
    
    cout << "Enter file name: ";
    cin >> fileName;
    
    if (remove(fileName) == 0) {
        cout << "File is removed successfully." << endl;
    } else {
        perror("remove");
    }
}

void loadOutFile(Student students[], int& count, string fileName) {
    ifstream fin(fileName);
    
    if (!fin.is_open()) {
        cout << "**** file opening error ****" << endl;
        return;
    }
    
    string line;
    
    while (getline(fin, line)) {
        if (line == "#") {
            count++;
            continue;
        }

        students[count].surname = line;

        getline(fin, line);
        students[count].nameTeam = line;

        getline(fin, line);
        students[count].nameCountry = line;

        getline(fin, line);
        students[count].age = stoi(line);

        getline(fin, line);
        students[count].gameNumber = stoi(line);

        getline(fin, line);
        students[count].height = stoi(line);

        getline(fin, line);
        students[count].weight = stoi(line);
    }

    fin.close();
    
    cout << "Successfully." << endl;
}

void addStudent(Student students[], int& count) {
    cout << "Enter surname: ";
    cin >> students[count].surname;
    
    cout << "Enter name your team: ";
    cin.ignore();
    getline(cin, students[count].nameTeam); 
    
    cout << "Enter name your country: ";
    cin >> students[count].nameCountry;
    
    cout << "Enter age: ";
    cin >> students[count].age;

    cout << "Enter game number: ";
    cin >> students[count].gameNumber;

    cout << "Enter height: ";
    cin >> students[count].height;

    cout << "Enter weight: ";
    cin >> students[count].weight;

    count++;
    
    cout << "Successfully." << endl;
}

void viewStudents(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "# " << i+1 << endl;
        cout << "Surname: " << students[i].surname << endl;
        cout << "Name team: " << students[i].nameTeam << endl;
        cout << "Name country: " << students[i].nameCountry << endl;
        cout << "Age: " << students[i].age << endl;
        cout << "Game number: " << students[i].gameNumber << endl;
        cout << "Height: " << students[i].height << endl;
        cout << "Weight: " << students[i].weight << endl;
    }
}

// Вывести информацию о самой молодой команде.
void solveTask(Student students[], int count) {
    int minAge = INT_MAX;
    for (int i = 0; i < count; i++) {
        if (students[i].age < minAge) {
            minAge = students[i].age;
        }
    }
    cout << "The youngest team(s):" << endl;
    for (int i = 0; i < count; i++) {
        if (students[i].age == minAge) {
            cout << students[i].age << " " << students[i].nameTeam << endl;
        }
    }
}

void saveToFile(Student students[], int count, string fileName) {
    ofstream fout(fileName);
    
    if (!fout.is_open()) {
        cout << "**** file opening error ****" << endl;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fout << students[i].surname << endl;
        fout << students[i].nameTeam << endl;
        fout << students[i].nameCountry << endl;
        fout << students[i].age << endl;
        fout << students[i].gameNumber << endl;
        fout << students[i].height << endl;
        fout << students[i].weight << endl;
        fout << "#" << endl;
    }

    fout.close();
    
    cout << "Successfully." << endl;
}

void editStudents(Student students[], int count) {
    string findName;
    
    cout << "Enter surname: ";
    cin >> findName;
    
    for (int i = 0; i < count; i++) {
        if (findName == students[i].surname) {
            cout << "It is okay." << endl;
            
            cout << "Enter surname: ";
            cin >> students[i].surname;
            
            cout << "Enter name team: ";
            cin >> students[i].nameTeam;
            
            cout << "Enter name country: ";
            cin >> students[i].nameCountry;
            
            cout << "Enter student age: ";
            cin >> students[i].age;

            cout << "Enter game number: ";
            cin >> students[i].gameNumber;

            cout << "Enter height: ";
            cin >> students[i].height;

            cout << "Enter weight: ";
            cin >> students[i].weight;
            
            cout << "Successfully." << endl;
            
            return;
        }
    }
    
    cout << "Couldn't find a student with that name :(" << endl;
}

void nullCount() {
    cout << "* I can't do it because there are 0 students loaded." << endl;
}

void quickSortByAge(Student students[], int left, int right) {
    int i = left, j = right;
    int pivot = students[(left + right) / 2].age;
    Student tmp;
    while (i <= j) {
        while (students[i].age < pivot) {
            i++;
        }
        while (students[j].age > pivot) {
            j--;
        }
        if (i <= j) {
            tmp = students[i];
            students[i] = students[j];
            students[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j) {
        quickSortByAge(students, left, j);
    }
    if (i < right) {
        quickSortByAge(students, i, right);
    }
}

void selectionSort(Student students[], int n) {
    int i, j, minIndex;
    Student tmp;
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (students[j].age < students[minIndex].age) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            tmp = students[i];
            students[i] = students[minIndex];
            students[minIndex] = tmp;
        }
    }
}

Student* searchByKey(Student students[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (students[i].age == key) {
            return &students[i];
        }
    }
    return NULL;
}

void clearFile(string fileName) {
    ofstream file(fileName, ios::out | ios::trunc);
    if (file.is_open()) {
        file.close();
        cout << "File cleared and written to successfully." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}