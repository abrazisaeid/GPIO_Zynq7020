# GPIO_Zynq7020

It is a simplified GPIO interrupt example for Xilinx ZYNQ FPGA.
I want to explain each function in this code what it can do.

first of all, we have 2 subfunctions and 1 main:
* GPIOIntrHandler
* SetupInterruptSystem
* main

## In the Mian part, we have this code:
```c
int main()
{

	XGpioPs_Config *GPIOConfigPtr;
	
	init_platform();
	
	GPIOConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	
	XGpioPs_CfgInitialize(&xGpioPs, GPIOConfigPtr,GPIOConfigPtr->BaseAddr);
	
	XGpioPs_SetDirectionPin(&xGpioPs, pbsw, 0);
	
	SetupInterruptSystem(&xscugic, &xGpioPs, XPS_GPIO_INT_ID);
	
	XGpioPs_SetDirectionPin(&xGpioPs, ledpin, 1);
	
	XGpioPs_SetOutputEnablePin(&xGpioPs, ledpin, 1);
	
	while(1){
	}

}
```
now let me tell you what was it.
```bash
GPIOConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
```
``` bash
XGpioPs_CfgInitialize(&xGpioPs, GPIOConfigPtr,GPIOConfigPtr->BaseAddr);
```
  
these lines are definitions of GPIO Config that we want to use.

in this simplified example we have 2 pins as GPIO: One for Input, One for Output.
```bash
XGpioPs_SetDirectionPin()
```
This function, use for showing which pis is Ip=nput and which pin is output and for this aim we use it.
```bash
SetupInterruptSystem()
```
  this function is for activation of interrupt of the system and it contains several functions for init interrupt of GPIO. this function contains:
```c
static void SetupInterruptSystem(XScuGic *XScuGicptr, XGpioPs *xgpiops, u16 GpioIntrId)
{  

	XScuGic_Config *IntcConfig;
	
	Xil_ExceptionInit();
	
	IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	
	XScuGic_CfgInitialize(XScuGicptr, IntcConfig,IntcConfig->CpuBaseAddress);
	
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,XScuGicptr);
	
	XScuGic_Connect(XScuGicptr, GpioIntrId,(Xil_ExceptionHandler)XGpioPs_IntrHandler,(void *)xgpiops);
	
	
	XGpioPs_SetIntrTypePin(xgpiops, pbsw, XGPIOPS_IRQ_TYPE_EDGE_RISING);
	
	XGpioPs_SetCallbackHandler(&xgpiops, (void *)xgpiops, GPIOIntrHandler);
	
	XGpioPs_IntrEnablePin(xgpiops, pbsw);
	
	XScuGic_Enable(XScuGicptr, GpioIntrId);
	
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);

}
```
in my code, I want to use a pin as Input that when changing the state of this pin calls a function with the name of XGpioPs_IntrHandler.
```bash
XGpioPs_SetOutputEnablePin
```
  This function is used for setting the Output Enables of all the pins in the specified bank.
```bash
XGpioPs_IntrHandler
```
This function is an interrupt of GPIO that is used to toggle the state of our led pin.

Please don’t hesitate to contact me for any further assistance.

Saeid Safari Abrazi

Abrazi.saeid@gmail.com
