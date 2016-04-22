/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Simulation Clock Implementation
*
*    @brief A simulated clock that manages a date and time automatically.
*
*    @details Once given a date and time to start at, it will handle the internal logic of updating the time
*             during updates.  Since the clock is simulated, it can be paused and unpaused.  
*             It can also be reset to another time if desired.
*
*    @copyright Copyright 2015.
*    @n         Fidelity Flight Simulation, Inc. (F2Si)
*    @n         All rights reserved.
*
*    @b Classification:      Unclassified
*
*    @b Project @b Name:     UH-72A Synthetic Flight Training System (SFTS)
*
*    @b Contract @b Number:  #W900KK-09-D-0577
*
*    @b Task @b Order:       0002
*
*    This work was generated under U.S. Government contract and the
*    government has unlimited data rights therein.
*
*    @b DISTRIBUTION @b STATEMENT @b D:
*    @n    Distribution authorized to the Department of Defense and U.S. DoD contractors only.
*    @n    Other requests shall be referred to the controlling DoD office.
*
*    @b Organizations:
*    @n    Fidelity Flight Simulation, Inc. (F2Si)
*    @n    1815 Parkway View Drive
*    @n    Pittsburgh, PA 15205
*    @n    (412) 321-3280
*
*    @addtogroup Time Simulation_Clock Component
*    @{
*/

#include "SimulationClock.h"  //USES: SimulationClockInputsT SimulationClockOutputsT
/**
 * @brief Reset the clock to a new date and time.
 * @details Resetting the clock will not affect its pause state
 * @param[in,out] ptOutputs the internal state of simulation clock
 * @param[in] eMonth current month of the year. valid range: (1 - 12)
 * @param[in] nDay the current calendar day of the month.  valid range: (1 - 31)
 * @param[in] nYear the current year.  valid range: any positive year number, that fits the size of the type.
 * @param[in] dMilliseconds the number of milliseconds of the current day.  valid range: (0 - 86,399,999)
 */
static void Reset(SimulationClockOutputsT *const ptOutputs, const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds);

/**
 * @brief Change whether the clock is paused or not.
 * @details There is no harm in setting a clock to the same pause state that it is already in.
 * @param[in,out] ptOutputs the internal state of simulation clock
 * @param[in] bPause whether or not to pause the clock
 */
static void SetPauseState(SimulationClockOutputsT *const ptOutputs, const BOOL bPause);

/**
 * @brief Pause the SimulationClock
 * @details The clock derives its time change from an internal timer.
 *          All we must do is pause the timer.
 * @param[in,out] ptOutputs the internal state of simulation clock
 */
static void Pause(SimulationClockOutputsT *const ptOutputs);

/**
 * @brief Unpause the SimulationClock
 * @details The clock derives its time change from an internal timer.
 *          All we must do is unpause the timer.
 * @param[in,out] ptOutputs the internal state of simulation clock
 */
static void UnPause(SimulationClockOutputsT *const ptOutputs);

/**
 * @brief Update the current date and time of the SimulationClock
 * @details This function should be called individually if a user wishes to
 *          update the date and time, but would not like to cause a reset or affect the pause states.
 *          This function does not need to be called before/after a pause state change, as the time values
 *          will already be up-to-date.
 * @param[in,out] ptOutputs the internal state of simulation clock
 */
static void Update(SimulationClockOutputsT *const ptOutputs);


/**
 * @brief Sets the initial state of SimulationClock
 * @details Before the output can be used and updated, it must first be initialized to a valid state.
 * @pre outputs must not be NULL.
 * @param[in,out] ptOutputs Represents the internal state of the object.
 *                The internal state of the object, will be initialized
 *                based on the input parameters and any pre-defined state decisions
 * @param[in] eMonth the date month to start the clock at. valid range: (1 - 12)
 * @param[in] nDay the day of the month to start the clock at.  valid range: (1 - 31)
 * @param[in] nYear the date year to start the clock at.  valid range: any positive year number, that fits the size of the type.
 * @param[in] dMilliseconds how many milliseconds of the current day to start the time at.  valid range: (0 - 86,399,999)
 */
void InitializeSimulationClock(SimulationClockOutputsT *const ptOutputs, const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds)
{
//construct date based on passed in values
    InitializeDateTime(&ptOutputs->m_tDateTime,
                       eMonth,
                       nDay,
                       nYear,
                       dMilliseconds);
    
    InitializeMillisecondTimer(&ptOutputs->m_tLocals.m_tTimer);
    ptOutputs->m_bPaused = TRUE;
}


/**
 * @brief Updates the state of SimulationClock and generate new output
 * @details The input is used against the internal state of the output to generate a new output
 * @param[in,out] ptOutputs Represents the internal state of the object.
 *                The internal state of the object, will be updated,
 *                based on the new inputs.
 * @param[in] ptInputs All of the conceivable inputs used to transform the outputs.
 */
void UpdateSimulationClock(SimulationClockOutputsT *const ptOutputs, const SimulationClockInputsT *const ptInputs)
{
//If specified by the client,
//call the backend API method Reset while forwarding its arguments.
//*capture any return values specified by the API method
if (ptInputs->m_bReset)
{
Reset(ptOutputs,ptInputs->m_eMonth,ptInputs->m_nDay,ptInputs->m_nYear,ptInputs->m_dMilliseconds);
}

//If specified by the client,
//call the backend API method SetPauseState while forwarding its arguments.
//*capture any return values specified by the API method
if (ptInputs->m_bSetPauseState)
{
SetPauseState(ptOutputs,ptInputs->m_bPause);
}

//If specified by the client,
//call the backend API method Update while forwarding its arguments.
//*capture any return values specified by the API method
if (ptInputs->m_bUpdate)
{
Update(ptOutputs);
}


}

/**
 * @brief Reset the clock to a new date and time.
 * @details Resetting the clock will not affect its pause state
 * @param[in,out] ptOutputs the internal state of simulation clock
 * @param[in] eMonth current month of the year. valid range: (1 - 12)
 * @param[in] nDay the current calendar day of the month.  valid range: (1 - 31)
 * @param[in] nYear the current year.  valid range: any positive year number, that fits the size of the type.
 * @param[in] dMilliseconds the number of milliseconds of the current day.  valid range: (0 - 86,399,999)
 */
static void Reset(SimulationClockOutputsT *const ptOutputs, const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds)
{
//reset the timer and set the datetime to a new date and time

    //reset the timer
    MillisecondTimerInputsT tTimerInputs={0};
    tTimerInputs.m_bReset = TRUE;
    UpdateMillisecondTimer(&ptOutputs->m_tLocals.m_tTimer, &tTimerInputs);

    //and apply a new datetime
    InitializeDateTime(&ptOutputs->m_tDateTime,
                       eMonth,
                       nDay,
                       nYear,
                       dMilliseconds);
}

/**
 * @brief Change whether the clock is paused or not.
 * @details There is no harm in setting a clock to the same pause state that it is already in.
 * @param[in,out] ptOutputs the internal state of simulation clock
 * @param[in] bPause whether or not to pause the clock
 */
static void SetPauseState(SimulationClockOutputsT *const ptOutputs, const BOOL bPause)
{
//pause or unpause the timer
    bPause ? Pause(ptOutputs) : UnPause(ptOutputs);
    
    //update the date and time values
    Update(ptOutputs);
}

/**
 * @brief Pause the SimulationClock
 * @details The clock derives its time change from an internal timer.
 *          All we must do is pause the timer.
 * @param[in,out] ptOutputs the internal state of simulation clock
 */
static void Pause(SimulationClockOutputsT *const ptOutputs)
{
//trigger timer to pause
    MillisecondTimerInputsT tTimerInputs={0};
    tTimerInputs.m_bSetPauseState = TRUE;
    tTimerInputs.m_bPause = TRUE;
    UpdateMillisecondTimer(&ptOutputs->m_tLocals.m_tTimer, &tTimerInputs);
    ptOutputs->m_bPaused = TRUE;
}

/**
 * @brief Unpause the SimulationClock
 * @details The clock derives its time change from an internal timer.
 *          All we must do is unpause the timer.
 * @param[in,out] ptOutputs the internal state of simulation clock
 */
static void UnPause(SimulationClockOutputsT *const ptOutputs)
{
//trigger timer to un pause
    MillisecondTimerInputsT tTimerInputs={0};
    tTimerInputs.m_bSetPauseState = TRUE;
    tTimerInputs.m_bPause = FALSE;
    UpdateMillisecondTimer(&ptOutputs->m_tLocals.m_tTimer, &tTimerInputs);
    ptOutputs->m_bPaused = FALSE;
}

/**
 * @brief Update the current date and time of the SimulationClock
 * @details This function should be called individually if a user wishes to
 *          update the date and time, but would not like to cause a reset or affect the pause states.
 *          This function does not need to be called before/after a pause state change, as the time values
 *          will already be up-to-date.
 * @param[in,out] ptOutputs the internal state of simulation clock
 */
static void Update(SimulationClockOutputsT *const ptOutputs)
{
//input triggers
    DateTimeInputsT tDateTimeInputs={0};
    MillisecondTimerInputsT tTimerInputs={0};
    
    //update timer duration
    tTimerInputs.m_bUpdate = TRUE;
    UpdateMillisecondTimer(&ptOutputs->m_tLocals.m_tTimer, &tTimerInputs);
    tTimerInputs.m_bUpdate = FALSE;

    //use the updated timer to update the date and time
    tDateTimeInputs.m_dNumberOfMilliseconds = ptOutputs->m_tLocals.m_tTimer.m_dElapsedTime_ms;
    UpdateDateTime(&ptOutputs->m_tDateTime,&tDateTimeInputs);

    //reset timer for next update
    tTimerInputs.m_bReset = TRUE;
    UpdateMillisecondTimer(&ptOutputs->m_tLocals.m_tTimer,&tTimerInputs);
}

///@}

