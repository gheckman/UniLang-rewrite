/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Send Reposition Message Data
*
*    @brief Structure for sending by the sim host of the reposition message to the flight model
*
*    @details sent over control socket
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
*    @addtogroup J2 Network_Message Communication
*    @{
*/

#ifndef SendRepositionMessageH
#define SendRepositionMessageH




#ifdef __cplusplus
extern "C"
{
#endif //#ifdef __cplusplus

/**
 * @brief Send Reposition Message
 * @details The internal state of the component
 */
typedef struct SendRepositionMessage_t
{

/**
 * @details 0 = Normal reposition | 1 = Special reposition
 */
int m_nRepositionType;
/**
 * @note units: degrees
 */
double m_dLatitude_deg;
/**
 * @note units: degrees
 */
double m_dLongitude_deg;
/**
 * @note units: feet
 */
double m_dMSLAltitude_ft;
/**
 * @note units: degrees
 */
float m_fMagneticHeading_deg;
/**
 * @note units: knots
 */
float m_fIndicatedAirspeed_kts;
/**
 * @note units: degrees
 */
float m_fAircraftPitch_deg;
/**
 * @note units: degrees
 */
float m_fAircraftRoll_deg;
/**
 * @note units: feet / minute
 */
float m_fVerticalSpeed_fpm;

/**
 * @details up to 8
 */
int m_nNumberOfEngines;

/**
 * @details Engine running (1 = true)
 */
int m_pnNumberOfEngines[MAX_NUMBER_OF_ENGINES];
/**
 * @note units: revolutions / minute
 */
float m_pfEngine_rpm[MAX_NUMBER_OF_ENGINES];

/**
 * @details turbine
 * @note units: percentage
 */
float m_pfN1_pct[MAX_NUMBER_OF_ENGINES];

/**
 * @details turbine
 * @note units: percentage
 */
float m_pfN2_pct[MAX_NUMBER_OF_ENGINES];

/**
 * @details up to 8
 */
int m_nNumberOfPropellers;
/**
 * @note units: revolutions / minute
 */
float m_pfPropeller_rpm[MAX_NUMBER_OF_PROPELLERS];
} SendRepositionMessageT;


#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif /* SendRepositionMessageH */

///@}

