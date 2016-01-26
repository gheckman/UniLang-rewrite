/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Send Low Speed Message Data
*
*    @brief Structure for sending by the sim host of the low speed message to the flight model
*
*    @details sent over data socket
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

#ifndef SendLowSpeedMessageH
#define SendLowSpeedMessageH




#ifdef __cplusplus
extern "C"
{
#endif //#ifdef __cplusplus

/**
 * @brief Send Low Speed Message
 * @details The internal state of the component
 */
typedef struct SendLowSpeedMessage_t
{

/**
 * @details up to 8
 */
int m_nNumberOfGears;

/**
 * @details (0 = up, 100 = full down)
 * @note units: percentage
 */
int m_nGearRequestedPosition[MAX_NUMBER_OF_LANDING_GEARS]_pct;

/**
 * @details up to 4
 */
int m_nNumberOfFlaps;

/**
 * @details (0 = retracted, 100 = extended)
 * @note units: percentage
 */
int m_nFlapRequestedPosition[MAX_NUMBER_OF_FLAPS]_pct;

/**
 * @details up to 8
 */
int m_nNumberOfSpeedBrakes;

/**
 * @details (0 = retracted, 100 = extended)
 * @note units: percentage
 */
int m_nSpeedBrakeRequestedPosition[MAX_NUMBER_OF_SPEED_BRAKES]_pct;
/**
 * @note units: inches of mercury
 */
float m_fSeaLevelPressure_inHg;
/**
 * @note units: degree farenheit
 */
float m_fSeaLevelTemperature_degf;

/**
 * @details 0.0 = Smooth, 10.0 = extremely rough
 */
float m_fRunwayRoughness;
/**
 * @note units: knots
 */
float m_fWindMagnitude_kts;
/**
 * @note units: degrees
 */
float m_fWindHeading_deg;
/**
 * @note units: degrees
 */
float m_fWindInclination_deg;

/**
 * @details 0.0 = Smooth, 10.0 = extremely rough
 */
float m_fTurbulence;
/**
 * @note units: pounds
 */
float m_fPayloadWeight_lbs;
/**
 * @note units: inches
 */
float m_fCGOffsetX_in;
/**
 * @note units: inches
 */
float m_fCGOffsetY_in;
/**
 * @note units: inches
 */
float m_fCGOffsetZ_in;

/**
 * @details up to 8
 */
int m_nNumberOfEngines;

/**
 * @details Engine starter running (1 = true)
 */
int m_nEngineStarterRunning[MAX_NUMBER_OF_ENGINES];

/**
 * @details Engine Bleed Air On (1 = true)
 *          0 = Off
 *          1 = Pneumatic
 *          2 = Pneumatic & Environmental
 */
int m_nBleedAir[MAX_NUMBER_OF_ENGINES];

/**
 * @details Engine ignition on (1 = true)
 */
int m_nIgnitionOn[MAX_NUMBER_OF_ENGINES];

/**
 * @details Bit 00 Set = Fuel available
 *          Bit 01 Set = Boost pump on
 *          Bit 02 Set = Fuel jet pump on
 *          Bit 03 Set = Engine driven jet pump on
 *          Bit 04 Set = Oil pump on
 */
int m_nEngineFlags1[MAX_NUMBER_OF_ENGINES];

/**
 * @details 0 = Normal
 *          1 = Anti-Ice doors in use
 *          2 = Sand filters in use
 *          3 = Sand filters pre-clogged
 *          4 = Sand filters clogged
 *          5 = Sand filters bypass door not fully open
 */
int m_nEngineInletState[MAX_NUMBER_OF_ENGINES];

/**
 * @details Ice build up on engine
 * @note units: inches
 */
float m_fIceStateEngine_in;

/**
 * @details Bit 00 Set = Engine hot start
 *          Bit 01 Set = Engine hung start
 *          Bit 02 Set = Engine overspeed governor fail
 *          Bit 03 Set = Engine compressor stall
 *          Bit 04 Set = Engine overspeed driveshaft fail
 *          Bit 05 Set = Engine underspeed governor fail
 *          Bit 06 Set = Engine failure
 *          Bit 07 Set = Engine droop compensation fail
 *          Bit 08 Set = Engine fire
 *          Bit 09 Set = Fuel filter 1/2 clogged
 *          Bit 10 Set = Engine chip detected
 *          Bit 11 Set = Engine oil filter clogged
 */
int m_nEngineFailureFlags[MAX_NUMBER_OF_ENGINES];

/**
 * @details up to 8
 */
int m_nNumberOfPropellers;

/**
 * @details Ice build up on propeller
 * @note units: inches
 */
float m_fIceStatesProp_in;

/**
 * @details Ice build up on right wing
 * @note units: inches
 */
float m_fIceStateRightWing_in;

/**
 * @details Ice build up on left wing
 * @note units: inches
 */
float m_fIceStateLeftWing_in;

/**
 * @details Ice build up on fuselage
 * @note units: inches
 */
float m_fIceStateFuselage_in;

/**
 * @details Ice build up on tail
 * @note units: inches
 */
float m_fIceStateTail_in;

/**
 * @details Time multiplier to allow for x2 (or more) passage of time
 */
float m_fTime;

/**
 * @details Bit 00 = Blow Tire #1 (1 = failed)
 *          Bit 01 = Blow Tire #2
 *          Bit 02 = Blow Tire #3
 *          Bit 03 = Blow Tire #4
 *          Bit 04 = Blow Tire #5
 *          Bit 05 = Blow Tire #6
 *          Bit 06 = Blow Tire #7
 *          Bit 07 = Blow Tire #8
 *          Bit 08 = Left door open
 *          Bit 09 = Right door open
 *          Bit 10 = EPU door open
 *          Bit 11 = Flight control's tail rotor pedals disconnected
 *          Bit 12 = Tail rotor drive failure
 *          Bit 13 = Loss of tail rotor effectiveness
 */
int m_nFailureFlags1;
} SendLowSpeedMessageT;


#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif /* SendLowSpeedMessageH */

///@}

