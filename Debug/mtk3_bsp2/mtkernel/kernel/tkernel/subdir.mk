################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtk3_bsp2/mtkernel/kernel/tkernel/cpuctl.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/device.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/deviceio.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/eventflag.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/int.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/klock.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/mailbox.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/memory.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/mempfix.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/mempool.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/messagebuf.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/misc_calls.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/mutex.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/objname.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/power.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/rendezvous.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/semaphore.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/task.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/task_manage.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/task_sync.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/time_calls.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/timer.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/tkinit.c \
../mtk3_bsp2/mtkernel/kernel/tkernel/wait.c 

C_DEPS += \
./mtk3_bsp2/mtkernel/kernel/tkernel/cpuctl.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/device.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/deviceio.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/eventflag.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/int.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/klock.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/mailbox.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/memory.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/mempfix.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/mempool.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/messagebuf.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/misc_calls.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/mutex.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/objname.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/power.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/rendezvous.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/semaphore.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/task.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/task_manage.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/task_sync.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/time_calls.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/timer.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/tkinit.d \
./mtk3_bsp2/mtkernel/kernel/tkernel/wait.d 

OBJS += \
./mtk3_bsp2/mtkernel/kernel/tkernel/cpuctl.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/device.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/deviceio.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/eventflag.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/int.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/klock.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/mailbox.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/memory.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/mempfix.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/mempool.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/messagebuf.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/misc_calls.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/mutex.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/objname.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/power.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/rendezvous.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/semaphore.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/task.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/task_manage.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/task_sync.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/time_calls.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/timer.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/tkinit.o \
./mtk3_bsp2/mtkernel/kernel/tkernel/wait.o 

SREC += \
mtk3bsp2_ra8m1.srec 

MAP += \
mtk3bsp2_ra8m1.map 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/mtkernel/kernel/tkernel/%.o: ../mtk3_bsp2/mtkernel/kernel/tkernel/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -march=armv8.1-m.main+mve.fp+fp.dp -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM85 -D_RA_ORDINAL=1 -D_RAFSP_EK_RA8M1_ -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/src" -I"." -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/api" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/instances" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_gen" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg/bsp" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/config" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/mtkernel/kernel/knlinc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -flax-vector-conversions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

