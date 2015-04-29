#ifndef __LGATT_BOMB_H__
#define __LGATT_BOMB_H__

#include "LGATTServer.h"


#ifdef APP_LOG
#undef APP_LOG
#endif

#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
    Serial.println();


class LGATTSBomb : public LGATTService
{
public:
    boolean isConnected(){ return _connected; };
protected:
    // prepare the data for profile
    virtual LGATTServiceInfo *onLoadService(int32_t index);
    // characteristic added
    virtual boolean onCharacteristicAdded(LGATTAttributeData &data);
    // descriptor added
    virtual boolean onDescriptorAdded(LGATTAttributeData &data);
    // connected or disconnected
    virtual boolean onConnection(const LGATTAddress &addr, boolean connected);
    // read action comming from master
    virtual boolean onRead(LGATTReadRequest &data);
    // write action comming from master
    virtual boolean onWrite(LGATTWriteRequest &data);
private:
    uint16_t _handle_control_bomb_char;
    uint16_t _handle_control_bomb_char_description;
    boolean _connected;
};

#endif
