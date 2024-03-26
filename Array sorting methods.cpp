// Array sorting methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include "MyMatrix.cs"
#include "ISort.cs"


int main()
{
    setlocale(LC_ALL, "RU");
    cout << "____________________________________\n";
    MyMatrix M(10, 8);
    M.RandomFill();
    MyMatrix Mcopy(&M);
    cout << "\nИсходная матрица\n";
    Mcopy.Print();

    

    vector<ISort*> Methods{};

    Methods.push_back(new BubbleSort());
    Methods.push_back(new SelectionSort());
    Methods.push_back(new InsertionSort());
    Methods.push_back(new QuickSort());
    Methods.push_back(new ShellSort());


    cout << "\nСортировки \n\n";
    for (ISort* method : Methods)
    {
        method->clear();//обнуление счетчиков
        for (int j = 2; j <= Mcopy.NumColumns(); j += 2)
        {
            vector<int*>* column = Mcopy.GetColumn(j);
            method->run(column);
            Mcopy.CopyColumn(j, column);
        }
        method->print();//вывод счетчиков
    }


    
    cout << "\nСортированная матрица\n";
    Mcopy.Print();

  

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
    