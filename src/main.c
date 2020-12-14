#include "../inc/ush.h"

int main(int argc, char const *argv[])
{

    do
    {
        printf("u&h> ");
        char *str = mx_getline();
        mx_replace_char(str, '\n', ';');
        printf("%s",str);
    } while (true);

    return 0;
}
