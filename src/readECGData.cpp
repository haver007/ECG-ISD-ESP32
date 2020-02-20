#include "readECGData.h"

readECGData::readECGData(RingbufHandle_t &_buffer)
{
    dataLock = xSemaphoreCreateMutex();
    adas1000 = new ADAS1000(18,19,23,5);
    format = DIGITAL;
    Serial.begin(9600);

    // xSemaphoreTake(dataLock);//Lock
    // xSemaphoreGive(dataLock);//Free
}

readECGData::~readECGData()
{
    
}

void readECGData::initialize(int divider)
{
    adas1000->setECGCTL_SoftwareReset();
    adas1000->setECGCTL_PowerOnEnabled(true);
    adas1000->setRegisterValue(ADAS1000_FRMCTL,0x1234);

    Serial.printf("ADAS1000_CMREFCTL %x\n", adas1000->getRegisterValue(ADAS1000_CMREFCTL));
	Serial.printf("ADAS1000_FILTCTL %x\n", adas1000->getRegisterValue(ADAS1000_FILTCTL));
	Serial.printf("ADAS1000_ECGCTL %x\n", adas1000->getRegisterValue(ADAS1000_ECGCTL));
	Serial.printf("ADAS1000_FRMCTL %x\n", adas1000->getRegisterValue(ADAS1000_FRMCTL));
	Serial.printf("ADAS1000_TESTTONE %x\n", adas1000->getRegisterValue(ADAS1000_TESTTONE));
    adas1000->setECGCTL_ADCConversionEnabled(true);
    adas1000->setECGCTL_ChannelLAEnabled(true);
    adas1000->setECGCTL_ChannelLLEnabled(true);
    adas1000->setECGCTL_ChannelRAEnabled(true);
    adas1000->setECGCTL_HighPerformance2MSPS();
    adas1000->setECGCTL_VREFBufferEnabled(true);
    adas1000->setECGCTL_MasterMode();
    adas1000->setECGCTL_DifferentialInput();

    adas1000->setFRMCTL_DataLeadIEnabled(false);
    adas1000->setFRMCTL_DataLeadIIEnabled(false);
    adas1000->setFRMCTL_DataLeadIIIEnabled(false);
    adas1000->setFRMCTL_DataLeadV1Enabled(false);
    adas1000->setFRMCTL_DataLeadV2Enabled(false);
    adas1000->setFRMCTL_PaceDetectionEnabled(false);
    adas1000->setFRMCTL_RespirationMagnitudeEnabled(false);
    adas1000->setFRMCTL_RespirationPhaseEnabled(false);
    adas1000->setFRMCTL_CRCWordEnabled(false);
    adas1000->setFRMCTL_GPIOWordEnabled(false);
    adas1000->setFRMCTL_LeadOffStatusEnabled(false);
    adas1000->setFRMCTL_DigitalFormat();
    adas1000->setFRMCTL_ReadyRepeatEnabled(true);

    adas1000->setCMREFCTL_ShieldDriveEnabled(true);
    adas1000->setCMREFCTL_RightLegDriveEnabled(true);
    adas1000->setCMREFCTL_CommonModeIsDrivenOutEnabled(true);

    switch (divider)
    {
    case 1:
        adas1000->setFRMCTL_SkipNoneFrame();
        break;
    case 2:
        adas1000->setFRMCTL_Skip2thFrame();
        break;
    case 4:
        adas1000->setFRMCTL_Skip4thFrame();
        break;

    default:
        adas1000->setFRMCTL_SkipNoneFrame();
        break;
    }

    //DEBUG   
    adas1000->setFRMCTL_DataLeadIEnabled(true);
    Serial.printf("ADAS1000_CMREFCTL %x\n", adas1000->getRegisterValue(ADAS1000_CMREFCTL));
	Serial.printf("ADAS1000_FILTCTL %x\n", adas1000->getRegisterValue(ADAS1000_FILTCTL));
	Serial.printf("ADAS1000_ECGCTL %x\n", adas1000->getRegisterValue(ADAS1000_ECGCTL));
	Serial.printf("ADAS1000_FRMCTL %x\n", adas1000->getRegisterValue(ADAS1000_FRMCTL));
	Serial.printf("ADAS1000_TESTTONE %x\n", adas1000->getRegisterValue(ADAS1000_TESTTONE));
     
}

void readECGData::loop()
{
        Serial.println("Test");
    while (1)
    {
  uint8_t dataBuffer[4] = { 0,0,0,0 };
	do{
		bool drdy = true;
		while (drdy)
		{
			adas1000->readFrame(dataBuffer);
			drdy = dataBuffer[0] & 0x40;
		}

	} while (dataBuffer[0] & 0x80);

	uint32_t data = (dataBuffer[1] << 16) + (dataBuffer[2] << 8) + dataBuffer[3];

    //Serial.println("Test");
    //Serial.println(adas1000->voltageConversion(data, format));
    }
}