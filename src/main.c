#include "../inc/ush.h"

int main(int argc, char const *argv[])
{

    do
    {
        printf("u&h> ");
        char *str = mx_getline();
        mx_replace_char(str, '\n', ';');
        t_2d_arr *commands_unparsed = mx_split_commands(str);

        /*  for (int i = 0; i < commands_unparsed->size; i++)
        {
            printf("%s\n", ((char **)(commands_unparsed->data))[i]);
        } */

        for (int i = 0; i < commands_unparsed->size; i++)
        {
            mx_process_command(((char **)(commands_unparsed->data))[i]);
        }

        // t_2d_arr *comands = mx_parse_commands(commands_unparsed);

        /*  printf("---------\n");

        for (int i = 0; i < comands->size; i++)
        {
            t_command *cur_comand = ((t_command **)(comands->data))[i];

            printf("%s - ", cur_comand->name);

            for (int j = 0; j < cur_comand->argc; j++)
            {
                printf("%s ", cur_comand->args[j]);
            }
            printf("%d\n", cur_comand->argc);
        } */

    } while (true);

    return 0;
}
