#ifndef FOC_PATCH_H
#define FOC_PATCH_H

#ifndef LL_ADC_INJ_IsTriggerSourceSWStart
  #define LL_ADC_INJ_IsTriggerSourceSWStart(x) 1
#endif

#ifndef Offset
  #define Offset SamplingTime
#endif

#endif