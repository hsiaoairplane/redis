
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libevent.h"

#define REDIS_HOST "127.0.0.1"
#define REDIS_PORT 6379

void
pub_cb(redisAsyncContext *c, void *r, void *privdata)
{
    printf("hello\n");
}

int main(void)
{
    redisAsyncContext *c = redisAsyncConnect(REDIS_HOST, REDIS_PORT);

    if (c->err) {
	printf("Error: %s\n", c->errstr);
	redisAsyncFree(c);
	exit(1);
    }

    redisAsyncCommand(c, pub_cb, NULL, "PUBLISH 0x8081 WoW");

    return 0;
}
