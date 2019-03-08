#ifndef DG200_METHOD
#define DG200_METHOD

#define DG_IP_STRING_LEN	32
#define DG_SHORT_STRING_LEN 32
#define DG_MEDIUM_STRING_LEN 128

typedef struct dg_outcome_s
{
	int nRet;
	char Message[DG_MEDIUM_STRING_LEN];
}dg_outcom_t;

typedef struct dg_wan_config_s
{
	int enable_dhcp;
	char ip[DG_IP_STRING_LEN];
	char netmask[DG_IP_STRING_LEN];
	char gateway[DG_IP_STRING_LEN];
	char dns1[DG_IP_STRING_LEN];
	char dns2[DG_IP_STRING_LEN];
	int webport;
}dg_wan_config_t;

typedef struct dg_global_config_s
{
	int nret;
	char message[DG_SHORT_STRING_LEN];
	char app_version[DG_SHORT_STRING_LEN];
	char app_root[DG_SHORT_STRING_LEN];
	int cms_port;
	char cms_addr[DG_SHORT_STRING_LEN];
	char cms_user[DG_SHORT_STRING_LEN];
	char cms_passwd[DG_SHORT_STRING_LEN];
	char shop_no[DG_SHORT_STRING_LEN];
	char shop_name[DG_SHORT_STRING_LEN];
	char shop_uuid[DG_MEDIUM_STRING_LEN];
	int box_no;
	char serial_num[DG_MEDIUM_STRING_LEN];
	char firmware_ver[DG_SHORT_STRING_LEN];
	char hardware_ver[DG_MEDIUM_STRING_LEN];
	char model[DG_SHORT_STRING_LEN];
	int web_port;
	int appservice_port;
	int login_type;
	char model_code[DG_MEDIUM_STRING_LEN];
	int upload_port;
	char upload_ipaddr[DG_SHORT_STRING_LEN];
	int upgrade_online;
	int upgrade_port;
	char upgrade_ipaddr[DG_SHORT_STRING_LEN];
	int cms_online;
	int cms_error_no;
	char cms_error_msg[DG_MEDIUM_STRING_LEN];

}dg_global_config_t;

typedef struct dg_para_file_get_s
{
	char file_path[DG_MEDIUM_STRING_LEN];
	
}dg_para_file_get_t;

struct buffer_atom;
typedef int (*dg_get_func)(struct buffer_atom* ,void * );

int dg_get_wan_config(dg_wan_config_t * _config);
int dg_set_wan_config(dg_wan_config_t * _config);
int dg_get_global_config(dg_global_config_t * _config);
int dg_get_para_file();
int dg_set_para_file(const char * file_full_name);


int dg_reset_system();
int dg_reboot_system();
int dg_upgrade_system(const char * file_full_name);


#endif

