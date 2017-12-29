#include <stdio.h>
#include <server.h>
int main(void)
{
        struct Server_t s={0};
        s.ip="0.0.0.0";
        s.port=9999;
        ServerCreate(&s);
        ServerClose(&s);
        return 0;
}
