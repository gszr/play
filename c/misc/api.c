#include <stdio.h>

/* The API to implement */

struct greet_api
{
    int (*say_hello)(char *name);
    int (*say_goodbye)(void);
};

/* The implementation */

int say_hello_impl(char *name)
{
    printf("Hello, %s\n", name);
    return 0;
}

int say_goodbye_impl()
{
    printf("Goodbye\n");
    return 0;
}

struct greet_api greet_api = 
{
    .say_hello = say_hello_impl,
    .say_goodbye = say_goodbye_impl
};

int main(int argc, char **argv)
{
    greet_api.say_hello(argv[0]);
    greet_api.say_goodbye();

    printf("%p, %p, %p\n", greet_api.say_hello, say_hello_impl, &say_hello_impl);

    return 0;
}
