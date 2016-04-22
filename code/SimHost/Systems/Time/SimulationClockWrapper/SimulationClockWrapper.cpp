//Wrapper class for easier testing
//DO NOT EDIT; this is generated code
#include "SimulationClockWrapper.hpp"
#include "test_utilities.hpp"

/**
 * @brief Create a clock at a specified date and time
 * @details The clock will start paused
 * @param[in] eMonth the date month to start the clock at. valid range: (1 - 12)
 * @param[in] nDay the day of the month to start the clock at.  valid range: (1 - 31)
 * @param[in] nYear the date year to start the clock at.  valid range: any positive year number, that fits the size of the type.
 * @param[in] dMilliseconds how many milliseconds of the current day to start the time at.  valid range: (0 - 86,399,999)
 */
SimulationClock::SimulationClock(const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds)
{
InitializeSimulationClock(&o,eMonth, nDay, nYear, dMilliseconds);

//destructure the observables
Destructure();

}

/**
 * @brief Reset the clock to a new date and time.
 * @details Resetting the clock will not affect its pause state
 * @param[in] eMonth current month of the year. valid range: (1 - 12)
 * @param[in] nDay the current calendar day of the month.  valid range: (1 - 31)
 * @param[in] nYear the current year.  valid range: any positive year number, that fits the size of the type.
 * @param[in] dMilliseconds the number of milliseconds of the current day.  valid range: (0 - 86,399,999)
 */
void SimulationClock::Reset(const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds)
{
//initialized to zero to ensure all the API triggers are set to false
SimulationClockInputsT i = {};

//set the trigger for the backend API method
i.m_bReset=true;

//set the triggered method parameters
util::Assign(i.m_eMonth,eMonth);
util::Assign(i.m_nDay,nDay);
util::Assign(i.m_nYear,nYear);
util::Assign(i.m_dMilliseconds,dMilliseconds);

//call the method
UpdateSimulationClock(&o,&i);

//destructure the observables
Destructure();

//return the API result if applicable
return; //backend API method is void

}

/**
 * @brief Change whether the clock is paused or not.
 * @details There is no harm in setting a clock to the same pause state that it is already in.
 * @param[in] bPause whether or not to pause the clock
 */
void SimulationClock::SetPauseState(const BOOL bPause)
{
//initialized to zero to ensure all the API triggers are set to false
SimulationClockInputsT i = {};

//set the trigger for the backend API method
i.m_bSetPauseState=true;

//set the triggered method parameters
util::Assign(i.m_bPause,bPause);

//call the method
UpdateSimulationClock(&o,&i);

//destructure the observables
Destructure();

//return the API result if applicable
return; //backend API method is void

}

/**
 * @brief Update the current date and time of the SimulationClock
 * @details This function should be called individually if a user wishes to
 *          update the date and time, but would not like to cause a reset or affect the pause states.
 *          This function does not need to be called before/after a pause state change, as the time values
 *          will already be up-to-date.
 */
void SimulationClock::Update(void)
{
//initialized to zero to ensure all the API triggers are set to false
SimulationClockInputsT i = {};

//set the trigger for the backend API method
i.m_bUpdate=true;

//set the triggered method parameters

//call the method
UpdateSimulationClock(&o,&i);

//destructure the observables
Destructure();

//return the API result if applicable
return; //backend API method is void

}

void SimulationClock::Destructure(){
util::Assign(paused,o.m_bPaused);
util::Assign(date_time,o.m_tDateTime);
}
