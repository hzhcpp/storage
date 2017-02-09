#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "redis_op.h"

#define TEST_MOUDLE  "test"
#define REDIS_OP_PROC  "redis"

int main(int argc, char *argv[])
{

    //建立连接
    redisContext* conn = NULL;
    int retn = 0;
    //char key[128] = { 0 };
		//char value[128] = { 0 };
		
    conn = rop_connectdb_nopwd("127.0.0.1", "6379");
    if (conn == NULL || conn->err) {
        if (conn) {
            printf("Connection error: %s\n", conn->errstr);
            LOG(TEST_MOUDLE, REDIS_OP_PROC, "rop_connect error\n");
            redisFree(conn);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        return 0;
    }
/*
    //set key
    scanf("%s",key);
    scanf("%s",value);
    set_string(conn,key, value);

    //get key
    scanf("%s",key);
    get_string(conn, key);
*/
    
     //set key
    retn = rop_string_set(conn, "FOO", "BAR");
    if (retn == 0) {
        printf("set succ!\n");
    }


    //get key
    char value[128] = {0};
    retn = rop_string_get(conn, "FOO", value);
    if (retn == 0) {
        printf("get %s = %s\n", "FOO", value);
    }

    //断开连接
    rop_disconnect(conn);

	return 0;
}
