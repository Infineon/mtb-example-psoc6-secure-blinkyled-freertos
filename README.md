# PSoC 64 MCU: Secure Blinky LED FreeRTOS

This code example demonstrates the implementation of a simple FreeRTOS task, which toggles an LED periodically using PSoC® 64 MCU.

## Requirements

- [ModusToolbox™ software](https://www.cypress.com/products/modustoolbox-software-environment) v2.1
- [cysecuretools 2.0.0](https://pypi.org/project/cysecuretools/)
- Other Tools: Python 3.7.0 or later
- Programming Language: C
- Associated Parts: All [PSoC® 64 MCU](http://www.cypress.com/PSoC6) parts

## Supported Kits

- CY8CKIT-064B0S2-4343W PSoC 64 Wi-Fi BT Pioneer Kit.
- CY8CPROTO-064B0S3 PSoC 64 SecureBoot Prototyping Kit.

**Note**: See the [Secure Boot SDK User Guide](https://www.cypress.com/documentation/software-and-drivers/psoc-64-secure-mcu-secure-boot-sdk-user-guide) before starting work with a target enabled with Cypress Secure Boot.

## Hardware Setup

This example is used with PSoC 64 Secure MCU kits. To program and run the example on a PSoC 64 Secure MCU platform, the device must be provisioned with keys and policies, and then programmed with the signed firmware to boot up correctly. 

Follow the instructions in the [Secure Boot SDK User Guide](https://www.cypress.com/documentation/software-and-drivers/psoc-64-secure-mcu-secure-boot-sdk-user-guide) to provision the device. 

**Note**: The PSoC 64 SecureBoot WiFi-BT Pioneer Kit and the CY8CPROTO-064B0S3 PSoC 64 SecureBoot Prototyping Kit ship with KitProg2 installed. ModusToolbox software requires KitProg3. Before using this code example, make sure that the board is upgraded to KitProg3. The tool and instructions are available in the [Firmware Loader](https://github.com/cypresssemiconductorco/Firmware-loader) GitHub repository. An error message stating "unable to find CMSIS-DAP device" or "KitProg firmware is out of date" appears if the board is not upgraded to KitProg3.

## Software Setup

Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en).

This example requires Python 3.7.0 and the 'cysecuretools' package to be installed.

### Install Python

#### In Windows:

1. Download the latest stable Python 3 release [Windows x86-64 Executable Installer](https://www.python.org/downloads/windows/).

   The required version is Python 3.7.

2. Install to the default location. Select the **Add Python 3.7 to PATH** option.

3. If you also have Python 2.7 installed, ensure that *Python 3.7* and *Python37\Scripts* have a higher priority in PATH than *C:\Python27*:

   1. Open **Control Panel** and select **System** > **Advanced System Settings** > **Environment Variables**.
	
   2. Find **PATH** in the list of System Variables, and click **Edit**.
	
   3. Move *C:\Users\%USER%\AppData\Local\Programs\Python\Python37\\* and *C:\Users\%USER%\AppData\Local\Programs\Python\Python37\Scripts\\* to the top.

4. Install pip. Run the following command on the command prompt:

   ```
   > python -m pip install --upgrade pip
   ```

#### In Linux:

Most distributions of Linux usually have Python 2 and Python 3 installed. 

1. Verify that Python points to Python 3. Run the following command: 

   ```
   > python --version
   ```
   
2. If Python is not installed on your machine, install it using the following command:

   ```
   > sudo apt install python3.7
   ```
   
3. Install pip. Run the following command:

   ```
   > sudo apt install python3-pip
   ```
   
4. Make sure that pip is using Python 3.7:

   ```
   > pip --version
   ```
   
#### In macOS:

1. Download and install the latest Python 3 release from https://www.python.org/downloads/mac-osx/.

2. Install pip.

   ```
   > python3 -m pip install --upgrade pip
   ```

### Install cysecuretools 

1. Run the following command:
   
   ```
   > pip install cysecuretools
   ```
	
## Using the Code Example

### In Eclipse IDE for ModusToolbox:

1. Click the **New Application** link in the Quick Panel (or, use **File** > **New** > **ModusToolbox Application**).

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the **Library Manager** to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. 
   
   To access the Library Manager, right-click the application name from the Project Workspace window in the IDE, and select **ModusToolbox** > **Library Manager** (or select it from the **Quick Panel**).

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example.

4. Optionally, update the **Application Name** and **Location** fields with the application name and local path where the application is created.

5. Click **Create** and complete the application creation process.

   For more details, see the Eclipse IDE for ModusToolbox User Guide: *{ModusToolbox install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*.

5. (**In macOS Only**) Add *python3* to ModusToolbox 2.1 config PATH:  
   
   1. Go to **Project** > **Properties** > **C/C++Build** > **Environment**.
   
   2. Add to the actual PATH your path to Python3 executable. 
   For example, *(...:/Library/Frameworks/Python.framework/Versions/3.7/bin*).

### In Command-line Interface (CLI):

1. Download and unzip this repository onto your local machine, or clone the repository.

2. Open a CLI terminal and navigate to the application folder.

   In Linux and macOS, you can use any terminal application. On Windows, navigate to the modus-shell directory (*{ModusToolbox install directory}/tools_\<version>/modus-shell*) and run *Cygwin.bat*.

3. Import the required libraries by executing the `make getlibs` command.

### Policy and Keys

1. Add the policy that was used to provision the device into the project.
	
   1. Ensure that you are in the *%WORKSPACE%/Secure_Blinky_LED_FreeRTOS/* directory.

   2. Execute the following command to finalize project initialization:

      ```
      > cysecuretools -t <kit-name> init
      ```
        
      For example, the following command finalizes project initialization for **CY8CKIT-064B0S2-4343W** kit:

      ```
      > cysecuretools -t cy8ckit-064b0s2-4343w init
      ```
    
   **Note**: After executing of the `init` command, all files that are required for application signing will be copied into *%WORKSPACE%/Secure_Blinky_LED_FreeRTOS/* directory, including the default policy for the chosen `<kit-name>`.
    
2. Add the keys that were used to provision the device into the project.
	
   Ensure that you are in the *%WORKSPACE%/Secure_Blinky_LED_FreeRTOS/* directory and the policy is already added in your project.

   If you do not have the keys, generate default keys using the following command:

   ```
   > cysecuretools -t <kit-name> create-keys       
   ```
  
   For example, following command generates default keys for **CY8CKIT-064B0S2-4343W** kit

   ```
   > cysecuretools -t cy8ckit-064b0s2-4343w create-keys
   ```

  **Note**: If you generate the keys, you must use these keys to provision your device. Otherwise, the example will not work correctly. See the "Generate New Keys" section in the [Secure Boot SDK User Guide](https://www.cypress.com/documentation/software-and-drivers/psoc-64-secure-mcu-secure-boot-sdk-user-guide).

## Operation

1. Connect the board to your PC using the provided USB cable through the KitProg3 USB connector.

2. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

3. Program the board. 

   ### Using ModusToolbox:

   1. Click **Run** > **Run Configurations**.
   
   2. Open **GDB OpenOCD Debugging**. 
   
   3. Select **Secure_Blinky_LED_FreeRTOS Program (KitProg3)**, and then click **Run**.

   ### Using CLI:

   From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. You can specify a target and toolchain manually:
   
   ```
   make program TARGET=<BSP> TOOLCHAIN=<toolchain>
   ```
   
   Example: 
   
   ```
   make program TARGET=CY8CKIT-064B0S2-4343W TOOLCHAIN=GCC_ARM
   ```
   
   **Note**:  Before building the application, ensure that the *libs* folder contains the BSP (.lib) file corresponding to the TARGET. Execute the `make getlibs` command to fetch the BSP contents before building the application.

4. After programming, the application starts automatically. Ensure that the following message is displayed in the UART terminal.

   ```
   ***************** PSoC 64 MCU: Secure Blinky LED FreeRTOS Example *****************
   ```

5. Observe that the kit's LED blinks at 1 Hz. 


## Debugging

You can debug the example code step-by-line.

1. Click **Run** > **Run Configurations**.

2. Open **GDB OpenOCD Debugging**. 

3. Select **Secure_Blinky_LED_FreeRTOS Debug (KitProg3)**, and then click **Run**.

See [PSoC® 64 Secure MCU Secure Boot SDK User Guide](https://www.cypress.com/documentation/software-and-drivers/psoc-64-secure-mcu-secure-boot-sdk-user-guide) for details.

## Design and Implementation

This example is designed to evaluate a simple FreeRTOS-based application on PSoC 64 devices using single-stage bootloading. A FreeRTOS task is created in the main function of the example. This task blinks an LED periodically. The BSP makefile's post-build command signs the application hex image built with ModusToolbox, so that the signed image can be programmed and run on PSoC 64 kits.

This example's source code is in the *main.c* file. The application's entry point is the `main()` function. It creates a FreeRTOS thread with the callback name as `blinky_task`. The `main()` function also initializes a FreeRTOS scheduler by invoking `vTaskStartScheduler()`; once the FreeRTOS scheduler is initialized successfully, the `blinky_task` callback is scheduled. The `blinky_task` callback toggles the user LED every 500 ms.

## Related Resources

| Application Notes                                            |                                                              |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| [AN228571](https://www.cypress.com/AN228571) – Getting Started with PSoC 6 MCU on ModusToolbox | Describes PSoC 6 MCU devices and how to build your first application with ModusToolbox |
| [AN221774](https://www.cypress.com/AN221774) – Getting Started with PSoC 6 MCU on PSoC Creator | Describes PSoC 6 MCU devices and how to build your first application with PSoC Creator |
| [AN210781](https://www.cypress.com/AN210781) – Getting Started with PSoC 6 MCU with Bluetooth Low Energy (BLE) Connectivity on PSoC Creator | Describes PSoC 6 MCU with BLE Connectivity devices and how to build your first application with PSoC Creator |
| [AN215656](https://www.cypress.com/AN215656) – PSoC 6 MCU: Dual-CPU System Design | Describes the dual-CPU architecture in PSoC 6 MCU, and shows how to build a simple dual-CPU design |
| **Code Examples**                                            |                                                              |
| [Using ModusToolbox IDE](https://github.com/cypresssemiconductorco/Code-Examples-for-ModusToolbox-Software) | [Using PSoC Creator](https://www.cypress.com/documentation/code-examples/psoc-6-mcu-code-examples) |
| **Device Documentation**                                     |                                                              |
| [PSoC 6 MCU Datasheets](https://www.cypress.com/search/all?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A575&f[2]=field_related_products%3A114026) | [PSoC 6 Technical Reference Manuals](https://www.cypress.com/search/all/PSoC%206%20Technical%20Reference%20Manual?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A583) |
| **Development Kits**                                         | Buy at Cypress.com                                     |
| [CY8CKIT-062-BLE](https://www.cypress.com/CY8CKIT-062-BLE) PSoC 6 BLE Pioneer Kit | [CY8CKIT-062-WiFi-BT](https://www.cypress.com/CY8CKIT-062-WiFi-BT) PSoC 6 WiFi-BT Pioneer Kit |
| [CY8CPROTO-063-BLE](https://www.cypress.com/CY8CPROTO-063-BLE) PSoC 6 BLE Prototyping Kit | [CY8CPROTO-062-4343W](https://www.cypress.com/cy8cproto-062-4343w) PSoC 6 Wi-Fi BT Prototyping Kit |
| **Middleware**                                               | Middleware libraries are distributed on GitHub               |
| PSoC 6 peripheral driver library and docs                    | [psoc6pdl](https://github.com/cypresssemiconductorco/psoc6pdl) on GitHub |
| CapSense library and docs                                    | [capsense](https://github.com/cypresssemiconductorco/capsense) on GitHub |
| Links to all PSoC 6 Middleware                               | [psoc6-middleware](https://github.com/cypresssemiconductorco/psoc6-middleware) on GitHub |
| **Tools**                                                    |                                                              |
| [ModusToolbox IDE](https://www.cypress.com/modustoolbox)     | The Cypress IDE for PSoC 6 and IoT designers                 |
| [PSoC Creator](https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide) | The Cypress IDE for PSoC and FM0+ development                |

## Other Resources

Cypress provides a wealth of data at www.cypress.com to help you to select the right device, and quickly and effectively integrate the device into your design.

For PSoC 6 MCU devices, see [How to Design with PSoC 6 MCU - KBA223067](https://community.cypress.com/docs/DOC-14644) in the Cypress community.


## Document History

Document Title: *CE228684 - PSoC 64 MCU: Secure Blinky LED with FreeRTOS*

| Revision     | Description of Change |
| --------     | --------------------- |
| v1.0.0       | New code example      |

------


All other trademarks or registered trademarks referenced herein are the property of their respective
owners.

![Banner](images/ifx-cy-banner.png)

-------------------------------------------------------------------------------

© Cypress Semiconductor Corporation, 2020. This document is the property of Cypress Semiconductor Corporation and its subsidiaries ("Cypress"). This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide. Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights. If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products. Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. No computing device can be absolutely secure. Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach"). Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach. In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes. It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product. "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage. Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices. "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness. Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, its directors, officers, employees, agents, affiliates, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
Cypress, the Cypress logo, Spansion, the Spansion logo, and combinations thereof, WICED, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress in the United States and other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.