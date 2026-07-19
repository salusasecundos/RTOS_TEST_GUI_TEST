#ifndef GUICONF_H
#define GUICONF_H

/*********************************************************************
*
*       Multi layer/display support
*/
#define GUI_NUM_LAYERS        (1)   // Maximum number of available layers

/*********************************************************************
*
*    Multi tasking support
*/
       
 #define GUI_OS              (1)       // Compile with multitasking support

/*********************************************************************
*
*       Configuration of touch support
*/
#ifndef   GUI_SUPPORT_TOUCH
  #define GUI_SUPPORT_TOUCH       (0)  // Support touchscreen
#endif

/*********************************************************************
*
*       Default font
*/
#define GUI_DEFAULT_FONT               &Font6x9

/*********************************************************************
*
*         Configuration of available packages
*/
#define GUI_SUPPORT_MOUSE             (0)    /* Support a mouse */
#define GUI_WINSUPPORT                (1)    /* Use window manager */
#define GUI_SUPPORT_MEMDEV            (1)    /* Memory device package available */
#define GUI_SUPPORT_DEVICES           (1)    /* Enable use of device pointers */

/* This define swaps the meaning of a logical color from
   ABGR to ARGB.
   
   It further swaps the meaning of a transparent pixel:
   ABGR: 0x00 means opaque, 0xFF means transparent (default)
   ARGB: 0x00 means transparent, 0xFF means opaque
*/
#define GUI_USE_ARGB					1

#endif  /* Avoid multiple inclusion */
