#include <Arduino.h>
Adafruit_MCP23X17 mcp[MAXMCP];

#ifdef __DEBUG__
#define __DEBUG__
bool DEBUG = true;
#ifndef

#ifdef __MAXMCP__
#define __MAXMCP__
#define MAXMCP 8
#ifndef


volatile bool tw1 = false;
volatile bool tw2 = false;
volatile bool tw3 = false;
volatile bool tw4 = false;
volatile bool tw5 = false;
volatile bool tw6 = false;
volatile bool tw7 = false;
volatile bool tw8 = false;
volatile bool tw9 = false;
volatile bool tw10 = false;
volatile bool tw11 = false;
volatile bool tw12 = false;
volatile bool tw13 = false;

volatile bool ts1 = false;
volatile bool ts2 = false;
volatile bool ts3 = false;
volatile bool ts4 = false;
volatile bool ts5 = false;
volatile bool ts6 = false;
volatile bool ts7 = false;
volatile bool ts8 = false;
volatile bool ts9 = false;
volatile bool ts10 = false;
volatile bool ts11 = false;
volatile bool awakenByInterrupt = false;

void intCallBack()
{
    awakenByInterrupt = true;
}
void cleanInterrupts()
{
    delay(50);
    mcp[4].readGPIOAB();
    mcp[5].readGPIOAB();
    mcp[6].readGPIOAB();

    awakenByInterrupt = false;
}

void printButtonPressed(int pin, int mcpadr)
{
    if (DEBUG)
    {
        Serial.print("Button: ");
        Serial.print(pin);
        Serial.print(" pressed ");
        Serial.print(" von MCP ");
        Serial.println(mcpadr, HEX);
    }
}

void handleInterrupt()
{

    int pin1 = TAST_MCP0.getLastInterruptPin();
    int pin1adr1 = TAST_MCP0.getDevice_address();

    int pin2 = TAST_MCP1.getLastInterruptPin();
    int pin1adr2 = TAST_MCP1.getDevice_address();

    int pin3 = TAST_MCP2.getLastInterruptPin();
    int pin1adr3 = TAST_MCP2.getDevice_address();

    int pin4 = LED_TAST_MCP0.getLastInterruptPin();
    int pin1adr4 = LED_TAST_MCP0.getDevice_address();

    switch (pin1)
    {
    case 0:
        // Setze Dinege für Taste 0 gedrückt.
        // Ist die Weichen Taste TW1
        //                               LED20                                              LED24
        //        TW1           TW2      /                                                   \ 
//--LED1---\----LED2----/-LED3--/----LED17-----------------------------LED25---------------LED26----/-----LED27----------
        //          \          /       TW5  S3RS3G                                                         /
        //           LED4     LED5                                                                        LED28
        //            \      /     TW3                                                                   /
        //--LED6-------\LED7/---LED8\--------LED16--------------------------------LED29 ---------/------/--------------LED30------
        //        S1GS1R             \       
    if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
            tw1 = true; // Taste gedrückt-> für weitere Auswertungen benötigt
        };
        break;
    case 1:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;

    case 2:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 3:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 4:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 5:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 6:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 7:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 8:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 9:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 10:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 11:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 12:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 13:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 14:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;
    case 15:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin1, pin1adr1);
        };
        break;

    default:
        // Setze Dinege für Taste x gedrückt.
        break;
    }

    switch (pin2)
    {
    case 0:
        // Setze Dinege für Taste 0 gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 1:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;

    case 2:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 3:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 4:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 5:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 6:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 7:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 8:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 9:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
        break;
    case 10:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 11:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 12:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 13:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 14:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;
    case 15:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin2, pin1adr2);
        };
        break;

    default:
        // Setze Dinege für Taste x gedrückt.
        break;
    }
    switch (pin3)
    {
    case 0:
        // Setze Dinege für Taste 0 gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 1:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;

    case 2:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 3:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 4:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 5:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 6:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 7:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 8:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 9:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 10:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 11:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 12:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 13:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 14:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;
    case 15:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin3, pin1adr3);
        };
        break;

    default:
        // Setze Dinege für Taste x gedrückt.
        break;
    }
    switch (pin4)
    {
    case 0:
        // Setze Dinege für Taste 0 gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
        break;
    case 1:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;

    case 2:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 3:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 4:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 5:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 6:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 7:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 8:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 9:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 10:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 11:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 12:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 13:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 14:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;
    case 15:
        // Setze Dinege für Taste x gedrückt.
        if (DEBUG)
        {
            printButtonPressed(pin4, pin1adr4);
        };
        break;

    default:
        // Setze Dinege für Taste x gedrückt.
        break;
    }

    //uint8_t val = TAST_MCP0.getLastInterruptPinValue();

    if (ledState)
    {
        digitalWrite(ledPin, LOW);
    }
    else
    {
        digitalWrite(ledPin, HIGH);
    }

    ledState = !ledState;

    //while ( !TAST_MCP0.digitalRead(pin));
    // and clean queued INT signal
    cleanInterrupts();
}
