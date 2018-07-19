#include "usbd_conf.h"
#include "usbd_core.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_pcd.h"

PCD_HandleTypeDef pcd;

void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle) {
  if (pcdHandle->Instance == USB) {
      __HAL_RCC_USB_CLK_ENABLE();

      /* Peripheral interrupt init */
      HAL_NVIC_SetPriority(USB_IRQn, 0, 0);
      HAL_NVIC_EnableIRQ(USB_IRQn);
  }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef* pcdHandle) {
  if(pcdHandle->Instance == USB) {
      __HAL_RCC_USB_CLK_DISABLE();

      /* Peripheral interrupt Deinit*/
      HAL_NVIC_DisableIRQ(USB_IRQn);
  }
}

/**
  * @brief  Setup Stage callback
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd) {
    USBD_LL_SetupStage((USBD_HandleTypeDef*)hpcd->pData, (uint8_t *)hpcd->Setup);
}

/**
  * @brief  Data Out Stage callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
    USBD_LL_DataOutStage((USBD_HandleTypeDef*)hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

/**
  * @brief  Data In Stage callback..
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
    USBD_LL_DataInStage((USBD_HandleTypeDef*)hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

/**
  * @brief  SOF callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd) {
    USBD_LL_SOF((USBD_HandleTypeDef*)hpcd->pData);
}

/**
  * @brief  Reset callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd) { 
  USBD_SpeedTypeDef speed = USBD_SPEED_FULL;

  switch (hpcd->Init.speed) {
      case PCD_SPEED_FULL:
          speed = USBD_SPEED_FULL;    
          break;
	
      default:
          speed = USBD_SPEED_FULL;    
          break;    
  }
  
  USBD_LL_SetSpeed((USBD_HandleTypeDef*)hpcd->pData, speed);  
  
  /*Reset Device*/
  USBD_LL_Reset((USBD_HandleTypeDef*)hpcd->pData);
}

/**
  * @brief  Suspend callback.
  * When Low power mode is enabled the debug cannot be used (IAR, Keil doesn't support it)
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd) {
  /* Inform USB library that core enters in suspend Mode */
  USBD_LL_Suspend((USBD_HandleTypeDef*)hpcd->pData);

  /*Enter in STOP mode */
  if (hpcd->Init.low_power_enable) {
    /* Set SLEEPDEEP bit and SleepOnExit of Cortex System Control Register */
      SCB->SCR |= (uint32_t)((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
  }
}

/**
  * @brief  Resume callback.
  * When Low power mode is enabled the debug cannot be used (IAR, Keil doesn't support it)
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd) {
  /* USER CODE BEGIN 3 */
  if (hpcd->Init.low_power_enable) {
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
      SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));   
  }

  USBD_LL_Resume((USBD_HandleTypeDef*)hpcd->pData);
}

/**
  * @brief  ISOOUTIncomplete callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
    USBD_LL_IsoOUTIncomplete((USBD_HandleTypeDef*)hpcd->pData, epnum);
}

/**
  * @brief  ISOINIncomplete callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum) {
    USBD_LL_IsoINIncomplete((USBD_HandleTypeDef*)hpcd->pData, epnum);
}

/**
  * @brief  ConnectCallback callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd) {
    USBD_LL_DevConnected((USBD_HandleTypeDef*)hpcd->pData);
}

/**
  * @brief  Disconnect callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd) {
    USBD_LL_DevDisconnected((USBD_HandleTypeDef*)hpcd->pData);
}

/**
  * @brief  Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev) {
    // Link PCD to USB stack
    pcd.pData = pdev;
    pdev->pData = &pcd;

    pcd.Instance = USB;
    pcd.Init.dev_endpoints = 8;
    pcd.Init.speed = PCD_SPEED_FULL;
    pcd.Init.ep0_mps = DEP0CTL_MPS_64;
    pcd.Init.phy_itface = PCD_PHY_EMBEDDED;
    pcd.Init.low_power_enable = DISABLE;
    pcd.Init.lpm_enable = DISABLE;
    pcd.Init.battery_charging_enable = DISABLE;
    
    HAL_PCD_Init(&pcd);

    HAL_PCDEx_PMAConfig(pdev->pData , 0x00 , PCD_SNG_BUF, 0x18);
    HAL_PCDEx_PMAConfig(pdev->pData , 0x80 , PCD_SNG_BUF, 0x58);
    HAL_PCDEx_PMAConfig(pdev->pData , 0x81 , PCD_SNG_BUF, 0x100);

    return USBD_OK;
}

/**
  * @brief  De-Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev) {
    HAL_PCD_DeInit((PCD_HandleTypeDef *)pdev->pData);
    return USBD_OK;
}

/**
  * @brief  Starts the Low Level portion of the Device driver. 
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev) {
    HAL_PCD_Start((PCD_HandleTypeDef *)pdev->pData);
    return USBD_OK;
}

/**
  * @brief  Stops the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev) {
    HAL_PCD_Stop((PCD_HandleTypeDef *)pdev->pData);
    return USBD_OK;
}

/**
  * @brief  Opens an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  ep_type: Endpoint Type
  * @param  ep_mps: Endpoint Max Packet Size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev,
                                  uint8_t ep_addr,
                                  uint8_t ep_type,
                                  uint16_t ep_mps) {
        HAL_PCD_EP_Open((PCD_HandleTypeDef *)pdev->pData,
                        ep_addr,
                        ep_mps,
                        ep_type);
        return USBD_OK;
}

/**
  * @brief  Closes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
    HAL_PCD_EP_Close((PCD_HandleTypeDef *)pdev->pData, ep_addr);
    return USBD_OK;
}

/**
  * @brief  Flushes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
    HAL_PCD_EP_Flush((PCD_HandleTypeDef *)pdev->pData, ep_addr);
    return USBD_OK;
}

/**
  * @brief  Sets a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
    HAL_PCD_EP_SetStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
    return USBD_OK;
}

/**
  * @brief  Clears a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
    HAL_PCD_EP_ClrStall((PCD_HandleTypeDef *)pdev->pData, ep_addr);
    return USBD_OK; 
}

/**
  * @brief  Returns Stall condition.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Stall (1: Yes, 0: No)
  */
uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
    PCD_HandleTypeDef* hpcd = (PCD_HandleTypeDef *)pdev->pData;

    if ((ep_addr & 0x80) == 0x80) {
        return hpcd->IN_ep[ep_addr & 0x7F].is_stall;
    } else {
        return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
    }
}

/**
  * @brief  Assigns a USB address to the device.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr) {
    HAL_PCD_SetAddress((PCD_HandleTypeDef *)pdev->pData, dev_addr);
    return USBD_OK; 
}

/**
  * @brief  Transmits data over an endpoint.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be sent
  * @param  size: Data size    
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev, 
                                    uint8_t ep_addr,
                                    uint8_t *pbuf,
                                    uint16_t size) {
    HAL_PCD_EP_Transmit((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
    return USBD_OK;
}

/**
  * @brief  Prepares an endpoint for reception.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be received
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev, 
                                          uint8_t ep_addr,
                                          uint8_t *pbuf,
                                          uint16_t size) {
    HAL_PCD_EP_Receive((PCD_HandleTypeDef *)pdev->pData, ep_addr, pbuf, size);
    return USBD_OK;
}

/**
  * @brief  Returns the last transferred packet size.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Recived Data Size
  */
uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr) {
    return HAL_PCD_EP_GetRxCount((PCD_HandleTypeDef *)pdev->pData, ep_addr);
}

/**
  * @brief  Delays routine for the USB Device Library.
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBD_LL_Delay(uint32_t Delay) {
    HAL_Delay(Delay);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  * @brief  static single allocation.
  * @param  size: size of allocated memory
  * @retval None
  */
void *USBD_static_malloc(uint32_t size)
{
  static uint32_t mem[MAX_STATIC_ALLOC_SIZE];
  return mem;
}

/**
  * @brief  Dummy memory free
  * @param  *p pointer to allocated  memory address
  * @retval None
  */
void USBD_static_free(void *p)
{

}
