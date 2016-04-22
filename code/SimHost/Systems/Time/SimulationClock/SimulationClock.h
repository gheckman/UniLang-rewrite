/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Simulation Clock Interface
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

#ifndef SimulationClockH
#define SimulationClockH


#include "SimulationClockData.h" //USES: SimulationClockInputsT SimulationClockOutputsT

#ifdef __cplusplus
extern "C"
{
#endif /* #ifdef __cplusplus */


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
void InitializeSimulationClock(SimulationClockOutputsT *const ptOutputs, const MonthE eMonth, const int nDay, const int nYear, const double dMilliseconds);

/**
 * @brief Updates the state of SimulationClock and generate new output
 * @details The input is used against the internal state of the output to generate a new output
 * @param[in,out] ptOutputs Represents the internal state of the object.
 *                The internal state of the object, will be updated,
 *                based on the new inputs.
 * @param[in] ptInputs All of the conceivable inputs used to transform the outputs.
 */
void UpdateSimulationClock(SimulationClockOutputsT *const ptOutputs, const SimulationClockInputsT *const ptInputs);


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* SimulationClockH */

///@}

