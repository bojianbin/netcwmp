#include <stdio.h>

#include "cwmp/pool.h"
#include "cwmp/http.h"
#include "cwmp/log.h"
#include "cwmp/cwmp_private.h"

#include "dg200_method.h"


struct buffer_atom
{
	pool_t * pool;
	char *buf;

	int total_len;
	int pos;
};
//1  len
size_t _save_data_atom(char *data, size_t size, size_t nmemb, void * calldata)
{

	struct buffer_atom * atom = calldata;


	if(size * nmemb + atom->pos > atom->total_len)
	{
		atom->buf = pool_prealloc(atom->pool, atom->buf, atom->total_len, atom->total_len * 1.5);
		atom->total_len = atom->total_len * 1.5;
	}

	memmove(atom->buf + atom->pos , data , size * nmemb);
	atom->pos += size * nmemb;
	
	return 0;
}


int dg_get_wanconfig(dg_wan_config_t * _config)
{
	int ret = 0 ,ret_outcome = -1;
	http_request_t * request = NULL;
	pool_t * pool = NULL;
	http_dest_t *  dest;
	http_socket_t * sock;
	http_response_t * response;
	char *url = "http//127.0.0.1//AppManager/GetIfConfig?Manager=1";
	struct buffer_atom atom;
	
	cwmp_log_init(NULL,CWMP_LOG_DEBUG);
	pool = pool_create(POOL_DEFAULT_SIZE);
	
	http_dest_create(&dest, url, pool);
   
    int rc = http_socket_create(&sock, AF_INET, SOCK_STREAM, 0, pool);
    if (rc != CWMP_OK)
    {
        cwmp_log_error("http send file: create socket error.");
        goto END;
    }

	atom.pool = pool;
	atom.buf = pool_palloc(pool, 2048);
	atom.total_len = 2048;
	atom.pos = 0;
	
	http_socket_set_writefunction(sock, _save_data_atom, &atom);

	rc = http_socket_connect(sock, AF_INET, dest->host, dest->port);
    if(rc != CWMP_OK)
    {
        cwmp_log_error("connect to host faild. Host is %s:%d.", dest->host, dest->port);
        goto END;
    }

    http_socket_set_recvtimeout(sock, 30);
	
	
	http_request_create(&request, pool);
	request->dest = dest;

	ret = http_get(sock, request, NULL, pool);
	if(ret <= 0 )
	{
		cwmp_log_error("http get error");
		goto END;
	}
	

    http_response_create(&response, pool);

	rc = http_read_response(sock, response, pool);
	
	if(rc != 200)
		goto END;

	ret = 
	ret_outcome = 0;
	
END:
	pool_destroy(pool);


	
	return ret_outcome;
}

