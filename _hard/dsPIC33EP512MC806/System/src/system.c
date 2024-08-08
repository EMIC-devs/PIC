void initSystem(void)
{
    _PLLPOST = 0;
    _PLLPRE = 0;
    _PLLDIV = 63;

    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    //Wait for Clock switch to occur
    while(OSCCONbits.COSC != 0b001);
    //Wait for PLL to lock
    while(OSCCONbits.LOCK != 1);
    //CLKDIV = 0x3040;

	ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
	ANSELG = 0;
}
