#include "Communication.h"

Payload data;
Payload dataOut;
RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, true, RFM69_IRQN);
unsigned long timer;

Communication::Communication(float *_level, bool *_tilted) {
    tilted = _tilted;
    level = _level;
    Serial.println("instanced com");
}

void Communication::begin() {
    pinMode(RFM69_RST, OUTPUT);
    digitalWrite(RFM69_RST, HIGH);
    delay(100);
    digitalWrite(RFM69_RST, LOW);
    delay(100);

    timer = millis();

    radio.initialize(FREQUENCY,NODEID,NETWORKID);
    radio.setPowerLevel(31); // power output ranges from 0 (5dBm) to 31 (20dBm)
    radio.encrypt(KEY);
}

void Communication::run() {

    if (radio.receiveDone()) {

        if (radio.DATALEN != sizeof(Payload)) {
            Serial.print("[com] ! invalid payload received, not matching Payload struct!");
        } else {
            data = *(Payload*)radio.DATA; //assume radio.DATA actually contains our struct and not something else
            Serial.print("[com] > nodeId:");
            Serial.println(data.nodeId);
            Serial.print("[com] > volume:");
            Serial.println(data.volume);
            *level = constrain(*level + data.volume, 0, 100);
        }

        if (radio.ACKRequested()) {
            byte nodeId = radio.SENDERID;
            radio.sendACK();
            Serial.print("[com] > ACK sent");
        }
    }

    if(timer + COMMUNICATION_DELAY < millis()) {
        Serial.println(NODEID);
        timer = millis();
        if(*tilted == true) {
            dataOut.nodeId = NODEID;
            dataOut.volume = 4; //it's hot!

            Serial.print("Sending struct (");
            Serial.print(sizeof(dataOut));
            Serial.print(" bytes) ... NodeID: ");
            Serial.print(NODEID);
            Serial.print(" - Receiver: ");
            Serial.print(RECEIVER);
            radio.send(RECEIVER, (const void*)(&dataOut), sizeof(dataOut));
            Serial.println();
        }
        //  else {
        //    digitalWrite(13, LOW);
        // }

    }
}
