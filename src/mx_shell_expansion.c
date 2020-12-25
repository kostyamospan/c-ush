#include "../inc/ush.h"

void mx_replace_exp(char **str)
{
    char *user_name = getenv("USER");
    char *home = getenv("HOME");
    char *pwd = getenv("PWD");
    char *oldpwd = getenv("OLDPWD");

    char *temp;

    /* if (strstr(str, (temp = mx_strconcant_new("~/", user_name)) != NULL))
    {
    } */
    if (strstr(*str, "~+") != NULL)
    {
        *str = mx_str_replace(*str, "~+", pwd);
    }
    if (strstr(*str, "~-") != NULL)
    {
        *str = mx_str_replace(*str, "~-", oldpwd ? oldpwd : pwd);
    }
    if (strstr(*str, "~") != NULL)
    {
        // printf("found!\n");
        *str = mx_str_replace(*str, "~", home);
    }

    char *env_value;
    char *str_copy = mx_strdup(*str);
    char *exp = mx_search_exp(str_copy);

    while (*str_copy && exp != NULL)
    {
        env_value = getenv(exp + 1);

        if (env_value != NULL)
            *str = mx_str_replace(*str, exp, env_value);

        *str_copy += mx_strlen(exp);

        free(exp);
        free(env_value);
        exp = mx_search_exp(str_copy);
    }

    /* free(user_name);
    free(pwd);
    free(oldpwd);
    free(str_copy);

    if (exp != NULL)
        free(exp); */
}

char *mx_search_exp(char *str)
{
    int e_i = -1;
    int j;

    if (str[0] == '$')
    {
        for (int i = 0; i < mx_strlen(str); i++)
        {
            if (i != 0)
            {
                if (!(mx_isdigit(str[i]) || mx_isalpha(str[i])))
                {
                    e_i = i;
                    break;
                }
            }
        }
    }
    else
    {
        return NULL;
    }

    if (e_i == -1)
        e_i = mx_strlen(str);

    char *res = mx_strnew(e_i);

    for (int i = 0; i < e_i; i++)
    {
        res[i] = str[i];
    }

    return res;
}
