#include "readECGData.h"
#include <iomanip>

readECGData::readECGData(RingbufHandle_t _buffer)
{
    dataLock = xSemaphoreCreateMutex();
    adas1000 = new ADAS1000(22, 26, 21, 17);
    format = DIGITAL;
    buffer = _buffer;
    Serial.begin(9600);
    pinMode(27, INPUT);
    String globalData = "";

    // xSemaphoreTake(dataLock);//Lock
    // xSemaphoreGive(dataLock);//Free
}

readECGData::~readECGData()
{
}

void readECGData::initialize(int divider)
{
//    adas1000->setECGCTL_SoftwareReset();
//     adas1000->setECGCTL_PowerOnEnabled(true);

//     Serial.printf("ADAS1000_FILTCTL %x\n", adas1000->getRegisterValue(ADAS1000_FILTCTL));
//     Serial.printf("ADAS1000_ECGCTL %x\n", adas1000->getRegisterValue(ADAS1000_ECGCTL));
//     Serial.printf("ADAS1000_FRMCTL %x\n", adas1000->getRegisterValue(ADAS1000_FRMCTL));
//     Serial.printf("ADAS1000_TESTTONE %x\n", adas1000->getRegisterValue(ADAS1000_TESTTONE));
//     adas1000->setECGCTL_ADCConversionEnabled(true);
//     adas1000->setECGCTL_ChannelLAEnabled(true);
//     adas1000->setECGCTL_ChannelLLEnabled(true);
//     adas1000->setECGCTL_ChannelRAEnabled(true);
//     adas1000->setECGCTL_HighPerformance2MSPS();
//     adas1000->setECGCTL_VREFBufferEnabled(true);
//     adas1000->setECGCTL_MasterMode();
//     adas1000->setECGCTL_DifferentialInput();
//     adas1000->setECGCTL_Gain3();//Finn

//     adas1000->setFRMCTL_DataLeadIEnabled(true);
//     adas1000->setFRMCTL_DataLeadIIEnabled(true);
//     adas1000->setFRMCTL_DataLeadIIIEnabled(true);
//     adas1000->setFRMCTL_DataLeadV1Enabled(false);
//     adas1000->setFRMCTL_DataLeadV2Enabled(false);
//     adas1000->setFRMCTL_PaceDetectionEnabled(false);
//     adas1000->setFRMCTL_RespirationMagnitudeEnabled(false);
//     adas1000->setFRMCTL_RespirationPhaseEnabled(false);
//     adas1000->setFRMCTL_CRCWordEnabled(false);
//     adas1000->setFRMCTL_GPIOWordEnabled(false);
//     adas1000->setFRMCTL_LeadOffStatusEnabled(false);
//     adas1000->setFRMCTL_DigitalFormat();
//     adas1000->setFRMCTL_ReadyRepeatEnabled(false);
//     adas1000->setFRMCTL_DataRate2kHz();

//     adas1000->setCMREFCTL_LAContributesToCommonModeEnabled(true); //From Finn
//     adas1000->setCMREFCTL_LLContributesToCommonModeEnabled(true); //From Finn
//     adas1000->setCMREFCTL_RAContributesToCommonModeEnabled(true); //From Finn
//     adas1000->setCMREFCTL_ShieldDriveEnabled(true);
//     adas1000->setCMREFCTL_RightLegDriveEnabled(true);
//     adas1000->setCMREFCTL_CommonModeIsDrivenOutEnabled(true);

//     adas1000->setFILTCTL_250HzLowPassFilter();

//     switch (divider){
//     case 1:
//         adas1000->setFRMCTL_SkipNoneFrame();
//         break;
//     case 2:
//         adas1000->setFRMCTL_Skip2thFrame();
//         break;
//     case 4:
//         adas1000->setFRMCTL_Skip4thFrame();
//         break;

//     default:
//         adas1000->setFRMCTL_SkipNoneFrame();
//         break;
//   }

    //DEBUG
    Serial.printf("ADAS1000_CMREFCTL %x\n", adas1000->getRegisterValue(ADAS1000_CMREFCTL));
    Serial.printf("ADAS1000_FILTCTL %x\n", adas1000->getRegisterValue(ADAS1000_FILTCTL));
    Serial.printf("ADAS1000_ECGCTL %x\n", adas1000->getRegisterValue(ADAS1000_ECGCTL));
    Serial.printf("ADAS1000_FRMCTL %x\n", adas1000->getRegisterValue(ADAS1000_FRMCTL));
    Serial.printf("ADAS1000_TESTTONE %x\n", adas1000->getRegisterValue(ADAS1000_TESTTONE));
    delay(5000);
}

void readECGData::loop()
{

    
    std::ostringstream ss;
    while (1)
    {
        vTaskDelay(50);
        if (true)//digitalRead(27)==0)
        {    
        
        uint8_t dataBuffer[4] = {0, 0, 0, 0};
        adas1000->readFrame(dataBuffer);
        uint32_t data = (dataBuffer[0] << 24) + (dataBuffer[1] << 16) + (dataBuffer[2] << 8) + dataBuffer[3];
        //Serial.printf("%x \n",data);
        switch ((data & 0xFF000000) >> 24)
        {
        case 0x11:
            ss << std::fixed << std::setprecision(10) << adas1000->voltageConversion(data & 0x00FFFFFF, format) << ",";
            break;
        case 0x12:
            ss << std::fixed << std::setprecision(10) << adas1000->voltageConversion(data & 0x00FFFFFF, format) << ",";
            break;
        case 0x13:
            ss << std::fixed << std::setprecision(10) << adas1000->voltageConversion(data & 0x00FFFFFF, format) << "";
            break;
        case 0xb0:
            ss << std::endl;
           // Serial.printf("%s", ss.str().c_str());
            xRingbufferSend(buffer, ss.str().c_str(), ss.str().length() + 1, 100);
            ss.clear();
            break;
        }
         }
    }
}
