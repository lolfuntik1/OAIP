#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    return x - 5 * pow(sin(x), 2) - 5;
}

double g(double x) {
    return 5 * pow(sin(x), 2) + 5;
}

void simple_iteration(double x0, double eps, int max_iter) {
    int iter = 0;
    double x = x0, x_prev;
    do {
        iter++;
        x_prev = x;
        x = g(x_prev);
        if (iter > max_iter) {
            cout << "Метод не сошелся за " << max_iter << " итераций\n";
            return;
        }
    } while (fabs(x - x_prev) > eps);
    cout << "Корень равен " << x << " найден после " << iter << " итераций\n";
}

int main() {
    double a = 3, b = 9, eps = 1e-1;
    int max_iter = 1000;
    for (double x = a; x <= b; x += 0.1) {
        double fx = f(x);
        if (fabs(fx) < eps) {
            cout << "Корень равен " << x << endl;
        }
    }
    cout << "Используем метод простой итерации:\n";
    simple_iteration((a + b) / 2, eps, max_iter);
    return 0;
}
