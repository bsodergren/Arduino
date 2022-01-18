long EEPROMReadlong(long address) {
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void EEPROMWritelong(int address, long value) {
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}


void split(int input_number)
{    
  thousands = int(input_number/1000);    
  hundreds = int(input_number/100);
  hundreds = hundreds-(int(hundreds/10)*10);     
  tens = int(input_number/10);  
  tens = tens-(int(tens/10)*10);  
  ones = input_number-(int(input_number/10)*10);
}

void write_number()
{
    for (int z=0; z<=ttime; z++)
    {
        if( thousands > 0)                  {setDigit(0,0,thousands,true);}
        if( hundreds > 0 || thousands > 0 ) {setDigit(0,1,hundreds,true);}
        if( tens > 0 || hundreds > 0  )     {setDigit(0,2,tens,true);}
                                             setDigit(0,3,ones,true);
    
    }
      
}
