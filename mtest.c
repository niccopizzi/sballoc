#include "./include/sballoc.h"

int main()
{
    char* test = sballoc(10);

    printf ("test is %p\n", test);
    strcpy(test, "Hola");
    printf("%s\n", test);
    return (0);
}