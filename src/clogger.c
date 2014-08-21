
/******************************************************************************
** General Logger in C it can enerate File and Log message passes to it      **
** It is having different logging level to catagorise loging                 **
******************************************************************************/

#include "clogger.h"

logger_p logger_init(void)
{
	logger_p log = (logger_p) malloc(sizeof(logger_t));
	if(log == NULL)
	{
		return NULL;
	}
	else
	{
		memset(log,0x00,sizeof(logger_t));
		strcpy(log->path ,DFL_PATH );
		strcpy(log->name ,DFL_NAME );
		strcpy(log->tag ,DFL_TAG );
		log->level = DFL_LEVEL ;
		log->interval = DFL_INTERVAL;
		log->create_time = 0;
		log->fp = NULL;
		return log;
	}
}

int logger_cleanup(logger_p log)
{
	if(log)
	{
		logger_close(log);
		free(log);
		
		return 0;
	}
	else
	{
		return -1;
	}
}

int logger_open(logger_p log)
{
	struct tm cur_time;
	char fname[PATH_MAX_SIZE + NAME_MAX_SIZE + 20]={0x00}; //additional 20 for time stamp
	if(log)
	{
		time(&log->create_time);
		localtime_r(&log->create_time , &cur_time);
		if(log->interval < 3600)
		{
			sprintf(fname,"%s/%s_%04d%02d%02d%02d%02d.log" ,log->path ,log->name ,cur_time.tm_year+1900,cur_time.tm_mon+1 ,cur_time.tm_mday ,cur_time.tm_hour ,cur_time.tm_min );
		}
		else
		{
			sprintf(fname,"%s/%s_%04d%02d%02d%02d.log" ,log->path ,log->name ,cur_time.tm_year+1900,cur_time.tm_mon+1 ,cur_time.tm_mday ,cur_time.tm_hour );
		}
		// if log->fp is open then close it first
		if(log->fp != NULL)
		{
			logger_close(log);
		}
		log->fp = fopen(fname ,"a+");
		if(log->fp == NULL)
		{
			return -1;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}


int logger_close(logger_p log)
{
	if(log)
	{
		if(log->fp != NULL)
		{
			fflush(log->fp);
			fclose(log->fp);
			log->fp == NULL;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

int logger_log_header(logger_p log,unsigned int log_level ,const char *leveltag ,const char *srcname ,unsigned int line_no)
{
	int ret_val = 0;
	struct tm cur_time;
	time_t temp_time;
	char logtag[64]={0x00};
	if(log == NULL)
	{
		return -1;
	}

	if(log_level > log->level)
	{
		log->is_log = 0;
		return 0;
	}
	log->is_log = 1;
	/////check for new file generation condition///////////
	temp_time = time(NULL);
	if((temp_time - log->create_time) > log->interval)
	{
		logger_open(log);
	}
	/////prepare tag//////////
	//time(&temp_time);
	temp_time = time(NULL);
	localtime_r(&temp_time , &cur_time);
	sprintf(logtag ,"[%s|%s|%d|%02d:%02d:%02d|%s]" ,log->tag ,srcname ,line_no ,cur_time.tm_hour ,cur_time.tm_min ,cur_time.tm_sec ,leveltag);
	/*  to be designed
	if(log_level == DISP_SCREEN)
	{
		fprintf(stdout ,"%s",logtag);
		fflush(stdout);
	}
	*/
	ret_val = fprintf(log->fp ,"%s" ,logtag);
	fflush(log->fp);
	return ret_val;
}

int logger_log_message(logger_p log,char *format ,...)
{
	int ret_val = 0;
	va_list args;
	if(log == NULL)
        {
                return -1;
        }
	if(log->is_log == 0)
	{
		return 0;
	}
	va_start(args,format);
	ret_val = vfprintf(log->fp ,format ,args);
	fprintf(log->fp,"\n");
	fflush(log->fp);
	va_end(args);
	return ret_val;
}
