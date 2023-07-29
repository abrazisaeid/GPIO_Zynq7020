# GPIO_Zynq7020

It is a simplified GPIO interrupt example for Xilinx ZYNQ FPGA.
I want to explain each function in this code what it can do.

first of all, we have 2 subfunctions and 1 main:
* GPIOIntrHandler
* SetupInterruptSystem
* main

#  in the Mian part, we have this code:

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
now let me tell you what was it.
* GPIOConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
* XGpioPs_CfgInitialize(&xGpioPs, GPIOConfigPtr,GPIOConfigPtr->BaseAddr);
these lines are definitions of GPIO Config that we want to use.

in this simplified example we have 2 pins as GPIO: One for Input, One for Output.

* XGpioPs_SetDirectionPin()
This function, use for showing which pis is Ip=nput and which pin is output and for this aim we use it.

it will continue as soon as possible.

