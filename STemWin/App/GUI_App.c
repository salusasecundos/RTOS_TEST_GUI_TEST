#include "GUI_App.h"
#include "GUI.h"

#include "DIALOG.h"
extern  WM_HWIN CreateFramewin(void); 
  

void GRAPHICS_MainTask(void)
{

  /* 1- Create a FrameWin using GUIBuilder */
//  CreateFramewin();
 
/* USER CODE BEGIN GRAPHICS_MainTask */
 /* User can implement his graphic application here */
  /* Hello Word example */
    GUI_SetBkColor(GUI_LIGHTBLUE);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
//    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font13B_1);
    GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
    HAL_Delay(1000);
    GUI_DispStringAt("How's going", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
   
/* USER CODE END GRAPHICS_MainTask */
  while(1)
  {
//	  GUI_Clear();
	  GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
	  GUI_Delay(1000);
	  GUI_DispStringAt("How's going", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
	  GUI_Delay(1000);
	  GUI_DispStringAt("0", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("1", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("2", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("3", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("4", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("5", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("6", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("7", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("8", 10, 10);
	  GUI_Delay(1000);
	  GUI_DispStringAt("9", 10, 10);
	  GUI_Delay(1000);

  }
}

/*************************** End of file ****************************/
