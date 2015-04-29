#include "LGATTSBomb.h"
#include <LGATTUUID.h>

#ifdef APP_LOG
#undef APP_LOG
#endif

#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
    Serial.println();

LGATTSBomb bomb;

void setup() {
  // put your setup code here, to run once:
  delay(5000);
  Serial.begin(9600);
  delay(5000);
  //LGATTServer.begin(g_gatts_uuid, 1, &uart);
  
    if (!LGATTServer.begin(1, &bomb))
    {
        APP_LOG("[FAILED] GATTS begin");
    }
    else
    {
        APP_LOG("GATTS begin");
    }
    
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  LGATTServer.handleEvents();
}

