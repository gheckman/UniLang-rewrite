/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Send High Speed Message Data
*
*    @brief Structure for sending by the sim host of the high speed message to the flight model
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

#ifndef SendHighSpeedMessageH
#define SendHighSpeedMessageH




#ifdef __cplusplus
extern "C"
{
#endif //#ifdef __cplusplus

/**
 * @brief Send High Speed Message
 * @details The internal state of the component
 */
typedef struct SendHighSpeedMessage_t
{

/**
 * @details 1.0 = Full deflection up, -1.0 = full deflection down
 */
float m_fPitchFlightControl;

/**
 * @details 1.0 = Full deflection right, -1.0 = full deflection left
 */
float m_fRollFlightControl;

/**
 * @details 1.0 = Full deflection right, -1.0 = full deflection left
 */
float m_fYawFlightControl;

/**
 * @details 1.0 = Full deflection up, 0.0 = full deflection down
 */
float m_fCollectiveFlightControl;

/**
 * @details 1.0 = Full deflection up, -1.0 = full deflection down
 */
float m_fPitchTrimPosition;

/**
 * @details 1.0 = Full deflection right, -1.0 = full deflection left
 */
float m_fRollTrimPosition;

/**
 * @details 1.0 = Full deflection right, -1.0 = full deflection left
 */
float m_fYawTrimPosition;

/**
 * @details AutoPilot Trim Control.  
 *          1.0 = Full deflection right, -1.0 = Full deflection left Both
 */
float m_pfYawSerialActuators[2];

/**
 * @details AutoPilot Trim Control.  
 *          1.0 = Full deflection right, -1.0 = Full deflection left Both
 */
float m_fYawTrimActuators;

/**
 * @details AutoPilot Trim Control.
 *          1.0 = Full deflection right, -1.0 = Full deflection left Both
 */
float m_pfRollSerialActuators[2];

/**
 * @details AutoPilot Trim Control.
 *          1.0 = Full deflection right, -1.0 = Full deflection left Both
 */
float m_fRollTrimActuators;

/**
 * @details AutoPilot Trim Control.
 *          1.0 = Full deflection up, -1.0 = Full deflection down Both
 */
float m_pfPitchSerialActuators[2];

/**
 * @details AutoPilot Trim Control.
 *          1.0 = Full deflection up, -1.0 = Full deflection down Both
 */
float m_fPitchTrimActuators;

/**
 * @details AutoPilot Trim Control.
 *          1.0 = Full deflection up, -1.0 = Full deflection down
 */
float m_pfCollectiveSerialActuators[2];

/**
 * @details AutoPilot Trim Control.
 *          1.0 = Full deflection up, -1.0 = Full deflection down Helicopter
 */
float m_fCollectiveTrimActuators;

/**
 * @details 0 = Normal(Actuator 1)
 *          1 = Normal(Actuator 2)
 *          2 = Trim Actuator Normal
 */
int m_nYawControlOverrideFlag;

/**
 * @details 0 = Normal(Actuator 1)
 *          1 = Normal(Actuator 2)
 *          2 = Trim Actuator Normal
 */
int m_nPitchControlOverrideFlag;

/**
 * @details 0 = Normal(Actuator 1)
 *          1 = Normal(Actuator 2)
 *          2 = Trim Actuator Normal
 */
int m_nRollControlOverrideFlag;

/**
 * @details 0 = Normal(Actuator 1)
 *          1 = Normal(Actuator 2)
 *          2 = Trim Actuator Normal
 */
int m_nCollectiveControlOverrideFlag;

/**
 * @details 1.0 = maximum braking, 0.0 = No braking
 */
float m_fFRightBrakes;

/**
 * @details 1.0 = maximum braking, 0.0 = No braking
 */
float m_fFLeftBrakes;

/**
 * @details 1.0 = Full deflection right, -1.0 = full deflection left.
 *          This only controls the nose wheel when it is not a caster or linked to the rudder.
 */
float m_fNoseWheelControl;

/**
 * @details 1.0 = maximum braking, 0.0 = No braking
 */
float m_fRotorBrake;

/**
 * @details 0 = Not attached | 1 = Attached | 2 = Fire Bucket | 3 = Cargo Pallet | 4 = Other
 */
int m_nWinchFlag;
/**
 * @note units: meters
 */
float m_fWinchLength_m;
/**
 * @note units: kilograms
 */
float m_fWinchPayloadMass_kg;
/**
 * @note units: meters
 */
float m_fWinchPayloadX_m;
/**
 * @note units: meters
 */
float m_fWinchPayloadY_m;
/**
 * @note units: meters
 */
float m_fWinchPayloadZ_m;

/**
 * @details 0 = not attached
 *          1 = attached
 *          2 = fire bucket
 *          3 = cargo pallet
 *          4 = other
 */
int m_nHookFlag;

/**
 * @details helicopter
 * @note units: meters
 */
float m_fHookLength_m;

/**
 * @details helicopter
 * @note units: kilograms
 */
float m_fHookPayloadMass_kg;

/**
 * @details helicopter
 * @note units: meters
 */
float m_fHookPlayloadX_m;

/**
 * @details helicopter
 * @note units: meters
 */
float m_fHookPlayloadY_m;

/**
 * @details helicopter
 * @note units: meters
 */
float m_fHookPlayloadZ_m;

/**
 * @details SAS Mode
 *          Bit 0 = Pitch SAS On
 *          Bit 1 = Roll SAS On
 *          Bit 2 = Yaw SAS
 */
int m_nSASMode;

/**
 * @details HAT for GC reference
 * @note units: feet
 */
float m_fHeightAboveTerrain_ft;

/**
 * @details up to 8
 */
int m_nNumberOfContactPoints;

/**
 * @details enumerated
 * @note units: feet
 */
float m_pfGroundContactLocation_ft[MAX_NUMBER_OF_CONTACT_LOCATIONS];

/**
 * @details up to 8
 */
int m_nNumberOfEngines;

/**
 * @details 1.0 = maximum throttle, 0.0 = idle throttle
 */
float m_pfThrottle[MAX_NUMBER_OF_ENGINES];

/**
 * @details 1.0 = maximum mixture, 0.0 = fuel cutoff
 */
float m_pfMixture[MAX_NUMBER_OF_ENGINES];

/**
 * @details up to 8
 */
int m_nNumberOfPropellers;
/**
 * @note units: degrees
 */
float m_pfPropPitch_deg[MAX_NUMBER_OF_PROPELLERS];

/**
 * @details up to 8
 */
int m_nNumberOfTanks;
/**
 * @note units: pounds
 */
float m_fFuelWeight[MAX_NUMBER_OF_FUEL_TANKS]_lbs;

/**
 * @details Bit 0 = Pause
 *          Bit 1 = Freeze (vertical)
 *          Bit 1 = Freeze (horizontal)
 */
int m_nFlag1;
} SendHighSpeedMessageT;


#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif /* SendHighSpeedMessageH */

///@}

