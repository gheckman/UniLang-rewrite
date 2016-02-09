/* vxbMethodDecl.h - VxBus driver method forward declarations */

/*
 * Copyright (C) 2007-2011 Wind River Systems, Inc.
 * All rights reserved.
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 *  DO NOT MODIFY THIS FILE MANUALLY
 *
 *  This file is automatically generated from
 *  the contents of target/src/hwif/methods *.c.
 *
 *  To build this file, change directory
 *  to target/src/hwif/methods and run:
 *       make vxbMethodDecl.h
 *
 */

METHOD_DECL(busCtlrAccessOverride);
METHOD_DECL(busCtlrBaseAddrCvt);
METHOD_DECL(busCtlrCfgInfo);
METHOD_DECL(busCtlrCfgRead);
METHOD_DECL(busCtlrCfgWrite);
METHOD_DECL(busCtlrDevCfgRead);
METHOD_DECL(busCtlrDevCfgWrite);
METHOD_DECL(busCtlrDevCtlr);
METHOD_DECL(busCtlrInterruptInfo);
METHOD_DECL(busCtlrMmuAttr);
METHOD_DECL(busDevShow);
METHOD_DECL(busMemAlloc);
METHOD_DECL(busMEMIOAlloc);
METHOD_DECL(busMemShow);
METHOD_DECL(driverControl);
METHOD_DECL(driver_unload);
METHOD_DECL(instParamModify);
METHOD_DECL(isrRerouteNotify);
METHOD_DECL(ixPciBoardInit);
METHOD_DECL(ixPciIntAck);
METHOD_DECL(ixPciIntGet);
METHOD_DECL(ixpSioChanReset);
METHOD_DECL(m512xFifoAlloc);
METHOD_DECL(m85xxLawBarAlloc);
METHOD_DECL(m85xxLawBarAllocSet);
METHOD_DECL(m85xxLawBarSet);
METHOD_DECL(m85xxWindowAlloc);
METHOD_DECL(miiConnectionModify);
METHOD_DECL(miiLpiModeGet);
METHOD_DECL(miiMediaUpdate);
METHOD_DECL(miiModeGet);
METHOD_DECL(miiModeSet);
METHOD_DECL(miiRead);
METHOD_DECL(miiWrite);
METHOD_DECL(mux2DevConnect);
METHOD_DECL(muxDevConnect);
METHOD_DECL(nonVolGet);
METHOD_DECL(nonVolSet);
METHOD_DECL(paramArraySet);
METHOD_DECL(paramListSet);
METHOD_DECL(pwrStateSet);
METHOD_DECL(qeCpcrCommand);
METHOD_DECL(qeMultiUserRamAlloc);
METHOD_DECL(qeMultiUserRamFree);
METHOD_DECL(qeMultiUserRamOffsetGet);
METHOD_DECL(qeThreadAlloc);
METHOD_DECL(qeThreadFree);
METHOD_DECL(QorIQLawAlloc);
METHOD_DECL(QorIQLawFind);
METHOD_DECL(QorIQLawFree);
METHOD_DECL(sharedMemSupportAPIGet);
METHOD_DECL(sioChanConnect);
METHOD_DECL(sioChanGet);
METHOD_DECL(sysBspDevFilter);
METHOD_DECL(vxbApmQmanFuncGet);
METHOD_DECL(armGicIntBaseGet);
METHOD_DECL(armGicIntDataShow);
METHOD_DECL(armGicIntLvlChg);
METHOD_DECL(armGicIntLvlDisable);
METHOD_DECL(armGicIntLvlEnable);
METHOD_DECL(armGicIntLvlVecAck);
METHOD_DECL(armGicIntLvlVecChk);
METHOD_DECL(vxbDevIntCapabCheck);
METHOD_DECL(vxbDevRegMap);
METHOD_DECL(vxbDmaBufMapCreate);
METHOD_DECL(vxbDmaBufMapDestroy);
METHOD_DECL(vxbDmaBufMapMemAlloc);
METHOD_DECL(vxbDmaBufMapMemFree);
METHOD_DECL(vxbDmaBufTagGet);
METHOD_DECL(vxbDmaResDedicatedGet);
METHOD_DECL(vxbDmaResourceGet);
METHOD_DECL(vxbDmaResourceRelease);
METHOD_DECL(vxbDrvUnlink);
METHOD_DECL(ebGicIntBaseGet);
METHOD_DECL(ebGicIntDataShow);
METHOD_DECL(ebGicIntLvlChg);
METHOD_DECL(ebGicIntLvlDisable);
METHOD_DECL(ebGicIntLvlEnable);
METHOD_DECL(ebGicIntLvlVecAck);
METHOD_DECL(ebGicIntLvlVecChk);
METHOD_DECL(vxbEepromInfoGet);
METHOD_DECL(vxbFlashChipInfoGet);
METHOD_DECL(vxbI2cBusDevShow);
METHOD_DECL(vxbI2cControlGet);
METHOD_DECL(vxbIntCtlrAck); 
METHOD_DECL(vxbIntCtlrAlloc);
METHOD_DECL(vxbIntCtlrConnect);
METHOD_DECL(vxbIntCtlrCpuAvail);
METHOD_DECL(vxbIntCtlrCpuCheck);
METHOD_DECL(vxbIntCtlrCpuDisable);
METHOD_DECL(vxbIntCtlrCpuReroute);
METHOD_DECL(vxbIntCtlrDisable); 
METHOD_DECL(vxbIntCtlrDisconnect);
METHOD_DECL(vxbIntCtlrEnable); 
METHOD_DECL(vxbIntCtlrFree);
METHOD_DECL(vxbIntCtlrIntReroute);
METHOD_DECL(vxbIntLevelGet);
METHOD_DECL(vxbIntDynaVecAlloc);
METHOD_DECL(vxbIntDynaVecConnect);
METHOD_DECL(vxbIntDynaVecDisable);
METHOD_DECL(vxbIntDynaVecEnable);
METHOD_DECL(vxbIntDynaVecErase);
METHOD_DECL(vxbIntDynaVecGet);
METHOD_DECL(vxbIntDynaVecMultiConnect);
METHOD_DECL(vxbIntDynaVecDevMultiProgram);
METHOD_DECL(vxbIntDynaVecOwnerFind);
METHOD_DECL(vxbIntDynaVecProgram);
METHOD_DECL(ioApicIntrBaseGet);
METHOD_DECL(ioApicIntrDataShow);
METHOD_DECL(ioApicIntrIdGet);
METHOD_DECL(ioApicIntrIntDisable);
METHOD_DECL(ioApicIntrIntEnable);
METHOD_DECL(ioApicIntrIntLock);
METHOD_DECL(ioApicIntrIntUnlock);
METHOD_DECL(ioApicIntrRedGet);
METHOD_DECL(ioApicIntrRedSet);
METHOD_DECL(ioApicIntrVersionGet);
METHOD_DECL(ioApicRedNumEntriesGet);
METHOD_DECL(loApicIntrBaseGet);
METHOD_DECL(loApicIntrEnable);
METHOD_DECL(loApicIntrInitAP);
METHOD_DECL(loApicIntrIntLock);
METHOD_DECL(loApicIntrIntUnlock);
METHOD_DECL(loApicIntrIpi);
METHOD_DECL(loApicIntrShow);
METHOD_DECL(mpApicAddrTableGet);
METHOD_DECL(mpApicBusTableGet);
METHOD_DECL(mpApicCpuIndexTableGet);
METHOD_DECL(mpApicDataShow);
METHOD_DECL(mpApicFpsGet);
METHOD_DECL(mpApicInterruptTableGet);
METHOD_DECL(mpApicloBaseGet);
METHOD_DECL(mpApicLogicalTableGet);
METHOD_DECL(mpApicLoIndexTableGet);
METHOD_DECL(mpApicNbusGet);
METHOD_DECL(mpApicNioApicGet);
METHOD_DECL(mpApicNiointGet);
METHOD_DECL(mpApicNlointGet);
METHOD_DECL(vxbMsgApiGet);
METHOD_DECL(vxbRapidIoCtlrInfoGet);
METHOD_DECL(vxbRtcFuncGet);
METHOD_DECL(sdBusCtlrInterruptInfo);
METHOD_DECL(vxbSdSpecInfoGet);
METHOD_DECL(vxbSpiControlGet);
METHOD_DECL(vxbSpiSpecialGet);
METHOD_DECL(vxbTimerFuncGet);
METHOD_DECL(vxbTimerNumberGet);
METHOD_DECL(vxbXbdDevCreate);
METHOD_DECL(vxFmnControlGet);
METHOD_DECL(vxIpiControlGet);