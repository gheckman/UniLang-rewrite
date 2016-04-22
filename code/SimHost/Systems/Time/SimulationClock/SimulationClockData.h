/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Simulation Clock Data
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

#ifndef SimulationClockDataH
#define SimulationClockDataH


#include <stdioLib.h>          //HASA: BOOL
#include "DateTime.h"          //HASA: HASA: DateTimeOutputsT
#include "MillisecondTimer.h"  //HASA: MillisecondTimerOutputsT
#include "Month.h"             //USES: MonthE


#ifdef __cplusplus
extern "C"
{
#endif /* #ifdef __cplusplus */

/**
 * @brief Simulation Clock Locals
 * @details Contains internal state that should not be referenced by the client.
 */
typedef struct SimulationClockLocals_t
{

    /**
     * @brief A timer used internally to keep track of time gone by.
     * @details The timer is reset after each update in order to get a delta time since the last update.  
     *          The timer's elapsed time is used when updating the simulated clock's date and time.
     */
MillisecondTimerOutputsT m_tTimer;

} SimulationClockLocalsT;

/**
 * @brief Simulation Clock Inputs
 * @details All of the conceivable inputs,
 *          that may influence the state of the component, 
 *          and potentially change any of the outputs
 */
typedef struct SimulationClockInputs_t
{
    /**
     * @brief A trigger for calling the backend API function: Reset.
     *        Reset the clock to a new date and time.
     * @details Setting the trigger will apply the transformation specified during an update.
     *          Resetting the clock will not affect its pause state
     */
    BOOL m_bReset;

    /**
     * @brief A trigger for calling the backend API function: SetPauseState.
     *        Change whether the clock is paused or not.
     * @details Setting the trigger will apply the transformation specified during an update.
     *          There is no harm in setting a clock to the same pause state that it is already in.
     */
    BOOL m_bSetPauseState;

    /**
     * @brief A trigger for calling the backend API function: Update.
     *        Update the current date and time of the SimulationClock
     * @details Setting the trigger will apply the transformation specified during an update.
     *          This function should be called individually if a user wishes to
     *          update the date and time, but would not like to cause a reset or affect the pause states.
     *          This function does not need to be called before/after a pause state change, as the time values
     *          will already be up-to-date.
     */
    BOOL m_bUpdate;


    /**
     * @brief current month of the year. valid range: (1 - 12)
     * @details This parameter is applied to the following functions:
     *          Reset
     */
MonthE m_eMonth;


    /**
     * @brief the current calendar day of the month.  valid range: (1 - 31)
     * @details This parameter is applied to the following functions:
     *          Reset
     */
int m_nDay;


    /**
     * @brief the current year.  valid range: any positive year number, that fits the size of the type.
     * @details This parameter is applied to the following functions:
     *          Reset
     */
int m_nYear;


    /**
     * @brief the number of milliseconds of the current day.  valid range: (0 - 86,399,999)
     * @details This parameter is applied to the following functions:
     *          Reset
     */
double m_dMilliseconds;


    /**
     * @brief whether or not to pause the clock
     * @details This parameter is applied to the following functions:
     *          SetPauseState
     */
BOOL m_bPause;

} SimulationClockInputsT;

/**
 * @brief Simulation Clock Outputs
 * @details All of the conceivable outputs
 *          that may be influenced by any of inputs during an update.
 */
typedef struct SimulationClockOutputs_t
{

    /**
     * @brief Whether the clock is currently paused or unpaused
     * @details This data member can be affected by the SetPauseState(BOOL)
     */
BOOL m_bPaused;


    /**
     * @brief Holds the current date and time
     * @details Updated internally using an internal timer
     */
DateTimeOutputsT m_tDateTime;

    /**
     * @brief The local state of the Simulation Clock
     * @details Contains internal state that should not be referenced by the client.
     */
SimulationClockLocalsT m_tLocals;

} SimulationClockOutputsT;


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* SimulationClockDataH */

///@}

