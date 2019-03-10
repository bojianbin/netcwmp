#ifndef __CWMP_DATA_MODEL_H__
#define __CWMP_DATA_MODEL_H__

#include <cwmp/cwmp.h>

typedef enum
{
    TASK_CALLBACK_WAN
}task_callback_type_e;

typedef struct 
{
    task_callback_type_e type;
    void * data1;
    void * data2;
}task_common_set_t;

int get_index_after_paramname(parameter_node_t * param, const char * tag_name);
void cwmp_model_load(cwmp_t * cwmp, const char * xmlfile);

#endif
