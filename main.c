#include <LPC214x.h>

void lcdcmd(unsigned int cmd);
void lcddata(unsigned int data);
void delay(unsigned int itime);

int main()
{
    unsigned char array[] = "Gaurav";
    unsigned int i = 0;

    PINSEL0 = 0x00;
    PINSEL1 = 0x00;
    PINSEL2 = 0x00;
    IODIR0 = 0x20000400; // Set EN as output
    IODIR1 = 0x02FF0000; // Set P1.16 - P1.23 as output
    IOCLR0 = 0x00000400; // Clear EN initially

    lcdcmd(0x38); // 16x2 LCD in 8-bit Mode
    delay(100);
    lcdcmd(0x06); // Increment cursor and shift right
    delay(100);
    lcdcmd(0x0C); // Display ON, Cursor OFF
    delay(100);
    lcdcmd(0x01); // Clear display screen
    delay(100);

    for (i = 0; i < 9; i++)
    {
        lcddata(array[i]);
        delay(100);
    }

    lcdcmd(0xC0);
    delay(100);

    for (i = 9; i < 14; i++)
    {
        lcddata(array[i]);
        delay(100);
    }

    return 0;
}

void delay(unsigned int itime)
{
    int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 200; j++);
}

void lcdcmd(unsigned int cmd)
{
    IOCLR1 = 0x00FF0000; // Clear previous data
    cmd = cmd << 16;     // Shift command to P1.16-P1.23
    IOSET1 = cmd;

    IOCLR1 = 0x02000000; // RS = 0 (Command Mode)
    IOSET0 = 0x20000000; // EN = 1 (Enable HIGH)
    delay(5);
    IOCLR0 = 0x20000000; // EN = 0 (Enable LOW)
}

void lcddata(unsigned int data)
{
    IOCLR1 = 0x00FF0000; // Clear previous data
    data = data << 16;   // Shift data to P1.16-P1.23
    IOSET1 = data;

    IOSET1 = 0x02000000; // RS = 1 (Data Mode)
    IOSET0 = 0x20000000; // EN = 1 (Enable HIGH)
    delay(5);
    IOCLR0 = 0x20000000; // EN = 0 (Enable LOW)
}
