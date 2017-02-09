#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <hiredis.h>

int main(int argc, char *argv[])
{
    
    int i = 0;
    redisContext *c;
    redisReply *reply;

    //创建一个服务器句柄
    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    //执行一个指令
    reply = redisCommand(c, "SET %s %s", "itcast", "nihao");
    if (reply == NULL) {
        printf("redisCommand set error\n");
        exit(1);
    }
    if (strcmp(reply->str, "OK") == 0) {
        printf("set itcast nihao  ok\n");
    }
    freeReplyObject(reply);

    //get
    reply = redisCommand(c, "GET %s", "itcast");
    if (reply == NULL) {
        printf("redisCommand get error\n");
        exit(1);
    }
    printf("get itcast = %s\n", reply->str);
    freeReplyObject(reply);

    //lpush lpush
    reply = redisCommand(c, "LPUSH %s %s", "my_list", "123");
    if (reply == NULL) {
        printf("redisCommand lpush error\n");
        exit(1);
    }
    freeReplyObject(reply);

    reply = redisCommand(c, "LPUSH %s %s", "my_list", "456");
    if (reply == NULL) {
        printf("redisCommand lpush error\n");
        exit(1);
    }
    if (reply->type != REDIS_REPLY_INTEGER) {
        printf("返回值类型不对\n");
        exit(1);
    }

    printf("当前 mylist的长度是 %lld\n", reply->integer);
    freeReplyObject(reply);    

    //lrange
    reply = redisCommand(c, "LRANGE %s 0 -1", "my_list");
    if (reply == NULL) {
        printf("redisCommand lRANGE error\n");
        exit(1);
    }
    if (reply->type != REDIS_REPLY_ARRAY) {
        printf("lrange 返回值类型不对\n");
        exit(1);
    }

    for (i = 0; i < reply->elements; i++) {
        printf("%d:%s\n", i, reply->element[i]->str);
    }

    freeReplyObject(reply);    


    //释放服务器句柄
    redisFree(c);

	return 0;
}
