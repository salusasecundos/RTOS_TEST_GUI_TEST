################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/tinyusb/src/portable/template/dcd_template.c 

OBJS += \
./Middlewares/tinyusb/src/portable/template/dcd_template.o 

C_DEPS += \
./Middlewares/tinyusb/src/portable/template/dcd_template.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/tinyusb/src/portable/template/%.o: ../Middlewares/tinyusb/src/portable/template/%.c Middlewares/tinyusb/src/portable/template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/BSP -I../Drivers/CMSIS/Include -I../Drivers/BSP/components/Bme280 -I../Drivers/BSP/components/common -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STemWin/inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../STemWin/App -I../STemWin/Target -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/tasks -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-tinyusb-2f-src-2f-portable-2f-template

clean-Middlewares-2f-tinyusb-2f-src-2f-portable-2f-template:
	-$(RM) ./Middlewares/tinyusb/src/portable/template/dcd_template.d ./Middlewares/tinyusb/src/portable/template/dcd_template.o

.PHONY: clean-Middlewares-2f-tinyusb-2f-src-2f-portable-2f-template

