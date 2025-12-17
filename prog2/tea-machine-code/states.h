#ifndef STATES_H
#define STATES_H


typedef enum {
   S_NO,                         ///< Used for initialisation if state is not yet known
   S_START,                      ///< Initial state
   S_INITIALISESUBSYSTEMS,       ///< Initialised subsystems
   S_CONFIGURE,                  ///< Ask user for action
   S_WAITFORPAYMENT,			 ///< Wait for the user to insert coins
   S_SHUTDOWN_SYSTEM,
   S_IDLE,
   S_INTERFACE,
   S_MAKEDRINK,
   S_DONEDRINK
} state_t;

#endif
