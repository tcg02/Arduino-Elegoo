#include <Arduino.h>

// Motor driver pins - Values are set to match default pin configuration on the Elegoo
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 100; // Motor PWM speed set

void elegoo_pin_set(int _in1, int _in2, int _in3, int _in4, int _ENA, int _ENB, int _ABS)
{
    in1 = _in1;
    in2 = _in2;
    in3 = _in3;
    in4 = _in4;
    ENA = _ENA;
    ENB = _ENB;
    ABS = _ABS;
}

void set_ABS(int _ABS)
{
    ABS = _ABS;
}

void move_forward()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
}

void move_backward()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
}

void move_left()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW); 
}

void move_right()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
} 
void stop()
{
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
}