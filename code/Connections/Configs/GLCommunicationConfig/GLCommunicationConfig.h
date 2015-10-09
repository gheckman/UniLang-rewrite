/**
*    @file
*
*    @author Joe Meyers
*    @author Trevor Hickey
*
*    @note GL Communication Config Interface
*
*    @brief GL Studios Connection Configuration
*
*    @details IP addresses and port numbers
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
*    @addtogroup Connections
*    @{
*/

#ifndef GLCommunicationConfigH
#define GLCommunicationConfigH



#ifndef GL1_IP_ADDRESS
#define GL1_IP_ADDRESS "172.31.1.10"
#endif

#ifndef GL2_IP_ADDRESS
#define GL2_IP_ADDRESS "172.31.1.11"
#endif

#ifndef GL1_APPLICATION_SEND_PORT_NUMBER
#define GL1_APPLICATION_SEND_PORT_NUMBER 49000
#endif

#ifndef GL1_SRNS_SEND_PORT_NUMBER
#define GL1_SRNS_SEND_PORT_NUMBER 49100
#endif

#ifndef GL2_SEND_PORT_NUMBER
#define GL2_SEND_PORT_NUMBER 49000
#endif

#ifndef GL1_APPLICATION_RECEIVE_PORT_NUMBER
#define GL1_APPLICATION_RECEIVE_PORT_NUMBER 49085
#endif

#ifndef GL1_SRNS_RECEIVE_PORT_NUMBER
#define GL1_SRNS_RECEIVE_PORT_NUMBER 48090
#endif

#ifndef GL2_RECEIVE_PORT_NUMBER
#define GL2_RECEIVE_PORT_NUMBER 49086
#endif


#endif /* GLCommunicationConfigH */

///@}
