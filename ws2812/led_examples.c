//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include "..\delay\delay.h"
#include "led_examples.h"
#include "ws2812.h"

// �������� ����� ������
tRGB const RainbowColors[] =
{
  {0,   255, 0},        // �������
  {165, 255, 0},        // ���������
  {255, 255, 0},        // Ƹ����
  {255, 0,   0},        // ������
  {255, 0,   255},      // �������
  {0,   0,   255},      // �����
  {0,   255, 255},       // ����������
};

// �������� ������ ����������
uint16_t AlgStep, AlgStep2, AlgStep3;

     
//==============================================================================
// ��������� � �������� ����� �������� �������� *source � �������� *desc
//==============================================================================
void StepChange(uint8_t *desc, uint8_t *source, uint8_t Step)
{
  if (*desc < *source)
  {
    if ((0xFF - *desc) < Step)
      *desc = 0xFF;
    else
      *desc += Step;
  }
    
  if (*desc > *source)
  {
    if (*desc > Step)
      *desc -= Step;
    else
      *desc = 0;
  }
}       
//==============================================================================


//==============================================================================
// ��������� � �������� ����� ����������� ���� pLEDsource � pLEDdesc
//==============================================================================
void StepChangeColor(tRGB *pLEDdesc, tRGB *pLEDsource, uint8_t Step)
{
  StepChange(&(pLEDdesc->R), &(pLEDsource->R), Step);
  StepChange(&(pLEDdesc->G), &(pLEDsource->G), Step);
  StepChange(&(pLEDdesc->B), &(pLEDsource->B), Step);
}
//==============================================================================


//==============================================================================
// ������� �������� ����� ������. ���������� ���-�� ������ � ����� �������.
// �� ��������� pPeriod ���������� ������ � �� ����� �������
//==============================================================================
uint16_t led_effect_start(uint8_t EffectNum, uint16_t *pPeriod)
{
  AlgStep = AlgStep2 = AlgStep3 = 0;
  
  switch (EffectNum)
  {
  // ����� ������� ����� � ������� fade-out
  case 0:
    *pPeriod = 0;
    return WS2812_LEDNUM*2; 
  // ������� ������� ����� � ������� fade-out
  case 1:
    *pPeriod = 0;
    return WS2812_LEDNUM*2; 
  // ������ ������� ����� � ������� fade-out
  case 2:
    *pPeriod = 0;
    return WS2812_LEDNUM*2; 
  // ����� ������� ����� � ������� fade-out
  case 3:
    *pPeriod = 0;
    return WS2812_LEDNUM*2; 
  // ������ ������� ����� � ������� fade-out
  case 4:
    *pPeriod = 0;
    return WS2812_LEDNUM*2; 
  // ������� ������� ����� � ������� fade-out
  case 5:
    *pPeriod = 0;
    return WS2812_LEDNUM*2; 
  // ���������� ������� ����� � ������� fade-out
  case 6:
    *pPeriod = 0;
    return WS2812_LEDNUM*2; 
  // ������ ������
  case 7:
    *pPeriod = 10;
    return 500;
  // ������ Sequental Lights
  case 8:
    ws2812_all_off();
    *pPeriod = SequentalLights_Period;
    return SequentalLights_LedNum * 2 * SequentalLights_CycleNum;
  case 9:
      *pPeriod = 0;
      return WS2812_LEDNUM*2;
  default:
    *pPeriod = 20;
    return 64;
  }
}
//==============================================================================


//==============================================================================
// ���������, ����������� ������ � ������� EffectNum. ������ ���������� � �������� ��������
//==============================================================================
void led_effect_tick(uint8_t EffectNum)
{
  tRGB *pLED = (tRGB*) ws2812_buff;

  switch(EffectNum)
  {
  // ����� ������� ����� � ������� fade-out
  case 0:
    ws2812_set_color(AlgStep / 2, 255, 255, 255);
    ws2812_fade_out_all(0);
    
    if (++AlgStep >= (WS2812_LEDNUM*2))
      AlgStep = 0;
    break;
  // ������� ������� ����� � ������� fade-out
  case 1:
    ws2812_set_color(AlgStep / 2, 255, 0, 0);
    ws2812_fade_out_all(4);
    

    if (++AlgStep >= (WS2812_LEDNUM*2))
      AlgStep = 0;
    break;
  // ������ ������� ����� � ������� fade-out
  case 2:
    ws2812_set_color(AlgStep / 2, 0, 255, 0);
    ws2812_fade_out_all(4);
    
    if (++AlgStep >= (WS2812_LEDNUM*2))
      AlgStep = 0;
    break;
  // ����� ������� ����� � ������� fade-out
  case 3:
    ws2812_set_color(AlgStep / 2, 0, 0, 255);
    ws2812_fade_out_all(4);
    
    if (++AlgStep >= (WS2812_LEDNUM*2))
      AlgStep = 0;
    break;
  // ������ ������� ����� � ������� fade-out
  case 4:
    ws2812_set_color(AlgStep / 2, 255, 255, 0);
    ws2812_fade_out_all(4);
    
    if (++AlgStep >= (WS2812_LEDNUM*2))
      AlgStep = 0;
    break;
  // ������� ������� ����� � ������� fade-out
  case 5:
    ws2812_set_color(AlgStep / 2, 0, 255, 255);
    ws2812_fade_out_all(4);
    
    if (++AlgStep >= (WS2812_LEDNUM*2))
      AlgStep = 0;
    break;
  // ���������� ������� ����� � ������� fade-out
  case 6:
    ws2812_set_color(AlgStep / 2, 255, 0, 255);
    ws2812_fade_out_all(4);
    
    if (++AlgStep >= (WS2812_LEDNUM*2))
      AlgStep = 0;
    break;
  // ������ ������
  case 7:
    // ����� ������� �������� ������
    for (uint16_t i = WS2812_LEDNUM; i > 1; i--) 
    {
      pLED[i-1].R = pLED[i-2].R;
      pLED[i-1].G = pLED[i-2].G;
      pLED[i-1].B = pLED[i-2].B;
    }
    
    // ���� ������ ������ ����   
    if (++AlgStep2 > Rainbow_ColorLength)
    {
      AlgStep2 = 0;

      //loop colouers
      if (++AlgStep3 >= 7)
        AlgStep3 = 0;
    }
        
    // ������� ����� ����� 0-�� ������� � ����� �� ����� Rainbow_FadeStep
    StepChangeColor(&(pLED[0]), (tRGB *) &(RainbowColors[AlgStep3]), Rainbow_FadeStep);
    
    if (++AlgStep >= 700)
      AlgStep = 0;
    break;
  // ������ Sequental Lights
  case 8:
    if ((AlgStep % (SequentalLights_LedNum*2)) < SequentalLights_LedNum)
    {
      ws2812_set_color((AlgStep % (SequentalLights_LedNum*2)), 255, 112, 0);
      ws2812_fade_out_all(4);
    }
    else
      ws2812_all_off();
    
    if (++AlgStep >= SequentalLights_LedNum * 2 * SequentalLights_CycleNum)
      AlgStep = 0;
    break;
  case 9:
	  ws2812_fade_out_all(0);
  default:
    ws2812_fade_out_all(4);
    break;
  }
}
//==============================================================================
