/*************************************************************************
	> File Name: netTool.c
	> Author: 
	> Mail: 
	> Created Time: Wed 13 Dec 2017 04:41:08 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <sys/select.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

#include "netTool.h"
//max_null_milliseconds <= 0:always wait
//max_null_milliseconds > 0:wait milliseconds
int readn(int fd,uint8_t * buf,int size,int max_null_milliseconds)
{
    fd_set rset;
    struct timeval timeout;
    int sum = 0;
    int ret = 0;

    while(1)
    {
        FD_ZERO(&rset);
        FD_SET(fd,&rset);
        if(max_null_milliseconds > 0)
        {
            timeout.tv_sec = max_null_milliseconds / 1000;
            timeout.tv_usec = (max_null_milliseconds % 1000) * 1000;
            ret = select(fd+1,&rset,NULL,NULL,&timeout);
        }else
        {
            ret = select(fd+1,&rset,NULL,NULL,NULL);
        }

        if(ret  == 0)
        {
            return -1;
        }else if(ret < 0)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }
        
        ret  = read(fd,buf + sum ,size - sum);
        
        if(ret > 0)
        {
            sum += ret;
            if(sum >= size)
            {
                return 0;
            }
        }else if(ret < 0)
        {
            if(errno == EAGAIN || errno == EINTR)
            {
                continue;
            }
            return -1;
        }else
        {
            return -1;
        }
    }

    return 0;
}

//max_null_milliseconds <= 0:always wait
//max_null_milliseconds > 0:wait milliseconds
int writen(int fd,uint8_t * buf,int size,int max_null_milliseconds)
{
    fd_set wset;
    struct timeval timeout;
    int sum = 0;
    int ret = 0;
    
    while(1)
    {
        FD_ZERO(&wset);
        FD_SET(fd,&wset);
        if(max_null_milliseconds > 0)
        {
            timeout.tv_sec = max_null_milliseconds / 1000;
            timeout.tv_usec = (max_null_milliseconds % 1000) * 1000;
            ret = select(fd+1,NULL,&wset,NULL,&timeout);
        }else
        {
            ret = select(fd+1,NULL,&wset,NULL,NULL);
        }

        if(ret  == 0)
        {
            return -1;
        }else if(ret < 0)
        {
            if(errno == EINTR)
                continue;
            
            return -1;
        }
        
        ret = write(fd,buf + sum,size - sum); 
        if(ret > 0)
        {
            sum += ret;
            if(sum >= size)
                return 0;
        }else if(ret < 0)
        {
            if(errno == EAGAIN || errno == EINTR)
                continue;
            
            return -1;
        }else
        {
            return -1;
        }
    }

    return 0;
}
