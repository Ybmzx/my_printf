# My Printf

***Just for fun.***

Implement `printf` without using any libraries other than `unistd.h` and `stdarg.h`.

## Supported Features:

`%d`, `%c`, `%s`, `%f`, `%.6f`

## Example

```c
int main() {
    printf("int     -> %d\n",   123);
    printf("float   -> %.3f\n", 12.34f);
    printf("float   -> %f\n",   12.34f);
    printf("string  -> %s\n",   "Hello world!");
    printf("char    -> %c\n",   'O');
    return 0;
}
```

**Output:**

```
int     -> 123
float   -> 12.340
float   -> 12.340000
string  -> Hello world!
char    -> O
```