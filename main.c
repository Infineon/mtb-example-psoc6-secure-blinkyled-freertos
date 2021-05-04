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
* Copyright 2020-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
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
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
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

/* Defines for Blinky LED task */
#define BLINKY_LED_TASK_NAME         ("Blinky Task")
#define BLINKY_LED_TASK_STACK_SIZE   (1024)
#define BLINKY_LED_TASK_PRIORITY     (5)
#define BLINKY_LED_TASK_DELAY_TICKS  (500)

/* Defines for Counter task */
#define COUNTER_TASK_NAME                ("Counter Task")
#define COUNTER_TASK_STACK_SIZE          (1024)
#define COUNTER_TASK_PRIORITY            (5)
#define COUNTER_LED_TASK_DELAY_TICKS     (1000)

UBaseType_t __attribute__((used)) uxTopUsedPriority;

#define uxTopReadyPriority uxTopUsedPriority

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void blinky_task( void * arg );
void counter_task( void * arg );

/*******************************************************************************
* Global Variables
********************************************************************************/


/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CM4 CPU. It does...
*    1. Creates FreeRTOS tasks
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

    /* Enable global interrupts */
         __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    printf("\r\n***** PSoC 64 MCU: Secure Blinky LED FreeRTOS Example ***** \r\n\n");
    printf("Build date %s and time %s\r\n\n", __DATE__, __TIME__);

    /* Create FreeRTOS task */
    retval = xTaskCreate( blinky_task, BLINKY_LED_TASK_NAME,BLINKY_LED_TASK_STACK_SIZE, NULL, BLINKY_LED_TASK_PRIORITY, NULL );

    if( pdPASS != retval )
    {
         printf("%s did not start!\r\n", BLINKY_LED_TASK_NAME);
    }

    /* Create FreeRTOS task */
    retval = xTaskCreate( counter_task, COUNTER_TASK_NAME, COUNTER_TASK_STACK_SIZE, NULL, COUNTER_TASK_PRIORITY, NULL );

    if( pdPASS == retval )
    {
        vTaskStartScheduler();
    }
    else
    {
        printf("%s did not start!\r\n", COUNTER_TASK_NAME);
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

    printf("%s started!\r\n", BLINKY_LED_TASK_NAME);

    /* Initialize the User LED */
    cyhal_gpio_init((cyhal_gpio_t) CYBSP_USER_LED1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    for(;;)
    {
        /* Toggle the user LED periodically */
        vTaskDelay(BLINKY_LED_TASK_DELAY_TICKS ) ;

        /* Invert the USER LED state */
        cyhal_gpio_toggle((cyhal_gpio_t) CYBSP_USER_LED1);
    }
}

/*******************************************************************************
* Function Name: counter_task
********************************************************************************
* Summary:
* This is the FreeRTOS task callback function. It does...
*    1. Increments a counter and prints to terminal
*
* Parameters:
*  void * context passed from main function
*
* Return:
*  void
*
*******************************************************************************/
void counter_task( void * arg )
{
    (void)arg;
    uint16 count = 0;

    printf("%s started!\r\n", COUNTER_TASK_NAME);

    for(;;)
    {
        /* Delay the print counter */
        vTaskDelay(COUNTER_LED_TASK_DELAY_TICKS ) ;

        /* Print out the counter number */
        printf("%d\r\n", count++);
    }
}


/* [] END OF FILE */
