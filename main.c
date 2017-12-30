/**
 * @Author: fjk
 * @Date:   2017-12-29T18:13:01+08:00
 * @Email:  sunnyfjk@gmail.com
 * @Filename: main.c
 * @Last modified by:   fjk
 * @Last modified time: 2017-12-30T11:43:26+08:00
 */

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
