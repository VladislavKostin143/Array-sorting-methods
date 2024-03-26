// Array sorting methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

void print_vector(vector<int*>* V)
{
    for (int* i : *V) { cout << *i << " "; }
    cout << "\n";
};

int GetSortingValue(int value) 
{
    int result =0,rest= value;
    while (rest != 0) 
        { 
          result += rest%10;
          rest /= 10;
        }
    return result;
};

class MyMatrix
{
private:
    int rows, columns;
    int* array;
public:
    MyMatrix();
    MyMatrix(int, int);
    MyMatrix(MyMatrix *);
    int NumRows();
    int NumColumns();
    void RandomFill();
    void SetElement(int, int, int);
    void SetElement(int, int, int *);
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
    array = (int*)malloc(sizeof(int*) * i * j);//выделяем память под массив указателей на int
};

MyMatrix::MyMatrix(MyMatrix *M) : MyMatrix(M->rows, M->columns)
{
    
    for (int i = 0; i < rows * columns; i++)
    {
        array[i] = (int)malloc(sizeof(int));//выделяем память под новый int для каждого элемента нового массива, получаемого копированием
        *(array+i)=M->array[i];
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

void MyMatrix::SetElement(int i, int j, int *value) {SetElement(i,j,*value);};

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
    cout <<setw(10)<< *GetElement(i,j)<<"(" << setw(3)<<GetSortingValue(*GetElement(i, j) )<<")";
};




vector<int*>* MyMatrix::GetRow(int ipar)
{
    if (ipar > 0 && ipar <= rows)
    {
        vector<int*>* result = new vector<int*>{};
        for (int j = 1; j <= NumColumns(); j++)
        {
            int *ptr = (int*)malloc(sizeof(int));
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
        vector<int*>* result = new vector<int*>{};
        for (int i = 1; i <= NumRows(); i++)
        {
            int* ptr = (int*)malloc(sizeof(int));
            *ptr = *GetElement(jpar, i);

            result->push_back(ptr);
        }
        return result;
    }
    else { cout << "Ошибка получения колонки " << jpar << "\n"; return nullptr; }
};

void MyMatrix::CopyRow(int ipar, vector<int*> *V)
{   
    cout << "копирование строки "<<ipar<<"\n";
    print_vector(V);
    int j = 0;
    for (int* i : *V) 
    {
        SetElement(ipar, j + 1, i);
        //SetElement(ipar, j + 1, j);
        j++;
    }
};

void MyMatrix::CopyColumn(int ipar, vector<int*>* V)
{
    cout << "копирование колонки " << ipar << "\n";
    print_vector(V);
    int j = 0;
    for (int* i : *V)
    {
        SetElement(j+1, ipar, i);
        //SetElement(ipar, j + 1, j);
        j++;
    }
};





void MyMatrix::Print()
{
    cout << "\n  ";
    for (int j = 1; j <= NumColumns(); j++)
    {
        cout << setw(15)<<right<<j;
    }
    cout << "\n";
    for (int i = 1; i <= NumRows(); i++)
    {
        cout <<setw(2)<< i;
        for (int j = 1; j <= NumColumns(); j++)
        {
            PrintElement(i, j);
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
    void clear();
    //void print_vector(vector<int*>*);
protected:
    string title;
    int duration;
    int comparisions;
    int replacements;
    int elements;
};



void ISort::print() { cout << "Элементов " << elements << ", время " << duration << " наносекунд, сравнений " << comparisions << ", замен " << replacements << "\n"; };
void ISort::clear() { elements = 0; duration = 0; comparisions = 0; replacements = 0; };
void ISort::run(vector<int*>* V) 
{
    clear();
    elements = V->size();
    cout << "\n" << title << "\n";
    cout << "Исходный вектор:\n";
    print_vector(V);
    auto start = std::chrono::system_clock::now();
    sort(V); 
    auto end = std::chrono::system_clock::now();
    duration = (int)chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Сотрированный вектор:\n";
    print_vector(V);
    print(); 

    };


class BubbleSort :public ISort
{public:
    BubbleSort() :ISort() { title = "Сортировка пузырьком"; };
    ~BubbleSort() {};
    void sort(vector<int*>*);
};

void BubbleSort::sort(vector<int*>*V)
{
    unsigned iterations = elements - 1;
    while (iterations > 0)
    {
    for (unsigned i = 0; i < iterations; i++)
    {
        int* PCurrentValue = (*V)[i]; //текущией элемент
        int* PNextValue = (*V)[i + 1];//следующий элемент
        comparisions++;
        if (GetSortingValue(*PCurrentValue) > GetSortingValue(*PNextValue))
        {
            replacements++;
            int* temp = PNextValue;
            (*V)[i + 1] = PCurrentValue;
            (*V)[i] = temp;
        }
    }
    iterations--;
    }
};


class SelectionSort :public ISort
{
public:
    SelectionSort() :ISort() { title = "Сортировка отбором"; };
    ~SelectionSort() {};
    void sort(vector<int*>*);
};

void SelectionSort::sort(vector<int*>* V)
{
    unsigned iterations = elements,start = 0;
    while (iterations > 0)
    {
        int* PMinValue = (*V)[start]; //минимальный элемент    
        unsigned MinIndex = start;
        for (unsigned i = start; i < (unsigned)elements; i++)
        {
            int* PCurrentValue = (*V)[i]; //текущией элемент
            comparisions++;
            if (GetSortingValue(*PCurrentValue) < GetSortingValue(*PMinValue))
                {
                PMinValue = PCurrentValue;
                MinIndex = i;
            }
            
        }
        int* temp = (*V)[start];
        (*V)[start] = PMinValue;
        (*V)[MinIndex] = temp;
        replacements++;
        start++;
        iterations--;
    }
};


class InsertionSort :public ISort
{
public:
    InsertionSort() :ISort() { title = "Сортировка вставкой"; };
    ~InsertionSort() {};
    void sort(vector<int*>*);
};

void InsertionSort::sort(vector<int*>* V)
{
    for (int i = 1; i < elements; i++)
        {
        for (int j = i; j > 0 && GetSortingValue(*((*V)[j - 1])) > GetSortingValue(*((*V)[j])); j--) // пока j>0 и элемент j-1 > j, x-массив int
            {
                swap((*V)[j - 1], (*V)[j]);
                replacements++;
                comparisions++;
            }
        }
};

class ShellSort :public ISort
{
public:
    ShellSort() :ISort() { title = "Метод Шелла"; };
    ~ShellSort() {};
    void sort(vector<int*>*);
};

void ShellSort::sort(vector<int*>* V)
{
    int i, j, step,*tmp;
    for (step = elements / 2; step > 0; step /= 2)
        for (i = step; i < elements; i++)
        {
            tmp = (*V)[i];
            for (j = i; j >= step; j -= step)
            {
                comparisions++;
                if (GetSortingValue(*tmp) < GetSortingValue(*((*V)[j-step])))
                    (*V)[j] = (*V)[j - step];
                else
                    break;
            }
            replacements++;
            (*V)[j] = tmp;
        }
};

class QuickSort :public ISort
{
public:
    QuickSort() :ISort() { title = "Быстрая сортировка"; };
    ~QuickSort() {};
    void sort(vector<int*>*);
    void QSort(vector<int*>*,int,int);
};

void QuickSort::QSort(vector<int*>* V, int left, int right)
    {
        if (right <= left)
            return;
        int ipi = left + (right - left)/2;
        swap((*V)[ipi], (*V)[right]);
        replacements++;
        int x = *((*V)[right]);
        int m = left;
        for (int i = left; i < right; i++)
            {
            comparisions++;
            if (GetSortingValue(*((*V)[i])) <= GetSortingValue(x))
                {
                swap((*V)[i], (*V)[m++]);
                replacements++;
                }
            }
        swap((*V)[m], (*V)[right]);
        QSort(V, left, m);
        QSort(V, m + 1, right);
    }


void QuickSort::sort(vector<int*>* V)
{
    QSort(V, 0, elements-1);
};



int main()
{
    setlocale(LC_ALL, "RU");
    cout << "____________________________________\n";
    MyMatrix M(8, 9);
    M.RandomFill();
    MyMatrix Mcopy(&M);

    Mcopy.Print();
    
    vector<int*>* row1 = Mcopy.GetRow(1);
    vector<int*>* row2 = Mcopy.GetRow(2);
    vector<int*>* row3 = Mcopy.GetRow(3);
    vector<int*>* row4 = Mcopy.GetRow(4);
    vector<int*>* row5 = Mcopy.GetRow(5);

    
    vector<int*>* column2 = Mcopy.GetColumn(2);
    vector<int*>* column4 = Mcopy.GetColumn(4);
    vector<int*>* column6 = Mcopy.GetColumn(4);
    vector<int*>* column8 = Mcopy.GetColumn(5);


    BubbleSort*S1=new BubbleSort();
    SelectionSort* S2 = new SelectionSort();
    InsertionSort* S3 = new InsertionSort();
    ShellSort* S4 = new ShellSort();
    QuickSort* S5 = new QuickSort();
    S1->run(column2);
    Mcopy.CopyColumn(2, column2);
    S2->run(column4);
    Mcopy.CopyColumn(4, column4);
    
    cout << "\nСортированная матрица\n";
    Mcopy.Print();

    cout << "\nИсходная матрица\n";
    M.Print();

    cout << "\nGetSortingValue(1131230)"<< GetSortingValue(1131230) <<"\n";

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
    