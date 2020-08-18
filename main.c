/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the PSoC 6 MCU Secure Blinky FreeRTOS
*              Example for ModusToolbox.
*
* Related Document: See Readme.md
*
*
*******************************************************************************
* Copyright (2020), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries ("Cypress") and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*******************************************************************************/

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"


/*******************************************************************************
* Macros
********************************************************************************/
/* Defines for a simple task */
#define SECURE_BLINKY_LED_EXAMPLE_NAME         ("SecureBlinkyFreeRTOS")
#define SECURE_BLINKY_LED_EXAMPLE_STACK_SIZE   (1024)
#define SECURE_BLINKY_LED_EXAMPLE_PRIORITY     (5)
#define SECURE_BLINKY_LED_EXAMPLE_DELAY_TICKS  (500)

UBaseType_t __attribute__((used)) uxTopUsedPriority;

#define uxTopReadyPriority uxTopUsedPriority

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void blinky_task( void * arg );

/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CM4 CPU. It does...
*    1. Creates a FreeRTOS task
*    2. Starts FreeRTOS scheduler
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;
    int retval;

    uxTopUsedPriority = configMAX_PRIORITIES - 1;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize retarget-io to use the debug UART port */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    /* Initialize the User LED */
    cyhal_gpio_init((cyhal_gpio_t) CYBSP_USER_LED1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "PSoC 64 MCU: Secure Blinky LED FreeRTOS Example "
           "****************** \r\n\n");

    /* Create FreeRTOS task */
    retval = xTaskCreate( blinky_task, SECURE_BLINKY_LED_EXAMPLE_NAME, SECURE_BLINKY_LED_EXAMPLE_STACK_SIZE, NULL, SECURE_BLINKY_LED_EXAMPLE_PRIORITY, NULL );

    if( pdPASS == retval )
    {
        vTaskStartScheduler();
    }

    for(;;)
    {
        /* vTaskStartScheduler never returns */
    }

}

/*******************************************************************************
* Function Name: blinky_task
********************************************************************************
* Summary:
* This is the FreeRTOS task callback function. It does...
*    1. Toggles LED for every 500ms in a tight for loop 
*
* Parameters:
*  void * context passed from main function
*
* Return:
*  void
*
*******************************************************************************/
void blinky_task( void * arg )
{
    (void)arg;

    for(;;)
    {
        /* Toggle the user LED periodically */
        Cy_SysLib_Delay(500) ;

        /* Invert the USER LED state */
        cyhal_gpio_toggle((cyhal_gpio_t) CYBSP_USER_LED1);
    }
}

/* [] END OF FILE */
