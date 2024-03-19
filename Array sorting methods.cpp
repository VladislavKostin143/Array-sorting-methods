// Array sorting methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class MyMatrix 
{
private: 
    int rows,columns;
    int* array;
public: 
    MyMatrix();
    MyMatrix(int, int);
    int NumRows();
    int NumColumns();
    void SetElement(int, int,int);
    void Print();
    void PrintElement(int, int);
};
MyMatrix::MyMatrix() :MyMatrix(2,2) { std::cout << "Конструктор по умолчанию\n"; };
MyMatrix::MyMatrix(int i, int j) 
    { columns = i, rows = j; 
      array = (int*)malloc(sizeof(int) * i * j); 
    };
void MyMatrix::SetElement(int i, int j, int value) 
    { if ((i < rows) && (j < columns)) 
        { *(array+i* columns +j) = value; }
     else 
        { std::cout << "Ошибка записи элемента.\n"; } 
    };
void MyMatrix::PrintElement(int i, int j)
{
    if ((i < rows) && (j < columns))
    {
        std::cout << "["<<i<<","<<j<<"]="<<*(array+i*columns+j) << " ";
    }
    else
    {
        std::cout << "Ошибка печати элемента."<< i<< " " << j << "\n";
    }
};


void MyMatrix::Print()
{
    for (int i = 0; i < NumRows(); i++)
    {
        std::cout << "i="<< i <<" ";
        for (int j = 0; j <NumColumns(); j++)
        {
            std::cout << "j=" << j << "  ";
            PrintElement(i, j);
            std::cout << "\t";
        }
        std::cout << "\n";
    }
};

int MyMatrix::NumRows() { return rows; };
int MyMatrix::NumColumns() { return columns; };


int main()
{
    setlocale(LC_ALL, "RU");
    std::cout << "____________________________________\n";
    MyMatrix M(3,4);
    for (int i = 0; i < M.NumRows(); i++) 
        {
        for (int j = 0; j < M.NumColumns(); j++)
            { M.SetElement(i, j, rand()); }

        }

    

    M.Print();
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
