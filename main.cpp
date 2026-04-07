#include <bits/stdc++.h>
using namespace std;

void clear_screen(){
    system("clear"); //очистка терминала для Unix систем
}

//ФУНКЦИИ

//1.линейная y=kx+b
double linear(double x, double k, double b) {
    return k*x+b;
}

//2.квадратичная y=ax²+bx+c
double quadratic(double x, double a, double b, double c) {
    return a*x*x+b*x+c;
}

//3.обратная пропорциональность y=k/x+b
double hyperbola(double x, double k, double b) {
    return k/x-b;
}

//4.синус y=sin(x)-b
double sinf(double x, double b) {
    return sin(x)-b;
}

//5.экспонента
double expf(double x, double b) {
    return exp(x)-b;
}

//6.логарифм
double logf(double x, double b) {
    return log(x)-b;
}

//ВЫБОР ФУНКЦИИ
void func() {
    cout << "\n\nВыберите функцию:\n";
    cout << "1.Линейная - kx + b = 0\n";
    cout << "2.Квадратичная - ax² + bx + c = 0\n";
    cout << "3.Гипербола - k/x = b (x != 0)\n";
    cout << "4.Синус - sin x = b (b ∈ [-1; 1])\n";
    cout << "5.Экспонента - eˣ = b (b > 0)\n";
    cout << "6.Натуральный логарифм - ln x = b (x > 0)\n";
}
void input_params(int type, double p[]) {
    if (type == 1) { cout << "\nk: "; cin >> p[0]; cout << "\nb: "; cin >> p[1]; }
    else if (type == 2) { cout << "\na: "; cin >> p[0]; cout << "\nb: "; cin >> p[1]; cout << "\nc: "; cin >> p[2]; }
    else if (type == 3) { cout << "\nk: "; cin >> p[0]; cout << "\nb: "; cin >> p[1]; if (p[0] == 0) { cout << "Ошибка: k не может быть 0\n"; return; } }
    else { cout << "\nb: "; cin >> p[0]; }
}

double eval(int type, double x, double p[]) {
    switch(type) {
        case 1: return linear(x, p[0], p[1]);
        case 2: return quadratic(x, p[0], p[1], p[2]);
        case 3: return hyperbola(x, p[0], p[1]);
        case 4: return sinf(x, p[0]);
        case 5: return expf(x, p[0]);
        case 6: return logf(x, p[0]);
        default: return 0;
    }
}

//МЕТОДЫ

void bisection(){
    int type; double p[3]={0}, a, b, c = 0, eps, fa, fb, fc; int iters = 0;
    clear_screen();

    cout << "МЕТОД БИСЕКЦИИ (ПОЛОВИННОГО ДЕЛЕНИЯ)";
    func();
    cin >> type;

    clear_screen();

    cout << "ВВОД КОЭФФИЦИЕНТОВ\n";
    input_params(type, p);

    clear_screen();

    cout << "ПАРАМЕТРЫ МЕТОДА";
    cout << "\nДля метода бисекции нужен интервал [a; b]:\n";
    cout << "a: "; cin >> a;
    cout << "b: "; cin >> b;
    cout << "Точность (например 0.0001): "; cin >> eps;
    clear_screen();
    fa = eval(type, a, p); fb = eval(type, b, p);

    // если значения функций на концах отрезка [a;b] равны, то корня на этом отрезке нет
    if (fa*fb>0){
        cout << "error: same signs on f(a) and f(b): " << fa << " " << fb << "\nНа отрезке нет корня или их чётное количество\n";
        return;
    }

    clear_screen();

    // пока длина отрезка больше точности И не превышен лимит итераций
    while (fabs(b-a) >= eps && iters < 50){ 
        iters++; c = (a+b)/2; fc = eval(type, c, p);
        if (fc == 0) break; // точно нашли корень
        // выбор новой половины отрезка (где есть корень):
        if (fc * fa < 0){ // если корень между а и с
            b = c; fb = fc;
        } else { // если корень между с и b
            a = c; fa = fc;
        }
    }

    cout << fixed << setprecision(10);
    cout << "РЕЗУЛЬТАТ\n";
    cout << "Корень: x = " << c;
    cout << "\nКоличество итераций: " << iters;
}

void chord(){
    int type; double p[3]={0}, x0, x1, eps, xp, xc; int iters = 0;
    clear_screen();

    cout << "МЕТОД ХОРД (СЕКУЩИХ)";
    func();
    cin >> type;

    clear_screen();

    cout << "ВВОД КОЭФФИЦИЕНТОВ\n";
    input_params(type, p);

    clear_screen();

    cout << "ПАРАМЕТРЫ МЕТОДА";
    cout << "\nВведите две начальные точки:\n";
    cout << "x0: "; cin >> x0;
    cout << "x1: "; cin >> x1;
    cout << "Точность (например 0.0001): "; cin >> eps;
    clear_screen();
    xp = x0, xc = x1; // xp - x_previous; xc - x_current

    while (iters<=50){
        iters++;
        double fp = eval(type, xp, p), fc = eval(type, xc, p);
        double xn = xc - fc * (xc - xp) / (fc - fp); // xn - x_next (следующее приближение)

        if (fabs(xn-xc) < eps) { // если достигли точности
            cout << fixed << setprecision(10);
            cout << "РЕЗУЛЬТАТ\n";
            cout << "Корень: x = " << xc;
            cout << "\nКоличество итераций: " << iters;
            return;
        }
        xp = xc; xc = xn;
    }
}

void newton(){
    int type; double p[3]={0}, x0, eps, x; int iters = 0;
    clear_screen();

    cout << "МЕТОД НЬЮТОНА (КАСАТЕЛЬНЫХ)";
    func();
    cin >> type;

    clear_screen();

    cout << "ВВОД КОЭФФИЦИЕНТОВ\n";
    input_params(type, p);

    clear_screen();

    cout << "ПАРАМЕТРЫ МЕТОДА";
    cout << "\nВведите начальное приближение:\n";
    cout << "x0: "; cin >> x0;
    cout << "Точность (например 0.0001): "; cin >> eps;
    clear_screen();

    x = x0;

    while (iters < 50){
        iters++;
        double fx = eval(type, x, p), dfx;  // fx = f(x), dfx = f'(x) (производная)
        
        switch (type){
            case 1: dfx = p[0]; break;
            case 2: dfx = 2*p[0]*x+p[1]; break;
            case 3: if (x == 0) { cout << "Ошибка: x=0\n"; return; }; dfx = -p[0]/(x*x); break;
            case 4: dfx = cos(x); break;
            case 5: dfx = exp(x); break;
            case 6: if (x <= 0) { cout << "Ошибка: x<=0 для логарифма\n"; return; }; dfx = 1/x; break;
        }

        // защита от деления на ноль (если производная = 0)
        if (fabs(dfx) < 1e-12){
            cout << "Ошибка: производная близка к нулю\n";
            return;
        }
        double xn = x - fx / dfx;
        
        // проверка на достижение точности
        if (fabs(xn - x) < eps){
            cout << fixed << setprecision(10);
            cout << "РЕЗУЛЬТАТ\n";
            cout << "Корень: x = " << xn;
            cout << "\nКоличество итераций: " << iters;
            return;
        }
        
        x = xn;  // переходим к следующей итерации
    }

    cout << "Не сошёлся за 50 итераций\n";

    
}

//МЕНЮ

void menu(){
    clear_screen();
    
    cout << "        SOLVER v1.1\n\n";

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

        if(choice == 0) break;
        clear_screen();
        if(choice == 1) bisection();
        else if(choice == 2) chord();
        else if(choice == 3) newton();
        else continue;
        
        cout << "\n\nEnter для продолжения...";
        cin.ignore(); cin.get();
    }
    return 0;
    
}