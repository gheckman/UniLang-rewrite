/**
*    @file
*
*    @author Trevor Hickey
*
*    @note Electrical Malfunctions Data
*
*    @brief electrical malfunctions
*
*    @details Derived from the malfunctions Excel sheet
*             ??s equal the ?? marks in the document.
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
*    @addtogroup Electrical Malfunctions
*    @{
*/

#ifndef ElectricalMalfunctionsH
#define ElectricalMalfunctionsH




#ifdef __cplusplus
extern "C"
{
#endif /* #ifdef __cplusplus */

/**
 * @brief Electrical Malfunctions
 * @details The internal state of the component
 */
typedef struct ElectricalMalfunctions_t
{

    /**
     * @brief Batt relay fails open
     * @details BAT DISCON caution advisory on CAD
     */
BOOL m_bBatteryRelayFails;


    /**
     * @brief Bus Tie 1 Fails Open
     * @details No load sharing possible BUSTIE OPEN caution indication and battery will not be charged
     */
BOOL m_bBusTie1FailsOpen;


    /**
     * @brief Bus Tie 2 Fails Open
     * @details No load sharing possible BUSTIE OPEN caution indication and battery will not be charged
     */
BOOL m_bBusTie2FailsOpen;


    /**
     * @brief malfunction on battery bus
     * @details ??
     */
BOOL m_bCircuitBatteryBus;


    /**
     * @brief Starter/Generator 1 temperature high
     * @details amp range=?
     */
BOOL m_bGenerator1StarterGeneratorOverheat;


    /**
     * @brief Starter/Generator 2 temperature high
     * @details amp range=?
     */
BOOL m_bGenerator2StarterGeneratorOverheat;


    /**
     * @brief Respective generator is disconnected from the power distribution system
     * @details If one generator has failed, both non-essential buses are disconnected.
     *          If both generators are failed both non-essential buses and both shed buses are disconnected.
     *          BATT DISCH warning illuminated.
     */
BOOL m_bGenerator1StarterGeneratorFail;


    /**
     * @brief Respective generator is disconnected from the power distribution system
     * @details If one generator has failed, both non-essential buses are disconnected.
     *          If both generators are failed both non-essential buses and both shed buses are disconnected.
     *          BATT DISCH warning illuminated.
     */
BOOL m_bGenerator2StarterGeneratorFail;


    /**
     * @brief Over voltage causes the generator to go offline.
     * @details GEN DISCON caution indicated
     *          +0 to +10? Vdc
     */
BOOL m_bGenerator1StarterGeneratorOvervoltage;


    /**
     * @brief Over voltage causes the generator to go offline.
     * @details GEN DISCON caution indicated
     *          +0 to +10? Vdc
     */
BOOL m_bGenerator2StarterGeneratorOvervoltage;


    /**
     * @brief Electrical short circuit causes buss voltage to drop below 12 volts.
     * @details Short circuit on the affected bus.
     *          Power supply is interrupted to effected bus, shed bus and both non-essential bus systems.
     *          Power supply is guaranteed to unaffected main bus and both essential buses.
     */
BOOL m_bShortCircuitMainBus1;


    /**
     * @brief Electrical short circuit causes buss voltage to drop below 12 volts.
     * @details Short circuit on the affected bus.
     *          Power supply is interrupted to effected bus, shed bus and both non-essential bus systems.
     *          Power supply is guaranteed to unaffected main bus and both essential buses.
     */
BOOL m_bShortCircuitMainBus2;

} ElectricalMalfunctionsT;


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* ElectricalMalfunctionsH */

///@}

