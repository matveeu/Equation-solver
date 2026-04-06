#include <bits/stdc++.h>
using namespace std;

#define ll long long

void clear_screen(){
    system("clear");
}

//ФУНКЦИИ

double linear(double x, double k, double b) {
    return k*x+b;
}


//МЕТОДЫ

void bisection(){
    int func;
    clear_screen();

    cout << "МЕТОД БИСЕКЦИИ (ПОЛОВИННОГО ДЕЛЕНИЯ)";

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

void chord(){
    int func;
    clear_screen();

    cout << "МЕТОД ХОРД (СЕКУЩИХ)";

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
    double x0, x1, eps;
    cout << "\nВведите две начальные точки:\n";
    cout << "x0 = "; cin >> x0;
    cout << "x1 = "; cin >> x1;
    cout << "Точность: "; cin >> eps;

    double xp = x0, xc = x1; //xp - x_previous; xc - x_current
    int iters = 0;

    while (iters<=50){
        iters++;
        double fp, fc; //fp - f_previous; fc - f_current

        switch (func){
            case 1:
                fp = linear(xp, params[0], params[1]);
                fc = linear(xc, params[0], params[1]);
                break;
        }

        double xn = xc - fc * (xc - xp) / (fc - fp); //xn - x_next

        double fn; //fn - f_next

        switch (func){
            case 1:
                fn = linear(xn, params[0], params[1]);
        }

        if (fabs(fn) < eps){
            xc = xn;
            break;
        }

        xp = xc;
        xc = xn;
    }

    clear_screen();

    cout << "РЕЗУЛЬТАТ\n";
    cout << "Корень: x = " << xc;
    cout << "\nКоличество итераций: " << iters;
}

void newton(){

}

//МЕНЮ

void menu(){
    clear_screen();
    
    cout << "        SOLVER 1.0.1\n\n";

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
            chord();
        } else if(choice == 3){
            newton();
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