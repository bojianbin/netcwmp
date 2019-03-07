#include <stdio.h>

#include "cwmp/pool.h"
#include "cwmp/http.h"
#include "cwmp/log.h"
#include "cwmp/cwmp_private.h"

//1  len
size_t print_data(char *data, size_t size, size_t nmemb, void * calldata)
{

	fwrite(data,nmemb,size,stdout);
	
	return 0;
}

int test_wan(int argc , char *argv[])
{
	int ret = 0 ;
	http_request_t * request = NULL;
	pool_t * pool = NULL;
	http_dest_t *  dest;
	http_socket_t * sock;
	http_response_t * response;
	
	if(argc != 2)
	{
		printf("usage:%s url\n",argv[0]);
		exit(0);
	}

	cwmp_log_init(NULL,CWMP_LOG_DEBUG);
	pool = pool_create(POOL_DEFAULT_SIZE);
	
	http_dest_create(&dest, argv[1], pool);
   
    int rc = http_socket_create(&sock, AF_INET, SOCK_STREAM, 0, pool);
    if (rc != CWMP_OK)
    {
        cwmp_log_error("http send file: create socket error.");
        exit(-1);
    }

	http_socket_set_writefunction(sock, print_data, NULL);

	rc = http_socket_connect(sock, AF_INET, dest->host, dest->port);
    if(rc != CWMP_OK)
    {
        cwmp_log_error("connect to host faild. Host is %s:%d.", dest->host, dest->port);
        exit(-1);
    }

    http_socket_set_recvtimeout(sock, 30);
	
	
	http_request_create(&request, pool);
	request->dest = dest;

	ret = http_get(sock, request, NULL, pool);
	if(ret <= 0 )
	{
		cwmp_log_error("http get error");
	}
	

    http_response_create(&response, pool);

	rc = http_read_response(sock, response, pool);
	
	cwmp_log_debug("We read finished and code is %d\n",rc);





END:
	pool_destroy(pool);


	
	return 0;
}


int main(int argc , char * argv[])
{

	test_wan(argc,argv);

	return 0;
}
