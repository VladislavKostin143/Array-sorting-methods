// Array sorting methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include "MyMatrix.cs"
#include "ISort.cs"


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
    