/************************************************************************
 * Id: util.c                                                           *
 *                                                                      *
 * TR069 Project:  A TR069 library in C                                 *
 * Copyright (C) 2013-2014  netcwmp.netcwmp group                                *
 *                                                                      *
 *                                                                      *
 * Email: netcwmp ( & ) gmail dot com                                *
 *                                                                      *  
 ***********************************************************************/

 
#include "cwmp/util.h"
#include "cwmp/md5.h"

static const char base64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static char * base64_encode(const char *src)
{
    char *str, *dst;
    size_t l;
    int t, r;

    l = strlen(src);
    if ((str = malloc(((l + 2) / 3) * 4 + 1)) == 0)
        return (void*)0;
    dst = str;
    r = 0;

    while (l >= 3)
    {
        t = (src[0] << 16) | (src[1] << 8) | src[2];
        dst[0] = base64[(t >> 18) & 0x3f];
        dst[1] = base64[(t >> 12) & 0x3f];
        dst[2] = base64[(t >> 6) & 0x3f];
        dst[3] = base64[(t >> 0) & 0x3f];
        src += 3;
        l -= 3;
        dst += 4;
        r += 4;
    }

    switch (l)
    {
    case 2:
        t = (src[0] << 16) | (src[1] << 8);
        dst[0] = base64[(t >> 18) & 0x3f];
        dst[1] = base64[(t >> 12) & 0x3f];
        dst[2] = base64[(t >> 6) & 0x3f];
        dst[3] = '=';
        dst += 4;
        r += 4;
        break;
    case 1:
        t = src[0] << 16;
        dst[0] = base64[(t >> 18) & 0x3f];
        dst[1] = base64[(t >> 12) & 0x3f];
        dst[2] = dst[3] = '=';
        dst += 4;
        r += 4;
        break;
    case 0:
        break;
    }

    *dst = 0;
    return (str);
}

static void cwmp_hex_to_string(char *to, const unsigned char *p, size_t len)
{
    const char  *hex = "0123456789abcdef";

    for (;len--; p++)
    {
        *to++ = hex[p[0] >> 4];
        *to++ = hex[p[0] & 0x0f];

    }
    *to = '\0';
}



void MD5(char *buf, ...)
{
    unsigned char   hash[HASHLEN];
    unsigned char   *p;
    va_list ap;
    MD5_CTX ctx;

    MD5Init(&ctx);

    va_start(ap, buf);
    while ((p = va_arg(ap, unsigned char *)) != NULL)
    {
        MD5Update(&ctx, p, strlen((char *) p));
    }
    va_end(ap);

    MD5Final(hash, &ctx);

    cwmp_hex_to_string(buf, hash, sizeof(hash));
}



void convert_to_hex(const char *Bin, char *Hex)
{
    unsigned short i;
    unsigned char j;
    for (i = 0; i < 16; i++)
    {
        j = (Bin[i] >> 4) & 0xf;
        if (j <= 9)
            Hex[i*2] = (j + '0');
        else
            Hex[i*2] = (j + 'a'-10);
        j = Bin[i] & 0xf;
        if (j <= 9)
            Hex[i*2+1] = (j + '0');
        else
            Hex[i*2+1] = (j + 'a'-10);
    }
    Hex[32] = '\0';
}

/*we assume localtime can get the local time correctly*/
int to_iso8601_datetime(char *buf,int len,time_t time,int utc_format)
{
	struct tm *_time = NULL;
	
	if( !buf || len <= 0 )
		return -1;

	if(utc_format)
	{
		_time = gmtime(&time);
		if(!_time)
			return -1;

		snprintf(buf,len - 1,"%d%02d%02dT%02d:%02d:%02dZ",
			_time->tm_year + 1900,
			_time->tm_mon + 1,
			_time->tm_mday,
			_time->tm_hour,
			_time->tm_min,
			_time->tm_sec);
	}else
	{
		time_t utc_time = 0;
		int time_zone_;
		struct tm * p_tm_time = localtime( &utc_time );

		//get time zone [-11 11]
		if(!p_tm_time)
			return -1;
		time_zone_ = ( p_tm_time->tm_hour > 12 ) ?   ( p_tm_time->tm_hour-=  24 )  :  p_tm_time->tm_hour;

		//generate time string
		_time = localtime(&time);
		if(!_time)
			return -1;

		snprintf(buf,len - 1,"%d%02d%02dT%02d:%02d:%02d%s%02d",
			_time->tm_year + 1900,
			_time->tm_mon + 1,
			_time->tm_mday,
			_time->tm_hour,
			_time->tm_min,
			_time->tm_sec,
			time_zone_ >= 0 ? "+":"-",
			time_zone_ < 0 ?(0 - time_zone_):time_zone_);
		
	}

	return 0;
}







