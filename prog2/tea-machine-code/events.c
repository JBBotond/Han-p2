// global variables
char * eventEnumToText[] =
{
   "E_NO",                ///< Used for initialisation of an event variable
   "E_START",             ///< First event after example is switched on
   "E_CONTINUE",          ///< Initialising subsystems is ready
   "E_CONTINUE_ERROR",    ///< Initialisation error
   "E_CONFIG_READY",      ///< User action is open gate
   "E_NOT_ENOUGH",        ///< Total inserted money is not enough
   "E_ENOUGH",            ///< Total inserted money is enough
   "E_EXIT_SYSTEM",       ///< System exception or shutdown
   "E_SELECT_DRINK",      ///< Select a desired drink
   "E_POUR",              ///< Pouring the desired drink
   "E_WAIT",              ///< Waiting for infusion
   "E_STILL_MAKING"       ///< Still being made
};
