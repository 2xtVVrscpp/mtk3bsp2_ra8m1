################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/cpu_clock.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/devinit.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/hw_setting.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/power_save.c 

C_DEPS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/cpu_clock.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/devinit.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/hw_setting.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/power_save.d 

OBJS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/cpu_clock.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/devinit.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/hw_setting.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/power_save.o 

SREC += \
mtk3bsp2_ra8m1.srec 

MAP += \
mtk3bsp2_ra8m1.map 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/%.o: ../mtk3_bsp2/mtkernel/kernel/sysdepend/iote_m367/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -march=armv8.1-m.main+mve.fp+fp.dp -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM85 -D_RA_ORDINAL=1 -D_RAFSP_EK_RA8M1_ -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/src" -I"." -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/api" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/instances" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_gen" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg/bsp" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/config" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/mtkernel/kernel/knlinc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -flax-vector-conversions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

