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

#include "J2SendConstraints.h"  //implements decelerations
#include <stdioLib.h>           //USES: fprintf


/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendHighSpeedMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendHighSpeedMessage(const SendHighSpeedMessageT *const ptSendHighSpeedMessage)
{
//used for indexing over array data members
size_t uIndex = 0u;

//check value constraints for pitch flight control

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fPitchFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fPitchFlightControl",">= -1.0f",ptSendHighSpeedMessage->m_fPitchFlightControl);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fPitchFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fPitchFlightControl","<= 1.0f",ptSendHighSpeedMessage->m_fPitchFlightControl);
}

//check value constraints for roll flight control

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRollFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRollFlightControl",">= -1.0f",ptSendHighSpeedMessage->m_fRollFlightControl);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRollFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRollFlightControl","<= 1.0f",ptSendHighSpeedMessage->m_fRollFlightControl);
}

//check value constraints for yaw flight control

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fYawFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fYawFlightControl",">= -1.0f",ptSendHighSpeedMessage->m_fYawFlightControl);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fYawFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fYawFlightControl","<= 1.0f",ptSendHighSpeedMessage->m_fYawFlightControl);
}

//check value constraints for collective flight control

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fCollectiveFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fCollectiveFlightControl",">= -1.0f",ptSendHighSpeedMessage->m_fCollectiveFlightControl);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fCollectiveFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fCollectiveFlightControl","<= 1.0f",ptSendHighSpeedMessage->m_fCollectiveFlightControl);
}

//check value constraints for pitch trim position

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fPitchTrimPosition >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fPitchTrimPosition",">= -1.0f",ptSendHighSpeedMessage->m_fPitchTrimPosition);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fPitchTrimPosition <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fPitchTrimPosition","<= 1.0f",ptSendHighSpeedMessage->m_fPitchTrimPosition);
}

//check value constraints for roll trim position

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRollTrimPosition >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRollTrimPosition",">= -1.0f",ptSendHighSpeedMessage->m_fRollTrimPosition);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRollTrimPosition <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRollTrimPosition","<= 1.0f",ptSendHighSpeedMessage->m_fRollTrimPosition);
}

//check value constraints for yaw trim position

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fYawTrimPosition >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fYawTrimPosition",">= -1.0f",ptSendHighSpeedMessage->m_fYawTrimPosition);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fYawTrimPosition <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fYawTrimPosition","<= 1.0f",ptSendHighSpeedMessage->m_fYawTrimPosition);
}

//check value constraints for yaw serial actuators

uIndex = 0;
for(; uIndex < 2; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfYawSerialActuators[uIndex] >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfYawSerialActuators",uIndex,">= -1.0f",ptSendHighSpeedMessage->m_pfYawSerialActuators[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfYawSerialActuators[uIndex] <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfYawSerialActuators",uIndex,"<= 1.0f",ptSendHighSpeedMessage->m_pfYawSerialActuators[uIndex]);
}

}
//check value constraints for yaw trim actuators

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fYawTrimActuators >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fYawTrimActuators",">= -1.0f",ptSendHighSpeedMessage->m_fYawTrimActuators);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fYawTrimActuators <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fYawTrimActuators","<= 1.0f",ptSendHighSpeedMessage->m_fYawTrimActuators);
}

//check value constraints for roll serial actuators

uIndex = 0;
for(; uIndex < 2; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfRollSerialActuators[uIndex] >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfRollSerialActuators",uIndex,">= -1.0f",ptSendHighSpeedMessage->m_pfRollSerialActuators[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfRollSerialActuators[uIndex] <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfRollSerialActuators",uIndex,"<= 1.0f",ptSendHighSpeedMessage->m_pfRollSerialActuators[uIndex]);
}

}
//check value constraints for roll trim actuators

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRollTrimActuators >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRollTrimActuators",">= -1.0f",ptSendHighSpeedMessage->m_fRollTrimActuators);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRollTrimActuators <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRollTrimActuators","<= 1.0f",ptSendHighSpeedMessage->m_fRollTrimActuators);
}

//check value constraints for pitch serial actuators

uIndex = 0;
for(; uIndex < 2; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfPitchSerialActuators[uIndex] >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfPitchSerialActuators",uIndex,">= -1.0f",ptSendHighSpeedMessage->m_pfPitchSerialActuators[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfPitchSerialActuators[uIndex] <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfPitchSerialActuators",uIndex,"<= 1.0f",ptSendHighSpeedMessage->m_pfPitchSerialActuators[uIndex]);
}

}
//check value constraints for pitch trim actuators

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fPitchTrimActuators >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fPitchTrimActuators",">= -1.0f",ptSendHighSpeedMessage->m_fPitchTrimActuators);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fPitchTrimActuators <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fPitchTrimActuators","<= 1.0f",ptSendHighSpeedMessage->m_fPitchTrimActuators);
}

//check value constraints for collective serial actuators

uIndex = 0;
for(; uIndex < 2; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfCollectiveSerialActuators[uIndex] >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfCollectiveSerialActuators",uIndex,">= -1.0f",ptSendHighSpeedMessage->m_pfCollectiveSerialActuators[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfCollectiveSerialActuators[uIndex] <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfCollectiveSerialActuators",uIndex,"<= 1.0f",ptSendHighSpeedMessage->m_pfCollectiveSerialActuators[uIndex]);
}

}
//check value constraints for collective trim actuators

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fCollectiveTrimActuators >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fCollectiveTrimActuators",">= -1.0f",ptSendHighSpeedMessage->m_fCollectiveTrimActuators);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fCollectiveTrimActuators <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fCollectiveTrimActuators","<= 1.0f",ptSendHighSpeedMessage->m_fCollectiveTrimActuators);
}

//check value constraints for yaw control override flag

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nYawControlOverrideFlag >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nYawControlOverrideFlag",">= 0",ptSendHighSpeedMessage->m_nYawControlOverrideFlag);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nYawControlOverrideFlag <= 7)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nYawControlOverrideFlag","<= 7",ptSendHighSpeedMessage->m_nYawControlOverrideFlag);
}

//check value constraints for pitch control override flag

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nPitchControlOverrideFlag >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nPitchControlOverrideFlag",">= 0",ptSendHighSpeedMessage->m_nPitchControlOverrideFlag);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nPitchControlOverrideFlag <= 7)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nPitchControlOverrideFlag","<= 7",ptSendHighSpeedMessage->m_nPitchControlOverrideFlag);
}

//check value constraints for roll control override flag

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nRollControlOverrideFlag >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nRollControlOverrideFlag",">= 0",ptSendHighSpeedMessage->m_nRollControlOverrideFlag);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nRollControlOverrideFlag <= 7)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nRollControlOverrideFlag","<= 7",ptSendHighSpeedMessage->m_nRollControlOverrideFlag);
}

//check value constraints for collective control override flag

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nCollectiveControlOverrideFlag",">= 0",ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag <= 7)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nCollectiveControlOverrideFlag","<= 7",ptSendHighSpeedMessage->m_nCollectiveControlOverrideFlag);
}

//check value constraints for right brake

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRightBrake >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRightBrake",">= 0.0f",ptSendHighSpeedMessage->m_fRightBrake);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRightBrake <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRightBrake","<= 1.0f",ptSendHighSpeedMessage->m_fRightBrake);
}

//check value constraints for left brake

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fLeftBrake >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fLeftBrake",">= 0.0f",ptSendHighSpeedMessage->m_fLeftBrake);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fLeftBrake <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fLeftBrake","<= 1.0f",ptSendHighSpeedMessage->m_fLeftBrake);
}

//check value constraints for nose wheel control

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fNoseWheelControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fNoseWheelControl",">= -1.0f",ptSendHighSpeedMessage->m_fNoseWheelControl);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fNoseWheelControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fNoseWheelControl","<= 1.0f",ptSendHighSpeedMessage->m_fNoseWheelControl);
}

//check value constraints for rotor brake

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRotorBrake >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRotorBrake",">= 0.0f",ptSendHighSpeedMessage->m_fRotorBrake);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fRotorBrake <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fRotorBrake","<= 1.0f",ptSendHighSpeedMessage->m_fRotorBrake);
}

//check value constraints for winch flag

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nWinchFlag >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nWinchFlag",">= 0",ptSendHighSpeedMessage->m_nWinchFlag);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nWinchFlag <= 4)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nWinchFlag","<= 4",ptSendHighSpeedMessage->m_nWinchFlag);
}

//check value constraints for winch length

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fWinchLength_m >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fWinchLength_m",">= 0.0f",ptSendHighSpeedMessage->m_fWinchLength_m);
}

//check value constraints for winch payload mass

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_fWinchPayloadMass_kg >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendHighSpeedMessage->m_fWinchPayloadMass_kg",">= 0.0f",ptSendHighSpeedMessage->m_fWinchPayloadMass_kg);
}

//check value constraints for winch payload x

//check value constraints for winch payload y

//check value constraints for winch payload z

//check value constraints for hook flag

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nHookFlag >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nHookFlag",">= 0",ptSendHighSpeedMessage->m_nHookFlag);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nHookFlag <= 4)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nHookFlag","<= 4",ptSendHighSpeedMessage->m_nHookFlag);
}

//check value constraints for hook length

//check value constraints for hook payload mass

//check value constraints for hook payload x

//check value constraints for hook payload y

//check value constraints for hook payload z

//check value constraints for SAS Mode

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nSASMode >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nSASMode",">= 0",ptSendHighSpeedMessage->m_nSASMode);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nSASMode <= 7)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nSASMode","<= 7",ptSendHighSpeedMessage->m_nSASMode);
}

//check value constraints for height of terrain

//check value constraints for number of contact points

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfContactPoints >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfContactPoints",">= 0",ptSendHighSpeedMessage->m_nNumberOfContactPoints);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfContactPoints <= MAX_NUMBER_OF_CONTACT_LOCATIONS)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfContactPoints","<= MAX_NUMBER_OF_CONTACT_LOCATIONS",ptSendHighSpeedMessage->m_nNumberOfContactPoints);
}

//check value constraints for ground contact location

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_CONTACT_LOCATIONS; ++uIndex){
}
//check value constraints for number of engines

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfEngines >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfEngines",">= 0",ptSendHighSpeedMessage->m_nNumberOfEngines);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfEngines <= MAX_NUMBER_OF_ENGINES)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfEngines","<= MAX_NUMBER_OF_ENGINES",ptSendHighSpeedMessage->m_nNumberOfEngines);
}

//check value constraints for throttle

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfThrottle[uIndex] >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfThrottle",uIndex,">= 0.0f",ptSendHighSpeedMessage->m_pfThrottle[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfThrottle[uIndex] <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfThrottle",uIndex,"<= 1.0f",ptSendHighSpeedMessage->m_pfThrottle[uIndex]);
}

}
//check value constraints for mixture

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfMixture[uIndex] >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfMixture",uIndex,">= 0.0f",ptSendHighSpeedMessage->m_pfMixture[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfMixture[uIndex] <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfMixture",uIndex,"<= 1.0f",ptSendHighSpeedMessage->m_pfMixture[uIndex]);
}

}
//check value constraints for number of propellers

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfPropellers >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfPropellers",">= 0",ptSendHighSpeedMessage->m_nNumberOfPropellers);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfPropellers <= MAX_NUMBER_OF_PROPELLERS)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfPropellers","<= MAX_NUMBER_OF_PROPELLERS",ptSendHighSpeedMessage->m_nNumberOfPropellers);
}

//check value constraints for prop pitch

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfPropPitch_deg[uIndex] >= -180.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfPropPitch_deg",uIndex,">= -180.0f",ptSendHighSpeedMessage->m_pfPropPitch_deg[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfPropPitch_deg[uIndex] <= 180.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfPropPitch_deg",uIndex,"<= 180.0f",ptSendHighSpeedMessage->m_pfPropPitch_deg[uIndex]);
}

}
//check value constraints for number of tanks

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfTanks >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfTanks",">= 0",ptSendHighSpeedMessage->m_nNumberOfTanks);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nNumberOfTanks <= MAX_NUMBER_OF_FUEL_TANKS)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nNumberOfTanks","<= MAX_NUMBER_OF_FUEL_TANKS",ptSendHighSpeedMessage->m_nNumberOfTanks);
}

//check value constraints for fuel weight

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_FUEL_TANKS; ++uIndex){
//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfFuelWeight_lbs[uIndex] >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfFuelWeight_lbs",uIndex,">= 0.0f",ptSendHighSpeedMessage->m_pfFuelWeight_lbs[uIndex]);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_pfFuelWeight_lbs[uIndex] <= 4000.0f)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %f","SendHighSpeedMessage->m_pfFuelWeight_lbs",uIndex,"<= 4000.0f",ptSendHighSpeedMessage->m_pfFuelWeight_lbs[uIndex]);
}

}
//check value constraints for flag1

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nFlag1 >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nFlag1",">= 0",ptSendHighSpeedMessage->m_nFlag1);
}

//if the value constraint is not met
if (!(ptSendHighSpeedMessage->m_nFlag1 <= 7)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendHighSpeedMessage->m_nFlag1","<= 7",ptSendHighSpeedMessage->m_nFlag1);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendLowSpeedMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendLowSpeedMessage(const SendLowSpeedMessageT *const ptSendLowSpeedMessage)
{
//used for indexing over array data members
size_t uIndex = 0u;

//check value constraints for number of gears

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfGears >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfGears",">= 0",ptSendLowSpeedMessage->m_nNumberOfGears);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfGears <= MAX_NUMBER_OF_LANDING_GEARS)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfGears","<= MAX_NUMBER_OF_LANDING_GEARS",ptSendLowSpeedMessage->m_nNumberOfGears);
}

//check value constraints for gear requested position

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_LANDING_GEARS; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnGearRequestedPosition_pct",uIndex,">= 0",ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct[uIndex] <= 100)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnGearRequestedPosition_pct",uIndex,"<= 100",ptSendLowSpeedMessage->m_pnGearRequestedPosition_pct[uIndex]);
}

}
//check value constraints for number of flaps

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfFlaps >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfFlaps",">= 0",ptSendLowSpeedMessage->m_nNumberOfFlaps);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfFlaps <= MAX_NUMBER_OF_FLAPS)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfFlaps","<= MAX_NUMBER_OF_FLAPS",ptSendLowSpeedMessage->m_nNumberOfFlaps);
}

//check value constraints for flap requested position

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_FLAPS; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnFlapRequestedPosition_pct",uIndex,">= 0",ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct[uIndex] <= 100)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnFlapRequestedPosition_pct",uIndex,"<= 100",ptSendLowSpeedMessage->m_pnFlapRequestedPosition_pct[uIndex]);
}

}
//check value constraints for number of speed brakes

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfSpeedBrakes",">= 0",ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes <= MAX_NUMBER_OF_SPEED_BRAKES)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfSpeedBrakes","<= MAX_NUMBER_OF_SPEED_BRAKES",ptSendLowSpeedMessage->m_nNumberOfSpeedBrakes);
}

//check value constraints for speed brake requested position

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_SPEED_BRAKES; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct",uIndex,">= 0",ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct[uIndex] <= 100)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct",uIndex,"<= 100",ptSendLowSpeedMessage->m_pnSpeedBrakeRequestedPosition_pct[uIndex]);
}

}
//check value constraints for sea level pressure

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fSeaLevelPressure_inHg",">= 0.0f",ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg <= 35.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fSeaLevelPressure_inHg","<= 35.0f",ptSendLowSpeedMessage->m_fSeaLevelPressure_inHg);
}

//check value constraints for sea level temperature

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf >= -148.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fSeaLevelTemperature_degf",">= -148.0f",ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf <= 302.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fSeaLevelTemperature_degf","<= 302.0f",ptSendLowSpeedMessage->m_fSeaLevelTemperature_degf);
}

//check value constraints for runway roughness

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fRunwayRoughness >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fRunwayRoughness",">= 0.0f",ptSendLowSpeedMessage->m_fRunwayRoughness);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fRunwayRoughness <= 10.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fRunwayRoughness","<= 10.0f",ptSendLowSpeedMessage->m_fRunwayRoughness);
}

//check value constraints for wind magnitude

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fWindMagnitude_kts >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fWindMagnitude_kts",">= 0.0f",ptSendLowSpeedMessage->m_fWindMagnitude_kts);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fWindMagnitude_kts <= 200.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fWindMagnitude_kts","<= 200.0f",ptSendLowSpeedMessage->m_fWindMagnitude_kts);
}

//check value constraints for wind heading

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fWindHeading_deg >= -360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fWindHeading_deg",">= -360.0f",ptSendLowSpeedMessage->m_fWindHeading_deg);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fWindHeading_deg <= 360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fWindHeading_deg","<= 360.0f",ptSendLowSpeedMessage->m_fWindHeading_deg);
}

//check value constraints for wind inclination

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fWindInclination_deg >= -360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fWindInclination_deg",">= -360.0f",ptSendLowSpeedMessage->m_fWindInclination_deg);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fWindInclination_deg <= 360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fWindInclination_deg","<= 360.0f",ptSendLowSpeedMessage->m_fWindInclination_deg);
}

//check value constraints for turbulence

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fTurbulence >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fTurbulence",">= 0.0f",ptSendLowSpeedMessage->m_fTurbulence);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fTurbulence <= 10.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fTurbulence","<= 10.0f",ptSendLowSpeedMessage->m_fTurbulence);
}

//check value constraints for payload weight

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fPayloadWeight_lbs >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fPayloadWeight_lbs",">= 0.0f",ptSendLowSpeedMessage->m_fPayloadWeight_lbs);
}

//check value constraints for CG offset x

//check value constraints for CG offset y

//check value constraints for CG offset z

//check value constraints for number of engines

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfEngines >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfEngines",">= 0",ptSendLowSpeedMessage->m_nNumberOfEngines);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfEngines <= MAX_NUMBER_OF_ENGINES)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfEngines","<= MAX_NUMBER_OF_ENGINES",ptSendLowSpeedMessage->m_nNumberOfEngines);
}

//check value constraints for engine starter running

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineStarterRunning[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineStarterRunning",uIndex,">= 0",ptSendLowSpeedMessage->m_pnEngineStarterRunning[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineStarterRunning[uIndex] <= 1)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineStarterRunning",uIndex,"<= 1",ptSendLowSpeedMessage->m_pnEngineStarterRunning[uIndex]);
}

}
//check value constraints for bleed air

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnBleedAir[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnBleedAir",uIndex,">= 0",ptSendLowSpeedMessage->m_pnBleedAir[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnBleedAir[uIndex] <= 2)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnBleedAir",uIndex,"<= 2",ptSendLowSpeedMessage->m_pnBleedAir[uIndex]);
}

}
//check value constraints for ignition

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnIgnition[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnIgnition",uIndex,">= 0",ptSendLowSpeedMessage->m_pnIgnition[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnIgnition[uIndex] <= 1)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnIgnition",uIndex,"<= 1",ptSendLowSpeedMessage->m_pnIgnition[uIndex]);
}

}
//check value constraints for engine flags 1

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineFlags1[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineFlags1",uIndex,">= 0",ptSendLowSpeedMessage->m_pnEngineFlags1[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineFlags1[uIndex] <= 31)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineFlags1",uIndex,"<= 31",ptSendLowSpeedMessage->m_pnEngineFlags1[uIndex]);
}

}
//check value constraints for engine inlet state

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineInletState[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineInletState",uIndex,">= 0",ptSendLowSpeedMessage->m_pnEngineInletState[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineInletState[uIndex] <= 5)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineInletState",uIndex,"<= 5",ptSendLowSpeedMessage->m_pnEngineInletState[uIndex]);
}

}
//check value constraints for ice state engine

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
}
//check value constraints for engine failure flags

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineFailureFlags[uIndex] >= 0)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineFailureFlags",uIndex,">= 0",ptSendLowSpeedMessage->m_pnEngineFailureFlags[uIndex]);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_pnEngineFailureFlags[uIndex] <= 65535)){
//report the failed constraint
fprintf(stderr, "%s[%d] fails constraint (%s) with value %d","SendLowSpeedMessage->m_pnEngineFailureFlags",uIndex,"<= 65535",ptSendLowSpeedMessage->m_pnEngineFailureFlags[uIndex]);
}

}
//check value constraints for number of propellers

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfPropellers >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfPropellers",">= 0",ptSendLowSpeedMessage->m_nNumberOfPropellers);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nNumberOfPropellers <= MAX_NUMBER_OF_PROPELLERS)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nNumberOfPropellers","<= MAX_NUMBER_OF_PROPELLERS",ptSendLowSpeedMessage->m_nNumberOfPropellers);
}

//check value constraints for ice states prop

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
}
//check value constraints for ice state right wing

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fIceStateRightWing_in >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fIceStateRightWing_in",">= 0.0f",ptSendLowSpeedMessage->m_fIceStateRightWing_in);
}

//check value constraints for ice state left wing

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fIceStateLeftWing_in >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fIceStateLeftWing_in",">= 0.0f",ptSendLowSpeedMessage->m_fIceStateLeftWing_in);
}

//check value constraints for ice state fuselage

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fIceStateFuselage_in >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fIceStateFuselage_in",">= 0.0f",ptSendLowSpeedMessage->m_fIceStateFuselage_in);
}

//check value constraints for ice state tail

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_fIceStateTail_in >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendLowSpeedMessage->m_fIceStateTail_in",">= 0.0f",ptSendLowSpeedMessage->m_fIceStateTail_in);
}

//check value constraints for time multiplier

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nTimeMultiplier >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nTimeMultiplier",">= 0",ptSendLowSpeedMessage->m_nTimeMultiplier);
}

//check value constraints for failure flags 1

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nFailureFlags1 >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nFailureFlags1",">= 0",ptSendLowSpeedMessage->m_nFailureFlags1);
}

//if the value constraint is not met
if (!(ptSendLowSpeedMessage->m_nFailureFlags1 <= 16383)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendLowSpeedMessage->m_nFailureFlags1","<= 16383",ptSendLowSpeedMessage->m_nFailureFlags1);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptEngineReposition the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnEngineReposition(const EngineRepositionT *const ptEngineReposition)
{
//check value constraints for running

//check value constraints for piston

//if the value constraint is not met
if (!(ptEngineReposition->m_fPiston_rpm >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","EngineReposition->m_fPiston_rpm",">= 0.0f",ptEngineReposition->m_fPiston_rpm);
}

//if the value constraint is not met
if (!(ptEngineReposition->m_fPiston_rpm <= 100000.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","EngineReposition->m_fPiston_rpm","<= 100000.0f",ptEngineReposition->m_fPiston_rpm);
}

//check value constraints for n1

//if the value constraint is not met
if (!(ptEngineReposition->m_fN1_pct >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","EngineReposition->m_fN1_pct",">= 0.0f",ptEngineReposition->m_fN1_pct);
}

//if the value constraint is not met
if (!(ptEngineReposition->m_fN1_pct <= 100.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","EngineReposition->m_fN1_pct","<= 100.0f",ptEngineReposition->m_fN1_pct);
}

//check value constraints for n2

//if the value constraint is not met
if (!(ptEngineReposition->m_fN2_pct >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","EngineReposition->m_fN2_pct",">= 0.0f",ptEngineReposition->m_fN2_pct);
}

//if the value constraint is not met
if (!(ptEngineReposition->m_fN2_pct <= 100.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","EngineReposition->m_fN2_pct","<= 100.0f",ptEngineReposition->m_fN2_pct);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptPropellerReposition the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnPropellerReposition(const PropellerRepositionT *const ptPropellerReposition)
{
//check value constraints for piston

//if the value constraint is not met
if (!(ptPropellerReposition->m_fPiston_rpm >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","PropellerReposition->m_fPiston_rpm",">= 0.0f",ptPropellerReposition->m_fPiston_rpm);
}

//if the value constraint is not met
if (!(ptPropellerReposition->m_fPiston_rpm <= 10000.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","PropellerReposition->m_fPiston_rpm","<= 10000.0f",ptPropellerReposition->m_fPiston_rpm);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendRepositionMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendRepositionMessage(const SendRepositionMessageT *const ptSendRepositionMessage)
{
//used for indexing over array data members
size_t uIndex = 0u;

//check value constraints for reposition type

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_nRepositionType >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendRepositionMessage->m_nRepositionType",">= 0",ptSendRepositionMessage->m_nRepositionType);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_nRepositionType <= 1)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendRepositionMessage->m_nRepositionType","<= 1",ptSendRepositionMessage->m_nRepositionType);
}

//check value constraints for latitude

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_dLatitude_deg >= -90.0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_dLatitude_deg",">= -90.0",ptSendRepositionMessage->m_dLatitude_deg);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_dLatitude_deg <= 90.0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_dLatitude_deg","<= 90.0",ptSendRepositionMessage->m_dLatitude_deg);
}

//check value constraints for longitude

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_dLongitude_deg >= -180.0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_dLongitude_deg",">= -180.0",ptSendRepositionMessage->m_dLongitude_deg);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_dLongitude_deg <= 180.0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_dLongitude_deg","<= 180.0",ptSendRepositionMessage->m_dLongitude_deg);
}

//check value constraints for MSL altitude

//check value constraints for magnetic heading

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fMagneticHeading_deg >= 0.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fMagneticHeading_deg",">= 0.0f",ptSendRepositionMessage->m_fMagneticHeading_deg);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fMagneticHeading_deg <= 360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fMagneticHeading_deg","<= 360.0f",ptSendRepositionMessage->m_fMagneticHeading_deg);
}

//check value constraints for indicated airspeed

//check value constraints for aircraft pitch

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fAircraftPitch_deg >= -360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fAircraftPitch_deg",">= -360.0f",ptSendRepositionMessage->m_fAircraftPitch_deg);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fAircraftPitch_deg <= 360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fAircraftPitch_deg","<= 360.0f",ptSendRepositionMessage->m_fAircraftPitch_deg);
}

//check value constraints for aircraft roll

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fAircraftRoll_deg >= -360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fAircraftRoll_deg",">= -360.0f",ptSendRepositionMessage->m_fAircraftRoll_deg);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fAircraftRoll_deg <= 360.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fAircraftRoll_deg","<= 360.0f",ptSendRepositionMessage->m_fAircraftRoll_deg);
}

//check value constraints for vertical speed

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fVerticalSpeed_fpm >= -100000.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fVerticalSpeed_fpm",">= -100000.0f",ptSendRepositionMessage->m_fVerticalSpeed_fpm);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fVerticalSpeed_fpm <= 100000.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fVerticalSpeed_fpm","<= 100000.0f",ptSendRepositionMessage->m_fVerticalSpeed_fpm);
}

//check value constraints for number of engines

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_nNumberOfEngines >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendRepositionMessage->m_nNumberOfEngines",">= 0",ptSendRepositionMessage->m_nNumberOfEngines);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_nNumberOfEngines <= MAX_NUMBER_OF_ENGINES)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendRepositionMessage->m_nNumberOfEngines","<= MAX_NUMBER_OF_ENGINES",ptSendRepositionMessage->m_nNumberOfEngines);
}

//check value constraints for engine

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_ENGINES; ++uIndex){
CheckConstraintsOnEngineReposition(&ptSendRepositionMessage->m_ptEngine[uIndex]);
}
//check value constraints for number of propellers

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_nNumberOfPropellers >= 0)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendRepositionMessage->m_nNumberOfPropellers",">= 0",ptSendRepositionMessage->m_nNumberOfPropellers);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_nNumberOfPropellers <= MAX_NUMBER_OF_PROPELLERS)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %d","SendRepositionMessage->m_nNumberOfPropellers","<= MAX_NUMBER_OF_PROPELLERS",ptSendRepositionMessage->m_nNumberOfPropellers);
}

//check value constraints for propeller

uIndex = 0;
for(; uIndex < MAX_NUMBER_OF_PROPELLERS; ++uIndex){
CheckConstraintsOnPropellerReposition(&ptSendRepositionMessage->m_ptPropeller[uIndex]);
}
//check value constraints for pitch flight control

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fPitchFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fPitchFlightControl",">= -1.0f",ptSendRepositionMessage->m_fPitchFlightControl);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fPitchFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fPitchFlightControl","<= 1.0f",ptSendRepositionMessage->m_fPitchFlightControl);
}

//check value constraints for roll flight control

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fRollFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fRollFlightControl",">= -1.0f",ptSendRepositionMessage->m_fRollFlightControl);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fRollFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fRollFlightControl","<= 1.0f",ptSendRepositionMessage->m_fRollFlightControl);
}

//check value constraints for yaw flight control

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fYawFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fYawFlightControl",">= -1.0f",ptSendRepositionMessage->m_fYawFlightControl);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fYawFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fYawFlightControl","<= 1.0f",ptSendRepositionMessage->m_fYawFlightControl);
}

//check value constraints for collective flight control

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fCollectiveFlightControl >= -1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fCollectiveFlightControl",">= -1.0f",ptSendRepositionMessage->m_fCollectiveFlightControl);
}

//if the value constraint is not met
if (!(ptSendRepositionMessage->m_fCollectiveFlightControl <= 1.0f)){
//report the failed constraint
fprintf(stderr, "%s fails constraint (%s) with value %f","SendRepositionMessage->m_fCollectiveFlightControl","<= 1.0f",ptSendRepositionMessage->m_fCollectiveFlightControl);
}


}

/**
 * @brief if a broken value constraint is triggered, the data is most likely in a state that does not make sense according to the ICD.
 *         The value should either be adjusted, or the constraint should be modified
 * @param[in] ptSendVersionRequestMessage the data type whose member variables will be checked against value constraints
 */
void CheckConstraintsOnSendVersionRequestMessage(const SendVersionRequestMessageT *const ptSendVersionRequestMessage)
{
//check value constraints for empty


}

///@}

