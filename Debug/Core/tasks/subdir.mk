################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: arm-none-eabi-gcc-11.2.0-211218-win64
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/tasks/gui_task.c \
../Core/tasks/led_task.c \
../Core/tasks/usb_task.c 

OBJS += \
./Core/tasks/gui_task.o \
./Core/tasks/led_task.o \
./Core/tasks/usb_task.o 

C_DEPS += \
./Core/tasks/gui_task.d \
./Core/tasks/led_task.d \
./Core/tasks/usb_task.d 


# Each subdirectory must supply rules for building sources it contributes
Core/tasks/%.o Core/tasks/%.su Core/tasks/%.cyclo: ../Core/tasks/%.c Core/tasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/BSP -I../Drivers/CMSIS/Include -I../Drivers/BSP/components/Bme280 -I../Drivers/BSP/components/common -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STemWin/inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../STemWin/App -I../STemWin/Target -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/tasks/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-tasks

clean-Core-2f-tasks:
	-$(RM) ./Core/tasks/gui_task.cyclo ./Core/tasks/gui_task.d ./Core/tasks/gui_task.o ./Core/tasks/gui_task.su ./Core/tasks/led_task.cyclo ./Core/tasks/led_task.d ./Core/tasks/led_task.o ./Core/tasks/led_task.su ./Core/tasks/usb_task.cyclo ./Core/tasks/usb_task.d ./Core/tasks/usb_task.o ./Core/tasks/usb_task.su

.PHONY: clean-Core-2f-tasks

