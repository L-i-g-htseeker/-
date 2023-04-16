#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include<Windows.h>
#undef DELETE
//#undef _XMEMORY_


using namespace std;
struct Node
{
    Node() {
        this->title = "";
        this->author = "";
        this->year_of_publication = 0;
        this->publishing_house = "";
        this->quantity_of_pages = 0;
        this->next = nullptr;
    }
    string title;
    string author;
    int year_of_publication;
    string publishing_house;
    int quantity_of_pages;
    Node* next;
};

struct struct_Head
{
    Node* Head;
    int count;
};

struct_Head* CreateStruct();
Node* CreateNode(struct_Head*& Newstruct);
void AddFirst(Node* NewNode, struct_Head*& Newstruct);
void AfterFind(int index, Node* NewNode, struct_Head*& Newstruct);
void AddEnd(Node* NewNode, struct_Head*& Newstruct);
Node* Find_index(int i, struct_Head*& Newstruct);
void Find(int ind, struct_Head*& Newstruct);
void Delete_q(int index, struct_Head*& Newstruct);
void Output(struct_Head*& Newstruct);
void save(struct_Head*& Newstruct, int &count);
void load(struct_Head*& Newstruct, int& count);
void add_bin(struct_Head*& Newstruct, int &count_file);
void sort_title(struct_Head*& Newstruct);
void sort_author(struct_Head*& Newstruct);
void sort_year_of_publication(struct_Head*& Newstruct);

enum
{
    ADD = 1,
    DELETE,
    FIND,
    SAVE,
    LOAD,
    ADD_BIN,
    OUTPUT,
    CLOSE,
    SORT
};

enum
{
    TITLE = 1,
    AUTHOR,
    YEAR_OF_PUBLICATION
};

int main()
{
    struct_Head* Head;
    Head = CreateStruct();
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    int count_file = 0;
    cout << "Программа односвязного списка с головным элементом, представляющая собой список книг" << endl;
    cout << "====================================" << endl;
    int n = 0;
    cout << "Что вы хотите сделать?" << endl;
    while (n != 8)
    {
        cout << "1) Добавить элемент" << endl;
        cout << "2) Удалить элемент из списка\n3) Найти элемент в списке" << endl;
        cout << "4) Сохранить список в бинарный файл\n5) Загрузить список с бинарного файла" << endl;
        cout << "6) Добавить несуществующие элементы списка с бинарного файла" << endl;
        cout << "7) Вывод списка на экран" << endl;
        cout << "8) Выход из программы" << endl;
        cout << "9) Сортировать элементы" << endl;
        cin >> n;
        switch (n)
        {
        case ADD:
        {
            int a;
            cout << "1) В начало списка" << endl;
            cout << "2) В конец списка" << endl;
            cout << "3) После заданного элемента" << endl;
            cin >> a;
            switch (a)
            {
            case 1:
            {
                Node* NewNode = CreateNode(Head);
                AddFirst(NewNode, Head);
                break;
            }
            case 2:
            {
                Node* NewNode = CreateNode(Head);
                AddEnd(NewNode, Head);
                break;
            }
            case 3:
            {
                int index;
                cout << "Введите порядковый номер элемента:" << endl;
                cin >> index;
                if (index > Head->count)
                {
                    cout << "Такого элемента нет :(" << endl;
                    break;
                }
                Node* NewNode = CreateNode(Head);
                AfterFind(index, NewNode, Head);
                break;
            }
            default:
                cout << "Выберите число ТОЛЬКО от 1 до 3!!!" << endl;
            }
        }
        break;
        case DELETE:
            {
            int index;
            cout << "Выберите элемент, который хотите удалить:" << endl;
            cin >> index;
            Delete_q(index, Head);
            }
            break;
        case FIND:
            {
            int index;
            cout << "Произвести поиск элемента в списке по:" << endl;
            cout << "1) Названию" << endl;
            cout << "2) Автору" << endl;
            cout << "3) Году издания" << endl;
            cin >> index;
            Find(index, Head);
            }
            break;
        case SAVE:
            save(Head, count_file);
            break;
        case LOAD:
            load(Head, count_file);
            break;
        case ADD_BIN:
            add_bin(Head, count_file);
            break;
        case OUTPUT:
            Output(Head);
            break;
        case CLOSE:
            n = 8;
            break;
        case SORT:
            cout << "По какому критерию сортировать?" << endl;
            int a;
            cout << "1) По названию" << endl;
            cout << "2) По автору" << endl;
            cout << "3) По году" << endl;
            cin >> a;
            switch (a)
            {
            case 1:
                sort_title(Head);
                break;
            case 2:
                sort_author(Head);
                break;
            case 3:
                sort_year_of_publication(Head);
                break;
            default:

                break;
            }
            break;
        default:
            cout << "Выберите число только от 1 до 8!" << endl;
            break;
        }
        cout << "====================================" << endl;
        cout << endl;
    }
    return 0;
}

struct_Head* CreateStruct()
{
    struct_Head* NewStruct = new struct_Head;
    NewStruct->count = 0;
    NewStruct->Head = nullptr;
    return NewStruct;
}

Node* CreateNode(struct_Head*& Newstruct)
{
    Node* NewNode = new Node;
    cout << "Введите название книги:" << endl;
    cin >> NewNode->title;
    cout << "Введите автора книги:" << endl;
    cin >> NewNode->author;
    cout << "Введите год издания:" << endl;
    cin >> NewNode->year_of_publication;
    cout << "Введите издательство:" << endl;
    cin >> NewNode->publishing_house;
    cout << "Введите кол-во страниц книги:" << endl;
    cin >> NewNode->quantity_of_pages;
    NewNode->next = nullptr;
    Newstruct->count++;
    return NewNode;
}

void AddFirst(Node* NewNode, struct_Head*& Newstruct)
{
    if (!Newstruct->Head)
    {
        Newstruct->Head = NewNode;
        return;
    }
    else
    {
        NewNode->next = Newstruct->Head;
        Newstruct->Head = NewNode;
    }
}

void AfterFind(int index, Node* NewNode, struct_Head*& Newstruct)
{
    try {
        Node* q = Find_index(index, Newstruct);
        NewNode->next = q->next;
        q->next = NewNode;
    }
    catch (const exception& ex) {
        cout << ex.what() << endl;
    }
}

void AddEnd(Node* NewNode, struct_Head*& Newstruct)
{
    Node* q = Newstruct->Head;
    while (q->next)q = q->next;
    q->next = NewNode;
}

Node* Find_index(int i, struct_Head*& Newstruct)
{
    Node* q = Newstruct->Head;
    for (int j = 1; j < i; j++) {
        if (q->next) {
            q = q->next;
        }
        else throw exception("Такого элемента в списке нет");
    }
    return q;
}


void Find(int ind, struct_Head*& Newstruct)
{
    Node* q = Newstruct->Head;
    if (ind == TITLE)
    {
        string title;
        cout << "Введите название книги:" << endl;
        cin >> title;
        while (q->title != title&&q) q = q->next;
        if (!q) {
            cout << "Такой книги нет" << endl;
            return;
        }
        cout << setw(20) << "Название книги" << setw(20) << "Автор книги" << setw(20) << "Год издания" << setw(20) << "Издательство" << setw(20) << "Кол-во страниц" << endl;
        cout << setw(20) << q->title << setw(20) << q->author << setw(20) << q->year_of_publication << setw(20) << q->publishing_house << setw(20) << q->quantity_of_pages << endl;
    }
    if (ind == AUTHOR)
    {
        string author;
        cout << "Введите автора книги:" << endl;
        cin >> author;
        while (q->author != author && q) q = q->next;
        if (!q) {
            cout << "Такой книги нет" << endl;
            return;
        }
        cout << setw(20) << "Название книги" << setw(20) << "Автор книги" << setw(20) << "Год издания" << setw(20) << "Издательство" << setw(20) << "Кол-во страниц" << endl;
        cout << setw(20) << q->title << setw(20) << q->author << setw(20) << q->year_of_publication << setw(20) << q->publishing_house << setw(20) << q->quantity_of_pages << endl;
    }
    if (ind == YEAR_OF_PUBLICATION)
    {
        int year;
        cout << "Введите дату публикации книги:" << endl;
        cin >> year;
        while (q->year_of_publication != year && q) q = q->next;
        if (!q) {
            cout << "Такой книги нет" << endl;
            return;
        }
        cout << setw(20) << "Название книги" << setw(20) << "Автор книги" << setw(20) << "Год издания" << setw(20) << "Издательство" << setw(20) << "Кол-во страниц" << endl;
        cout << setw(20) << q->title << setw(20) << q->author << setw(20) << q->year_of_publication << setw(20) << q->publishing_house << setw(20) << q->quantity_of_pages << endl;
    }
}

void Delete_q(int index, struct_Head*& Newstruct)
{
    Node* q = nullptr;
    try {
        q = Find_index(index, Newstruct);
    }
    catch (const exception& ex) {
        cout << ex.what() << endl;
        return;
    }
    if (q == Newstruct->Head) {
        Newstruct->Head = q->next;
        Newstruct->count--;
        delete q;
        return;
    }
    Node* p = Newstruct->Head;
    while (p && p->next != q) {
        p = p->next;
    }
    p->next = q->next;
    delete q;
    Newstruct->count--;
}

void Output(struct_Head*& Newstruct)
{
    Node* q = Newstruct->Head;
    cout << setw(20) << "Название книги"
         << setw(20) << "Автор книги" 
         << setw(20) << "Год издания" 
         << setw(20) << "Издательство"
         << setw(20) << "Кол-во страниц"
         << setw(20) << endl;

    while (q)
    {
        cout << setw(20) << q->title
             << setw(20) << q->author
             << setw(20) << q->year_of_publication
             << setw(20) << q->publishing_house
             << setw(20) << q->quantity_of_pages
             << setw(20) << endl;
        q = q->next;
    }
}

void save(struct_Head*& Newstruct, int &count_file)
{
    string file = "MyFile.txt";
    fstream fs;
    fs.exceptions(fstream::badbit | fstream::failbit);
    try
    {
        fs.open(file, fstream::out | fstream::binary);
        cout << "Файл успешно открыт!" << endl;
    }
    catch (const fstream::failure& ex)
    {
        cout << ex.what() << endl;
        cout << ex.code() << endl;
    }
    Node* q = Newstruct->Head;
    while (q)
    {
        fs.write((char*)&(*q), sizeof(Node));
        q = q->next;
        count_file++;
    }
    cout << "====================================" << endl;
    cout << "Данные успешно сохранены!" << endl;
    fs.close();
}

void load(struct_Head*& Newstruct, int&count_file)
{
    string file = "MyFile.txt";
    fstream fs;
    fs.exceptions(fstream::badbit | fstream::failbit);
    try
    {
        fs.open(file, fstream::in | fstream::binary);
        cout << "Файл успешно открыт!" << endl;
    }
    catch (const fstream::failure& ex)
    {
        cout << ex.what() << endl;
        cout << ex.code() << endl;
    }

    Node* q = Newstruct->Head;
    while (q->next) q = q->next;
    try {
        for (int i = 0; i < count_file; i++) {
            Node* newNode = new Node;
            fs.read((char*)&(*newNode), sizeof(Node));
            q->next = newNode;
            q = newNode;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка чтения файла" << endl;
        cout << e.what() << endl;
    }
    fs.close();
}

void add_bin(struct_Head*& Newstruct, int&count_file)
{
    string file = "MyFile.txt";
    fstream fs;
    fs.exceptions(fstream::badbit | fstream::failbit);
    try
    {
        fs.open(file, fstream::in | fstream::binary);
        cout << "Файл успешно открыт!" << endl;
    }
    catch (const fstream::failure& ex)
    {
        cout << ex.what() << endl;
        cout << ex.code() << endl;
    }   
    Node* q = Newstruct->Head;
    try {
        for (int i = 0; i < count_file; i++) {
            Node* newNode = new Node;
            bool replay = false;
            fs.read((char*)newNode, sizeof(Node));
            /*if (!fs.read((char*)newNode, sizeof(Node))) {
                break;
            }*/
            q = Newstruct->Head;
            while (q) {
                if (q->author == newNode->author && q->publishing_house == newNode->publishing_house && q->quantity_of_pages == newNode->quantity_of_pages &&
                    q->title == newNode->title && q->year_of_publication == newNode->year_of_publication)
                {
                    replay = true;
                    delete newNode;
                    newNode = nullptr;
                    break;
                }
                q = q->next;
            }
            if (!replay) {
               /* q = Newstruct->Head;
                while (q->next) q = q->next;
                q->next = newNode;
                newNode->next = nullptr;
                Newstruct->count++;*/
                AddEnd(newNode, Newstruct);
                newNode->next = nullptr;
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка чтения файла" << endl;
        cout << e.what() << endl;
    }
    fs.close();
}
void sort_title(struct_Head*& Newstruct)
{
    Node* q = Newstruct->Head;
    for (int i = 1; i <= Newstruct->count; i++) {
        q = Newstruct->Head;
        bool flag = true;
        for (int j = 1; j <= Newstruct->count - i; j++)
        {
            bool swap_ = false;
            if (q->title > q->next->title) {
                swap_ = true;
                flag = false;
                Node* p = q->next;
                q->next = q->next->next;
                if (q == Newstruct->Head) {
                    p->next = q;
                    Newstruct->Head = p;
                }
                else {
                    Node* temp = Newstruct->Head;
                    while (temp->next != q)temp = temp->next;
                    temp->next = p;
                    p->next = q;
                }
            }
            if (!swap_) q = q->next;
        }
        if (flag) {
            break;
        }
    }
}

void sort_author(struct_Head*& Newstruct)
{
    Node* q = Newstruct->Head;
    for (int i = 1; i <= Newstruct->count; i++) {
        q = Newstruct->Head;
        bool flag = true;
        for (int j = 1; j <= Newstruct->count - i; j++)
        {
            bool swap_ = false;
            if (q->author > q->next->author) {
                swap_ = true;
                flag = false;
                Node* p = q->next;
                q->next = q->next->next;
                if (q == Newstruct->Head) {
                    p->next = q;
                    Newstruct->Head = p;
                }
                else {
                    Node* temp = Newstruct->Head;
                    while (temp->next != q)temp = temp->next;
                    temp->next = p;
                    p->next = q;
                }
            }
            if (!swap_) q = q->next;
        }
        if (flag) {
            break;
        }
    }
}

void sort_year_of_publication(struct_Head*& Newstruct)
{
    Node* q = Newstruct->Head;
    for (int i = 1; i <= Newstruct->count; i++) {
        q = Newstruct->Head;
        bool flag = true;
        for (int j = 1; j <= Newstruct->count - i; j++)
        {
            bool swap_ = false;
            if (q->year_of_publication > q->next->year_of_publication) {
                swap_ = true;
                flag = false;
                Node* p = q->next;
                q->next = q->next->next;
                if (q == Newstruct->Head) {
                    p->next = q;
                    Newstruct->Head = p;
                }
                else {
                    Node* temp = Newstruct->Head;
                    while (temp->next != q)temp = temp->next;
                    temp->next = p;
                    p->next = q;
                }
            }
            if (!swap_) q = q->next;
        }
        if (flag) {
            break;
        }
    }
}