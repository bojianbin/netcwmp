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

#include "cwmpd.h"
#include "data_model.h"

#define CWMP_VALUE_UNSET -1


int              cwmp_argc;
char           **cwmp_argv;


static pool_t * cwmp_global_pool;



/**
 *  daemonize process
 * 
 * @note: 
 *
 *
 * @param[in] _chdir	  	:change process current dir "/"
 * @param[in] close_stdfd	:close fd 0,1 and 2
 *
 * @return: 0 if success . -1 if error
 */
int cwmp_daemon(int _chdir, int close_stdfd)
{
    int fd;

	if (fork() != 0) 
		exit(0); /* parent exits */

	setsid(); /* create a new session */

    if (_chdir == 1) 
	{
        if(chdir("/") != 0) 
		{
            perror("chdir");
            return (-1);
        }
    }

    if (close_stdfd == 1 && (fd = open("/dev/null", O_RDWR, 0)) != -1) 
	{
        if(dup2(fd, STDIN_FILENO) < 0) 
		{
            perror("dup2 stdin");
            return (-1);
        }
        if(dup2(fd, STDOUT_FILENO) < 0) 
		{
            perror("dup2 stdout");
            return (-1);
        }
        if(dup2(fd, STDERR_FILENO) < 0) 
		{
            perror("dup2 stderr");
            return (-1);
        }

        if (fd > STDERR_FILENO) 
		{
            if(close(fd) < 0) 
			{
                perror("close");
                return (-1);
            }
        }
    }
	
    return (0);
}

void cwmp_getopt(int argc, char **argv)
{
    
}


static int cwmp_save_argv( int argc, char *const *argv)
{
    cwmp_argv = (char **) argv;
    cwmp_argc = argc;

    return 0;
}


int cwmp_set_var(cwmp_t * cwmp)
{
    FUNCTION_TRACE();


    cwmp_bzero(cwmp, sizeof(cwmp_t));
    cwmp->new_request = CWMP_TRUE;
    pool_t * pool = pool_create(POOL_DEFAULT_SIZE);
    cwmp->pool = pool;

    cwmp->queue = queue_create(pool);

    return CWMP_OK;
}




#ifdef USE_CWMP_OPENSSL
void cwmp_init_ssl(cwmp_t * cwmp)
{
    char * cafile = cwmp_conf_pool_get(cwmp_global_pool, "cwmp:ca_file");
    char * capasswd = cwmp_conf_pool_get(cwmp_global_pool, "cwmp:ca_password");   
    cwmp->ssl_ctx = openssl_initialize_ctx(cafile, capasswd);
}
#endif




int main(int argc, char **argv)
{


    cwmp_pid_t pid;
    cwmp_t * cwmp;

    int syslog_enable = 0;
    int cwmp_enable = 0;

#ifdef WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    pid = getpid();

    cwmp_log_init(NULL, CWMP_LOG_DEBUG);
    cwmp_global_pool = pool_create(POOL_DEFAULT_SIZE);
    cwmp = pool_palloc(cwmp_global_pool, sizeof(cwmp_t));

    cwmp_conf_open("/etc/cwmp.conf");
    
    cwmp_enable=cwmp_conf_get_int("cwmp:enable");
    if(!cwmp_enable)
    {
        exit(-1);    
    }

    cwmp_getopt(argc, argv);
   
    //cwmp_daemon(1,0);

	cwmp_set_var(cwmp);
	
    cwmp_conf_init(cwmp);

	cwmp_event_init(cwmp);
	

#ifdef USE_CWMP_OPENSSL
    cwmp_init_ssl(cwmp);
#endif

    cwmp_model_load(cwmp, "/etc/device.xml");
    cwmp_process_start_master(cwmp);

    return 0;
}



