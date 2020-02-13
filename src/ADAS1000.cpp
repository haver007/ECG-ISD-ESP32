// 
// 
// 

#include "ADAS1000.h"

ADAS1000::ADAS1000()
{
}

void ADAS1000::setRegisterValue(uint8_t regAddr, uint32_t regVal)
{
	uint8_t writeCommand[4] = {0,0,0,0};
	writeCommand[0] = 0x80 + regAddr;
	writeCommand[1] = ((regVal & 0xFF0000) >> 16);
	writeCommand[2] = ((regVal & 0x00FF00) >> 8);
	writeCommand[3] = ((regVal & 0x0000FF) >> 0);
	spidev.write(writeCommand, 4);
}

void ADAS1000::setRegisterValue(uint32_t regVal)
{
	uint8_t writeCommand[4] = {0,0,0,0};
	writeCommand[0] = (((0x800000 + regVal) & 0xFF000000) >> 24);
	writeCommand[1] = ((regVal & 0x00FF0000) >> 16);
	writeCommand[2] = ((regVal & 0x0000FF00) >> 8);
	writeCommand[3] = ((regVal & 0x000000FF) >> 0);
	spidev.write(writeCommand, 4);
}

void ADAS1000::readFrame(uint8_t * dataBuffer)
{
	uint8_t readData[4] = { 0x40, 0x00, 0x00, 0x00 };
	spidev.read(readData,dataBuffer, 4);
}

uint32_t ADAS1000::getRegisterValue(uint8_t regAddr)
{
	uint8_t readCommand[4] = {0,0,0,0};
	uint8_t readData[4] = {0, 0, 0, 0};
	readCommand[0] = regAddr;
	spidev.write(readCommand, 4);
	spidev.read(readData, 4);
	return
		((uint32_t)readData[1] << 16) +
		((uint32_t)readData[2] << 8) +
		((uint32_t)readData[3] << 0);
}

void ADAS1000::setFRMCTL_DataLeadIEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_LEAD_I_LADIS, !enabled);
}

void ADAS1000::setFRMCTL_DataLeadIIEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_LEAD_II_LLDIS, !enabled);
}

void ADAS1000::setFRMCTL_DataLeadIIIEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_LEAD_III_RADIS, !enabled);
}

void ADAS1000::setFRMCTL_DataLeadV1Enabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_V1DIS, !enabled);
}

void ADAS1000::setFRMCTL_DataLeadV2Enabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_V2DIS, !enabled);
}

void ADAS1000::setFRMCTL_PaceDetectionEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_PACEDIS, !enabled);
}

void ADAS1000::setFRMCTL_RespirationMagnitudeEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_RESPMDIS, !enabled);
}

void ADAS1000::setFRMCTL_RespirationPhaseEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_RESPPHDIS, !enabled);
}

void ADAS1000::setFRMCTL_LeadOffStatusEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_LOFFDIS, !enabled);
}

void ADAS1000::setFRMCTL_GPIOWordEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_GPIODIS, !enabled);
}

void ADAS1000::setFRMCTL_CRCWordEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_CRCDIS, !enabled);
}

void ADAS1000::setFRMCTL_ReadyRepeatEnabled(bool enabled)
{
	writeBit(ADAS1000_FRMCTL, ADAS1000_FRMCTL_RDYRPT, enabled);
}

void ADAS1000::setFRMCTL_ElectrodeFormat(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_DATAFMT, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_FRMCTL_DATAFMT_ELECTRODE);
}

void ADAS1000::setFRMCTL_DigitalFormat(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_DATAFMT, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_FRMCTL_DATAFMT_DIGITAL);
}

void ADAS1000::setFRMCTL_SkipNoneFrame(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_SKIP, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FRMCTL_SKIP_NONE_FRAME);
}

void ADAS1000::setFRMCTL_Skip2thFrame(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_SKIP, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FRMCTL_SKIP_2TH_FRAME);
}

void ADAS1000::setFRMCTL_Skip4thFrame(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_SKIP, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FRMCTL_SKIP_4TH_FRAME);
}

void ADAS1000::setFRMCTL_DataRate128kHz(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_DATARATE, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FRMCTL_FRMRATE_128KHZ);
}

void ADAS1000::setFRMCTL_DataRate16kHz(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_DATARATE, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FRMCTL_FRMRATE_16KHZ);
}

void ADAS1000::setFRMCTL_DataRate2kHz(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_DATARATE, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FRMCTL_FRMRATE_2KHZ);
}

void ADAS1000::setFRMCTL_DataRate31Hz(void)
{
	writeBits(ADAS1000_FRMCTL, ADAS1000_FRMCTL_DATARATE, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FRMCTL_FRMRATE_31_25HZ);
}

void ADAS1000::setTESTTONE_LAEnabled(bool enabled)
{
	writeBit(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONLA, enabled);
}

void ADAS1000::setTESTTONE_LLEnabled(bool enabled)
{
	writeBit(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONLL, enabled);
}

void ADAS1000::setTESTTONE_RAEnabled(bool enabled)
{
	writeBit(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONRA, enabled);
}

void ADAS1000::setTESTTONE_V1Enabled(bool enabled)
{
	writeBit(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONV1, enabled);
}

void ADAS1000::setTESTTONE_V2Enabled(bool enabled)
{
	writeBit(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONV2, enabled);
}

void ADAS1000::setTESTTONE_SineWave150Hz(void)
{
	writeBits(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONTYPE, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_TESTTONE_TONTYPE_SIN_WAVE_150HZ);
}

void ADAS1000::setTESTTONE_SineWave10Hz(void)
{
	writeBits(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONTYPE, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_TESTTONE_TONTYPE_SIN_WAVE_10HZ);
}

void ADAS1000::setTESTTONE_SquareWave1Hz(void)
{
	writeBits(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONTYPE, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_TESTTONE_TONTYPE_SQUARE_WAVE_1HZ);
}

void ADAS1000::setTESTTONE_External(void)
{
	writeBits(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONINT, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_TESTTONE_TONINT_INTERNAL);
}

void ADAS1000::setTESTTONE_Internal(void)
{
	writeBits(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONINT, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_TESTTONE_TONINT_INTERNAL);
}

void ADAS1000::setTESTTONE_OutPutEnabled(bool enabled)
{
	writeBit(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONOUT, enabled);
}

void ADAS1000::setTESTTONE_ModeEnabled(bool enabled)
{
	writeBit(ADAS1000_TESTTONE, ADAS1000_TESTTONE_TONEN, enabled);
}

void ADAS1000::setECGCTL_ChannelLAEnabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_LAEN, enabled);
}

void ADAS1000::setECGCTL_ChannelLLEnabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_LLEN, enabled);
}

void ADAS1000::setECGCTL_ChannelRAEnabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_RAEN, enabled);
}

void ADAS1000::setECGCTL_ChannelV1Enabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_V1EN, enabled);
}

void ADAS1000::setECGCTL_ChannelV2Enabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_V2EN, enabled);
}

void ADAS1000::setECGCTL_SingleEndedInput(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_CHCONFIG, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_CHCONFIG_SINGLE_ENDED_INPUT);
}

void ADAS1000::setECGCTL_DifferentialInput(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_CHCONFIG, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_CHCONFIG_DIFFERENTIAL_INPUT);
}

void ADAS1000::setECGCTL_Gain0(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_GAIN, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_ECGCTL_GAIN_GAIN0);
}

void ADAS1000::setECGCTL_Gain1(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_GAIN, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_ECGCTL_GAIN_GAIN1);
}

void ADAS1000::setECGCTL_Gain2(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_GAIN, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_ECGCTL_GAIN_GAIN2);
}

void ADAS1000::setECGCTL_Gain3(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_GAIN, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_ECGCTL_GAIN_GAIN3);
}

void ADAS1000::setECGCTL_VREFBufferEnabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_VREFBUF, enabled);
}

void ADAS1000::setECGCTL_CrystalOscillatorXTAL(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_CLKEXT, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_CLKEXT_XTAL);
}

void ADAS1000::setECGCTL_ExternalClock(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_CLKEXT, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_CLKEXT_CLK_IO);
}

void ADAS1000::setECGCTL_SingleChannelMode(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_GANG, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_GANG_SINGLECHANNELMODE);
}

void ADAS1000::setECGCTL_GangMode(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_GANG, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_GANG_GANGMODE);
}

void ADAS1000::setECGCTL_MasterMode(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_MASTER, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_MASTER_MASTER);
}

void ADAS1000::setECGCTL_SlaveMode(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_MASTER, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_MASTER_SLAVE);
}

void ADAS1000::setECGCTL_LowPower1MSPS(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_HP, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_HP_1MSPS);
}

void ADAS1000::setECGCTL_HighPerformance2MSPS(void)
{
	writeBits(ADAS1000_ECGCTL, ADAS1000_ECGCTL_HP, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_ECGCTL_HP_2MSPS);
}

void ADAS1000::setECGCTL_ADCConversionEnabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_CNVEN, enabled);
}

void ADAS1000::setECGCTL_PowerOnEnabled(bool enabled)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_PWREN, enabled);
}

void ADAS1000::setECGCTL_SoftwareReset(void)
{
	writeBit(ADAS1000_ECGCTL, ADAS1000_ECGCTL_SWRST, true);
	writeBit(ADAS1000_NOP, 0, 0);
}

void ADAS1000::setCMREFCTL_LAContributesToCommonModeEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_LACM, enabled);
}

void ADAS1000::setCMREFCTL_LLContributesToCommonModeEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_LLCM, enabled);
}

void ADAS1000::setCMREFCTL_RAContributesToCommonModeEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RACM, enabled);
}

void ADAS1000::setCMREFCTL_V1ContributesToCommonModeEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_V1CM, enabled);
}

void ADAS1000::setCMREFCTL_V2ContributesToCommonModeEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_V2CM, enabled);
}

void ADAS1000::setCMREFCTL_LAContributesToRLDEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_LARLD, enabled);
}

void ADAS1000::setCMREFCTL_LLContributesToRLDEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_LLRLD, enabled);
}

void ADAS1000::setCMREFCTL_RAContributesToRLDEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RARLD, enabled);
}

void ADAS1000::setCMREFCTL_V1ContributesToRLDEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_V1RLD, enabled);
}

void ADAS1000::setCMREFCTL_V2ContributesToRLDEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_V2RLD, enabled);
}

void ADAS1000::setCMREFCTL_CEContributesToRLDEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_CERLD, enabled);
}

void ADAS1000::setCMREFCTL_CommonElectrodeEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_CEREFEN, enabled);
}

void ADAS1000::setCMREFCTL_RLDOUTReferenceDrive(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RLDSEL, ADAS1000_BITS_LENGTH_OF_FOUR, ADAS1000_CMREFCTL_RLDSEL_RLD_OUT);
}

void ADAS1000::setCMREFCTL_LAReferenceDrive(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RLDSEL, ADAS1000_BITS_LENGTH_OF_FOUR, ADAS1000_CMREFCTL_RLDSEL_LA);
}

void ADAS1000::setCMREFCTL_LLReferenceDrive(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RLDSEL, ADAS1000_BITS_LENGTH_OF_FOUR, ADAS1000_CMREFCTL_RLDSEL_LL);
}

void ADAS1000::setCMREFCTL_RAReferenceDrive(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RLDSEL, ADAS1000_BITS_LENGTH_OF_FOUR, ADAS1000_CMREFCTL_RLDSEL_RA);
}

void ADAS1000::setCMREFCTL_V1ReferenceDrive(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RLDSEL, ADAS1000_BITS_LENGTH_OF_FOUR, ADAS1000_CMREFCTL_RLDSEL_V1);
}

void ADAS1000::setCMREFCTL_V2ReferenceDrive(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RLDSEL, ADAS1000_BITS_LENGTH_OF_FOUR, ADAS1000_CMREFCTL_RLDSEL_V2);
}

void ADAS1000::setCMREFCTL_CommonModeIsDrivenOutEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_DRVCM, enabled);
}

void ADAS1000::setCMREFCTL_InternalCommonMode(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_EXTCM, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_CMREFCTL_EXTCM_Internal);
}

void ADAS1000::setCMREFCTL_ExternalCommonMode(void)
{
	writeBits(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_EXTCM, ADAS1000_BITS_LENGTH_OF_ONE, ADAS1000_CMREFCTL_EXTCM_External);
}

void ADAS1000::setCMREFCTL_RightLegDriveEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_RLD_EN, enabled);
}

void ADAS1000::setCMREFCTL_ShieldDriveEnabled(bool enabled)
{
	writeBit(ADAS1000_CMREFCTL, ADAS1000_CMREFCTL_SHLDEN, enabled);
}

void ADAS1000::setFILTCTL_2kHNotchFilterForSPIMasterEnabled(bool enabled)
{
	writeBit(ADAS1000_FILTCTL, ADAS1000_FILTCTL_MN2K, enabled);
}

void ADAS1000::setFILTCTL_2kHNotchFilterEnabled(bool enabled)
{
	writeBit(ADAS1000_FILTCTL, ADAS1000_FILTCTL_N2KBP, enabled);
}

void ADAS1000::setFILTCTL_40HzLowPassFilter(void)
{
	writeBits(ADAS1000_FILTCTL, ADAS1000_FILTCTL_LPF, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FILTCTL_LPF_40HZ);
}

void ADAS1000::setFILTCTL_150HzLowPassFilter(void)
{
	writeBits(ADAS1000_FILTCTL, ADAS1000_FILTCTL_LPF, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FILTCTL_LPF_150HZ);
}

void ADAS1000::setFILTCTL_250HzLowPassFilter(void)
{
	writeBits(ADAS1000_FILTCTL, ADAS1000_FILTCTL_LPF, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FILTCTL_LPF_250HZ);
}

void ADAS1000::setFILTCTL_450HzLowPassFilter(void)
{
	writeBits(ADAS1000_FILTCTL, ADAS1000_FILTCTL_LPF, ADAS1000_BITS_LENGTH_OF_TWO, ADAS1000_FILTCTL_LPF_450HZ);
}

float ADAS1000::voltageConversion(uint32_t data, Leadformat format)
{
	float ecgVoltage = 0;

	if (format == DIGITAL) {

		if (data> 8388608) {
			ecgVoltage = ((4 * ECG_VREFF*(-(16777216 - data)) / ECG_GAIN) / (16777215));
		}
		else {
			ecgVoltage = ((4 * ECG_VREFF*data) / ECG_GAIN) / (16777215);
		}
	}
	else if (format == ELECTRODE) {
		ecgVoltage = (2 * data*(ECG_VREFF / ECG_GAIN)) / (16777215);
	}

	return ecgVoltage;
}

void ADAS1000::writeBit(uint32_t regAddr, uint32_t bitStart, bool enabled)
{
	uint32_t regValue = getRegisterValue(regAddr);
	uint32_t newRegValue = (enabled) ? (regValue | bitStart) : (regValue & ~bitStart);
	setRegisterValue(regAddr, newRegValue);
}


void ADAS1000::writeBits(uint32_t regAddr, uint32_t bitStart, uint32_t length, uint32_t data)
{
	uint32_t regValue = getRegisterValue(regAddr);
	uint32_t mask = ((1 << length) - 1) << (log2(bitStart) - length + 1);
	data <<= (log2(bitStart) - length + 1);
	data &= mask;
	regValue &= ~(mask);
	regValue |= data;
	setRegisterValue(regAddr, regValue);
}

uint32_t ADAS1000::log2(uint32_t number) const
{
	return (number > 1) ? 1 + log2(number / 2) : 0;
}

ADAS1000::~ADAS1000()
{
}
