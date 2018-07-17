/*********************************************************************************
//������
//���ߣ����ƮԾ     ʱ�䣺       �ص㣺
//CPU�ͺţ�         ϵͳ��Ƶ��
//�汾�ţ�V0.0        
*********************************************************************************/
/*********************************************************************************
�ļ�������
*********************************************************************************/
#include "IAP.h"
/*********************************************************************************
����������
*********************************************************************************/

/*********************************************************************************
��������������
*********************************************************************************/
/*********************************************************************************
�ⲿ����������
*********************************************************************************/
/*********************************************************************************
˽�б���������
*********************************************************************************/ 
//#pragma location=0x0F80
//uint32_t Vector_Table[32];
/*********************************************************************************
���Ա���������
*********************************************************************************/
/*********************************************************************************
�ڲ�����������
*********************************************************************************/
/*********************************************************************************
���ܴ��붨����
*********************************************************************************/
/*********************************************************************************
 Function:      //
 Description:   //����BootLoader�����ж�������
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
//uint32_t Vector[32] = {0};
//uint32_t Vector1[32] = {0};
void STM8_Interrupt_Vector_Table_Init(void)
{
  unsigned char i = 0,Index = 0;
  unsigned char version[11] = {0};
  uint32_t Vector[32] = {0};
  
  Read_Version(version);
  for(i = 0;i < 11;i++)
  {
    if(version[i] != BLD_VERSION[i])
    {
      Save_Version();
      
      FLASH_Unlock(FLASH_MemType_Program);    
      for(Index = 1; Index < 0X20;Index++)
      {
        Vector[Index] = FLASH_ReadWord(0X8000+4*Index);
      }
      FLASH_Lock(FLASH_MemType_Program);
      
      WriteRom (INTERRUPT_VECTOR_ADD,Vector,128);
      break;
    }
  }
//  for(Index = 0; Index < 0X20;Index++)
//  {
//    Vector1[Index] = *((const uint32_t *)(INTERRUPT_VECTOR_ADD+4*Index));
//  }
//  
}
/*********************************************************************************
 Function:      //
 Description:   //��FLASH��ַ����
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
uint32_t FLASH_ReadWord(uint32_t Address)
{
 return(*(PointerAttr uint32_t *) (uint32_t)Address);       
}

/*********************************************************************************
 Function:      //
 Description:   ////���³�ʼ��STM8���ж�������  �������¶��嵽APP���ж�������
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
uint32_t aaa;
void STM8_Interrupt_Vector_Table_Redirection(void)
{
  disableInterrupts();   //�ر��ж�  
  uint8_t Index = 0;	
  
 
  FLASH_Unlock(FLASH_MemType_Program);
  for(Index = 1; Index < 0X20;Index++)
  {
    aaa = FLASH_ReadWord(0X8000+4*Index);
   if(FLASH_ReadWord(0X8000+4*Index)!=(0X82000000+APP_START_ADDR+Index*4))
   {
    FLASH_ProgramWord(0X8000+4*Index,0X82000000+APP_START_ADDR+Index*4);
   }
   aaa = FLASH_ReadWord(0X8000+4*Index);
  }
  FLASH_Lock(FLASH_MemType_Program);
}
/*********************************************************************************
 Function:      //
 Description:   //��������д��Flash
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
uint32_t addr = 0xE000;
ErrorStatus FlashWrite (void *pbuff, unsigned short length)
{
 unsigned short itemp;
 unsigned char *p; 
 unsigned short itemp16;
 
 do
 {FLASH_Unlock(FLASH_MemType_Program); }//����FLASH���
 while (FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET); 
 itemp = 0;
 p = pbuff;
 while (itemp < length)
 {
   FLASH_ProgramByte(addr ,p[itemp]);
   itemp16 = 0xffff;
   while(FLASH_GetFlagStatus(FLASH_FLAG_EOP) == RESET)
   {
    itemp16 --;
    if(itemp16 <= 1)
    {
      FLASH_Lock(FLASH_MemType_Program);
      return ERROR;
    }
   }
   itemp16 = FLASH_ReadByte(addr);
   if(p[itemp] != itemp16)
   {
     FLASH_Lock(FLASH_MemType_Program);
     return ERROR;
   }
   else
   {itemp ++;addr++;}
 }
 FLASH_Lock(FLASH_MemType_Program);
 return SUCCESS;
}
/*********************************************************************************
 Function:      //
 Description:   //��ת��Ӧ�ó�������
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
void JumptoAPP(void)
{
  sim();               // disable interrupts�����������תǰ���жϣ���ת���³��������һ���жϡ�
  asm("LDW X,  SP ");
  asm("LD  A,  $FF");
  asm("LD  XL, A  ");
  asm("LDW SP, X  ");
  asm("JPF $E000");
}
/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:	    	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/
/**************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/

/*********************************************************************************
 Function:      //
 Description:   //
 Input:         //
                //
 Output:        //
 Return:      	//
 Others:        //
*********************************************************************************/