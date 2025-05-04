#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// ЗАДАЧА 1 (vector<double>) 
void task1() {
    vector<double> vec = { 3.14, 2.71, 1.618, 0.577 };

    // Добавление элементов
    vec.push_back(4.669);
    vec.insert(vec.begin() + 2, 1.414);

    // Удаление элементов
    vec.erase(remove(vec.begin(), vec.end(), 0.577), vec.end());

    // Добавление максимума в начало
    if (!vec.empty()) {
        double max_val = *max_element(vec.begin(), vec.end());
        vec.insert(vec.begin(), max_val);
    }

    cout << "Task1: ";
    for (double num : vec) cout << num << " ";
    cout << endl;
}

//  ЗАДАЧА 2 (vector<Money>) 
class Money {
public:
    long rub;
    int kop;

    Money(long r = 0, int k = 0) : rub(r), kop(k) { normalize(); }

    void normalize() {
        if (kop >= 100) {
            rub += kop / 100;
            kop %= 100;
        }
    }

    bool operator<(const Money& other) const {
        return (rub < other.rub) || (rub == other.rub && kop < other.kop);
    }

    friend ostream& operator<<(ostream& os, const Money& m) {
        os << m.rub << "." << (m.kop < 10 ? "0" : "") << m.kop;
        return os;
    }
};

void task2() {
    vector<Money> vec = { Money(150, 75), Money(200, 50), Money(100, 99) };

    // Добавление элементов
    vec.push_back(Money(300, 25));
    vec.insert(vec.begin(), Money(50, 0));

    // Удаление элемента
    vec.erase(vec.begin() + 1);

    // Удаление минимального элемента
    if (!vec.empty()) {
        auto min_it = min_element(vec.begin(), vec.end());
        vec.erase(min_it);
    }

    cout << "Task2: ";
    for (const Money& m : vec) cout << m << " ";
    cout << endl;
}

// ЗАДАЧА 3 (MySet template) 
template <typename T>
class MySet {
    vector<T> data;
public:
    void add(const T& item) {
        if (find(data.begin(), data.end(), item) == data.end())
            data.push_back(item);
    }

    void remove(const T& item) {
        data.erase(remove(data.begin(), data.end(), item), data.end());
    }

    // Ручной подсчёт суммы вместо accumulate
    void addAverageToElements() {
        if (data.empty()) return;

        T sum = T();
        for (const T& item : data) sum = sum + item;
        T avg = sum / data.size();

        for (T& item : data) item = item + avg;
    }

    void print() {
        cout << "Task3: ";
        for (const T& item : data) cout << item << " ";
        cout << endl;
    }
};

//  ЗАДАЧА 4 (stack<Money>) 
void task4() {
    stack<Money> st;
    vector<Money> temp = { Money(100, 50), Money(500, 99), Money(200, 10) };

    // Заполнение стека
    for (const Money& m : temp) st.push(m);

    // Поиск и удаление минимума через вектор
    vector<Money> helper;
    while (!st.empty()) {
        helper.push_back(st.top());
        st.pop();
    }

    if (!helper.empty()) {
        auto min_it = min_element(helper.begin(), helper.end());
        helper.erase(min_it);
    }

    // Восстановление стека
    for (auto it = helper.rbegin(); it != helper.rend(); ++it)
        st.push(*it);

    // Вывод
    cout << "Task4: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

//  ЗАДАЧА 5 (StackSet template) 
template <typename T>
class StackSet {
    stack<T> data;
public:
    void push(const T& item) {
        data.push(item);
    }

    // Ручной подсчёт суммы
    void addAverageToElements() {
        if (data.empty()) return;

        vector<T> temp;
        T sum = T();
        size_t count = 0;

        // Сбор элементов и суммы
        while (!data.empty()) {
            sum = sum + data.top();
            temp.push_back(data.top());
            data.pop();
            count++;
        }

        T avg = sum / count;

        // Добавление среднего и восстановление стека
        for (T& item : temp) item = item + avg;
        for (auto it = temp.rbegin(); it != temp.rend(); ++it)
            data.push(*it);
    }

    void print() {
        stack<T> temp = data;
        cout << "Task5: ";
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

// Перегрузка операторов для Money
Money operator+(const Money& a, const Money& b) {
    return Money(a.rub + b.rub, a.kop + b.kop);
}

Money operator/(const Money& m, int div) {
    long total = m.rub * 100 + m.kop;
    total /= div;
    return Money(total / 100, total % 100);
}

int main() {
    task1();
    task2();

    MySet<int> set3;
    set3.add(10);
    set3.add(20);
    set3.addAverageToElements();
    set3.print();

    task4();

    StackSet<Money> set5;
    set5.push(Money(100, 50));
    set5.push(Money(200, 75));
    set5.addAverageToElements();
    set5.print();

    return 0;
}