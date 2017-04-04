// filename ******** Sensors.h ************** 
// Lab 8 Spring 2017
// Matt Owens & Rebecca Ho
// 3/29/17

// Initializes ADC8 and ADC9 sampling
// 125k max sampling
// SS2 triggering event: software trigger, busy-wait sampling
// SS2 1st sample source: Ain9 (PE4)
// SS2 2nd sample source: Ain8 (PE5)
// SS2 interrupts: enabled after 2nd sample but not promoted to controller
void ADC_Init12(void);

//------------ADC_In12------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: two 12-bit result of ADC conversions
// Samples ADC1 and ADC2 
// 125k max sampling
// software trigger, busy-wait sampling
// data returned by reference
// data[0] is ADC1 (PE2,light) 0 to 4095
// data[1] is ADC2 (PE1,soil) 0 to 4095
void ADC_In12(uint32_t data[2]);

// ***************** CheckSensors ****************
// Check soil moisture and light sensors
// Inputs:  none
// Outputs: none
void CheckSensors(void);

// ***************** CheckMoisture ****************
// Check if soil moisture has changed. Output song if it has.
// Turn on green LED if soil is now dry.
// Inputs:  none
// Outputs: none
void CheckMoisture(void);

// ***************** CheckLight ****************
// Check if enough light is being received by the plant
// Inputs:  none
// Outputs: none
void CheckLight(void);

void SetCheckFrequency(uint32_t);
