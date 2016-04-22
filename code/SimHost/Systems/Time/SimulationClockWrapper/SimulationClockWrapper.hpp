//Wrapper class for easier testing
//DO NOT EDIT; this is generated code
#pragma once
    #include "SimulationClock.h"

class SimulationClock {

//the component state we are wrapping in order to make testing easier
SimulationClockOutputsT o;
void Destructure();

public:
//expose the backend API of the component

    /**
     * @brief Create a clock at a specified date and time
     * @details The clock will start paused
     * @param[in] eMonth the date month to start the clock at. valid range: (1 - 12)
     * @param[in] nDay the day of the month to start the clock at.  valid range: (1 - 31)
     * @param[in] nYear the date year to start the clock at.  valid range: any positive year number, that fits the size of the type.
     * @param[in] dMilliseconds how many milliseconds of the current day to start the time at.  valid range: (0 - 86,399,999)
     */
SimulationClock(const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds);

    /**
     * @brief Reset the clock to a new date and time.
     * @details Resetting the clock will not affect its pause state
     * @param[in] eMonth current month of the year. valid range: (1 - 12)
     * @param[in] nDay the current calendar day of the month.  valid range: (1 - 31)
     * @param[in] nYear the current year.  valid range: any positive year number, that fits the size of the type.
     * @param[in] dMilliseconds the number of milliseconds of the current day.  valid range: (0 - 86,399,999)
     */
void Reset(const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds);

    /**
     * @brief Change whether the clock is paused or not.
     * @details There is no harm in setting a clock to the same pause state that it is already in.
     * @param[in] bPause whether or not to pause the clock
     */
void SetPauseState(const BOOL bPause);

    /**
     * @brief Update the current date and time of the SimulationClock
     * @details This function should be called individually if a user wishes to
     *          update the date and time, but would not like to cause a reset or affect the pause states.
     *          This function does not need to be called before/after a pause state change, as the time values
     *          will already be up-to-date.
     */
void Update(void);

//data members for direct access
BOOL paused;
DateTimeOutputsT date_time;
};
