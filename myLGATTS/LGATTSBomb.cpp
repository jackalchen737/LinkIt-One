#include "vmbtgatt.h"
#include "LGATTSBomb.h"


static LGATTServiceInfo g_bomb_decl[] =
{
    {TYPE_SERVICE, "0000AAAF-0000-1000-8000-00805F9B34FB", TRUE, 0, 0, 0},
    {TYPE_CHARACTERISTIC, "0000AAA1-0000-1000-8000-00805F9B34FB", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0},
    {TYPE_DESCRIPTOR, "00002901-0000-1000-8000-00805f9b34fb", FALSE, VM_GATT_CHAR_PROP_READ, VM_GATT_CHAR_PROP_READ, 0},
    {TYPE_END, 0, 0, 0, 0, 0}
};


LGATTServiceInfo *LGATTSBomb::onLoadService(int32_t index)
{
    return g_bomb_decl;
}

// characteristic added
boolean LGATTSBomb::onCharacteristicAdded(LGATTAttributeData &data)
{
    const VM_BT_UUID *uuid = &(data.uuid);
    APP_LOG("LGATTBomb::onCharacteristicAdded f[%d] uuid[12] = [0x%x] len[%d]", data.failed, uuid->uuid[12], uuid->len);
    
    if (!data.failed)
    {
        if (0xA1 == uuid->uuid[12])
        {
            _handle_control_bomb_char = data.handle;
        }
        
    }
    return true;
}

// characteristic added
boolean LGATTSBomb::onDescriptorAdded(LGATTAttributeData &data)
{
    const VM_BT_UUID *uuid = &(data.uuid);
    APP_LOG("LGATTBomb::ononDescriptorAdded f[%d] uuid[12] = [0x%x] len[%d]", data.failed, uuid->uuid[12], uuid->len);
    
    if (!data.failed)
    {
        if (0x01 == uuid->uuid[12])
        {
            _handle_control_bomb_char_description = data.handle;
        }
    }
    return true;
}


// connected or disconnected
boolean LGATTSBomb::onConnection(const LGATTAddress &addr, boolean connected)
{
    _connected = connected;
    APP_LOG("LGATTSBomb::onConnection connected [%d], [%x:%x:%x:%x:%x:%x]", _connected, 
        addr.addr[5], addr.addr[4], addr.addr[3], addr.addr[2], addr.addr[1], addr.addr[0]);

    return true;
}

// read action comming from master
boolean LGATTSBomb::onRead(LGATTReadRequest &data)
{
    APP_LOG("LGATTSUart::onRead _connected [%d]", _connected);
    if (_connected)
    {
        if(data.attr_handle == _handle_control_bomb_char_description)
        {
            LGATTAttributeValue value = {0};
            const char *str = "Bomb Control";
            memcpy(value.value, str, strlen(str));
            value.len = strlen(str);
            
            APP_LOG("LGATTSUart::onRead onRead [%d][%s]", value.len, value.value);
            
            data.ackOK(value);
        }
        else
        {
            data.ackFail();
        }
    }
    return true;
}

#define sendAckOk(data) (!data.need_rsp) ? : data.ackOK()
#define sendAckFail(data) (!data.need_rsp) ? : data.ackFail()

// write action comming from master
boolean LGATTSBomb::onWrite(LGATTWriteRequest &data)
{
    APP_LOG("LGATTSUart::onWrite _connected [%d]", _connected);
    // todo read UART data.
    if (_connected)
    {
        if(data.attr_handle == _handle_control_bomb_char)
        {
            APP_LOG("central data on peripheral rx[%d][%d]", data.value.value[0], data.value.len);
            
            // if need to rsp to central.
            if(data.value.len != 1)
            {
                sendAckFail(data);
            }
            else
            {
                sendAckOk(data);
                uint8_t bomb_control = data.value.value[0];
                
                switch(bomb_control)
                {
                    case 0:
                        APP_LOG("get control code 0");
                        sendAckOk(data);
                        break;
                    case 1:
                        APP_LOG("get control code 1");
                        sendAckOk(data);
                        break;
                    case 2:
                        APP_LOG("get control code 2");
                        sendAckOk(data);
                        break;
                    case 3:
                        APP_LOG("get control code 3");
                        sendAckOk(data);
                        break;
                    case 4:
                        APP_LOG("get control code 4");
                        sendAckOk(data);
                        break;
                    case 5:
                        APP_LOG("get control code 5");
                        sendAckOk(data);
                        break;
                    default:
                        sendAckFail(data);
                }
            }
        }
        else
        {
            sendAckFail(data);
        }
    }
    return true;
}





