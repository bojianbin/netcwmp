#include "../dg200_method.h"
#include "cwmp/session.h"



int  cpe_refresh_igd_wanipconnection(cwmp_t * cwmp, parameter_node_t * param_node, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();

    if(!param_node)
    {
        return FAULT_CODE_9002;
    }
    parameter_node_t * tmp_param, *tmp_node, *child_param;
    child_param = param_node->child;
    if(child_param)
    {
        for(tmp_param=child_param->next_sibling; tmp_param; )
        {
            cwmp_log_info("refresh WANConnectionDevice node, delete param %s\n", tmp_param->name);
            tmp_node = tmp_param->next_sibling;
            cwmp_model_delete_parameter(tmp_param);
            tmp_param = tmp_node;
        }
        child_param->next_sibling = NULL;

        int wan_index = get_index_after_paramname(param_node, "WANDevice"); 
        int wan_conn_dev_index = get_index_after_paramname(param_node, "WANConnectionDevice"); 

        if(wan_index == 1)
        {
            parameter_node_t * ipconn_param;
            switch(wan_conn_dev_index)
            {
                case 1: 
                    cwmp_model_copy_parameter(param_node, &ipconn_param, 1);
                    break;

                case 2:
                    cwmp_model_copy_parameter(param_node, &ipconn_param, 1); 
                    cwmp_model_copy_parameter(param_node, &ipconn_param, 2);
                    break;

            }
            
            
        }
        else
        if(wan_index == 2)
        {
            //don't support
        }

        cwmp_model_refresh_object(cwmp, param_node, 0, callback_reg); 
    }

    return FAULT_CODE_OK;
}


dg_wan_config_t g_wan_config = {0};
int cpe_get_igd_wd_wcd_wic_type(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    int ret ;
    dg_wan_config_t config;

    FUNCTION_TRACE();
    ret  = dg_get_wan_config(&config);
    if(ret < 0)
        return FAULT_CODE_9001;

    switch(config.enable_dhcp)
    {
        case 0:
            *value = pool_pstrdup(pool,"Static");
            break;
        case 1:
            *value = pool_pstrdup(pool,"DHCP");
            break;
    }
    
    return FAULT_CODE_OK;
}
int cpe_set_igd_wd_wcd_wic_type(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();

    task_common_set_t *wan_set = (task_common_set_t *)calloc(1,sizeof(task_common_set_t));
    wan_set->type = TASK_CALLBACK_WAN;
    wan_set->data1 = (void *)1;
    wan_set->data2 = strdup(value);
    callback_reg(cwmp,(callback_func_t)wan_set,NULL,NULL);

    return FAULT_CODE_OK;
}
int cpe_get_igd_wd_wcd_wic_externalip(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    int ret ;
    dg_wan_config_t config;

    FUNCTION_TRACE();
    ret  = dg_get_wan_config(&config);
    if(ret < 0)
        return FAULT_CODE_9001;

    *value = pool_pstrdup(pool,config.ip);
    return	FAULT_CODE_OK;
}
int cpe_set_igd_wd_wcd_wic_externalip(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();

    task_common_set_t *wan_set = (task_common_set_t *)calloc(1,sizeof(task_common_set_t));
    wan_set->type = TASK_CALLBACK_WAN;
    wan_set->data1 = (void *)2;
    wan_set->data2 = strdup(value);
    callback_reg(cwmp,(callback_func_t)wan_set,NULL,NULL);

    return FAULT_CODE_OK;
}
int cpe_get_igd_wd_wcd_wic_subnetmask(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    int ret ;
    dg_wan_config_t config;

    FUNCTION_TRACE();
    ret  = dg_get_wan_config(&config);
    if(ret < 0)
        return FAULT_CODE_9001;

    *value = pool_pstrdup(pool,config.netmask);
    return	FAULT_CODE_OK;
}
int cpe_set_igd_wd_wcd_wic_subnetmask(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();
    task_common_set_t *wan_set = (task_common_set_t *)calloc(1,sizeof(task_common_set_t));
    wan_set->type = TASK_CALLBACK_WAN;
    wan_set->data1 = (void *)3;
    wan_set->data2 = strdup(value);
    callback_reg(cwmp,(callback_func_t)wan_set,NULL,NULL);

    return FAULT_CODE_OK;
}
int cpe_get_igd_wd_wcd_wic_defaultgateway(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    int ret ;
    dg_wan_config_t config;

    FUNCTION_TRACE();
    ret  = dg_get_wan_config(&config);
    if(ret < 0)
        return FAULT_CODE_9001;

    *value = pool_pstrdup(pool,config.gateway);
    return	FAULT_CODE_OK;
}
int cpe_set_igd_wd_wcd_wic_defaultgateway(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();
    task_common_set_t *wan_set = (task_common_set_t *)calloc(1,sizeof(task_common_set_t));
    wan_set->type = TASK_CALLBACK_WAN;
    wan_set->data1 = (void *)4;
    wan_set->data2 = strdup(value);
    callback_reg(cwmp,(callback_func_t)wan_set,NULL,NULL);

    return FAULT_CODE_OK;
}
int cpe_get_igd_wd_wcd_wic_dns(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    int ret ;
    dg_wan_config_t config;

    FUNCTION_TRACE();
    ret  = dg_get_wan_config(&config);
    if(ret < 0)
        return FAULT_CODE_9001;

    *value = pool_pstrdup(pool,config.dns1);
    return	FAULT_CODE_OK;
}
int cpe_set_igd_wd_wcd_wic_dns(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();
    task_common_set_t *wan_set = (task_common_set_t *)calloc(1,sizeof(task_common_set_t));
    wan_set->type = TASK_CALLBACK_WAN;
    wan_set->data1 = (void *)5;
    wan_set->data2 = strdup(value);
    callback_reg(cwmp,(callback_func_t)wan_set,NULL,NULL);

    return FAULT_CODE_OK;
}
int cpe_get_igd_wd_wcd_wic_mac(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    int ret ;
    char buf[512] = {0};
    
    FUNCTION_TRACE();
    ret = cwmp_session_get_localip(NULL,buf,"eth0");
    if(ret < 0)
        return FAULT_CODE_9001;

    *value = pool_pstrdup(pool,buf);

    return FAULT_CODE_OK;
}
int cpe_set_igd_wd_wcd_wic_mac(cwmp_t * cwmp, const char * name, const char * value, int length, callback_register_func_t callback_reg)
{
    FUNCTION_TRACE();

    return FAULT_CODE_OK;
}