/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Propeller Reposition Data
*
*    @brief propeller data sent over reposition
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
*    @addtogroup J2 Communication
*    @{
*/

#ifndef PropellerRepositionH
#define PropellerRepositionH




#ifdef __cplusplus
extern "C"
{
#endif /* #ifdef __cplusplus */

/**
 * @brief Propeller Reposition
 * @details The internal state of the component
 */
typedef struct PropellerReposition_t
{

    /**
     * @brief RPM of piston
     * @note units: revolutions / minute
     */
float m_fPiston_rpm;

} PropellerRepositionT;


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* PropellerRepositionH */

///@}

