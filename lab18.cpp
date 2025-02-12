//#include <iostream>
//#include <string>
//#include <list>
//
//using namespace std;

//class HashTable {
//private:
//	//Реализация Хэш-таблицы с помощью списка
//	list<string>* table;
//	//Количесвто элементов в таблице
//	int total_elements;
//
//
//	//Хэш функция (подставьте свою функцию сюда)
//	int getHash(string key) {
//
//		int s = 0;
//		for (int i = 0; i < key.size(); i++) {
//			s += int(key[i]);
//		}
//		return s % total_elements;
//	}
//public:
//	//Конструктор который создает массив из односвязнных списков
//	HashTable(int n) {
//		if (n > 0) {
//			total_elements = n;
//			table = new list<string>[total_elements];
//		}
//		else {
//			cout << "..:: Incorrect size! ::.." << endl;
//		}
//	}
//	~HashTable() {
//		delete[] table; // Деструктор для освобождения памяти
//	}
//	//Проверка наличия значения в таблице
//	bool Contains(string key) {
//		int index = getHash(key);
//		for (const auto& elem : table[index]) {
//			if (elem == key) {
//				return true;
//			}
//		}
//		return false;
//	}
//	//Вставка элемента
//	void InsertElement(string key) {
//		if (Contains(key) == false) {
//			table[getHash(key)].push_front(key);
//		}
//		else {
//			cout << "..:: Exists in this table! ::.." << endl;
//		}
//	}
//	void removeElement(string key) {
//		int x = getHash(key);
//
//		list<string>::iterator i;
//		for (i = table[x].begin(); i != table[x].end(); i++) {
//
//			if (*i == key)
//				break;
//		}
//		if (i != table[x].end())
//			table[x].erase(i);
//	}
//	void printAll() {
//		int total_collisions = 0;  // Счетчик коллизий
//
//		for (int i = 0; i < total_elements; i++) {
//			int elements_in_bucket = table[i].size();
//			int bucket_collisions = max(0, elements_in_bucket - 1);  // Коллизии для текущего бакета
//			total_collisions += bucket_collisions;
//
//			cout << "Index " << i << ": ";
//			for (string j : table[i])
//				cout << j << " => ";
//			cout << endl;
//		}
//
//		cout << "\n[Total collisions: " << total_collisions << "]\n";
//	}
//};
//
//int main() {
//	HashTable ht(3);
//	string arr[] = {"Masha", "Sasha", "Andrey", "Kirill", "Masha"};
//
//	for (int i = 0; i < 5; i++) {
//		ht.InsertElement(arr[i]);
//	}
//    cout << "..:: Hash Table ::.." << endl;
//    ht.printAll();
//
//	ht.removeElement("Masha");
//    cout << endl << "..:: After deleting Masha ::.." << endl;
//    ht.printAll();
//
//    return 0;
//
//}


#include <iostream>
#include <list>
#include <string>
using namespace std;

struct Student {
    string fio;
    string group;
    int rating;
};

class HashTable {
private:
    // Храним пары: ключ (ФИО) + данные студента
    list<pair<string, Student>>* table;
    int total_elements;

    // Хеш-функция для ФИО
    int getHash(string key) {
        int s = 0;
        for (char c : key) s += static_cast<int>(c);
        return s % total_elements;
    }

public:
    HashTable(int n) {
        if (n > 0) {
            total_elements = n;
            table = new list<pair<string, Student>>[total_elements];
        }
        else {
            throw invalid_argument("Invalid table size!");
        }
    }

    ~HashTable() {
        delete[] table;
    }

    // Вставка студента с проверкой уникальности ФИО
    void InsertElement(Student student) {
        string key = student.fio;
        int index = getHash(key);

        // Проверка на существование записи
        if (Contains(key)) {
            return;
        }

        // Вставка новой записи
        table[index].emplace_front(key, student);
    }

    // Поиск студента по ФИО
    bool Contains(string key) {
        int index = getHash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) return true;
        }
        return false;
    }

    // Удаление студента по ФИО
    void removeElement(string key) {
        int index = getHash(key);
        auto& chain = table[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                return;
            }
        }
        cout << "..:: Student " << key << " not found! ::.." << endl;
    }

    // Вывод
    void printAll() {
        int total_collisions = 0;
        // Подсчет коллизий
        for (int i = 0; i < total_elements; i++) {
            int bucket_size = table[i].size();
            total_collisions += max(0, bucket_size - 1);
        // Вывод бакетов и значений в них
        //    cout << endl << "Bucket " << i << " (" << bucket_size << " elements):";
        //    for (const auto& pair : table[i]) {
        //        cout << endl << "[FIO: " << pair.second.fio
        //            << " | Group: " << pair.second.group
        //            << " | Rating: " << pair.second.rating << "]";
        //    }
        //    cout << endl;
        }
        cout << endl << "Total collisions: " << total_collisions << endl;
    }
};


string GeneratorFIO() {
    string FIO;
    while (FIO.size() != 3) {
        int a = rand() % 100;
        if (a >= 41 && a <= 90) {
            FIO += char(a);
        }
    }
    return FIO;
}

string GeneratorGROUP() {
    return to_string(rand() % 100);
}

int GeneratorRAITING() {
    return rand() % 100;
}


int main() {

    HashTable HT_40(40);
    HashTable HT_75(75);
    HashTable HT_90(90);
    for (int i = 0; i < 100; i++) {
        HT_40.InsertElement({ GeneratorFIO(), GeneratorGROUP(), GeneratorRAITING() });
        HT_75.InsertElement({ GeneratorFIO(), GeneratorGROUP(), GeneratorRAITING() });
        HT_90.InsertElement({ GeneratorFIO(), GeneratorGROUP(), GeneratorRAITING() });
    }
    HT_40.printAll();
    HT_75.printAll();
    HT_90.printAll();
}
