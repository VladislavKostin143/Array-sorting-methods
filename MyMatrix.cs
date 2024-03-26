#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <windows.h>



using namespace std;

int GetSortingValue(int value)
{
    int result = 0, rest = value;
    while (rest != 0)
    {
        result += rest % 10;
        rest /= 10;
    }
    return result;
};

void print_vector(vector<int*>* V)
{
    for (int* i : *V) { cout << *i << "("<<GetSortingValue(*i)<<") "; }
    cout << "\n";
};



class MyMatrix
{
    private:
    int rows, columns;
    int* array;
    public:
    MyMatrix();
    MyMatrix(int, int);
    MyMatrix(MyMatrix*);
    int NumRows();
    int NumColumns();
    void RandomFill();
    void SetElement(int, int, int);
    void SetElement(int, int, int*);
    int* GetElement(int, int);
    void Print();
    void PrintElement(int, int);
    vector<int*>* GetRow(int);
    void CopyRow(int, vector<int*>*);
    void CopyColumn(int, vector<int*>*);
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

MyMatrix::MyMatrix() : MyMatrix(2, 2) { cout << "Конструктор по умолчанию\n"; };

MyMatrix::MyMatrix(int i, int j)
{
    rows = i, columns = j;
    array = (int*) malloc(sizeof(int*)* i * j);//выделяем память под массив указателей на int
};

MyMatrix::MyMatrix(MyMatrix * M) : MyMatrix(M->rows, M->columns)
{

    for (int i = 0; i < rows * columns; i++)
    {
        array[i] = (int)malloc(sizeof(int));//выделяем память под новый int для каждого элемента нового массива, получаемого копированием
        *(array + i) = M->array[i];
    }
};

void MyMatrix::RandomFill()
{
    for (int i = 0; i < rows * columns; i++)
    {
        array[i] = (int)malloc(sizeof(int));//выделяем память под новый int для каждого элемента нового массива
        *(array + i) = rand();
    }
};

void MyMatrix::SetElement(int i, int j, int value)
{
    if (ValidIndex(i, j))
    {
        array[(i - 1) * columns + j - 1] = (int)malloc(sizeof(int));//выделяем память под новый int для устанавливаемого элемента
        *(array + (i - 1) * columns + j - 1) = value;
    }
    else
    {
        cout << "Ошибка записи элемента (" << i << "," << j << ")\n";
    }
};

void MyMatrix::SetElement(int i, int j, int * value) { SetElement(i, j, *value); };

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

void MyMatrix::PrintElement(int i, int j)
{
    cout << setw(10) << *GetElement(i, j) << "(" << setw(3) << GetSortingValue(*GetElement(i, j)) << ")";
};




vector<int*>* MyMatrix::GetRow(int ipar)
{
    if (ipar > 0 && ipar <= rows)
    {
        vector<int*>* result = new vector<int*> { };
        for (int j = 1; j <= NumColumns(); j++)
        {
            int* ptr = (int*)malloc(sizeof(int));
            *ptr = *GetElement(ipar, j);
            result->push_back(ptr);
        }
        return result;
    }
    else { cout << "Ошибка получения строки " << ipar << "\n"; return nullptr; }
};



vector<int*>* MyMatrix::GetColumn(int jpar)
{
    if (jpar > 0 && jpar <= columns)
    {
        vector<int*>* result = new vector<int*> { };
        for (int i = 1; i <= NumRows(); i++)
        {
            int* ptr = (int*)malloc(sizeof(int));
            *ptr = *GetElement(i,jpar);

            result->push_back(ptr);
        }
        return result;
    }
    else { cout << "Ошибка получения колонки " << jpar << "\n"; return nullptr; }
};

void MyMatrix::CopyRow(int ipar, vector<int*> * V)
{
    int j = 0;
    for (int* i : *V)
    {
        SetElement(ipar, j + 1, i);
        //SetElement(ipar, j + 1, j);
        j++;
    }
};

void MyMatrix::CopyColumn(int ipar, vector<int*> * V)
{
    int j = 0;
    for (int* i : *V)
    {
        SetElement(j + 1, ipar, i);
        //SetElement(ipar, j + 1, j);
        j++;
    }
};





void MyMatrix::Print()
{
    HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);//консоль
    SetConsoleTextAttribute(hnd, 0x9E);//фон голубой,цвет шрифта желтый
      

    cout << "\n    ";
    for (int j = 1; j <= NumColumns(); j++)
    {
        cout << setw(15) << right << j;
    }
    cout << "\n";
    for (int i = 1; i <= NumRows(); i++)
    {
        SetConsoleTextAttribute(hnd, 0x9E);//фон голубой,цвет шрифта желтый
        cout << setw(4) << i;
        SetConsoleTextAttribute(hnd, 0x07);//старый
        for (int j = 1; j <= NumColumns(); j++)
        {
            PrintElement(i, j);
        }
        cout << "\n";
    }
};

int MyMatrix::NumRows() { return rows; };
int MyMatrix::NumColumns() { return columns; };
