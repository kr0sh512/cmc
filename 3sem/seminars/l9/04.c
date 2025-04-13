
// по номеру начального размер блока и указатель на таблицу файлов
// вывести размер файла

unsigned int
f(unsigned int n, unsigned int *table)
{
    unsigned int size = 0;
    int first_block = table[n];
    while (first_block) {
        size++; // размер блока
        first_block = table[first_block];
    }

    return size;
}
