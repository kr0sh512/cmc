#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int
return_bit_int(int *mas, int n)
{
    unsigned int byte = mas[n / (sizeof(int) * 8)]; // (sizeof(int) * 8) == 32
    int offset = 32 - 1 - n % 32;

    return (byte & (1 << offset)) >> offset;
}

int
return_bit_byte(unsigned char *mas, int n)
{
    unsigned int byte = mas[n / (sizeof(char) * 8)]; // (sizeof(char) * 8) == 8
    int offset = 8 - 1 - n % 8;

    return (byte & (1 << offset)) >> offset;
}

// пусть битовый массив записан в файл. Массив - свободные блоки ФС. Вывести максимальную длину свободных блоков.

int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);

    int size = lseek(fd, 0, SEEK_END);
    unsigned char *mas = malloc(size);

    lseek(fd, 0, 0); // SEEK_CUR == 0, SEEK_SET == 1, SEEK_END == 2

    for (int i = 0; i < size; ++i) {
        read(fd, mas + i, 1); // читаем из файла массив
    }

    int max_len = 0;
    int tmp = 0;                         // для хранения текущей длины
    for (int i = 0; i < size * 8; ++i) { // пробегаем по всем битам
        if (return_bit_byte(mas, i) == 1) {
            tmp++;
        } else {
            max_len = (max_len > tmp) ? max_len : tmp;
            tmp = 0;
        }
    }
    max_len = (max_len > tmp) ? max_len : tmp; // если последний бит был 1, то надо доп проверку

    printf("%d\n", max_len);

    return 0;
}
