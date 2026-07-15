#ifndef FOC_PATCH_H
#define FOC_PATCH_H

/* Mock definitions to allow Simple FOC to compile on STM32F0 hardware */

#ifndef LL_ADC_INJ_IsTriggerSourceSWStart
  #define LL_ADC_INJ_IsTriggerSourceSWStart(x) 1
#endif

#ifndef Offset
  #define Offset SamplingTime
#endif

#endif