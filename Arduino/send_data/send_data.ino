#include <math.h>

struct Data {

    float a;
    float b;
    float c;

    float d;
    float e;
    float f;
    
} data;

void update_data() {
   unsigned long c_time = millis()/1000.0;
   data.a = sin(c_time);
   data.b = cos(c_time);
   data.c = tan(c_time);
   data.d = atan(c_time);
   data.e = atan2(c_time, log10(c_time));
   data.f = log(c_time);
}

int length_data = sizeof(data);

//char send_buffer[length_data];

void setup() {
    Serial.begin(115200);
    Serial.println("test utility that sends 6 floats over the serial connection");
    Serial.print("length of serialized array: "); Serial.print(length_data); Serial.print(" Size of float: "); Serial.println(length_data);
}

void loop() {
    update_data();
    char send_buffer[length_data];
    memcpy(&send_buffer, &data, length_data);   // copy the struct into the new buffer
    Serial.write('S');                    // starting byte to ensure data integrity
    Serial.write((uint8_t *) &send_buffer, length_data);  // send the actual data
    Serial.write('E');                    // end byte to ensure data integrity
    
    delay(50);

}


