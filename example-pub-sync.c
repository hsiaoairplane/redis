
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libevent.h"

#define REDIS_HOST "127.0.0.1"
#define REDIS_PORT 6379

static redisContext *context = NULL;

static int
check_redis(void)
{
    if(context != NULL) {
        return 0;
    }

    context = redisConnect(REDIS_HOST, REDIS_PORT);
    if (context == NULL || context->err)
    {
        if (context)
        {
            printf("Connection error: %s\n", context->errstr);
            redisFree(context);
        }
        else
        {
            printf("Connection error: can't allocate redis context\n");
        }
	return 1;
    }

    return 0;
}

int main(void)
{
    redisReply *reply;

    check_redis();
    reply = redisCommand(context, "PUBLISH 0x8081 WoW");
    reply = redisCommand(context, "PUBLISH 0x8082 LoL");
    freeReplyObject(reply);

    return 0;
}
