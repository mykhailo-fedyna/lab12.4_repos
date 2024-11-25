#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

// Структура для зберігання даних про людину
struct Zodiac {
    string surname; // Прізвище
    string name;    // Ім'я
    string zodiac_sign; // Знак Зодіаку
    int birthday[3]; // День народження: [0] - день, [1] - місяць, [2] - рік
};

// Функція для запису об'єкта Zodiac у бінарний файл
void writeToBinary(ofstream& file, const Zodiac& person) {
    size_t length;

    // Визначаємо довжину рядка прізвища
    length = person.surname.size();
    // Записуємо довжину прізвища
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    // Записуємо сам рядок прізвища
    file.write(person.surname.c_str(), length);

    // Визначаємо довжину рядка імені
    length = person.name.size();
    // Записуємо довжину імені
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    // Записуємо сам рядок імені
    file.write(person.name.c_str(), length);

    // Визначаємо довжину рядка знака Зодіаку
    length = person.zodiac_sign.size();
    // Записуємо довжину знака Зодіаку
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    // Записуємо сам рядок знака Зодіаку
    file.write(person.zodiac_sign.c_str(), length);

    // Записуємо масив з датою народження
    file.write(reinterpret_cast<const char*>(person.birthday), sizeof(person.birthday));
}

// Функція для зчитування об'єкта Zodiac із бінарного файлу
void readFromBinary(ifstream& file, Zodiac& person) {
    size_t length;
    char buffer[256]; // Буфер для зчитування рядків

    // Зчитуємо довжину прізвища
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    // Зчитуємо сам рядок прізвища
    file.read(buffer, length);
    buffer[length] = '\0'; // Завершуємо рядок символом кінця
    person.surname = buffer; // Присвоюємо значення прізвища

    // Зчитуємо довжину імені
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    // Зчитуємо сам рядок імені
    file.read(buffer, length);
    buffer[length] = '\0'; // Завершуємо рядок символом кінця
    person.name = buffer; // Присвоюємо значення імені

    // Зчитуємо довжину знака Зодіаку
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    // Зчитуємо сам рядок знака Зодіаку
    file.read(buffer, length);
    buffer[length] = '\0'; // Завершуємо рядок символом кінця
    person.zodiac_sign = buffer; // Присвоюємо значення знака Зодіаку

    // Зчитуємо масив з датою народження
    file.read(reinterpret_cast<char*>(person.birthday), sizeof(person.birthday));
}

// Функція для виведення меню
void displayMenu() {
    // Виводимо доступні опції для користувача
    cout << "\n--- Меню ---\n";
    cout << "1. Додати дані про людину\n";
    cout << "2. Відсортувати за знаком Зодіаку\n";
    cout << "3. Показати людей, народжених у заданому місяці\n";
    cout << "4. Зберегти дані у бінарний файл\n";
    cout << "5. Зчитати дані з бінарного файлу\n";
    cout << "6. Вийти\n";
    cout << "Виберіть опцію: ";
}

// Функція для додавання нової людини
void addPerson(Zodiac*& people, int& size) {
    Zodiac newPerson; // Новий об'єкт типу Zodiac

    // Зчитуємо дані для нового об'єкта
    cout << "Введіть прізвище: ";
    cin >> newPerson.surname;
    cout << "Введіть ім'я: ";
    cin >> newPerson.name;
    cout << "Введіть знак Зодіаку: ";
    cin >> newPerson.zodiac_sign;
    cout << "Введіть день народження (день, місяць, рік): ";
    cin >> newPerson.birthday[0] >> newPerson.birthday[1] >> newPerson.birthday[2];

    // Виділяємо новий масив для збереження усіх людей (включаючи нового)
    Zodiac* temp = new Zodiac[size + 1];
    // Копіюємо існуючі об'єкти до нового масиву
    for (int i = 0; i < size; ++i) {
        temp[i] = people[i];
    }
    // Додаємо нового користувача в масив
    temp[size] = newPerson;
    // Звільняємо пам'ять старого масиву
    delete[] people;
    // Оновлюємо вказівник на новий масив
    people = temp;
    // Збільшуємо розмір
    size++;
}
void sortByZodiac(Zodiac* people, int size) {
    // Сортування масиву людей за знаком Зодіаку
    for (int i = 0; i < size - 1; ++i) { // Зовнішній цикл
        for (int j = i + 1; j < size; ++j) { // Внутрішній цикл
            if (people[i].zodiac_sign > people[j].zodiac_sign) { // Порівнюємо знаки Зодіаку
                Zodiac temp = people[i]; // Тимчасова змінна для перестановки
                people[i] = people[j]; // Міняємо місцями
                people[j] = temp;
            }
        }
    }
    cout << "Масив відсортовано за знаком Зодіаку.\n"; // Повідомлення про завершення сортування
}

void displayByMonth(Zodiac* people, int size, int month) {
    // Виведення людей, народжених у заданому місяці
    bool found = false; // Прапорець для перевірки, чи є люди
    for (int i = 0; i < size; ++i) { // Проходимо по всьому масиву
        if (people[i].birthday[1] == month) { // Перевіряємо місяць народження
            // Виводимо інформацію про людину
            cout << "Прізвище: " << people[i].surname
                << ", Ім'я: " << people[i].name
                << ", Знак Зодіаку: " << people[i].zodiac_sign
                << ", День народження: " << people[i].birthday[0] << "."
                << people[i].birthday[1] << "." << people[i].birthday[2] << "\n";
            found = true; // Змінюємо прапорець
        }
    }
    if (!found) { // Якщо людей у заданому місяці немає
        cout << "Немає людей, народжених у цьому місяці.\n";
    }
}

void saveToFile(Zodiac* people, int size, const string& filename) {
    // Збереження масиву людей у бінарний файл
    ofstream file(filename, ios::binary); // Відкриваємо файл для запису
    if (!file) { // Перевіряємо, чи файл відкрився
        cout << "Помилка відкриття файлу для запису.\n"; // Повідомляємо про помилку
        return;
    }
    file.write(reinterpret_cast<const char*>(&size), sizeof(size)); // Записуємо кількість людей
    for (int i = 0; i < size; ++i) { // Проходимо по всьому масиву
        writeToBinary(file, people[i]); // Записуємо кожен об'єкт у файл
    }
    file.close(); // Закриваємо файл
    cout << "Дані збережено у бінарний файл.\n"; // Повідомляємо про успіх
}

void loadFromFile(Zodiac*& people, int& size, const string& filename) {
    // Зчитування масиву людей із бінарного файлу
    ifstream file(filename, ios::binary); // Відкриваємо файл для читання
    if (!file) { // Перевіряємо, чи файл відкрився
        cout << "Помилка відкриття файлу для зчитування.\n"; // Повідомляємо про помилку
        return;
    }
    file.read(reinterpret_cast<char*>(&size), sizeof(size)); // Зчитуємо кількість людей
    delete[] people; // Видаляємо старий масив (якщо є)
    people = new Zodiac[size]; // Виділяємо пам'ять для нового масиву
    for (int i = 0; i < size; ++i) { // Проходимо по всьому масиву
        readFromBinary(file, people[i]); // Зчитуємо кожен об'єкт із файлу
    }
    file.close(); // Закриваємо файл
    cout << "Дані зчитано з бінарного файлу.\n"; // Повідомляємо про успіх

    for (int i = 0; i < size; ++i) { // Виводимо зчитані дані
        cout << "Прізвище: " << people[i].surname
            << ", Ім'я: " << people[i].name
            << ", Знак Зодіаку: " << people[i].zodiac_sign
            << ", День народження: " << people[i].birthday[0] << "."
            << people[i].birthday[1] << "." << people[i].birthday[2] << "\n";
    }
}

int main() {
    SetConsoleCP(1251); // Встановлюємо кодування для підтримки української мови
    SetConsoleOutputCP(1251); // Встановлюємо виведення українською мовою
    Zodiac* people = nullptr; // Масив людей, початково порожній
    int size = 0; // Розмір масиву
    bool running = true; // Прапорець для роботи циклу меню

    while (running) { // Основний цикл програми
        displayMenu(); // Виводимо меню
        int choice; // Змінна для вибору користувача
        cin >> choice; // Зчитуємо вибір

        switch (choice) { // Обробка вибору
        case 1:
            addPerson(people, size); // Додаємо нову людину
            break;
        case 2:
            sortByZodiac(people, size); // Сортуємо за знаком Зодіаку
            break;
        case 3: {
            int month; // Змінна для номера місяця
            cout << "Введіть номер місяця: ";
            cin >> month; // Зчитуємо номер місяця
            displayByMonth(people, size, month); // Виводимо людей, народжених у цьому місяці
            break;
        }
        case 4: {
            string filename; // Змінна для імені файлу
            cout << "Введіть ім'я файлу для збереження: ";
            cin >> filename; // Зчитуємо ім'я файлу
            saveToFile(people, size, filename); // Зберігаємо дані у файл
            break;
        }
        case 5: {
            string filename; // Змінна для імені файлу
            cout << "Введіть ім'я файлу для зчитування: ";
            cin >> filename; // Зчитуємо ім'я файлу
            loadFromFile(people, size, filename); // Зчитуємо дані з файлу
            break;
        }
        case 6:
            running = false; // Завершуємо роботу програми
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n"; // Повідомлення про некоректний вибір
        }
    }

    delete[] people; // Звільняємо пам'ять для масиву
    return 0; // Повертаємо успіх виконання програми
}
