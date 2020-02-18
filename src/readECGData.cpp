#include "readECGData.h"

readECGData::readECGData(RingbufHandle_t &_buffer)
{
    dataLock = xSemaphoreCreateMutex();
    adas1000 = new ADAS1000();
    format = DIGITAL;

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
}

void readECGData::loop()
{
    while (1)
    {
    }
}