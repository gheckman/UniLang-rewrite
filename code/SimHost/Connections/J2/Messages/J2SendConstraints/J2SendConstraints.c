/**
*    @file
*
*    @author Trevor Hickey
*
*    @note J2 Send Constraints Implementation
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

#include "J2SendConstraints.h"    //implements decelerations
#include "ConstraintUtilities.h"  //USES: CheckValueConstraint(), CheckIntervalConstraint(), ComparisonOperatorE, IntervalTypeE

/**
 * @brief checks a constraint by comparing a value
 * @details macro forwards value as string, and passed flag implicitly
 */
#ifndef CHECK_VALUE
#define CHECK_VALUE(VAR,OP,VALUE) CheckValueConstraint(VAR, OP, VALUE, #VAR, &bPassed)
#endif

/**
 * @brief checks a constraint by comparing a value
 * @details macro forwards value as string, and passed flag implicitly
 */
#ifndef CHECK_INDEXED_VALUE
#define CHECK_INDEXED_VALUE(VAR,OP,VALUE) CheckValueConstraintFromArrayIndex(VAR[INDEX], INDEX, OP, VALUE, #VAR, &bPassed)
#endif

/**
 * @brief checks a value constraint using an interval
 * @details macro forwards value as string, and passed flag implicitly
 */
#ifndef CHECK_INTERVAL
#define CHECK_INTERVAL(VAR,BEGIN,END,TYPE) CheckIntervalConstraint(VAR, BEGIN, END, TYPE, #VAR, &bPassed)
#endif

/**
 * @brief checks an indexed value constraint using an interval
 * @details macro forwards value as string, and passed flag implicitly
 */
#ifndef CHECK_INDEXED_INTERVAL
#define CHECK_INDEXED_INTERVAL(VAR,INDEX,BEGIN,END,TYPE) CheckIntervalConstraintFromArrayIndex(VAR[INDEX], INDEX, BEGIN, END, TYPE, #VAR, &bPassed)
#endif


/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendHighSpeedMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendHighSpeedMessage(const SendHighSpeedMessageT *const ptSendHighSpeedMessage)
{
//a flag returned to the caller to signify whether constraints have passed
BOOL bPassed = TRUE;

//used for indexing over array data members
size_t uIndex = 0u;


//check value constraints for pitch flight control
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fPitchFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for roll flight control
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fRollFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for yaw flight control
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fYawFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for collective flight control
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fCollectiveFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for pitch trim position
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fPitchTrimPosition, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for roll trim position
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fRollTrimPosition, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for yaw trim position
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fYawTrimPosition, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for yaw serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfYawSerialActuators, uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for yaw trim actuators
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fYawTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for roll serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfRollSerialActuators, uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for roll trim actuators
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fRollTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for pitch serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfPitchSerialActuators, uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for pitch trim actuators
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fPitchTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for collective serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfCollectiveSerialActuators, uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for collective trim actuators
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fCollectiveTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for yaw control override flag
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nYawControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED);


//check value constraints for pitch control override flag
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nPitchControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED);


//check value constraints for roll control override flag
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nRollControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED);


//check value constraints for collective control override flag
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED);


//check value constraints for right brake
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fRightBrake, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for left brake
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fLeftBrake, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for nose wheel control
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fNoseWheelControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for rotor brake
CHECK_INTERVAL(ptSendHighSpeedMessage->m_fRotorBrake, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for winch flag
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nWinchFlag, 0, 4, INTERVAL_TYPE_CLOSED);


//check value constraints for winch length
CHECK_VALUE(ptSendHighSpeedMessage->m_fWinchLength_m, COMPARISON_OPERATOR_GREATER_EQUAL, 0.0f);


//check value constraints for winch payload mass
CHECK_VALUE(ptSendHighSpeedMessage->m_fWinchPayloadMass_kg, COMPARISON_OPERATOR_GREATER_EQUAL, 0.0f);


//check value constraints for winch payload x

//check value constraints for winch payload y

//check value constraints for winch payload z

//check value constraints for hook flag
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nHookFlag, 0, 4, INTERVAL_TYPE_CLOSED);


//check value constraints for hook length

//check value constraints for hook payload mass

//check value constraints for hook payload x

//check value constraints for hook payload y

//check value constraints for hook payload z

//check value constraints for SAS Mode
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nSASMode, 0, 7, INTERVAL_TYPE_CLOSED);


//check value constraints for height of terrain

//check value constraints for number of contact points
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nNumberOfContactPoints, 0, MAX_NUMBER_OF_CONTACT_LOCATIONS, INTERVAL_TYPE_CLOSED);


//check value constraints for ground contact location
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_CONTACT_LOCATIONS; ++uIndex){
}

//check value constraints for number of engines
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nNumberOfEngines, 0, MAX_NUMBER_OF_ENGINES, INTERVAL_TYPE_CLOSED);


//check value constraints for throttle
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfThrottle, uIndex, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for mixture
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfMixture, uIndex, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for number of propellers
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nNumberOfPropellers, 0, MAX_NUMBER_OF_PROPELLERS, INTERVAL_TYPE_CLOSED);


//check value constraints for prop pitch
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfPropPitch_deg, uIndex, -180.0f, 180.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for number of tanks
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nNumberOfTanks, 0, MAX_NUMBER_OF_FUEL_TANKS, INTERVAL_TYPE_CLOSED);


//check value constraints for fuel weight
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_FUEL_TANKS; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendHighSpeedMessage->m_pfFuelWeight_lbs, uIndex, 0.0f, 4000.0f, INTERVAL_TYPE_CLOSED);

}

//check value constraints for flag1
CHECK_INTERVAL(ptSendHighSpeedMessage->m_nFlag1, 0, 7, INTERVAL_TYPE_CLOSED);



//returns the flag to the caller to signify whether constraints have passed
return bPassed;


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendLowSpeedMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendLowSpeedMessage(const SendLowSpeedMessageT *const ptSendLowSpeedMessage)
{
//a flag returned to the caller to signify whether constraints have passed
BOOL bPassed = TRUE;

//used for indexing over array data members
size_t uIndex = 0u;


//check value constraints for number of gears
CHECK_INTERVAL(ptSendLowSpeedMessage->m_nNumberOfGears, 0, MAX_NUMBER_OF_LANDING_GEARS, INTERVAL_TYPE_CLOSED);


//check value constraints for gear requested position
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_LANDING_GEARS; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct, uIndex, 0, 100, INTERVAL_TYPE_CLOSED);

}

//check value constraints for number of flaps
CHECK_INTERVAL(ptSendLowSpeedMessage->m_nNumberOfFlaps, 0, MAX_NUMBER_OF_FLAPS, INTERVAL_TYPE_CLOSED);


//check value constraints for flap requested position
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_FLAPS; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct, uIndex, 0, 100, INTERVAL_TYPE_CLOSED);

}

//check value constraints for number of speed brakes
CHECK_INTERVAL(ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes, 0, MAX_NUMBER_OF_SPEED_BRAKES, INTERVAL_TYPE_CLOSED);


//check value constraints for speed brake requested position
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_SPEED_BRAKES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct, uIndex, 0, 100, INTERVAL_TYPE_CLOSED);

}

//check value constraints for sea level pressure
CHECK_INTERVAL(ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg, 0.0f, 35.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for sea level temperature
CHECK_INTERVAL(ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf, -148.0f, 302.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for runway roughness
CHECK_INTERVAL(ptSendLowSpeedMessage->m_fRunwayRoughness, 0.0f, 10.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for wind magnitude
CHECK_INTERVAL(ptSendLowSpeedMessage->m_fWindMagnitude_kts, 0.0f, 200.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for wind heading
CHECK_INTERVAL(ptSendLowSpeedMessage->m_fWindHeading_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for wind inclination
CHECK_INTERVAL(ptSendLowSpeedMessage->m_fWindInclination_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for turbulence
CHECK_INTERVAL(ptSendLowSpeedMessage->m_fTurbulence, 0.0f, 10.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for payload weight
CHECK_VALUE(ptSendLowSpeedMessage->m_fPayloadWeight_lbs, COMPARISON_OPERATOR_GREATER_EQUAL, 0.0f);


//check value constraints for CG offset x

//check value constraints for CG offset y

//check value constraints for CG offset z

//check value constraints for number of engines
CHECK_INTERVAL(ptSendLowSpeedMessage->m_nNumberOfEngines, 0, MAX_NUMBER_OF_ENGINES, INTERVAL_TYPE_CLOSED);


//check value constraints for engine starter running
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnEngineStarterRunning, uIndex, 0, 1, INTERVAL_TYPE_CLOSED);

}

//check value constraints for bleed air
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnBleedAir, uIndex, 0, 2, INTERVAL_TYPE_CLOSED);

}

//check value constraints for ignition
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnIgnition, uIndex, 0, 1, INTERVAL_TYPE_CLOSED);

}

//check value constraints for engine flags 1
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnEngineFlags1, uIndex, 0, 31, INTERVAL_TYPE_CLOSED);

}

//check value constraints for engine inlet state
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnEngineInletState, uIndex, 0, 5, INTERVAL_TYPE_CLOSED);

}

//check value constraints for ice state engine
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
}

//check value constraints for engine failure flags
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CHECK_INDEXED_INTERVAL(ptSendLowSpeedMessage->m_pnEngineFailureFlags, uIndex, 0, 65535, INTERVAL_TYPE_CLOSED);

}

//check value constraints for number of propellers
CHECK_INTERVAL(ptSendLowSpeedMessage->m_nNumberOfPropellers, 0, MAX_NUMBER_OF_PROPELLERS, INTERVAL_TYPE_CLOSED);


//check value constraints for ice states prop
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
}

//check value constraints for ice state right wing
CHECK_VALUE(ptSendLowSpeedMessage->m_fIceStateRightWing_in, COMPARISON_OPERATOR_GREATER_EQUAL, 0.0f);


//check value constraints for ice state left wing
CHECK_VALUE(ptSendLowSpeedMessage->m_fIceStateLeftWing_in, COMPARISON_OPERATOR_GREATER_EQUAL, 0.0f);


//check value constraints for ice state fuselage
CHECK_VALUE(ptSendLowSpeedMessage->m_fIceStateFuselage_in, COMPARISON_OPERATOR_GREATER_EQUAL, 0.0f);


//check value constraints for ice state tail
CHECK_VALUE(ptSendLowSpeedMessage->m_fIceStateTail_in, COMPARISON_OPERATOR_GREATER_EQUAL, 0.0f);


//check value constraints for time multiplier
CHECK_VALUE(ptSendLowSpeedMessage->m_nTimeMultiplier, COMPARISON_OPERATOR_GREATER_EQUAL, 0);


//check value constraints for failure flags 1
CHECK_INTERVAL(ptSendLowSpeedMessage->m_nFailureFlags1, 0, 16383, INTERVAL_TYPE_CLOSED);



//returns the flag to the caller to signify whether constraints have passed
return bPassed;


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptEngineReposition the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnEngineReposition(const EngineRepositionT *const ptEngineReposition)
{
//a flag returned to the caller to signify whether constraints have passed
BOOL bPassed = TRUE;


//check value constraints for running

//check value constraints for piston
CHECK_INTERVAL(ptEngineReposition->m_fPiston_rpm, 0.0f, 100000.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for n1
CHECK_INTERVAL(ptEngineReposition->m_fN1_pct, 0.0f, 100.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for n2
CHECK_INTERVAL(ptEngineReposition->m_fN2_pct, 0.0f, 100.0f, INTERVAL_TYPE_CLOSED);



//returns the flag to the caller to signify whether constraints have passed
return bPassed;


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptPropellerReposition the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnPropellerReposition(const PropellerRepositionT *const ptPropellerReposition)
{
//a flag returned to the caller to signify whether constraints have passed
BOOL bPassed = TRUE;


//check value constraints for piston
CHECK_INTERVAL(ptPropellerReposition->m_fPiston_rpm, 0.0f, 10000.0f, INTERVAL_TYPE_CLOSED);



//returns the flag to the caller to signify whether constraints have passed
return bPassed;


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendRepositionMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendRepositionMessage(const SendRepositionMessageT *const ptSendRepositionMessage)
{
//a flag returned to the caller to signify whether constraints have passed
BOOL bPassed = TRUE;

//used for indexing over array data members
size_t uIndex = 0u;


//check value constraints for reposition type
CHECK_INTERVAL(ptSendRepositionMessage->m_nRepositionType, 0, 1, INTERVAL_TYPE_CLOSED);


//check value constraints for latitude
CHECK_INTERVAL(ptSendRepositionMessage->m_dLatitude_deg, -90.0, 90.0, INTERVAL_TYPE_CLOSED);


//check value constraints for longitude
CHECK_INTERVAL(ptSendRepositionMessage->m_dLongitude_deg, -180.0, 180.0, INTERVAL_TYPE_CLOSED);


//check value constraints for MSL altitude

//check value constraints for magnetic heading
CHECK_INTERVAL(ptSendRepositionMessage->m_fMagneticHeading_deg, 0.0f, 360.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for indicated airspeed

//check value constraints for aircraft pitch
CHECK_INTERVAL(ptSendRepositionMessage->m_fAircraftPitch_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for aircraft roll
CHECK_INTERVAL(ptSendRepositionMessage->m_fAircraftRoll_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for vertical speed
CHECK_INTERVAL(ptSendRepositionMessage->m_fVerticalSpeed_fpm, -100000.0f, 100000.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for number of engines
CHECK_INTERVAL(ptSendRepositionMessage->m_nNumberOfEngines, 0, MAX_NUMBER_OF_ENGINES, INTERVAL_TYPE_CLOSED);


//check value constraints for engine
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckConstraintsOnEngineReposition(&ptSendRepositionMessage->m_ptEngine[uIndex]);
}

//check value constraints for number of propellers
CHECK_INTERVAL(ptSendRepositionMessage->m_nNumberOfPropellers, 0, MAX_NUMBER_OF_PROPELLERS, INTERVAL_TYPE_CLOSED);


//check value constraints for propeller
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
CheckConstraintsOnPropellerReposition(&ptSendRepositionMessage->m_ptPropeller[uIndex]);
}

//check value constraints for pitch flight control
CHECK_INTERVAL(ptSendRepositionMessage->m_fPitchFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for roll flight control
CHECK_INTERVAL(ptSendRepositionMessage->m_fRollFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for yaw flight control
CHECK_INTERVAL(ptSendRepositionMessage->m_fYawFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);


//check value constraints for collective flight control
CHECK_INTERVAL(ptSendRepositionMessage->m_fCollectiveFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED);



//returns the flag to the caller to signify whether constraints have passed
return bPassed;


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendVersionRequestMessage the data type whose member variables will be checked against value constraints
 * @return whether the constraints have passed or not
 */
BOOL CheckConstraintsOnSendVersionRequestMessage(const SendVersionRequestMessageT *const ptSendVersionRequestMessage)
{
//a flag returned to the caller to signify whether constraints have passed
BOOL bPassed = TRUE;


//check value constraints for empty


//returns the flag to the caller to signify whether constraints have passed
return bPassed;


}

///@}

