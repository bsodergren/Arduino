



int adc_key_val[6] ={ 115, 740, 835,  925, 955, 1024 };          // Original, works after actually reading the analog0
                                                                                  // You might want to change these values to fit your resistor array
int NUM_KEYS = 6;
int adc_key_in;
int key=-1; 

int get_key(unsigned int input)
{
    int k;
    for (k = 0; k < NUM_KEYS; k++)    // Start counting
    {
      //if (input == adc_key_val[k])        // Works, but doesn't allow for deviations
      if (input < adc_key_val[k])            // should be more reliable as it looks for a range instead of a fixed value.
 {
  
            return k;                                  // Breaks the for loop
        }
   }
   
    if (k >= NUM_KEYS)k = -1;            // No valid key pressed
    return k;                                          // So break the loop and look for another keypress
}
