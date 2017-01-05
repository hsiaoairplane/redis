#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <signal.h>  

#include "hiredis/hiredis.h"  
#include "hiredis/async.h"  
#include "hiredis/adapters/libevent.h"  

#define REDIS_HOST "127.0.0.1"
#define REDIS_PORT 6379
  
void subCallback(redisAsyncContext *c, void *r, void *priv) {  
    redisReply *reply = r;  
    if (reply == NULL) return;  
    if (reply->type == REDIS_REPLY_ARRAY && reply->elements == 3 ) {  
        if ( strcmp( reply->element[0]->str, "subscribe" ) != 0 ) {  
            printf( "Received[%s] channel %s: %s\n",  
                    (char*)priv,  
                    reply->element[1]->str,  
                    reply->element[2]->str );  
        }  
    }  
}  
  
int main (int argc, char **argv) {  
    signal(SIGPIPE, SIG_IGN);
    struct event_base *base = event_base_new();  
  
    redisAsyncContext *c = redisAsyncConnect(REDIS_HOST, REDIS_PORT);
    if (c->err) {  
        /* Let *c leak for now... */  
        printf("Error: %s\n", c->errstr);  
        return 1;
    }  
  
    redisLibeventAttach(c, base);
    redisAsyncCommand(c, subCallback, (char*) "sub", "SUBSCRIBE 0x8081");
    redisAsyncCommand(c, subCallback, (char*) "sub", "SUBSCRIBE 0x8082");
  
    event_base_dispatch(base);

    return 0;  
}  
