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
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fPitchFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fPitchFlightControl", &bPassed);
//check value constraints for roll flight control
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fRollFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fRollFlightControl", &bPassed);
//check value constraints for yaw flight control
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fYawFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fYawFlightControl", &bPassed);
//check value constraints for collective flight control
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fCollectiveFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fCollectiveFlightControl", &bPassed);
//check value constraints for pitch trim position
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fPitchTrimPosition, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fPitchTrimPosition", &bPassed);
//check value constraints for roll trim position
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fRollTrimPosition, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fRollTrimPosition", &bPassed);
//check value constraints for yaw trim position
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fYawTrimPosition, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fYawTrimPosition", &bPassed);
//check value constraints for yaw serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfYawSerialActuators[uIndex], uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfYawSerialActuators", &bPassed);}

//check value constraints for yaw trim actuators
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fYawTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fYawTrimActuators", &bPassed);
//check value constraints for roll serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfRollSerialActuators[uIndex], uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfRollSerialActuators", &bPassed);}

//check value constraints for roll trim actuators
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fRollTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fRollTrimActuators", &bPassed);
//check value constraints for pitch serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfPitchSerialActuators[uIndex], uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfPitchSerialActuators", &bPassed);}

//check value constraints for pitch trim actuators
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fPitchTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fPitchTrimActuators", &bPassed);
//check value constraints for collective serial actuators
uIndex = 0;
for(; uIndex < 2; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfCollectiveSerialActuators[uIndex], uIndex, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfCollectiveSerialActuators", &bPassed);}

//check value constraints for collective trim actuators
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fCollectiveTrimActuators, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fCollectiveTrimActuators", &bPassed);
//check value constraints for yaw control override flag
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nYawControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nYawControlOverrideFlag", &bPassed);
//check value constraints for pitch control override flag
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nPitchControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nPitchControlOverrideFlag", &bPassed);
//check value constraints for roll control override flag
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nRollControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nRollControlOverrideFlag", &bPassed);
//check value constraints for collective control override flag
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag, 0, 7, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nCollectiveControlOverrideFlag", &bPassed);
//check value constraints for right brake
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fRightBrake, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fRightBrake", &bPassed);
//check value constraints for left brake
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fLeftBrake, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fLeftBrake", &bPassed);
//check value constraints for nose wheel control
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fNoseWheelControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fNoseWheelControl", &bPassed);
//check value constraints for rotor brake
CheckIntervalConstraint(ptSendHighSpeedMessage->m_fRotorBrake, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_fRotorBrake", &bPassed);
//check value constraints for winch flag
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nWinchFlag, 0, 4, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nWinchFlag", &bPassed);
//check value constraints for winch length
CheckValueConstraint(ptSendHighSpeedMessage->m_fWinchLength_m, 0.0f, , "SendHighSpeedMessage->m_fWinchLength_m", &bPassed);
//check value constraints for winch payload mass
CheckValueConstraint(ptSendHighSpeedMessage->m_fWinchPayloadMass_kg, 0.0f, , "SendHighSpeedMessage->m_fWinchPayloadMass_kg", &bPassed);
//check value constraints for winch payload x

//check value constraints for winch payload y

//check value constraints for winch payload z

//check value constraints for hook flag
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nHookFlag, 0, 4, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nHookFlag", &bPassed);
//check value constraints for hook length

//check value constraints for hook payload mass

//check value constraints for hook payload x

//check value constraints for hook payload y

//check value constraints for hook payload z

//check value constraints for SAS Mode
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nSASMode, 0, 7, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nSASMode", &bPassed);
//check value constraints for height of terrain

//check value constraints for number of contact points
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nNumberOfContactPoints, 0, MAX_NUMBER_OF_CONTACT_LOCATIONS, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nNumberOfContactPoints", &bPassed);
//check value constraints for ground contact location
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_CONTACT_LOCATIONS; ++uIndex){
}

//check value constraints for number of engines
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nNumberOfEngines, 0, MAX_NUMBER_OF_ENGINES, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nNumberOfEngines", &bPassed);
//check value constraints for throttle
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfThrottle[uIndex], uIndex, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfThrottle", &bPassed);}

//check value constraints for mixture
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfMixture[uIndex], uIndex, 0.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfMixture", &bPassed);}

//check value constraints for number of propellers
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nNumberOfPropellers, 0, MAX_NUMBER_OF_PROPELLERS, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nNumberOfPropellers", &bPassed);
//check value constraints for prop pitch
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfPropPitch_deg[uIndex], uIndex, -180.0f, 180.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfPropPitch_deg", &bPassed);}

//check value constraints for number of tanks
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nNumberOfTanks, 0, MAX_NUMBER_OF_FUEL_TANKS, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nNumberOfTanks", &bPassed);
//check value constraints for fuel weight
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_FUEL_TANKS; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendHighSpeedMessage->m_pfFuelWeight_lbs[uIndex], uIndex, 0.0f, 4000.0f, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_pfFuelWeight_lbs", &bPassed);}

//check value constraints for flag1
CheckIntervalConstraint(ptSendHighSpeedMessage->m_nFlag1, 0, 7, INTERVAL_TYPE_CLOSED, "SendHighSpeedMessage->m_nFlag1", &bPassed);

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
CheckIntervalConstraint(ptSendLowSpeedMessage->m_nNumberOfGears, 0, MAX_NUMBER_OF_LANDING_GEARS, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_nNumberOfGears", &bPassed);
//check value constraints for gear requested position
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_LANDING_GEARS; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct[uIndex], uIndex, 0, 100, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnGearRequestedPosition_pct", &bPassed);}

//check value constraints for number of flaps
CheckIntervalConstraint(ptSendLowSpeedMessage->m_nNumberOfFlaps, 0, MAX_NUMBER_OF_FLAPS, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_nNumberOfFlaps", &bPassed);
//check value constraints for flap requested position
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_FLAPS; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct[uIndex], uIndex, 0, 100, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnFlapRequestedPosition_pct", &bPassed);}

//check value constraints for number of speed brakes
CheckIntervalConstraint(ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes, 0, MAX_NUMBER_OF_SPEED_BRAKES, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_nNumberOfSpeedBrakes", &bPassed);
//check value constraints for speed brake requested position
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_SPEED_BRAKES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct[uIndex], uIndex, 0, 100, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct", &bPassed);}

//check value constraints for sea level pressure
CheckIntervalConstraint(ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg, 0.0f, 35.0f, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_fSeaLevelPressure_inHg", &bPassed);
//check value constraints for sea level temperature
CheckIntervalConstraint(ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf, -148.0f, 302.0f, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_fSeaLevelTemperature_degf", &bPassed);
//check value constraints for runway roughness
CheckIntervalConstraint(ptSendLowSpeedMessage->m_fRunwayRoughness, 0.0f, 10.0f, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_fRunwayRoughness", &bPassed);
//check value constraints for wind magnitude
CheckIntervalConstraint(ptSendLowSpeedMessage->m_fWindMagnitude_kts, 0.0f, 200.0f, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_fWindMagnitude_kts", &bPassed);
//check value constraints for wind heading
CheckIntervalConstraint(ptSendLowSpeedMessage->m_fWindHeading_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_fWindHeading_deg", &bPassed);
//check value constraints for wind inclination
CheckIntervalConstraint(ptSendLowSpeedMessage->m_fWindInclination_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_fWindInclination_deg", &bPassed);
//check value constraints for turbulence
CheckIntervalConstraint(ptSendLowSpeedMessage->m_fTurbulence, 0.0f, 10.0f, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_fTurbulence", &bPassed);
//check value constraints for payload weight
CheckValueConstraint(ptSendLowSpeedMessage->m_fPayloadWeight_lbs, 0.0f, , "SendLowSpeedMessage->m_fPayloadWeight_lbs", &bPassed);
//check value constraints for CG offset x

//check value constraints for CG offset y

//check value constraints for CG offset z

//check value constraints for number of engines
CheckIntervalConstraint(ptSendLowSpeedMessage->m_nNumberOfEngines, 0, MAX_NUMBER_OF_ENGINES, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_nNumberOfEngines", &bPassed);
//check value constraints for engine starter running
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnEngineStarterRunning[uIndex], uIndex, 0, 1, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnEngineStarterRunning", &bPassed);}

//check value constraints for bleed air
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnBleedAir[uIndex], uIndex, 0, 2, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnBleedAir", &bPassed);}

//check value constraints for ignition
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnIgnition[uIndex], uIndex, 0, 1, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnIgnition", &bPassed);}

//check value constraints for engine flags 1
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnEngineFlags1[uIndex], uIndex, 0, 31, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnEngineFlags1", &bPassed);}

//check value constraints for engine inlet state
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnEngineInletState[uIndex], uIndex, 0, 5, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnEngineInletState", &bPassed);}

//check value constraints for ice state engine
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
}

//check value constraints for engine failure flags
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckIntervalConstraintFromArrayIndex(ptSendLowSpeedMessage->m_pnEngineFailureFlags[uIndex], uIndex, 0, 65535, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_pnEngineFailureFlags", &bPassed);}

//check value constraints for number of propellers
CheckIntervalConstraint(ptSendLowSpeedMessage->m_nNumberOfPropellers, 0, MAX_NUMBER_OF_PROPELLERS, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_nNumberOfPropellers", &bPassed);
//check value constraints for ice states prop
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
}

//check value constraints for ice state right wing
CheckValueConstraint(ptSendLowSpeedMessage->m_fIceStateRightWing_in, 0.0f, , "SendLowSpeedMessage->m_fIceStateRightWing_in", &bPassed);
//check value constraints for ice state left wing
CheckValueConstraint(ptSendLowSpeedMessage->m_fIceStateLeftWing_in, 0.0f, , "SendLowSpeedMessage->m_fIceStateLeftWing_in", &bPassed);
//check value constraints for ice state fuselage
CheckValueConstraint(ptSendLowSpeedMessage->m_fIceStateFuselage_in, 0.0f, , "SendLowSpeedMessage->m_fIceStateFuselage_in", &bPassed);
//check value constraints for ice state tail
CheckValueConstraint(ptSendLowSpeedMessage->m_fIceStateTail_in, 0.0f, , "SendLowSpeedMessage->m_fIceStateTail_in", &bPassed);
//check value constraints for time multiplier
CheckValueConstraint(ptSendLowSpeedMessage->m_nTimeMultiplier, 0, , "SendLowSpeedMessage->m_nTimeMultiplier", &bPassed);
//check value constraints for failure flags 1
CheckIntervalConstraint(ptSendLowSpeedMessage->m_nFailureFlags1, 0, 16383, INTERVAL_TYPE_CLOSED, "SendLowSpeedMessage->m_nFailureFlags1", &bPassed);

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
CheckIntervalConstraint(ptEngineReposition->m_fPiston_rpm, 0.0f, 100000.0f, INTERVAL_TYPE_CLOSED, "EngineReposition->m_fPiston_rpm", &bPassed);
//check value constraints for n1
CheckIntervalConstraint(ptEngineReposition->m_fN1_pct, 0.0f, 100.0f, INTERVAL_TYPE_CLOSED, "EngineReposition->m_fN1_pct", &bPassed);
//check value constraints for n2
CheckIntervalConstraint(ptEngineReposition->m_fN2_pct, 0.0f, 100.0f, INTERVAL_TYPE_CLOSED, "EngineReposition->m_fN2_pct", &bPassed);

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
CheckIntervalConstraint(ptPropellerReposition->m_fPiston_rpm, 0.0f, 10000.0f, INTERVAL_TYPE_CLOSED, "PropellerReposition->m_fPiston_rpm", &bPassed);

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
CheckIntervalConstraint(ptSendRepositionMessage->m_nRepositionType, 0, 1, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_nRepositionType", &bPassed);
//check value constraints for latitude
CheckIntervalConstraint(ptSendRepositionMessage->m_dLatitude_deg, -90.0, 90.0, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_dLatitude_deg", &bPassed);
//check value constraints for longitude
CheckIntervalConstraint(ptSendRepositionMessage->m_dLongitude_deg, -180.0, 180.0, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_dLongitude_deg", &bPassed);
//check value constraints for MSL altitude

//check value constraints for magnetic heading
CheckIntervalConstraint(ptSendRepositionMessage->m_fMagneticHeading_deg, 0.0f, 360.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fMagneticHeading_deg", &bPassed);
//check value constraints for indicated airspeed

//check value constraints for aircraft pitch
CheckIntervalConstraint(ptSendRepositionMessage->m_fAircraftPitch_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fAircraftPitch_deg", &bPassed);
//check value constraints for aircraft roll
CheckIntervalConstraint(ptSendRepositionMessage->m_fAircraftRoll_deg, -360.0f, 360.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fAircraftRoll_deg", &bPassed);
//check value constraints for vertical speed
CheckIntervalConstraint(ptSendRepositionMessage->m_fVerticalSpeed_fpm, -100000.0f, 100000.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fVerticalSpeed_fpm", &bPassed);
//check value constraints for number of engines
CheckIntervalConstraint(ptSendRepositionMessage->m_nNumberOfEngines, 0, MAX_NUMBER_OF_ENGINES, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_nNumberOfEngines", &bPassed);
//check value constraints for engine
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckConstraintsOnEngineReposition(&ptSendRepositionMessage->m_ptEngine[uIndex]);
}

//check value constraints for number of propellers
CheckIntervalConstraint(ptSendRepositionMessage->m_nNumberOfPropellers, 0, MAX_NUMBER_OF_PROPELLERS, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_nNumberOfPropellers", &bPassed);
//check value constraints for propeller
uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
CheckConstraintsOnPropellerReposition(&ptSendRepositionMessage->m_ptPropeller[uIndex]);
}

//check value constraints for pitch flight control
CheckIntervalConstraint(ptSendRepositionMessage->m_fPitchFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fPitchFlightControl", &bPassed);
//check value constraints for roll flight control
CheckIntervalConstraint(ptSendRepositionMessage->m_fRollFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fRollFlightControl", &bPassed);
//check value constraints for yaw flight control
CheckIntervalConstraint(ptSendRepositionMessage->m_fYawFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fYawFlightControl", &bPassed);
//check value constraints for collective flight control
CheckIntervalConstraint(ptSendRepositionMessage->m_fCollectiveFlightControl, -1.0f, 1.0f, INTERVAL_TYPE_CLOSED, "SendRepositionMessage->m_fCollectiveFlightControl", &bPassed);

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

