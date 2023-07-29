#include <stdio.h>
#include "platform.h"
#include "xgpiops.h"
#include "xil_types.h"
#include "Xscugic.h"
#include "Xil_exception.h"
#include "xscutimer.h"

#define ledpin 0
#define pbsw 50

static XScuGic xscugic;
static XGpioPs xGpioPs;
static int toggle = 1;

static void GPIOIntrHandler(void *CallBackRef, int Bank, u32 Status)
{
	XGpioPs_IntrClearPin(&xGpioPs, pbsw);
	if (toggle == 0 )
		toggle = 1;
	else
		toggle = 0;
	XGpioPs_WritePin(&xGpioPs, ledpin, toggle);
}

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

     return 0;
}



