/************************************************************************
 *                                                                      *
 * Netcwmp/Opencwmp Project                                             *
 * A software client for enabling TR-069 in embedded devices (CPE).     *
 *                                                                      *
 * Copyright (C) 2013-2014  netcwmp.netcwmp group                            *
 *                                                                      *
 * This program is free software; you can redistribute it and/or        *
 * modify it under the terms of the GNU General Public License          *
 * as published by the Free Software Foundation; either version 2       *
 * of the License, or (at your option) any later version.               *
 *                                                                      *
 * This program is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU Lesser General Public     *
 * License along with this library; if not, write to the                *
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,          *
 * Boston, MA  02111-1307 USA                                           *
 *                                                                      *
 * Copyright 2013-2014  Mr.x(Mr.x) <netcwmp@gmail.com>          *
 *                                                                      *
 ***********************************************************************/

#include "cwmp_module.h"
#include "cwmp/session.h"
#include <cwmp/cfg.h>



void cwmp_conf_init(cwmp_t * cwmp)
{
    int ret ;
    pool_t * pool;
    FUNCTION_TRACE();

    /*read from conf file*/
    pool = cwmp->pool;
    cwmp->httpd_port =  cwmp_conf_get_int("cwmpd:httpd_port"); //cwmp_nvram_get_int("cwmp:httpd_port");

    cwmp->acs_auth  =   cwmp_conf_get_int("cwmp:acs_auth");
    cwmp->cpe_auth  =   cwmp_conf_get_int("cwmp:cpe_auth");

    if(cwmp->acs_auth)
    {
        cwmp->acs_user = cwmp_conf_pool_get(pool, "cwmp:acs_username");
        cwmp->acs_pwd = cwmp_conf_pool_get(pool, "cwmp:acs_password");
    }

	if(cwmp->cpe_auth)
	{
	    cwmp->cpe_user = cwmp_conf_pool_get(pool, "cwmp:cpe_username");
    	cwmp->cpe_pwd = cwmp_conf_pool_get(pool, "cwmp:cpe_password");

	}

    cwmp->acs_url   =   cwmp_conf_pool_get(pool, "cwmp:acs_url"); //  "http://192.168.0.69:8000/otnms/acs/webservice.action";//cwmp_nvram_getdup(pool, "cwmp:acs_url");

    cwmp->cpe_mf    =   cwmp_conf_pool_get(pool, "cwmp:cpe_manufacture"); //     "ZTE"; //cwmp_nvram_getdup(pool, "cwmp:cpe_manufacture");

    cwmp->cpe_name  =   cwmp_conf_pool_get(pool, "cwmp:cpe_name"); //  "00D0D0"; //cwmp_nvram_getdup(pool, "cwmp:cpe_name");

    cwmp->cpe_pc    =   cwmp_conf_pool_get(pool, "cwmp:cpe_pc"); //      "ZXECS EBG2100";

    cwmp_log_debug("url:%s\nmf:%s\noui:%s\nsn:%s\nname:%s\npc:%s\nhttpd port:%d\n",    cwmp->acs_url, cwmp->cpe_mf, cwmp->cpe_oui, cwmp->cpe_sn, cwmp->cpe_name, cwmp->cpe_pc,
                   cwmp->httpd_port);

    cwmp->event_filename = cwmp_conf_pool_get(pool, "cwmp:event_filename");
	cwmp->config_filename = cwmp_conf_pool_get(pool,"cwmp:configuration_filename");
	cwmp->upgrade_filename = cwmp_conf_pool_get(pool,"cwmp:upgrade_filename");
	if(!cwmp->config_filename)
	{
		cwmp->config_filename = pool_pstrdup(pool, "/usr/dmboxupgrade/para.bin");
	}
	if(!cwmp->upgrade_filename)
	{
		cwmp->upgrade_filename = pool_pstrdup(pool, "/usr/dmboxupgrade/upgrade.bin");
	}


    cwmp->cpe_oui = pool_pstrdup(pool,"OUI_example");
    cwmp->cpe_sn = pool_pstrdup(pool,"sn_example");
    cwmp->cpe_app_verson = pool_pstrdup(pool,"version_example");
    cwmp->cpe_hw_version = pool_pstrdup(pool,"hwversion_example");
    cwmp->cpe_spec = pool_pstrdup(pool,"spec_example");

}



