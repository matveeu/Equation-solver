#include <bits/stdc++.h>
using namespace std;

#define ll long long

void clear_screen(){
    system("clear");
}

double linear(double x, double k, double b) {
    return k*x+b;
}

void bisection(){
    int func;
    clear_screen();

    cout << "МЕТОД БИСЕКЦИИ";

    cout << "\n\nВыберите функцию:\n";
    cout << "1.Линейная - kx + b = 0\n";
    cin >> func;

    clear_screen();
    cout << "ВВОД КОЭФФИЦИЕНТОВ\n";

    double params[4] = {0};

    switch (func){
        case 1:
            cout << "Функция: kx + b = 0\n";
            cout << "k = "; cin >> params[0];
            cout << "b = "; cin >> params[1];
            break;
    }
    clear_screen();

    cout << "ПАРАМЕТРЫ МЕТОДА";
    double a, b, eps;
    cout << "\nДля метода бисекции нужен интервал [a; b]:\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "Точность (например 0.0001): "; cin >> eps;

    double fa, fb;

    switch (func){
        case 1:
            fa = linear(a, params[0], params[1]);
            fb = linear(b, params[0], params[1]);
            break;
    }
    if (fa*fb>0){
        cout << "error: same signs on f(a) and f(b): " << fa << " " << fb << endl;
        return;
    }

    clear_screen();

    double c;
    int iters = 0;

    while (fabs(b-a) >= eps && iters < 50){
        iters++;
        c = (a+b)/2;

        double fc;

        switch (func){
            case 1:
                fc = linear(c, params[0], params[1]);
                break;
        }

        if (fc == 0) break;

        if (fc * fa < 0){
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    cout << "РЕЗУЛЬТАТ\n";
    cout << "Корень: x = " << c;
    cout << "\nКоличество итераций: " << iters;
}

void newton(){
    
}

void chord(){

}

void menu(){
    clear_screen();
    
    cout << "        SOLVER 1.0\n\n";

    cout << "1.Метод бисекции\n";
    cout << "2.Метод хорд\n";
    cout << "3.Метод Ньютона(касательных)\n\n";

    cout << "0.Выход\n\n";

    cout << "Выберите метод: ";
}

int main(){
    int choice;

    while(true) {
        menu();
        cin >> choice;

        clear_screen();

        if(choice == 0){
            break;
        }
        if(choice == 1){
            bisection();
        } else if(choice == 2){
            newton();
        } else if(choice == 3){
            chord();
        } else {
            cout << "\n\n\nВыберите один из трёх существующих методов!";
            cin.ignore();
            cin.get();
            continue;
        }

        cout << "\nPress any button to exit...";
        cin.ignore();
        cin.get();
    }

    return 0;
    
}