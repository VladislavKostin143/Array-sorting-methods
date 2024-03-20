// Array sorting methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class MyMatrix
{
private:
    int rows, columns;
    int* array;
public:
    MyMatrix();
    MyMatrix(int, int);
    int NumRows();
    int NumColumns();
    void SetElement(int, int, int);
    int* GetElement(int, int);
    void Print();
    void PrintElement(int, int);
    vector<int*>* GetRow(int);
    vector<int*>* GetColumn(int);

    bool ValidIndex(int, int);
};
bool MyMatrix::ValidIndex(int i, int j) //проверяет допустимые индексы от 1 до rows или columns
{
    if ((i > 0 && i <= rows) && (j > 0 && j <= columns))
    {
        return true;
    }
    else
    {
        return false;
    };
};

MyMatrix::MyMatrix() :MyMatrix(2, 2) { cout << "Конструктор по умолчанию\n"; };

MyMatrix::MyMatrix(int i, int j)
{
    rows = i, columns = j;
    array = (int*)malloc(sizeof(int) * i * j);
};
void MyMatrix::SetElement(int i, int j, int value)
{
    if (ValidIndex(i, j))
    {
        *(array + (i - 1) * columns + j - 1) = value;
    }
    else
    {
        cout << "Ошибка записи элемента (" << i << "," << j << ")\n";
    }
};
void MyMatrix::PrintElement(int i, int j)
{
    if (ValidIndex(i, j))
    {
        //std::cout << "["<<i<<","<<j<<"]="<<*(array+i*columns+j) << " ";
        cout << *(array + (i - 1) * columns + j - 1);
    }
    else
    {
        cout << "Ошибка печати элемента." << i << " " << j << "\n";
    }
};

int* MyMatrix::GetElement(int i, int j)
{
    if (ValidIndex(i, j))
    {
        return (array + (i - 1) * columns + j - 1);
    }
    else
    {
        return array;//возвращаем первый элемент
    }
};
vector<int*>* MyMatrix::GetRow(int ipar)
{
    if (ipar > 0 && ipar <= rows)
    {
        vector<int*>* result = new vector<int*>{};
        for (int j = 1; j <= NumColumns(); j++)
        {
            result->push_back(GetElement(ipar, j));
        }
        return result;
    }
    else { cout << "Ошибка получения строки " << ipar << "\n"; return nullptr; }
};

vector<int*>* MyMatrix::GetColumn(int jpar)
{
    if (jpar > 0 && jpar <= columns)
    {
        vector<int*>* result = new vector<int*>{};
        for (int i = 1; i <= NumRows(); i++)
        {
            result->push_back(GetElement(i, jpar));
        }
        return result;
    }
    else { cout << "Ошибка получения колонки " << jpar << "\n"; return nullptr; }
};


void MyMatrix::Print()
{
    cout << "\n\t ";
    for (int j = 1; j <= NumColumns(); j++)
    {
        cout << j << "\t ";
    }
    cout << "\n";
    for (int i = 1; i <= NumRows(); i++)
    {
        cout << i << "\t ";
        for (int j = 1; j <= NumColumns(); j++)
        {
            PrintElement(i, j);
            cout << "\t";
        }
        cout << "\n";
    }
};

int MyMatrix::NumRows() { return rows; };
int MyMatrix::NumColumns() { return columns; };

class ISort
{
public:

    ISort() {title="не задан";duration=0;comparisions=0;replacements=0; };
    ~ISort() = default;
    virtual void sort(vector<int*>*) {};
    void run(vector<int*>*);
    void print();
protected:
    string title;
private:
    int duration;
    int comparisions;
    int replacements;
};

void ISort::print() { cout << "Метод " << title << " вренмя " << duration << " сек сравнений " << comparisions << " замен " << replacements << "\n"; };
void ISort::run(vector<int*>* V) 
{   int starttime = (int)time(NULL);
    sort(V); 
    duration = (int)time(NULL) - starttime;
    print(); 
    };

class SimpleSort :public ISort 
{public:
    SimpleSort() :ISort() { title = "простая сортировка"; };
    ~SimpleSort() {};
    void sort(vector<int*>*) { cout << "сортируем"; };
};

int main()
{
    setlocale(LC_ALL, "RU");
    cout << "____________________________________\n";
    MyMatrix M(8, 9);
    for (int i = 1; i <= M.NumRows(); i++)
    {
        for (int j = 1; j <= M.NumColumns(); j++)
        {
            M.SetElement(i, j, rand());
        }

    }
    M.Print();

    cout << "\n2 строка\t";
    vector<int*>* second_row = M.GetRow(2);
    vector<int*>* second_column = M.GetColumn(2);
    for (int* i : *second_row)
    {
        cout << *i << "\t";
    }

    cout << "\n2 колонка\t";
    for (int* j : *second_column)
    {
        cout << *j << "\t";
    }

    SimpleSort *S1=new SimpleSort();
    S1->run(second_row);
    

    cout << "\nРабота завершена\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
