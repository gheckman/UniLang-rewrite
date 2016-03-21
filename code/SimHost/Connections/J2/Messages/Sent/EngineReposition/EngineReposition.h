/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Engine Reposition Data
*
*    @brief engine data sent over reposition
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

#ifndef EngineRepositionH
#define EngineRepositionH




#ifdef __cplusplus
extern "C"
{
#endif /* #ifdef __cplusplus */

/**
 * @brief Engine Reposition
 * @details The internal state of the component
 */
typedef struct EngineReposition_t
{

    /**
     * @brief running
     * @details 0 = Engine off | 1 = Engine on
     */
int m_nRunning;


    /**
     * @brief RPM of piston
     * @note units: revolutions / minute
     */
float m_fPiston_rpm;


    /**
     * @brief n1 of turbine
     * @note units: percentage
     */
float m_fN1_pct;


    /**
     * @brief n2 of turbine
     * @note units: percentage
     */
float m_fN2_pct;

} EngineRepositionT;


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* EngineRepositionH */

///@}

