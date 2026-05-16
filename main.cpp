#include <bits/stdc++.h>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void clear_screen(){
    system(CLEAR); //очистка терминала
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

void printcoef() {
    cout << CYAN << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "║" << BOLD << "           ВВОД КОЭФФИЦИЕНТОВ           " << RESET << CYAN << "║" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << "\n\n";
}

void printparams() {
    cout << CYAN << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "║" << BOLD << "            ПАРАМЕТРЫ МЕТОДА            " << RESET << CYAN << "║" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << "\n\n";
}

void printres() {
    cout << CYAN << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "║" << GREEN << BOLD << "               РЕЗУЛЬТАТ                " << RESET << CYAN << "║" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << "\n\n";
}
//ВЫБОР ФУНКЦИИ
void func() {
    cout << MAGENTA << BOLD << "Выберите функцию:\n" << RESET;
    cout << GREEN << "1. " << RESET << "Линейная - kx + b = 0\n";
    cout << GREEN << "2. " << RESET << "Квадратичная - ax² + bx + c = 0\n";
    cout << GREEN << "3. " << RESET << "Гипербола - k/x = b (x != 0)\n";
    cout << GREEN << "4. " << RESET << "Синус - sin x = b (b ∈ [-1; 1])\n";
    cout << GREEN << "5. " << RESET << "Экспонента - eˣ = b (b > 0)\n";
    cout << GREEN << "6. " << RESET << "Натуральный логарифм - ln x = b (x > 0)\n";
}
void input_params(int type, double p[]) {
    if (type == 1) { cout << "\nk: " << GREEN; cin >> p[0]; cout << RESET << "\nb: " << GREEN; cin >> p[1]; }
    else if (type == 2) { cout << "\na: " << GREEN; cin >> p[0]; cout << RESET << "\nb: " << GREEN; cin >> p[1]; cout << RESET << "\nc: " << GREEN; cin >> p[2]; }
    else if (type == 3) { cout << "\nk: " << GREEN; cin >> p[0]; cout << RESET << "\nb: " << GREEN; cin >> p[1]; if (p[0] == 0) { cout << RED "Ошибка: k не может быть 0\n" << RESET; return; } }
    else { cout << "\nb: " << GREEN; cin >> p[0]; }
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

    cout << CYAN << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "║" << BOLD << "  МЕТОД БИСЕКЦИИ (ПОЛОВИННОГО ДЕЛЕНИЯ)  " << RESET << CYAN << "║" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << "\n\n";
    func();
    cout << MAGENTA << "Ваш выбор: " << BLUE;
    cin >> type;

    clear_screen();

    printcoef();
    input_params(type, p);

    clear_screen();

    printparams();
    cout << MAGENTA << "\nДля метода бисекции нужен интервал [a; b]:\n";
    cout << RESET << "a: " << GREEN; cin >> a;
    cout << RESET << "b: " << GREEN; cin >> b;
    cout << RESET << "Точность (например 0.0001): " << BLUE; cin >> eps;
    clear_screen();
    fa = eval(type, a, p); fb = eval(type, b, p);

    // если значения функций на концах отрезка [a;b] равны, то корня на этом отрезке нет
    if (fa*fb>0){
        cout << RED << "error: same signs on f(a) and f(b): " << fa << " " << fb << YELLOW <<"\nНа отрезке нет корня или их чётное количество.\n" << RESET;
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
    printres();
    cout << "Корень: x = " << MAGENTA << c << RESET;
    cout << "\nКоличество итераций: " << BLUE << iters << RESET;
}

void chord(){
    int type; double p[3]={0}, x0, x1, eps, xp, xc; int iters = 0;
    clear_screen();

    cout << CYAN << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "║" << BOLD << "          МЕТОД ХОРД (СЕКУЩИХ)          " << RESET << CYAN << "║" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << "\n\n";
    func();
    cout << MAGENTA << "Ваш выбор: " << BLUE;
    cin >> type;

    clear_screen();

    printcoef();
    input_params(type, p);

    clear_screen();

    printparams();
    cout << MAGENTA << "\nВведите две начальные точки:\n";
    cout << RESET << "x0: " << GREEN; cin >> x0;
    cout << RESET << "x1: " << GREEN; cin >> x1;
    cout << RESET << "Точность (например 0.0001): " << BLUE; cin >> eps;
    clear_screen();
    xp = x0, xc = x1; // xp - x_previous; xc - x_current

    if (type == 3 && (x0 == 0 || x1 == 0)) {
        cout << RED << "Ошибка: гипербола не определена в x=0.\n" << RESET;
        return;
    }

    while (iters<=50){
        iters++;
        double fp = eval(type, xp, p), fc = eval(type, xc, p);
        double xn = xc - fc * (xc - xp) / (fc - fp); // xn - x_next (следующее приближение)

        if (fabs(xn-xc) < eps) { // если достигли точности
            cout << fixed << setprecision(10);
            printres();
            cout << "Корень: x = " << MAGENTA << xc << RESET;
            cout << "\nКоличество итераций: " << BLUE << iters;
            return;
        }
        xp = xc; xc = xn;
    }
}

void newton(){
    int type; double p[3]={0}, x0, eps, x; int iters = 0;
    clear_screen();

    cout << CYAN << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "║" << BOLD << "      МЕТОД НЬЮТОНА (КАСАТЕЛЬНЫХ)       " << RESET << CYAN << "║" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << "\n\n";
    func();
    cout << MAGENTA << "Ваш выбор: " << BLUE;
    cin >> type;

    clear_screen();

    printcoef();
    input_params(type, p);

    clear_screen();

    printparams();
    cout << MAGENTA <<"\nВведите начальное приближение:\n";
    cout << RESET << "x0: " << GREEN; cin >> x0;
    cout << RESET << "Точность (например 0.0001): " << BLUE; cin >> eps;
    clear_screen();

    x = x0;

    while (iters < 50){
        iters++;
        double fx = eval(type, x, p), dfx;  // fx = f(x), dfx = f'(x) (производная)
        
        switch (type){
            case 1: dfx = p[0]; break;
            case 2: dfx = 2*p[0]*x+p[1]; break;
            case 3: if (x == 0) { cout << RED << "Ошибка: x=0.\n"; return; }; dfx = -p[0]/(x*x); break;
            case 4: dfx = cos(x); break;
            case 5: dfx = exp(x); break;
            case 6: if (x <= 0) { cout << RED << "Ошибка: x<=0 для логарифма.\n"; return; }; dfx = 1/x; break;
        }

        // защита от деления на ноль (если производная = 0)
        if (fabs(dfx) < 1e-12){
            cout << RED << "Ошибка: производная близка к нулю.\n";
            return;
        }
        double xn = x - fx / dfx;
        
        if (type == 3 && xn == 0) {
            cout << RED << "Ошибка: метод ушёл в точку разрыва x=0.\n";
            return;
        }

        if (type == 6 && xn <= 0) {
            cout << RED << "Ошибка: метод ушёл в x<=0, логарифм не определён.\n";
            return;
        }
        // проверка на достижение точности
        if (fabs(xn - x) < eps){
            cout << fixed << setprecision(10);
            printres();
            cout << "Корень: x = " << MAGENTA << xn << RESET;
            cout << "\nКоличество итераций: " << BLUE << iters;
            return;
        }
        
        x = xn;  // переходим к следующей итерации
    }

    cout << YELLOW << "Не сошёлся за 50 итераций.\n";

    
}

//МЕНЮ

void menu(){
    clear_screen();
    
    cout << CYAN << "╔════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "║" << BOLD << "              SOLVER v1.3               " << RESET << CYAN << "║" << RESET << endl;
    cout << CYAN << "║                                        ║" << RESET << endl;
    cout << CYAN << "╚════════════════════════════════════════╝" << RESET << "\n\n";

    cout << GREEN << "1. " << RESET << "Метод бисекции\n";
    cout << GREEN << "2. " << RESET << "Метод хорд\n";
    cout << GREEN << "3. " << RESET << "Метод Ньютона(касательных)\n\n";

    cout << RED << "0" << RESET << ".Выход.\n\n";

    cout << MAGENTA << "Выберите метод: " << BLUE;
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
        
        cout << CYAN << "\n\nEnter для продолжения...";
        cin.ignore(); cin.get();
    }
    return 0;
    
}