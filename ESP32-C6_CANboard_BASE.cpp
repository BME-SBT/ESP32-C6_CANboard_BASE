#include <valami> // CAN kommunikációhoz könyvtár?

#define GND     -1 
#define VCC_3V3 -1 

// GPIO pin-ek funkcióval
#define GPIO_4   16  // TXD0 (TX - Transmit Data)
#define GPIO_5   17  // RXD0 (RX - Receive Data)
#define ADC_0    0   // IO0: (ADC0)
#define ADC_1    1   // IO1: (ADC1)
#define ADC_2    2   // IO2: (ADC2)
#define I_MON    3   // IO3: (Current Monitor - I_MON)
#define CLK      4   // IO4: (Clock)
#define LATCH_1  5   // IO5: (Latch 1)
#define LATCH_2  6   // IO6: (Latch 2)
#define DATA     7   // IO7: (Data), pl. 7-szegmenses kijelzõhöz
#define GPIO_1   8   // IO8: GPIO, chip boot
#define GPIO_2   9   // IO9: GPIO, chip boot
#define CAN_RX   18  // IO18: (CAN RX)
#define CAN_TX   19  // IO19: (CAN TX)
#define HEARTBEAT_PIN 10 // IO10: Heartbeat LED
#define GPIO_6   11  // IO11
#define USB_C    12  // IO12: (USB-C)
#define USB_D    13  // IO13: (USB-D)
#define GPIO_7   15  // IO15
#define GPIO_8   20  // IO20
#define GPIO_9   21  // IO21
#define GPIO_10  22  // IO22
#define GPIO_11  23  // IO23

// Kimeneti állapot
void Out(int pin, bool state) {
    digitalWrite(pin, state ? LOW : HIGH); // LOW az aktív, jó az invertálás?
}

void SevenSegment(int number) {
    Out(LATCH_1, false);
    Out(LATCH_2, false);

    for (int i = 0; i < 8; i++) {
        bool bitValue = (number >> i) & 0x01;
        Out(DATA, bitValue);
        Out(CLK, true);
        Out(CLK, false);
    }

    Out(LATCH_1, true);
    Out(LATCH_2, true);
}

void UsrLed(bool state) {
    Out(GPIO_1, state);
}

void Heartbeat() {
    static bool state = false;
    state = !state; // Állapot váltás
    Out(HEARTBEAT_PIN, state);
}

void setup() {

    pinMode(GPIO_4, OUTPUT); // TXD0: UART adatátvitel
    pinMode(GPIO_5, INPUT);  // RXD0: UART adatfogadás

    pinMode(ADC_0, INPUT);
    pinMode(ADC_1, INPUT);
    pinMode(ADC_2, INPUT);

    pinMode(I_MON, INPUT);

    pinMode(CLK, OUTPUT);
    pinMode(LATCH_1, OUTPUT);
    pinMode(LATCH_2, OUTPUT);
    pinMode(DATA, OUTPUT);

    pinMode(GPIO_1, OUTPUT);
    pinMode(GPIO_2, OUTPUT);
    pinMode(GPIO_6, OUTPUT);
    pinMode(GPIO_7, OUTPUT);
    pinMode(GPIO_8, OUTPUT);
    pinMode(GPIO_9, OUTPUT);
    pinMode(GPIO_10, OUTPUT);
    pinMode(GPIO_11, OUTPUT);

    pinMode(CAN_RX, INPUT);
    pinMode(CAN_TX, OUTPUT);

    pinMode(USB_C, OUTPUT);
    pinMode(USB_D, OUTPUT);

    pinMode(HEARTBEAT_PIN, OUTPUT);

    // Alapértelmezett állapotok
    digitalWrite(CLK, LOW);
    digitalWrite(LATCH_1, LOW);
    digitalWrite(LATCH_2, LOW);
    digitalWrite(DATA, LOW);
    digitalWrite(GPIO_1, LOW);
    digitalWrite(GPIO_2, LOW);
    digitalWrite(GPIO_6, LOW);
    digitalWrite(GPIO_7, LOW);
    digitalWrite(GPIO_8, LOW);
    digitalWrite(GPIO_9, LOW);
    digitalWrite(GPIO_10, LOW);
    digitalWrite(GPIO_11, LOW);
    digitalWrite(CAN_TX, LOW);
    digitalWrite(USB_C, LOW);
    digitalWrite(USB_D, LOW);
    digitalWrite(HEARTBEAT_PIN, LOW);

    Serial.begin(115200);
    Serial.println("GPIO konfigurációk beállítva.");
}

void loop() {

    Heartbeat();
    delay(1000);

    //test
    SevenSegment(0b10101010);
    delay(500);
}
