#include <unistd.h>
#include <stdarg.h>

int itoa(int num, char* buff) {
    if (num == 0) {
        buff[0] = '0';
        buff[1] = '\0';
        return 1;
    }

    int i = 0;
    int is_negative = 0;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num != 0) {
        buff[i ++] = '0' + num % 10;
        num /= 10;
    }

    if (is_negative) buff[i ++] = '-';

    int l = 0, r = i - 1;
    while (l < r) {
        char temp = buff[l];
        buff[l] = buff[r];
        buff[r] = temp;
        l ++;
        r --;
    }

    buff[i] = '\0';

    return i;
}

int printf(const char* fmt, ...);

int ftoa(float num, int precision, char* buff) {
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    int integer_part = (int)num;
    float decimal_part = num - integer_part;

    int integer_len = itoa(integer_part, buff);

    if (precision == 0) {
        return integer_len;
    }

    buff[integer_len] = '.';

    buff = buff + integer_len + 1;

    for (int i = 0; i < precision; i ++) {
        decimal_part *= 10;
        buff[i] = (int)decimal_part + '0';
        decimal_part -= (int)decimal_part;
    }

    buff[precision] = '\0';

    return integer_len + precision + 1;
}

int isdigit(char c) {
    return '0' <= c && '9' >= c;
}

int atoi(const char* str, int* ret_len) {
    int result = 0, i = 0;
    for (; isdigit(str[i]); i ++) {
        result = result * 10 + (str[i] - '0');
    }
    if (ret_len != NULL) {
        *ret_len = i;
    }
    return result;
}

size_t strlen(const char* str) {
    int size = 0;
    for (; str[size] != '\0'; size ++);
    return size;
}

int printf_process_string(const char* str) {
    int len = strlen(str);
    write(STDERR_FILENO, str, len);
    return len;
}

int printf_process_char(char c) {
    write(STDOUT_FILENO, &c, 1);
    return 1;
}

int printf_process_int(int number) {
    char s[32];
    int len = itoa(number, s);
    write(STDOUT_FILENO, s, len);
    return len;
}

int printf_process_float(float number, int precision) {
    char s[256];
    int len = ftoa(number, precision, s);
    write(STDOUT_FILENO, s, len);
    return len;
}

int printf(const char* fmt, ...) {
    va_list valist;
    va_start(valist, fmt);

    int written = 0;
    int fmt_size = strlen(fmt);

    int i = 0;
    while (i < fmt_size) {
        if (fmt[i] != '%') {
            write(STDOUT_FILENO, &fmt[i], 1);
            i ++;
            written ++;
            continue;
        }
        i ++; // skip '%'

        int precision = 6;

        if (fmt[i] == '.') {
            i ++;
            int skip_len = 0;
            precision = atoi(&fmt[i], &skip_len);
            i += skip_len;
        }

        switch (fmt[i]) {
        case 'c':
            char c = (char)va_arg(valist, int);
            written += printf_process_char(c);
            i ++;
            break;
        case 's':
            char* str = va_arg(valist, char*);
            written += printf_process_string(str);
            i ++;
            break;
        case 'd':
            int integer = va_arg(valist, int);
            written += printf_process_int(integer);
            i ++;
            break;
        case 'f':
            float floating = va_arg(valist, double);
            written += printf_process_float(floating, precision);
            i ++;
            break;
        default:
            break;
        }
    }
    return written;
}

int main() {
    printf("int     -> %d\n",   123);
    printf("float   -> %.3f\n", 12.34f);
    printf("float   -> %f\n",   12.34f);
    printf("string  -> %s\n",   "Hello world!");
    printf("char    -> %c\n",   'O');
    return 0;
}