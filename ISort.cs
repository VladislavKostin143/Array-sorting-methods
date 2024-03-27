class ISort
{
    public:

    ISort() { title = "не задан"; duration = 0; comparisions = 0; replacements = 0; elements = 0; };
    ~ISort() = default;
    virtual void sort(vector<int*>*) { };
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



void ISort::print() { cout <<left<<setw(30)<< title << " " <<right<< setw(10) << duration << " наносекунд, сравнений " << setw(8) << comparisions << ", замен " << setw(8) << replacements << "\n"; };
void ISort::clear() { elements = 0; duration = 0; comparisions = 0; replacements = 0; };
void ISort::run(vector<int*> * V)
{
    
    elements = V->size();
    //cout << "\n" << title << "\n";
    //cout << "Исходный вектор:\n";
    //print_vector(V);
    auto start = std::chrono::system_clock::now();
    sort(V);
    auto end = std::chrono::system_clock::now();
    duration = (int)chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    //cout << "Сотрированный вектор:\n";
    //print_vector(V);
    

};


class BubbleSort :public ISort
{public:
    BubbleSort() :ISort() { title = "Сортировка пузырьком"; };
~BubbleSort() { };
void sort(vector<int*>*);
};

void BubbleSort::sort(vector<int*> * V)
{

    for (int i = 0; i < elements; i++) 
        {
        bool swapped = false;
            for (int j = 0; j < elements - 1 - i; j++)
                { comparisions++;
                if (GetSortingValue(*((*V)[j])) < GetSortingValue(*((*V)[j + 1])))
                    { swapped = true;
                        swap((*V)[j], (*V)[j+1]);
                        replacements++;
                    }
                }
        if (!swapped) break;
        }
};


class SelectionSort :public ISort
{
public:
    SelectionSort() :ISort() { title = "Сортировка отбором"; };
~SelectionSort() { };
void sort(vector<int*>*);
};

void SelectionSort::sort(vector<int*> * V)
{
    unsigned iterations = elements, start = 0;
    while (iterations > 0)
    {
        int* PMinValue = (*V)[start]; //минимальный элемент    
        unsigned MinIndex = start;
        for (unsigned i = start; i < (unsigned)elements; i++)
        {
            int* PCurrentValue = (*V)[i]; //текущией элемент
            comparisions++;
            if (GetSortingValue(*PCurrentValue) > GetSortingValue(*PMinValue))
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
~InsertionSort() { };
void sort(vector<int*>*);
};

void InsertionSort::sort(vector<int*> * V)
{
    for (int i = 1; i < elements; i++)
    {
        for (int j = i; j > 0 && GetSortingValue(*((*V)[j - 1])) < GetSortingValue(*((*V)[j])); j--) // пока j>0 и элемент j-1 > j, x-массив int
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
~ShellSort() { };
void sort(vector<int*>*);
};

void ShellSort::sort(vector<int*> * V)
{
    int i, j, step,*tmp;
    for (step = elements / 2; step > 0; step /= 2)
        for (i = step; i < elements; i++)
        {
            tmp = (*V)[i];
            for (j = i; j >= step; j -= step)
            {
                comparisions++;
                if (GetSortingValue(*tmp) > GetSortingValue(*((*V)[j - step])))
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
~QuickSort() { };
void sort(vector<int*>*);
void QSort(vector<int*>*, int, int);
};

void QuickSort::QSort(vector<int*> * V, int start, int end)
    {
    
    if (start >= end)  { return;}

    int current= start;
    for (int i= start + 1; i <= end; i++)
    {
        // если i-ый элемент меньше начального
        comparisions++;
        if (GetSortingValue(*((*V)[i])) > GetSortingValue(*((*V)[start])))
        {
            swap((*V)[++current], (*V)[i]); // меняем его с левым
            replacements++;
        }
    }
    swap((*V)[start], (*V)[current]); // Меняем выбранный (start) и последний обмененный элементы
    replacements++;

    if (current > start) { QSort(V, start, current - 1); } // Сортируем элементы слева
    
    if (end > current + 1) { QSort(V, current + 1, end); }// Сортируем элементы справа
    

};


void QuickSort::sort(vector<int*> * V)
{
    QSort(V, 0, elements - 1);
};
