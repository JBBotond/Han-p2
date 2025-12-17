#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "fsm_functions/fsm.h"
#include "console_functions/keyboard.h"
#include "console_functions/display.h"
#include "console_functions/devConsole.h"

extern char * eventEnumToText[];
extern char * stateEnumToText[];

state_t state;
event_t event;
state_t previousState;
event_t previousEvent;

int exitCode = 0;             //signal graceful shutdown

// Local function prototypes State related
void S_InitialiseSubsystems_onEntry(void);
void S_InitialiseSubsystems_onExit(void); // not used NULL in state chart
void S_Configure_onEntry(void);
void S_Configure_onExit(void);
//		these might be useful
//	-----------------------------
//void S_WaitForCoins_onEntry(void);
//void S_WaitForCoins_onExit(void); // not used NULL in state chart

// Exception function, for gracefull shutdown
void S_ShutdownSystem(int exitCode);

// Subsystems
//void dispenseCola(void);         ///cola dispensor
//event_t getCoin(void);           ///coin acceptor


//helper functions
void delay_ms(uint32_t d);

// Main
int main(void)
{
   //           State                                     onEntry()                       onExit()

   //                                 From                     Event                To

   // Should unexpected events in a state be flushed or not?
   FSM_FlushEnexpectedEvents(true);

   // Set the finite state machine in the S_START state
   // and add a E_START event into the event buffer
   state = S_START;
   FSM_AddEvent(E_START);    // Machine is switched on

   while(event != E_EXIT_SYSTEM)
   {
      if(!FSM_NoEvents())
      {
         // Get the event and handle it
         previousEvent = event;
         previousState = state;
         event = FSM_GetEvent();
         state = FSM_EventHandler(state, event);
         DCSdebugSystemInfo("Transition: %s --> %s --> %s", stateEnumToText[previousState], eventEnumToText[event], stateEnumToText[state]);   ///Debug info
      }
   }
   S_ShutdownSystem(exitCode);
}

void S_InitialiseSubsystems_onEntry(void)
{

   // Initalize the debug console
   DSPinitialise();                                /// Initialise User interface
   DSPshowDisplay();                               /// And debug console
   DCSinitialise();
   KYBinitialise();

   // Inform the CVM user
   DSPshow(2, "Program started");                  /// Update user interface

   FSM_AddEvent(E_CONTINUE);           /// Initialisation done, go to next state
}

void S_InitialiseSubsystems_onExit(void)
{
   /// nothing to do onExit
}

void S_Configure_onEntry(void)
{
   //add price here??
   FSM_AddEvent(E_CONFIG_READY);      /// Configuration complete Internal generated event
}

void S_Configure_onExit(void)
{
   /// nothing to do onExit
}

void S_ShutdownSystem(int status)
{
   if (status !=0)
   {
      DCSshowSystemError("System shutting down error code %d, state = %", status, stateEnumToText[state]);
   }
   else
   {
      DCSsimulationSystemInfo("System shutting down", status);
   }
   exit(status);
}

/// Subsystems (HAL -- simulations)

/// Helper functions

/// simulate delay in miliseconds
void delay_ms(uint32_t d)
{
   DCSdebugSystemInfo("Delay waiting for %d micro-seconds", d);
   sleep(d/1000);
}
