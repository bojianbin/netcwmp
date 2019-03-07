#include <stdio.h>

#include "cwmp/pool.h"
#include "cwmp/http.h"
#include "cwmp/log.h"
#include "cwmp/cwmp_private.h"
#include "cJSON.h"

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
int _parse_wan_json(struct buffer_atom* _atom,void * _para)
{
	cJSON *root = NULL;
	cJSON *node = NULL;
	dg_wan_config_t *_config = _para;

	if( !_atom || !_para )
		return -1;

	root = cJSON_Parse(_atom->buf);
	if(!root)
		return -1;
	
	node = cJSON_GetObjectItemCaseSensitive(root,"bEnableDHCP");
	if(node)
	{
		_config->enable_dhcp = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strIPAddr");
	if(node)
	{
		snprintf(_config->ip,DG_IP_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strNetMask");
	if(node)
	{
		snprintf(_config->netmask,DG_IP_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strGateWay");
	if(node)
	{
		snprintf(_config->gateway,DG_IP_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strDNS1");
	if(node)
	{
		snprintf(_config->dns1,DG_IP_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strDNS2");
	if(node)
	{
		snprintf(_config->dns2,DG_IP_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nWebPort");
	if(node)
	{
		_config->webport = node->valueint;
	}

	cJSON_Delete(root);

	return 0;
}
int _parse_global_json(struct buffer_atom* _atom,void * _para)
{
	cJSON *root = NULL;
	cJSON *node = NULL;
	dg_global_config_t *_config = _para;

	if( !_atom || !_para )
		return -1;

	root = cJSON_Parse(_atom->buf);
	if(!root)
		return -1;

	node = cJSON_GetObjectItemCaseSensitive(root,"nRet");
	if(node)
	{
		_config->nret = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"Message");
	if(node)
	{
		snprintf(_config->message,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strAppVersion");
	if(node)
	{
		snprintf(_config->app_version,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strAppRoot");
	if(node)
	{
		snprintf(_config->app_root,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nCMSPort");
	if(node)
	{
		_config->cms_port = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strCMSAddr");
	if(node)
	{
		snprintf(_config->cms_addr,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strCMSUser");
	if(node)
	{
		snprintf(_config->cms_user,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strCMSPassword");
	if(node)
	{
		snprintf(_config->cms_passwd,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strShopNo");
	if(node)
	{
		snprintf(_config->shop_no,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strShopName");
	if(node)
	{
		snprintf(_config->shop_name,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strShopUUID");
	if(node)
	{
		snprintf(_config->shop_uuid,DG_MEDIUM_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nBoxNo");
	if(node)
	{
		_config->box_no = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strSerialNum");
	if(node)
	{
		snprintf(_config->serial_num,DG_MEDIUM_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strFirmwareVer");
	if(node)
	{
		snprintf(_config->firmware_ver,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strHardwareVer");
	if(node)
	{
		snprintf(_config->hardware_ver,DG_MEDIUM_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strModel");
	if(node)
	{
		snprintf(_config->model,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nWebPort");
	if(node)
	{
		_config->web_port = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nAppServicePort");
	if(node)
	{
		_config->appservice_port = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nLoginType");
	if(node)
	{
		_config->login_type = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strModuleCode");
	if(node)
	{
		snprintf(_config->model_code,DG_MEDIUM_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nUploadPort");
	if(node)
	{
		_config->upload_port = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strUploadIPAddr");
	if(node)
	{
		snprintf(_config->upload_ipaddr,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"bUpgradeOnline");
	if(node)
	{
		_config->upgrade_online = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nUpgradePort");
	if(node)
	{
		_config->upgrade_port = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"strUpgradeIPAddr");
	if(node)
	{
		snprintf(_config->upgrade_ipaddr,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"bCMSOnline");
	if(node)
	{
		_config->cms_online = node->valueint;
	}

	node = cJSON_GetObjectItemCaseSensitive(root,"nCMSErrorNo");
	if(node)
	{
		_config->cms_error_no = node->valueint;
	}
	
	node = cJSON_GetObjectItemCaseSensitive(root,"strCMSErrorMessage");
	if(node)
	{
		snprintf(_config->cms_error_msg,DG_SHORT_STRING_LEN,"%s",node->valuestring);
	}

	
	cJSON_Delete(root);
	
	return 0;
}


int dg_get_method(char *_url,dg_get_func _func,void *_config)
{
	int ret = 0 ,ret_outcome = -1;
	http_request_t * request = NULL;
	pool_t * pool = NULL;
	http_dest_t *  dest;
	http_socket_t * sock;
	http_response_t * response;
	char *url = _url;
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
	atom.buf = pool_pcalloc(pool, 2048);
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

	ret = _func(&atom,_config);
	if(ret < 0 )
	{
		cwmp_log_error("parse wan json error");
		goto END;
	}

	/*success if got here*/
	ret_outcome = 0;
	
END:
	pool_destroy(pool);


	
	return ret_outcome;
}


int dg_get_wan_config(dg_wan_config_t * _config)
{
	char *url = "http//127.0.0.1/AppManager/GetIfConfig?Manager=1";

	return dg_get_method(url,_parse_wan_json,_config);
}

int dg_get_global_config(dg_global_config_t * _config)
{
	char *url = "http//127.0.0.1/AppManager/AppParameter?Manager=1";

	return dg_get_method(url,_parse_global_json,_config);
}