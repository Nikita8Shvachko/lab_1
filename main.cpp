#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct Node {
    string word;
    int important_number;
    Node *next;
};

Node *create_node(string data1, int data2) {
    Node *node = new Node;
    node->word = data1;
    node->important_number = data2;
    node->next = nullptr;
    return node;
}

void add_node_increasong_filter(Node *&head, string data1, int data2) {
    Node *new_node = create_node(data1, data2);
    Node *current = head;
    Node *prev = nullptr;
    bool duplicate = false;
    while (current != nullptr) {
        if (data2 == current->important_number) {
            cerr << "Ошибка Ключевое число " << data2 << " уже есть." << endl;//дупликат найден
            duplicate = true;
            break;
        } else if (data2 < current->important_number) {//не найден
            new_node->next = current;
            if (prev == nullptr) {
                head = new_node;//вставка в начало
            } else {
                prev->next = new_node;//вставка в середину
            }
            duplicate = false;
            break;
        }

        prev = current;
        current = current->next;
    }
    // Если не было дубликата и  не вставлен в середину то в конец
    if (!duplicate && current == nullptr) {
        if (prev == nullptr) {
            head = new_node;
        } else {
            prev->next = new_node;
        }
    }
}

void destroy_node(Node *node) {
    delete node;
}

void desstroy_list(Node *&head) {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        destroy_node(current);
        current = next;
    }
    head = nullptr;
}

void read_file_into_list(string filename, Node *&head) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла" << endl;
        return;
    }

    string data1;
    int data2;

    while (file >> data1 >> data2) {
        Node *new_node = create_node(data1, data2);

        add_node_increasong_filter(head, data1, data2);
    }
    file.close();
}

void print_list(Node *head) {
    Node *current = head;
    while (current != nullptr) {
        cout << current->word << " " << current->important_number << endl;
        current = current->next;
    }
}

void find_in_list(Node *head, int key) {
    Node *current = head;
    while (current != nullptr) {
        if (current->important_number == key) {
            cout << current->word << " " << current->important_number << endl;
            return;
        }
        current = current->next;
    }
    cout << "Ключ слово - " << key << " нет" << endl;
}

int main() {
    string filename = "data.txt";
    Node *head = nullptr;
    read_file_into_list(filename, head);
    print_list(head);
    find_in_list(head, 3);
    string test, test_n;
    cin >> test >> test_n;
    cout << endl;
    add_node_increasong_filter(head, test, stoi(test_n));
    print_list(head);
    find_in_list(head, 3);
    desstroy_list(head);
    return 0;
}
