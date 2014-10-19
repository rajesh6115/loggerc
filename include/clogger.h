
/******************************************************************************
** General Logger in C it can enerate File and Log message passes to it      **
** It is having different logging level to catagorise loging                 **
******************************************************************************/

#ifndef _LOGGER_C_H_
#define _LOGGER_C_H_
#define ENABLE_THREADS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef ENABLE_THREADS
#include <pthread.h>
#endif

#define PATH_MAX_SIZE 256
#define NAME_MAX_SIZE 64
#define TAG_MAX_SIZE 16

#define LOG_EMERG 0 
#define LOG_ALERT 1
#define LOG_CRITICAL 2
#define LOG_ERROR 3
#define LOG_WARNING 4
#define LOG_NOTICE 5
#define LOG_INFO 6
#define LOG_DEBUG 7
#define LOG_DEFAULT 8
#define LOG_CONT 9
#define LOG_CONSOL 10

#define DFL_NAME "united"
#define DFL_PATH "."
#define DFL_TAG "LOG"
#define DFL_INTERVAL 300
#define DFL_LEVEL 5

typedef struct logger{
	FILE *fp;
	unsigned int level;
	unsigned int is_log;
	time_t create_time;
	time_t interval;
	char path[PATH_MAX_SIZE];
	char name[NAME_MAX_SIZE];
	char tag[TAG_MAX_SIZE];
#ifdef ENABLE_THREADS
	pthread_mutex_t file_lock;
#endif
}logger_t;
typedef logger_t * logger_p;

logger_p logger_init(void);
int logger_cleanup(logger_p);
#ifdef ENABLE_THREADS
int logger_lock(logger_p);
int logger_unlock(logger_p);
#endif
int logger_open(logger_p);
int logger_close(logger_p);
int logger_set(logger_p ,unsigned int option, const char *);
int logger_log_header(logger_p log,unsigned int log_level ,const char *leveltag ,const char *srcname ,unsigned int line_no);
int logger_log_message(logger_p ,char *format ,...);
#define DBG_VERBOSE(OBJECT,PRINTDATA) { OBJECT.mcfn_Lock();OBJECT.mcfn_logCallerInfo(VERBOSE,"~VB~",__FILE__,__LINE__); OBJECT.mcfn_logMessage PRINTDATA;OBJECT.mcfn_Unlock();} 
#define DBG_INFO(OBJECT,PRINTDATA) { OBJECT.mcfn_Lock();OBJECT.mcfn_logCallerInfo(INFO,"~IN~",__FILE__,__LINE__); OBJECT.mcfn_logMessage PRINTDATA;OBJECT.mcfn_Unlock();}
#define DBG_ERROR(OBJECT,PRINTDATA) { OBJECT.mcfn_Lock();OBJECT.mcfn_logCallerInfo(LOGERROR,"~ER~",__FILE__,__LINE__); OBJECT.mcfn_logMessage PRINTDATA;OBJECT.mcfn_Unlock();}
#define DBG_CRITICAL(OBJECT,PRINTDATA) { OBJECT.mcfn_Lock();OBJECT.mcfn_logCallerInfo(CRITICAL,"~CR~",__FILE__,__LINE__); OBJECT.mcfn_logMessage PRINTDATA;OBJECT.mcfn_Unlock();}
#define DBG_LOGMSG(OBJECT,PRINTDATA) { OBJECT.mcfn_Lock();OBJECT.mcfn_logCallerInfo(CRITICAL,"~LM~",__FILE__,__LINE__); OBJECT.mcfn_logMessage PRINTDATA;OBJECT.mcfn_Unlock();}

#endif


