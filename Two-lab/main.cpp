#include <iostream>

using namespace std;

/* ************************************ */
double sqrt_recursive(double a, double x); // выполнение с помощью рекурсии
double sqrt_normal(double a); // нормальное выполнение
/* ************************************ */

int main() {
    double a;
    cout << "Введите число a: ";
    cin >> a; // необходимое число из которого нам нужно найти корень
    
    while (a < 1) {
        cout << "Значение а должно быть больше 0." << endl;
        cout << "Введите число a: ";
        cin >> a;
    }
    
    double x0 = 0.5 * (1 + a); // def. val. for sqrt_recursive()
    
    double res = sqrt_recursive(a, x0);
    cout << "(рекурсивная функция) Корень из " << a << " = " << res << endl;
    
    res = sqrt_normal(a);
    cout << "(нормальная функиця) Корень из " << a << " = " << res << endl;
    return 0;
}

double sqrt_recursive(double a, double x) {
    double next_x = 0.5 * (x + a/x);
    
    if (next_x == x) {
        return x;
    } else {
        return sqrt_recursive(a, next_x);
    }
}

double sqrt_normal(double a) {
    double x0 = 0.5 * (1 + a);
    double x = x0;
    double next_x = 0.5 * (x + a/x);
    
    while (next_x != x) {
        x = next_x;
        next_x = 0.5 * (x + a/x);
    }
    return x;
}
