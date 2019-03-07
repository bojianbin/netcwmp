#ifndef DG200_METHOD
#define DG200_METHOD

#define DG_IP_LEN	32


typedef struct dg_wan_config_s
{
	int enable_dhcp;
	char ip[DG_IP_LEN];
	char netmask[DG_IP_LEN];
	char gateway[DG_IP_LEN];
	char dns1[DG_IP_LEN];
	char dns2[DG_IP_LEN];
	int webport;
}dg_wan_config_t;



int dg_get_wanconfig(dg_wan_config_t * _config);

#endif

