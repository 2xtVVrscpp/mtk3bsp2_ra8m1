/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.00.00
 *
 *    Copyright (C) 2006-2019 by Ken Sakamura.
 *    This software is distributed under the T-License 2.1.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2019/12/11.
 *
 *----------------------------------------------------------------------
 */

#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include "kernel.h"

#define LED1 (1<<0)     // port 600
#define LED2 (1<<14)    // port 414
#define LED3 (1<<7)     // port 107

#define GPIO_LED (1<<5)// P505

#define BUFSIZE 256
enum DEVICE_CODE{
    DEV_UART,
    DEV_I2C,
    DEV_ADC,
};

/*
 * Entry routine for the user application.
 * At this point, Initialize and start the user application.
 *
 * Entry routine is called from the initial task for Kernel,
 * so system call for stopping the task should not be issued
 * from the contexts of entry routine.
 * We recommend that:
 * (1)'usermain()' only generates the user initial task.
 * (2)initialize and start the user application by the user
 * initial task.
 */

//LOCAL void task_1(INT stacd, void *exinf);  // task execution function
//LOCAL ID    tskid_1;            // Task ID number
//LOCAL T_CTSK ctsk_1 = {             // Task creation information
//    .itskpri    = 2,
//    .stksz      = 1024,
//    .task       = task_1,
//    .tskatr     = TA_HLNG | TA_RNG3,
//};
//LOCAL void task_2(INT stacd, void *exinf);  // task execution function
//LOCAL ID    tskid_2;            // Task ID number
//LOCAL T_CTSK ctsk_2 = {             // Task creation information
//    .itskpri    = 10,
//    .stksz      = 1024,
//    .task       = task_2,
//    .tskatr     = TA_HLNG | TA_RNG3,
//};

ID dd_com = -1;
LOCAL UINT wflgptn = 1<<0, rflgptn;

LOCAL void read_tsk(INT stacd, void *exinf);  // task execution function
LOCAL ID    tskid_read;            // Task ID number
LOCAL T_CTSK ctsk_read = {             // Task creation information
    .itskpri    = 10,
    .stksz      = 1024,
    .task       = read_tsk,
    .tskatr     = TA_HLNG | TA_RNG3,
};

LOCAL void send_tsk(INT stacd, void *exinf);  // task execution function
LOCAL ID    tskid_send;            // Task ID number
LOCAL T_CTSK ctsk_send = {             // Task creation information
    .itskpri    = 8,
    .stksz      = 1024,
    .task       = send_tsk,
    .tskatr     = TA_HLNG | TA_RNG3,
};

LOCAL ER open_device(enum DEVICE_CODE target)
{
    ER err = E_OK;

    switch(target){
        case DEV_UART:
            dd_com = tk_opn_dev((UB*)"huarta", TD_UPDATE);
            if(dd_com < E_OK){
                tm_printf((UB*)"uart_init: open error\n");
                err = -1;
            }
            break;
        case DEV_I2C:
            dd_com = tk_opn_dev((UB*)"hiica", TD_UPDATE);
            if(dd_com < E_OK){
                tm_printf((UB*)"uart_init: open error\n");
                err = -1;
            }
            break;
        default:
            tm_printf((UB*)"undefined error\n");
            err = -2;
            break;
    }

    return err;
}

LOCAL SZ get_str_siz(const char str[], const char d){
    SZ i = 0;
    while(str[i] != '\0' && str[i] != d){
        i++;
    }
    return i;
}

LOCAL void read_tsk(INT stacd, void *exinf)
{
    char data_com[BUFSIZE] = {'\0'};
    ER err;
    UB err_cnt = 0, i;

    tm_printf((UB*)"tsk read start\n");

    if(dd_com == -1){
        err = open_device(DEV_UART);
        if(err != E_OK){
            tm_printf((UB*)"open error\n");
            tk_ext_tsk();
        }
    }

    while(1){
        err = tk_rea_dev(dd_com, 0, data_com, BUFSIZE, TMO_FEVR);
        i = get_str_siz(data_com, '\r');
        data_com[i] = (UB)'\0';
        tm_printf((UB*)"get data: %s\n", data_com);

        if(err >= E_OK){
            tm_printf((UB*)"Read Success %d\n", err);
            err_cnt = 0;
            if (data_com[0] == 'A'){
                out_h(PORT_PODR(5), (in_h(PORT_PODR(5)))^GPIO_LED);
                data_com[0] = '\0';
              }
            if(data_com[0] == 'L' && knl_strcmp((char*)data_com, "LED1") == 0){
                out_h(PORT_PODR(6), (in_h(PORT_PODR(6)))^LED1);
            }else if(data_com[0] == 'L' && knl_strcmp((char*)data_com, "LED2") == 0){
                out_h(PORT_PODR(4), (in_h(PORT_PODR(4)))^LED2);
            }else if(data_com[0] == 'L' && knl_strcmp((char*)data_com, "LED3") == 0){
                out_h(PORT_PODR(1), (in_h(PORT_PODR(1)))^LED3);
              }

//            err = tk_wri_dev(dd_com, 0, data_com, get_str_siz(data_com, '\0'), TMO_FEVR);
//            if(err >= E_OK){
//                tm_printf((UB*)"Send Success: %d\n", err);
//            } else {
//                tm_printf((UB*)"Send Error: %d\n", err);
//              }
        }else {
            tm_printf((UB*)"Read Error %d\n", err);
        }
//        read command wait the buffer so it is not needed tk_dly_tsk
        tk_dly_tsk(100);
        data_com[0] = (UB)'\0';
    }
    tk_ext_tsk();
}

LOCAL void send_tsk(INT stacd, void *exinf)
{
    ER err;
    UB i = 0;

    tm_printf((UB*)"tsk send start\n");

    if(dd_com == -1){
        err = open_device(DEV_UART);
        if(err != E_OK){
            tm_printf((UB*)"open error\n");
            tk_ext_tsk();
        }
    }

    while(1){
        err = tk_wri_dev(dd_com, 0, "hello\n", get_str_siz("hello\n", '\0'), TMO_FEVR);
        if(err >= E_OK){
            tm_printf((UB*)"Send Success: %d\n", err);
            i = 0;
        } else {
            tm_printf((UB*)"Send Error: %d\n", err);
            i++;

            // timeout
            if(i > 5){
                break;
            }
        }
//
        tk_dly_tsk(1000);
    }
    tk_ext_tsk();
}

/* usermain関数 */
EXPORT INT    usermain( void )
{
    tm_printf((UB*)"Start User-main program.\n");

    tskid_read = tk_cre_tsk(&ctsk_read);
    tk_sta_tsk(tskid_read, 0);

//    tskid_send = tk_cre_tsk(&ctsk_send);
//    tk_sta_tsk(tskid_send, 0);

    tk_slp_tsk(TMO_FEVR);

    return 0;
}
