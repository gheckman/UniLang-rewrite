/**
*    @file
*
*    @author Trevor Hickey
*
*    @note J2 Send Constraints Implementation
*
*    @brief brief
*
*    @details details
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

#include "J2SendConstraints.h"  //implements decelerations


/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendToJ2Messages the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendToJ2Messages(const SendToJ2MessagesT *const ptSendToJ2Messages)
{

}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendHighSpeedMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendHighSpeedMessage(const SendHighSpeedMessageT *const ptSendHighSpeedMessage)
{
if (!(ptSendHighSpeedMessage->m_fPitchFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fPitchFlightControl",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fPitchFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fPitchFlightControl","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRollFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRollFlightControl",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRollFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRollFlightControl","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fYawFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fYawFlightControl",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fYawFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fYawFlightControl","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fCollectiveFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fCollectiveFlightControl",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fCollectiveFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fCollectiveFlightControl","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fPitchTrimPosition >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fPitchTrimPosition",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fPitchTrimPosition <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fPitchTrimPosition","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRollTrimPosition >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRollTrimPosition",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRollTrimPosition <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRollTrimPosition","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fYawTrimPosition >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fYawTrimPosition",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fYawTrimPosition <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fYawTrimPosition","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfYawSerialActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfYawSerialActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfYawSerialActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfYawSerialActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fYawTrimActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fYawTrimActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fYawTrimActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fYawTrimActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfRollSerialActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfRollSerialActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfRollSerialActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfRollSerialActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRollTrimActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRollTrimActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRollTrimActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRollTrimActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfPitchSerialActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfPitchSerialActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfPitchSerialActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfPitchSerialActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fPitchTrimActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fPitchTrimActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fPitchTrimActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fPitchTrimActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfCollectiveSerialActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfCollectiveSerialActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfCollectiveSerialActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfCollectiveSerialActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fCollectiveTrimActuators >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fCollectiveTrimActuators",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fCollectiveTrimActuators <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fCollectiveTrimActuators","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nYawControlOverrideFlag >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nYawControlOverrideFlag",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nYawControlOverrideFlag <= 7)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nYawControlOverrideFlag","<= 7",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nPitchControlOverrideFlag >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nPitchControlOverrideFlag",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nPitchControlOverrideFlag <= 7)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nPitchControlOverrideFlag","<= 7",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nRollControlOverrideFlag >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nRollControlOverrideFlag",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nRollControlOverrideFlag <= 7)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nRollControlOverrideFlag","<= 7",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nCollectiveControlOverrideFlag",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag <= 7)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nCollectiveControlOverrideFlag","<= 7",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRightBrake >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRightBrake",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRightBrake <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRightBrake","<= 1",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fLeftBrake >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fLeftBrake",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fLeftBrake <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fLeftBrake","<= 1",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fNoseWheelControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fNoseWheelControl",">= -1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fNoseWheelControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fNoseWheelControl","<= 1.0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRotorBrake >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRotorBrake",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fRotorBrake <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fRotorBrake","<= 1",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nWinchFlag >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nWinchFlag",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nWinchFlag <= 4)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nWinchFlag","<= 4",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fWinchLength_m >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fWinchLength_m",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_fWinchPayloadMass_kg >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_fWinchPayloadMass_kg",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nHookFlag >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nHookFlag",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nHookFlag <= 4)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nHookFlag","<= 4",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nSASMode >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nSASMode",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nSASMode <= 7)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nSASMode","<= 7",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfContactPoints >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfContactPoints",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfContactPoints <= MAX_NUMBER_OF_CONTACT_LOCATIONS)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfContactPoints","<= MAX_NUMBER_OF_CONTACT_LOCATIONS",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfEngines >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfEngines",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfEngines <= MAX_NUMBER_OF_ENGINES)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfEngines","<= MAX_NUMBER_OF_ENGINES",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfThrottle >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfThrottle",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfThrottle <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfThrottle","<= 1",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfMixture >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfMixture",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfMixture <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfMixture","<= 1",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfPropellers >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfPropellers",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfPropellers <= MAX_NUMBER_OF_PROPELLERS)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfPropellers","<= MAX_NUMBER_OF_PROPELLERS",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfPropPitch_deg >= 180)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfPropPitch_deg",">= 180",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfPropPitch_deg <= -180)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfPropPitch_deg","<= -180",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfTanks >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfTanks",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nNumberOfTanks <= MAX_NUMBER_OF_FUEL_TANKS)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nNumberOfTanks","<= MAX_NUMBER_OF_FUEL_TANKS",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfFuelWeight_lbs >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfFuelWeight_lbs",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_pfFuelWeight_lbs <= 4000)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendHighSpeedMessage->m_pfFuelWeight_lbs","<= 4000",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nFlag1 >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nFlag1",">= 0",SendHighSpeedMessage);
}

if (!(ptSendHighSpeedMessage->m_nFlag1 <= 7)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendHighSpeedMessage->m_nFlag1","<= 7",SendHighSpeedMessage);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendLowSpeedMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendLowSpeedMessage(const SendLowSpeedMessageT *const ptSendLowSpeedMessage)
{
if (!(ptSendLowSpeedMessage->m_nNumberOfGears >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfGears",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfGears <= MAX_NUMBER_OF_LANDING_GEARS)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfGears","<= MAX_NUMBER_OF_LANDING_GEARS",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnGearRequestedPosition_pct",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct <= 100)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnGearRequestedPosition_pct","<= 100",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfFlaps >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfFlaps",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfFlaps <= MAX_NUMBER_OF_FLAPS)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfFlaps","<= MAX_NUMBER_OF_FLAPS",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnFlapRequestedPosition_pct",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct <= 100)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnFlapRequestedPosition_pct","<= 100",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfSpeedBrakes",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes <= MAX_NUMBER_OF_SPEED_BRAKES)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfSpeedBrakes","<= MAX_NUMBER_OF_SPEED_BRAKES",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct <= 100)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct","<= 100",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fSeaLevelPressure_inHg",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg <= 35)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fSeaLevelPressure_inHg","<= 35",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf >= -148)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fSeaLevelTemperature_degf",">= -148",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf <= 302)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fSeaLevelTemperature_degf","<= 302",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fRunwayRoughness >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fRunwayRoughness",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fRunwayRoughness <= 10)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fRunwayRoughness","<= 10",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fWindMagnitude_kts >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fWindMagnitude_kts",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fWindMagnitude_kts <= 200)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fWindMagnitude_kts","<= 200",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fWindHeading_deg >= -360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fWindHeading_deg",">= -360",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fWindHeading_deg <= 360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fWindHeading_deg","<= 360",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fWindInclination_deg >= -360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fWindInclination_deg",">= -360",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fWindInclination_deg <= 360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fWindInclination_deg","<= 360",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fTurbulence >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fTurbulence",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fTurbulence <= 10)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fTurbulence","<= 10",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fPayloadWeight_lbs > 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fPayloadWeight_lbs","> 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfEngines >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfEngines",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfEngines <= MAX_NUMBER_OF_ENGINES)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfEngines","<= MAX_NUMBER_OF_ENGINES",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineStarterRunning >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineStarterRunning",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineStarterRunning <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineStarterRunning","<= 1",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnBleedAir >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnBleedAir",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnBleedAir <= 2)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnBleedAir","<= 2",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnIgnition >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnIgnition",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnIgnition <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnIgnition","<= 1",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineFlags1 >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineFlags1",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineFlags1 <= 31)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineFlags1","<= 31",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineInletState >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineInletState",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineInletState <= 5)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineInletState","<= 5",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineFailureFlags >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineFailureFlags",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_pnEngineFailureFlags <= 65535)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_pnEngineFailureFlags","<= 65535",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfPropellers >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfPropellers",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nNumberOfPropellers <= MAX_NUMBER_OF_PROPELLERS)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nNumberOfPropellers","<= MAX_NUMBER_OF_PROPELLERS",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fIceStateRightWing_in >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fIceStateRightWing_in",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fIceStateLeftWing_in >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fIceStateLeftWing_in",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fIceStateFuselage_in >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fIceStateFuselage_in",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_fIceStateTail_in >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendLowSpeedMessage->m_fIceStateTail_in",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nTimeMultiplier >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nTimeMultiplier",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nFailureFlags1 >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nFailureFlags1",">= 0",SendLowSpeedMessage);
}

if (!(ptSendLowSpeedMessage->m_nFailureFlags1 <= 16383)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendLowSpeedMessage->m_nFailureFlags1","<= 16383",SendLowSpeedMessage);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptEngineReposition the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnEngineReposition(const EngineRepositionT *const ptEngineReposition)
{
if (!(ptEngineReposition->m_fPiston_rpm >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"EngineReposition->m_fPiston_rpm",">= 0",EngineReposition);
}

if (!(ptEngineReposition->m_fPiston_rpm <= 100000)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"EngineReposition->m_fPiston_rpm","<= 100000",EngineReposition);
}

if (!(ptEngineReposition->m_fN1_pct >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"EngineReposition->m_fN1_pct",">= 0",EngineReposition);
}

if (!(ptEngineReposition->m_fN1_pct <= 100)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"EngineReposition->m_fN1_pct","<= 100",EngineReposition);
}

if (!(ptEngineReposition->m_fN2_pct >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"EngineReposition->m_fN2_pct",">= 0",EngineReposition);
}

if (!(ptEngineReposition->m_fN2_pct <= 100)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"EngineReposition->m_fN2_pct","<= 100",EngineReposition);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptPropellerReposition the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnPropellerReposition(const PropellerRepositionT *const ptPropellerReposition)
{
if (!(ptPropellerReposition->m_fPiston_rpm >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"PropellerReposition->m_fPiston_rpm",">= 0",PropellerReposition);
}

if (!(ptPropellerReposition->m_fPiston_rpm <= 10000)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"PropellerReposition->m_fPiston_rpm","<= 10000",PropellerReposition);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendRepositionMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendRepositionMessage(const SendRepositionMessageT *const ptSendRepositionMessage)
{
if (!(ptSendRepositionMessage->m_nRepositionType >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendRepositionMessage->m_nRepositionType",">= 0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_nRepositionType <= 1)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendRepositionMessage->m_nRepositionType","<= 1",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_dLatitude_deg >= -90)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_dLatitude_deg",">= -90",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_dLatitude_deg <= 90)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_dLatitude_deg","<= 90",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_dLongitude_deg >= -180)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_dLongitude_deg",">= -180",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_dLongitude_deg <= 180)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_dLongitude_deg","<= 180",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fMagneticHeading_deg >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fMagneticHeading_deg",">= 0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fMagneticHeading_deg <= 360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fMagneticHeading_deg","<= 360",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fAircraftPitch_deg >= -360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fAircraftPitch_deg",">= -360",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fAircraftPitch_deg <= 360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fAircraftPitch_deg","<= 360",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fAircraftRoll_deg >= -360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fAircraftRoll_deg",">= -360",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fAircraftRoll_deg <= 360)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fAircraftRoll_deg","<= 360",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fVerticalSpeed_fpm >= -100000)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fVerticalSpeed_fpm",">= -100000",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fVerticalSpeed_fpm <= 100000)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fVerticalSpeed_fpm","<= 100000",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_nNumberOfEngines >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendRepositionMessage->m_nNumberOfEngines",">= 0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_nNumberOfEngines <= MAX_NUMBER_OF_ENGINES)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendRepositionMessage->m_nNumberOfEngines","<= MAX_NUMBER_OF_ENGINES",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_nNumberOfPropellers >= 0)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendRepositionMessage->m_nNumberOfPropellers",">= 0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_nNumberOfPropellers <= MAX_NUMBER_OF_PROPELLERS)){
fprintf(stderr, "%s fails constraint (%s) with value %d,"SendRepositionMessage->m_nNumberOfPropellers","<= MAX_NUMBER_OF_PROPELLERS",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fPitchFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fPitchFlightControl",">= -1.0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fPitchFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fPitchFlightControl","<= 1.0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fRollFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fRollFlightControl",">= -1.0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fRollFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fRollFlightControl","<= 1.0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fYawFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fYawFlightControl",">= -1.0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fYawFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fYawFlightControl","<= 1.0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fCollectiveFlightControl >= -1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fCollectiveFlightControl",">= -1.0",SendRepositionMessage);
}

if (!(ptSendRepositionMessage->m_fCollectiveFlightControl <= 1.0)){
fprintf(stderr, "%s fails constraint (%s) with value %f,"SendRepositionMessage->m_fCollectiveFlightControl","<= 1.0",SendRepositionMessage);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendVersionRequestMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendVersionRequestMessage(const SendVersionRequestMessageT *const ptSendVersionRequestMessage)
{

}

///@}

