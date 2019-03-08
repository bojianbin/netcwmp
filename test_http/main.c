#include <stdio.h>

#include "cwmp/pool.h"
#include "cwmp/http.h"
#include "cwmp/log.h"
#include "cwmp/cwmp_private.h"
#include "cJSON.h"
#include "dg200_method.h"


int test_json()
{	
	char *str = "{\"enable\": 1 , \"name\":\"bojianbin\"}";
	cJSON * root = cJSON_Parse(str);
	cJSON * node = cJSON_GetObjectItem(root,"enable");
	printf("enable:%s\n",node->valuestring);
	printf("enable:%d\n",node->valueint);

	node = cJSON_GetObjectItem(root,"name");
	printf("name:%s\n",node->valuestring);


	return 0;
}


int main(int argc , char * argv[])
{
	int ret = 0;
	dg_global_config_t config;

	cwmp_log_init(NULL,CWMP_LOG_DEBUG);

	ret = dg_get_global_config(&config);
	if(ret < 0 )
	{
		printf("dg_get_global_config error\n");
		exit(0);
	}

	printf("appversion:%s\nhardversion:%s\n",
		config.app_version,config.hardware_ver);
	

	return 0;
}
