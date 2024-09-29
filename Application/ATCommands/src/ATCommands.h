#ifndef __AT_COMMANDS_H__
#define __AT_COMMANDS_H__

#include <tk/tkernel.h>
#include <tm/tmonitor.h>

#define AT_ERROR "ERROR"
#define AT_SUCCESS "OK"
#define NumberOfCommands 16
#define CMDSIZE 32

char* cmd_list[NumberOfCommands]={
      "+NAME",
      "+RESET",
      "+ATTR",
      "+CRFOP",
      "+CNE",
      "+PERIOD",
      "+PWMODE",
      "+CFUN"
};

typedef enum ternary
{
    AT_COMMANDS_SUCCESS = 0,
    AT_COMMANDS_ERROR_NO_SERIAL,
    AT_COMMANDS_ERROR_BUFFER_FULL,
    AT_COMMANDS_ERROR_SYNTAX
} AT_COMMANDS_ERRORS;

typedef enum
{
    AT_COMMAND_READ,
    AT_COMMAND_WRITE,
    AT_COMMAND_TEST,
    AT_COMMAND_RUN
} AT_COMMAND_TYPE;

AT_COMMANDS_ERRORS update(char* get_data);

#endif
