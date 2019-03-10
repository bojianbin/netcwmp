
//InternetGatewayDevice.DeviceInfo.Manufacturer
int cpe_get_igd_di_manufacturer(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_mf);
    cwmp_log_debug("cpe_get_igd_di_manufacturer: value is %s", *value);
    return	FAULT_CODE_OK;
}

//InternetGatewayDevice.DeviceInfo.ManufacturerOUI
int cpe_get_igd_di_manufactureroui(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_oui);
    return	FAULT_CODE_OK;
}

//InternetGatewayDevice.DeviceInfo.ProductClass
int cpe_get_igd_di_productclass(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_pc);
    return	FAULT_CODE_OK;
}

//InternetGatewayDevice.DeviceInfo.SerialNumber
int cpe_get_igd_di_serialnumber(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
	FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_sn);
    return	FAULT_CODE_OK;
}

//InternetGatewayDevice.DeviceInfo.SpecVersion
int cpe_get_igd_di_specversion(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
	FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_spec);
    return	FAULT_CODE_OK;
}

//InternetGatewayDevice.DeviceInfo.HardwareVersion
int cpe_get_igd_di_hardwareversion(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
	FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_hw_version);
    return	FAULT_CODE_OK;
}

//InternetGatewayDevice.DeviceInfo.SoftwareVersion
int cpe_get_igd_di_softwareversion(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
	FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_app_verson);
    return	FAULT_CODE_OK;
}

//InternetGatewayDevice.DeviceInfo.ProvisioningCode
int cpe_get_igd_di_provisioningcode(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
	FUNCTION_TRACE();
    *value = pool_pstrdup(pool,cwmp->cpe_spec);
    return	FAULT_CODE_OK;
}





