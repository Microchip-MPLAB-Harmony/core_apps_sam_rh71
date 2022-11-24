/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <string.h>
#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    uint32_t i = 0;

    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        appData.writeBuffer[i] = i;
    }
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            if (DRV_SST38_Status(DRV_SST38_INDEX) == SYS_STATUS_READY)
            {
                appData.state = APP_STATE_OPEN_DRIVER;
            }
            break;
        }

        case APP_STATE_OPEN_DRIVER:
        {
            appData.handle = DRV_SST38_Open((SYS_MODULE_INDEX)DRV_SST38_INDEX, DRV_IO_INTENT_READWRITE);

            if (appData.handle != DRV_HANDLE_INVALID)
            {
                appData.state = APP_STATE_ID_GET;
            }
            break;
        }

        case APP_STATE_ID_GET:
        {
            if (DRV_SST38_ReadProductId(appData.handle, &appData.readManId, &appData.readDeviceId) != true)
            {
                appData.state = APP_STATE_ERROR;
            }
            else
            {
                if ( (appData.readManId == SST38_MANUFACTURER_ID) && (appData.readDeviceId == SST38_DEVICE_ID) )
                {
                    appData.state = APP_STATE_ERASE_FLASH;
                }
                else
                {
                    appData.state = APP_STATE_ERROR;
                }
            }
            break;
        }

        case APP_STATE_ERASE_FLASH:
        {
            if (DRV_SST38_ChipErase(appData.handle) != true)
            {
                appData.state = APP_STATE_ERROR;
            }
            else
        {
                appData.state = APP_STATE_READ_MEMORY_ERASED;
            }
            break;
        }

        case APP_STATE_READ_MEMORY_ERASED:
        {
            if (DRV_SST38_Read(appData.handle, appData.readBuffer, BUFFER_SIZE, 0x60000000U) != true)
            {
                appData.state = APP_STATE_ERROR;
            }
            else
            {
                appData.state = APP_STATE_VERIFY_ERASE;
            }
            break;
        }

        case APP_STATE_VERIFY_ERASE:
        {
            bool errorErase = false;
            uint32_t i = 0;

            for (i = 0; i < BUFFER_SIZE; i++)
            {
                if (appData.readBuffer[i] != 0xFF ){
                    errorErase = true;
                }
            }

            if (errorErase)
            {
                appData.state = APP_STATE_ERROR;
            }
            else
            {
                appData.state = APP_STATE_WRITE_MEMORY;
            }
            break;
        }

        case APP_STATE_WRITE_MEMORY:
        {
            if (DRV_SST38_PageWrite(appData.handle, appData.writeBuffer, 0x60000000U) != true)
            {
                appData.state = APP_STATE_ERROR;
            }
            else
            {
                appData.state = APP_STATE_READ_MEMORY;
            }
            break;
        }
        
        case APP_STATE_READ_MEMORY:
        {
            if (DRV_SST38_Read(appData.handle, appData.readBuffer, BUFFER_SIZE, 0x60000000U) != true)
            {
                appData.state = APP_STATE_ERROR;
            }
            else
            {
                appData.state = APP_STATE_VERIFY_DATA;
            }
            break;
        }    

        case APP_STATE_VERIFY_DATA:
        {
            if (!memcmp(appData.writeBuffer, appData.readBuffer, BUFFER_SIZE))
        {
                appData.state = APP_STATE_SUCCESS;
            }
            else
            {
                appData.state = APP_STATE_ERROR;
            }
            break;
        }

        case APP_STATE_SUCCESS:
        {
            LED_ON();
            break;
        }

        case APP_STATE_ERROR:
        default:
            LED_OFF();
    }
}


/*******************************************************************************
 End of File
 */
