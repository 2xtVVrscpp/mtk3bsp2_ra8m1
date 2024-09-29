/*
The original program of this program is Arduino library.

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "ATCommands.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "kernel.h"

/**
 * @brief isValidCmdChar
 * Hackish attempt at validating input commands
 * @param ch
 * @return int
 */
int isValidCmdChar(const char ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '+') || (ch == '#') || (ch == '$') || (ch == '@') || (ch == '_') || (ch == '=') || (ch == '?');
}

BOOL run(UB cmd_num){
    return 0;
}
BOOL read(UB cmd_num){
    return 0;
}
BOOL test(UB cmd_num){
    return 0;
}
BOOL write(UB cmd_num){
    return 0;
}

/**
 * @brief ok
 * prints OK to terminal
 *
 */
void ok()
{
    tm_printf((UB*)"OK");
}

/**
 * @brief error
 * prints ERROR to terminal
 *
 */
void error()
{
    tm_printf((UB*)"ERROR");
}


/**
 * @brief parseParameters
 * Called mainly by parseCommand as an extention to tokenize parameters
 * usually supplied in WRITE (eg AT+COMMAND=param1,param2) commands.  It makes
 * use of malloc so check above in parseCommand where we free it to keep things
 * neat.
 * @param pos
 * @return true
 * @return false
 */
BOOL parseParameters(char* get_data, UB pos)
{
    return TRUE;
}

/**
 * @brief parseCommand
 * Checks the incoming buffer to ensure it begins with AT and then seeks to
 * determine if the command is of type RUN, TEST, READ or WRITE.  For WRITE
 * commands the buffer is furthered parsed to extract parameters.  Once
 * all actions are complete and the command type is determined the command
 * is compared against the delcared array (atCommands) to find a matching
 * command name.  If a match is found the function is passed to the handler
 * for later execution.
 * @return true 
 * @return false 
 */
BOOL parseCommand(char* get_data, UB* type, UB* cmd_num, UB* arg_pos)
{
    INT i = 0;
    char commands[256];

    if (get_data[i++] != 'A' || get_data[i++] != 'T')
    {
        return FALSE;
    }


    for (i = 2; get_data[i] != '\0'; i++)
    {
        // eliminate
        if (isValidCmdChar(get_data[i]) == 0)
        {
            return FALSE;
        }

        // determine command type
        if (get_data[i] == '=')
        {
            // Is this a TEST or a WRITE command?
            if (get_data[i + 1] == '?')
            {
                *type = AT_COMMAND_TEST;
                break;
            }
            else
            {
                *type = AT_COMMAND_WRITE;
                break;
            }
        }
        if (get_data[i] == '?')
        {
            *type = AT_COMMAND_READ;
            break;
        }
    }

    if(get_data[i] == '\0'){
        *type = AT_COMMAND_RUN;
    }

    *arg_pos = i;

    for(int j = 0;j<256 && get_data[j+2] != '\0';j++){
        commands[j] = get_data[j+2];
    }

    // search for matching command in array
    for (UB j = 0; j < NumberOfCommands; j++)
    {
        if (knl_strcmp(commands, cmd_list[j]) == 0)
        {
            *cmd_num = j;
            break;
        }
    }

    // if we did not find a match there's no point in continuing
    if (*cmd_num == -1)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL process_cmd(char* get_data, UB type, UB cmd_num, UB arg_pos){
    // handle the different commands
        switch (type)
        {
        case AT_COMMAND_RUN:
            run(cmd_num);
            goto process;
        case AT_COMMAND_READ:
            read(cmd_num);
            goto process;
        case AT_COMMAND_TEST:
            test(cmd_num);
            goto process;
        case AT_COMMAND_WRITE:
            if (parseParameters(get_data, arg_pos))
            {
                write(cmd_num);
                goto process;
            }
            return FALSE;

        process:
            // future placeholder
            return TRUE;
        }
        return TRUE;
}



/**
 * @brief update
 * Main function called by the loop.  Reads in available charactrers and writes
 * to the buffer.  When the line terminator is found continues to parse and eventually
 * process the command.
 * @return AT_COMMANDS_ERRORS 
 */
AT_COMMANDS_ERRORS update(char* get_data)
{
    UB type, cmd_num, arg_pos;
    if (!parseCommand(get_data, &type, &cmd_num, &arg_pos))
    {
        error();
        return AT_COMMANDS_ERROR_SYNTAX;
    }

    // process the command
    process_cmd(get_data, type, cmd_num, arg_pos);

    return AT_COMMANDS_SUCCESS;
}





