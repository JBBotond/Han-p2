char * stateEnumToText[] =
{
   "S_NO",                         ///< Used for initialisation if state is not yet known
   "S_START",                      ///< Initial state
   "S_INITIALISESUBSYSTEMS",       ///< Initialised subsystems
   "S_CONFIGURE",                  ///< Ask user for action               ///< Handle the 50c insert
   "S_WAITFORPAYMENT",               ///< Wait for the user to insert coins
   "S_SHUTDOWN_SYSTEM",            ///< Exception or system exit shutdown requested
    "S_IDLE",		/// idle, wait for user selection
    "S_INTERFACE",	/// ask user for money --> enough/not enough
    "S_MAKEDRINK",	/// drink is in the making
    "S_DONEDRINK"	/// drink is given to user
};
