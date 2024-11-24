#include <iostream>
#include <vector>
#include <random>

#define SIZE 1000
#define m 57

using namespace std;

// хеш-функция
int my_hash(int number) {
    return (number + 7) % SIZE;
}

// генерация n-значного числа
int generate_random() {
    std::random_device rd;  // Obtain a random seed
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> dis(10000, 99999);
    return dis(gen);
}

// вывод хеш-таблицы
void print_table(vector<int>& table) {
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != -1) {
            cout << "Index: " << i << ", number: " << table[i] << endl;
        }
    }
}

// проверка на нахождение числа в векторе
bool is_in(vector<int>& table, int n) {
    int start_index = my_hash(n);
    int qp = 1; // Начало квадратичного пробинга

    while (table[start_index] != -1) { // Пока ячейка не пуста
        if (table[start_index] == n) { // Если найдено
            cout << endl << n << " is in the table! Index: " << start_index << endl;
            return true;
        }
        start_index = (start_index + qp * qp) % SIZE; // Квадратичный пробинг
        qp++;

        // Предохранитель от зацикливания, если таблица полностью заполнена
        if (qp > SIZE) {
            break;
        }
    }

    cout << "Element not found!" << endl;
    return false; // Не найдено
}

// удалить элемент из таблицы
void delete_element(vector<int>& table, int n) {
    int start_index = my_hash(n);
    int qp = 1; // Начало квадратичного пробинга

    while (table[start_index] != -1) { // Пока ячейка не пуста
        if (table[start_index] == n) { // Если найдено
            table[start_index] = -1;  // Удаление элемента (установка в значение по умолчанию)
            cout << "Deleted " << n << " from index " << start_index << endl;
            return;
        }
        start_index = (start_index + qp * qp) % SIZE; // Квадратичный пробинг
        qp++;

        // Предохранитель от зацикливания
        if (qp > SIZE) {
            break;
        }
    }

    cout << "Element not found!" << endl;
}

// добавить элемент (случайный или конкретный)
void add_element(vector<int>& table, int n = -1) {
    int number = (n == -1) ? generate_random() : n;

    if (number < 10000 || number > 99999) {
        cout << endl << "Tried number is not 5-digit" << endl;
        return;
    }

    if (!is_in(table, number)) {
        int index = my_hash(number);
        int qp = 1; // quadratic probing

        while (table[index] != -1) {
            index = (index + qp * qp) % SIZE;
            qp++;
            if (qp > SIZE) {
                cout << "Cannot insert " << number << ", table full." << endl;
                return;
            }
        }

        table[index] = number;
        cout << "Inserted " << number << " at " << index << endl;
    }
}

int main()
{
    // значение по умолчанию -1
    vector<int> table(SIZE, -1);

    // average count attempt
    int aca = m;

    // введение чисел в вектор
    for (int i = 0; i < m; i++) {
        int number = generate_random();
        int index = my_hash(number);

        if (!is_in(table, number)) {
            int qp = 1; // quad prob
            while (table[index] != -1) {
                if (qp > SIZE) {
                    cout << "qp is greater than SIZE." << endl;
                    break;
                }
                index = (index + qp * qp) % SIZE;
                aca++;
                qp++;
            }

            table[index] = number;
        }
        else {
            cout << "Caught duplicate: " << number << endl;
            i--;
        }
    }

    // вывод вектора
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != -1) {
            cout << "Index: " << i << ", number: " << table[i] << endl;
            k++;
        }
    }
    cout << endl << "Completed packing: " << k << endl;

    cout << "Average Count Attempt: " << (float)aca / m << endl;

    // НАЧАЛО ВТОРОЙ ЛАБЫ
    bool running = true;
    while (running) {
        cout << endl;
        cout << "\t0 - show table" << endl;
        cout << "\t1 - add 1 random number" << endl;
        cout << "\t2 - add X random numbers " << endl;
        cout << "\t3 - add 1 specific number " << endl;
        cout << "\t4 - delete 1 specific number " << endl;
        cout << "\t5 - replace A for B " << endl;
        cout << "\t9 - finish " << endl;
        cout << endl;

        int task = 0;
        int x = 0;
        int specific = 0;
        int A = 0;
        int B = 0;
        cin >> task;
        switch (task)
        {
        case 0:
            print_table(table);
            break;
        case 1:
            add_element(table);
            break;
        case 2:
            cout << "Type X -> ";
            cin >> x;

            for (int i = 0; i < x; i++)
                add_element(table);
            break;
        case 3:
            cout << "type specific number to add ";
            cin >> specific;

            add_element(table, specific);
            break;
        case 4:
            cout << "type specific number to delete ";
            cin >> specific;

            delete_element(table, specific);
            break;
        case 5:
            cout << "type A ";
            cin >> A;
            cout << "type B ";
            cin >> B;

            if (is_in(table, A) && 10000 <= B && B <= 99999) {
                delete_element(table, A);
                add_element(table, B);
            }
            else {
                cout << "Element A not found or B is not 5-digit" << endl;
            }

            break;
        case 9:
            running = false;
            break;
        default:
            cout << "Invalid option. Please select a valid task." << endl;
            break;
        }
    }
}
