#include "Instruments/ExampleInstrument.h"
#include "InterruptTimer.h"
#include "Constants.h"
#include "Arduino.h"

void ExampleInstrument::SetUp()
{
    //Settup pins
    for(uint8_t i=0; i < sizeof(pins); i++){
        pinMode(i, OUTPUT);
    }

    // With all pins setup, let's do a first run reset
    ResetAll();
    delay(500); // Wait a half second for safety

    // Setup timer to handle interrupts for floppy driving
    InterruptTimer::initialize(TIMER_RESOLUTION, Tick);
}

void ExampleInstrument::Reset(uint8_t instrument)
{
    //Not Yet Implemented
}

void ExampleInstrument::ResetAll()
{
    //Not Yet Implemented
}

void ExampleInstrument::PlayNote(uint8_t instrument, uint8_t note, uint8_t velocity)
{
    for(int8_t i = 0; i < 16; i++){
        if(_activeNotes[instrument][i] & MSB_BITMASK !=1){
            _activeNotes[instrument][i] = (0x80 & note);
            return;
        }
    }
}

void ExampleInstrument::StopNote(uint8_t instrument, uint8_t note, uint8_t velocity)
{
    for(int8_t i = 0; i < 16; i++){
        if((_activeNotes[instrument][i] & MSB_BITMASK) == 1)
        {
            if((_activeNotes[instrument][i] & (~MSB_BITMASK)) == note)
            {
                _activeNotes[instrument][i] = 0;
                return;
            }
        }
        else{
            return;
        }
    }
}

void ExampleInstrument::SetKeyPressure(uint8_t instrument, uint8_t note, uint8_t velocity)
{
    //Not Yet Implemented
}

/*
Called by the timer interrupt at the specified resolution.  Because this is called extremely often,
it's crucial that any computations here be kept to a minimum!

Additionally, the ICACHE_RAM_ATTR helps avoid crashes with WiFi libraries, but may increase speed generally anyway
 */
#pragma GCC push_options
#pragma GCC optimize("Ofast") // Required to unroll this loop, but useful to try to keep this speedy
#ifdef ARDUINO_ARCH_ESP32
void ICACHE_RAM_ATTR ExampleInstrument::Tick()
#else
void ExampleInstrument::tick()
#endif
{
    //Not Yet Implemented
}




uint8_t ExampleInstrument::getNumActiveNotes(uint8_t instrument)
{
    return _numActiveNotes[instrument];
}

bool ExampleInstrument::isNoteActive(uint8_t instrument, uint8_t note)
{
    for(uint8_t i=0; i<16; i++){

        if ((_activeNotes[instrument][i] & (~ MSB_BITMASK)) == note){
            return true;
        }
        else if((_activeNotes[instrument][i] & MSB_BITMASK) == 0){
            return false;
        }
    }
    return false;
}