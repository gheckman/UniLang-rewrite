/**
*    @file
*
*    @author Trevor Hickey
*
*    @note J2 Send Constraints Interface
*
*    @brief A set of debug functions used to determine that the value constraints of a set of data are being met.
*
*    @details Data constraints may be specified by an ICD, or constrained based on what we deem acceptable.
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
*    @addtogroup J2_Communication
*    @{
*/

#ifndef J2SendConstraintsH
#define J2SendConstraintsH


#include "SendToJ2Messages.h"  //all structs


#ifdef __cplusplus
extern "C"
{
#endif /* #ifdef __cplusplus */



/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendHighSpeedMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendHighSpeedMessage(const SendHighSpeedMessageT *const ptSendHighSpeedMessage);

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendLowSpeedMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendLowSpeedMessage(const SendLowSpeedMessageT *const ptSendLowSpeedMessage);

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptEngineReposition the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnEngineReposition(const EngineRepositionT *const ptEngineReposition);

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptPropellerReposition the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnPropellerReposition(const PropellerRepositionT *const ptPropellerReposition);

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendRepositionMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendRepositionMessage(const SendRepositionMessageT *const ptSendRepositionMessage);

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendVersionRequestMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendVersionRequestMessage(const SendVersionRequestMessageT *const ptSendVersionRequestMessage);


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* J2SendConstraintsH */

///@}

