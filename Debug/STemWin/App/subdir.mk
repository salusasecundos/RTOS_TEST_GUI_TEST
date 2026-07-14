################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: arm-none-eabi-gcc-11.2.0-211218-win64
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STemWin/App/GUI_App.c 

OBJS += \
./STemWin/App/GUI_App.o 

C_DEPS += \
./STemWin/App/GUI_App.d 


# Each subdirectory must supply rules for building sources it contributes
STemWin/App/%.o STemWin/App/%.su STemWin/App/%.cyclo: ../STemWin/App/%.c STemWin/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/BSP -I../Drivers/CMSIS/Include -I../Drivers/BSP/components/Bme280 -I../Drivers/BSP/components/common -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STemWin/inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../STemWin/App -I../STemWin/Target -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/tasks -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STemWin-2f-App

clean-STemWin-2f-App:
	-$(RM) ./STemWin/App/GUI_App.cyclo ./STemWin/App/GUI_App.d ./STemWin/App/GUI_App.o ./STemWin/App/GUI_App.su

.PHONY: clean-STemWin-2f-App

