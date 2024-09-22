################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/hllint_ent.S 

C_SRCS += \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/group_int.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/hllint_tbl.c \
../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/intvect_tbl.c 

C_DEPS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/group_int.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/hllint_tbl.d \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/intvect_tbl.d 

OBJS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/group_int.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/hllint_ent.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/hllint_tbl.o \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/intvect_tbl.o 

SREC += \
mtk3bsp2_ra8m1.srec 

S_UPPER_DEPS += \
./mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/hllint_ent.d 

MAP += \
mtk3bsp2_ra8m1.map 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/%.o: ../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/%.c
	$(file > $@.in,-mthumb -mfloat-abi=hard -march=armv8.1-m.main+mve.fp+fp.dp -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM85 -D_RA_ORDINAL=1 -D_RAFSP_EK_RA8M1_ -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/src" -I"." -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/api" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/instances" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_gen" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg/bsp" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/config" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/mtkernel/kernel/knlinc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -flax-vector-conversions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"
mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/%.o: ../mtk3_bsp2/mtkernel/kernel/sysdepend/cpu/rx65n/%.S
	$(file > $@.in,-mthumb -mfloat-abi=hard -march=armv8.1-m.main+mve.fp+fp.dp -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -g -gdwarf-4 -x assembler-with-cpp -D_RENESAS_RA_ -D_RA_CORE=CM85 -D_RA_ORDINAL=1 -D_RAFSP_EK_RA8M1_ -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/src" -I"." -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/api" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/fsp/inc/instances" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_gen" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg/bsp" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/ra_cfg/fsp_cfg" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/config" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_ra8m1/mtk3_bsp2/mtkernel/kernel/knlinc" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

