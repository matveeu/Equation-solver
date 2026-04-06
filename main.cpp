#include <bits/stdc++.h>
using namespace std;

#define ll long long

void clear_screen(){
    system("clear"); //очистка терминала для Unix систем
}

//ФУНКЦИИ

//линейная y=kx+b
double linear(double x, double k, double b) {
    return k*x+b;
}

//квадратичная y=ax²+bx+c и её производная y'=2ax+b
double quadratic(double x, double a, double b, double c) {
    return a*x*x+b*x+c;
}
double quadratic_derivative(double x, double a, double b, double c) {
    return 2*a*x+b;
}


//МЕТОДЫ

void bisection(){
    int func; // номер функции
    clear_screen();

    cout << "МЕТОД БИСЕКЦИИ (ПОЛОВИННОГО ДЕЛЕНИЯ)";

    cout << "\n\nВыберите функцию:\n";
    cout << "1.Линейная - kx + b = 0\n";
    cout << "2.Квадратичная - ax² + bx + c = 0\n";
    cin >> func;

    clear_screen();

    cout << "ВВОД КОЭФФИЦИЕНТОВ\n";

    double params[4] = {0}; // массив для хранения коэффициентов функции

    switch (func){
        case 1:
            cout << "Функция: kx + b = 0\n";
            cout << "k = "; cin >> params[0]; // коэф k
            cout << "b = "; cin >> params[1]; // коэф b
            break;
        case 2:
            cout << "Функция: ax² + bx + c = 0\n";
            cout << "a = "; cin >> params[0]; //коэф а
            cout << "b = "; cin >> params[1]; //коэф b
            cout << "c = "; cin >> params[2]; //коэф c
            break;
    }

    clear_screen();

    cout << "ПАРАМЕТРЫ МЕТОДА";
    double a, b, eps; // a,b - границы [a;b], eps - точность
    cout << "\nДля метода бисекции нужен интервал [a; b]:\n";
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "Точность (например 0.0001): "; cin >> eps;

    double fa, fb; // значения функции на концах отрезка [a;b]

    switch (func){
        case 1:
            fa = linear(a, params[0], params[1]);
            fb = linear(b, params[0], params[1]);
            break;
        case 2:
            fa = quadratic(a, params[0], params[1], params[2]);
            fb = quadratic(b, params[0], params[1], params[2]);
            break;
    }

    // если значения функций на концах отрезка [a;b] равны, то корня на этом отрезке нет
    if (fa*fb>0){
        cout << "error: same signs on f(a) and f(b): " << fa << " " << fb << endl;
        cout << "На отрезке нет корня или их чётное количество" << endl;
        return;
    }

    clear_screen();

    double c; // середина отрезка
    int iters = 0; // кол-во итераций

    // пока длина отрезка больше точности И не превышен лимит итераций
    while (fabs(b-a) >= eps && iters < 50){ 
        iters++;
        c = (a+b)/2; // середина отрезка

        double fc; // значение функции в середине отрезка

        switch (func){
            case 1:
                fc = linear(c, params[0], params[1]);
                break;
            case 2:
                fc = quadratic(c, params[0], params[1], params[2]);
                break;
        }

        if (fc == 0) break; // точно нашли корень

        // выбор новой половины отрезка (где есть корень)
        if (fc * fa < 0){ // если корень между а и с
            b = c;
            fb = fc;
        } else { // если корень между с и b
            a = c;
            fa = fc;
        }
    }

    cout << "РЕЗУЛЬТАТ\n";
    cout << "Корень: x = " << c;
    cout << "\nКоличество итераций: " << iters;
}

void chord(){
    int func; //номер функции
    clear_screen();

    cout << "МЕТОД ХОРД (СЕКУЩИХ)";

    cout << "\n\nВыберите функцию:\n";
    cout << "1.Линейная - kx + b = 0\n";
    cout << "2.Квадратичная - ax² + bx + c = 0\n";
    cin >> func;

    clear_screen();

    cout << "ВВОД КОЭФФИЦИЕНТОВ\n";

    double params[4] = {0}; // коэффициенты функции

    switch (func){
        case 1:
            cout << "Функция: kx + b = 0\n";
            cout << "k = "; cin >> params[0];
            cout << "b = "; cin >> params[1];
            break;
        case 2:
            cout << "Функция: ax² + bx + c = 0\n";
            cout << "a = "; cin >> params[0]; //коэф а
            cout << "b = "; cin >> params[1]; //коэф b
            cout << "c = "; cin >> params[2]; //коэф c
            break;
    }

    clear_screen();

    cout << "ПАРАМЕТРЫ МЕТОДА";
    double x0, x1, eps; // начальные точки и точность
    cout << "\nВведите две начальные точки:\n";
    cout << "x0 = "; cin >> x0;
    cout << "x1 = "; cin >> x1;
    cout << "Точность (например 0.0001): "; cin >> eps;

    double xp = x0, xc = x1; // xp - x_previous; xc - x_current
    int iters = 0; // кол-во итераций

    while (iters<=50){
        iters++;
        double fp, fc; // fp - f_previous; fc - f_current

        switch (func){
            case 1:
                fp = linear(xp, params[0], params[1]);
                fc = linear(xc, params[0], params[1]);
                break;
            case 2:
                fp = quadratic(xp, params[0], params[1], params[2]);
                fc = quadratic(xc, params[0], params[1], params[2]);
                break;
        }

        double xn = xc - fc * (xc - xp) / (fc - fp); // xn - x_next (следующее приближение)

        double fn; // fn - f_next (f(xn))

        switch (func){
            case 1:
                fn = linear(xn, params[0], params[1]);
                break;
            case 2:
                fn = quadratic(xn, params[0], params[1], params[2]);
                break;
        }

        if (fabs(fn) < eps){ // если достигли точности
            xc = xn; // обновляем корень
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
    int func;  // номер выбранной функции
    clear_screen();

    cout << "МЕТОД НЬЮТОНА (КАСАТЕЛЬНЫХ)";

    cout << "\n\nВыберите функцию:\n";
    cout << "1. Линейная - kx + b = 0\n";
    cout << "2.Квадратичная - ax² + bx + c = 0\n";
    cin >> func;

    clear_screen();

    cout << "ВВОД КОЭФФИЦИЕНТОВ\n";

    double params[4] = {0};  // коэффициенты функции

    switch (func){
        case 1:
            cout << "Функция: kx + b = 0\n";
            cout << "k = "; cin >> params[0];  // коэффициент k
            cout << "b = "; cin >> params[1];  // коэффициент b
            break;
        case 2:
            cout << "Функция: ax² + bx + c = 0\n";
            cout << "a = "; cin >> params[0]; //коэф а
            cout << "b = "; cin >> params[1]; //коэф b
            cout << "c = "; cin >> params[2]; //коэф c
            break;
    }

    clear_screen();

    cout << "ПАРАМЕТРЫ МЕТОДА";
    double x0, eps;  // x0 - начальное приближение, eps - точность
    cout << "\nВведите начальное приближение:\n";
    cout << "x0 = "; cin >> x0;
    cout << "Точность (например 0.0001): "; cin >> eps;

    double x = x0;  // текущее приближение корня (начинаем с x0)
    int iters = 0;  // счётчик итераций

    // лимит 50 итераций, чтобы не зависнуть
    while (iters < 50){
        iters++;
        
        double fx, dfx;  // fx = f(x), dfx = f'(x) (производная)
        
        switch (func){
            case 1:
                // для линейной функции: f(x) = kx + b
                fx = linear(x, params[0], params[1]);
                dfx = params[0];  // производная от kx+b равна просто k
                break;
            case 2:
                // для квадратичной функции: f(x) = ax² + bx + c
                fx = quadratic(x, params[0], params[1], params[2]);
                dfx = quadratic_derivative(x, params[0], params[1], params[2]);
                break;
        }

        // защита от деления на ноль (если производная = 0)
        if (fabs(dfx) < 1e-12){
            cout << "Ошибка: производная близка к нулю\n";
            return;
        }
        
        double xn = x - fx / dfx;
        
        // проверка на достижение точности
        if (fabs(xn - x) < eps){
            x = xn;  // обновляем корень
            break;
        }
        
        x = xn;  // переходим к следующей итерации
    }

    clear_screen();

    cout << "РЕЗУЛЬТАТ\n";
    cout << "Корень: x = " << x;
    cout << "\nКоличество итераций: " << iters;
}

//МЕНЮ

void menu(){
    clear_screen();
    
    cout << "        SOLVER 1.0.4\n\n";

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