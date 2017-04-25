#include <math.h>

struct Data {

    float a;
    float b;
    float c;

    float d;
    float e;
    float f;
    
} data;

float test = 1.2345;
float test2 = 222.2;
float test3 = 333.3;
float test4 = 4444.4;
float test5 = 0.5555;
float test6 = 0.66666;
float test7 = 7.0;
float test8 = 2.0/3.0;

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
    //Serial.println("test utility that sends 6 floats over the serial connection");
    //Serial.print("length of serialized array: "); Serial.print(length_data); Serial.print(" Size of float: "); Serial.println(length_data);
}

void loop() {
    //update_data();
    //char send_buffer[length_data];
    //memcpy(&send_buffer, &data, length_data);   // copy the struct into the new buffer
    //Serial.write('S');                    // starting byte to ensure data integrity
    //Serial.write((uint8_t *) &send_buffer, length_data);  // send the actual data
    test = sin(millis() / 1000.0);
    test2 = cos(millis() / 1000.0);
    Serial.write((uint8_t *) &test, sizeof(test));
    Serial.write((uint8_t *) &test2, sizeof(test2));
//    Serial.write((uint8_t *) &test2, sizeof(test2));
//    Serial.write((uint8_t *) &test3, sizeof(test3));
//    Serial.write((uint8_t *) &test4, sizeof(test4));
//    Serial.write((uint8_t *) &test5, sizeof(test5));
//    Serial.write((uint8_t *) &test6, sizeof(test6));
//    Serial.write((uint8_t *) &test7, sizeof(test7));
//    Serial.write((uint8_t *) &test8, sizeof(test8));
    Serial.write('\n');                    // end byte to ensure data integrity
    
    delay(5);

}



