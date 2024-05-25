#include <math.h>  // Include the math library for sqrt()
#include <SCServo.h>
SCSCL sc;

/// ------- CPG ---------///
unsigned long previousMillis4 = 0;
const long interval4 = 400; // interval at which to update (milliseconds)
int j = 0; // move the loop variable to global scope

unsigned long previousMillis3 = 0;
const long interval3 = 400;

const int Output = 5;
float C1_Values[Output];
float C2_Values[Output];
float O1_Values[Output];
float O2_Values[Output];

float C1 = 1;
float C2 = 1;
float O1;
float O2;
float W11, W12, W21, W22;
float alpha = 6;
float phi = 2.6;
int i = 0;  //time


//จุดต่ำสุดสูงสุดของกราฟ O1
float MIN_O1 = -0.999206032;
float MAX_O1 = 0.970415895;

//จุดต่ำสุดสูงสุดของกราฟ O2
float MIN_O2 = -0.99999983;
float MAX_O2 = 0.999999831;

// //----------เดินหน้า---------------//
//ขาหน้าขวา
const int MAX_ID6 = 662;  //ยกขาขึ้น
const int MIN_ID6 = 562;  //ยกขาลง 562
const int MAX_ID8 = 301;  //ก้าวขาถอย   
const int MIN_ID8 = 207;  //ก้าวขาหน้า   

//ขาหน้าซ้าย
const int MIN_ID4 = 454;  //ยกขาขึ้น 
const int MAX_ID4 = 254;  //ยกขาลง  
const int MIN_ID2 = 567;  //ก้าวขาถอย 
const int MAX_ID2 = 661;  //ก้าวขาหน้า 

//ขาหลังขวา
const int MAX_ID7 = 466;  //ยกขาขึ้น 
const int MIN_ID7 = 566;  //ยกขาลง
const int MAX_ID3 = 454;  //ก้าวขาหน้า
const int MIN_ID3 = 554;  //ก้าวขาถอย

//ขาหลังซ้าย
const int MAX_ID1= 619;  //ยกขาขึ้น
const int MIN_ID1 = 519;  //ยกขาลง 
const int MAX_ID9 = 447;  //ก้าวขาหน้า
const int MIN_ID9 = 347;  //ก้าวขาถอย


float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

bool working1 = false;
bool work1 = false;
bool doing1 = false;
bool working2 = false;
bool work2 = false;
bool doing2 = false;

/// ------- CPG ---------///

// ------ hormones variable -------- //
const int trigPin1 = 11;    // Trigger for sensor 1
const int echoPin1 = 12;    // Echo for sensor 1
const int trigPin2 = 9;     // Trigger for sensor 2
const int echoPin2 = 10;    // Echo for sensor 2

unsigned long previousMillis = 0;
const long interval = 100;  // Interval between readings in milliseconds
float duration1, cm1;
float duration2, cm2;

// Define array size
const int arraySize = 8; // Array size set to 8

// Arrays to store distance values
int sensor1Values[arraySize];
int sensor2Values[arraySize];

// Counter to track the number of valid entries in the array
int validEntries = 0;

// Index to keep track of the current position in the arrays
int index = 0;

// Array to store Hc1 values
float Hc1[2] = {0, 0};
float Hc2[2] = {0, 0};

// ------ end hormones variable -------- //

//// ----- buzzer voice ------- ////
const int buzzerPin = 8;
bool isPeeping = false;
// Define the frequency of the beep (in Hertz)
const int beepFrequency = 1000; // Adjust the frequency as needed
const int beepFrequency2 = 800;
// Define the duration for the beep (in milliseconds)
const unsigned long beepDuration = 3000; // 1 second
// Variables to manage timing
unsigned long startMillis2;
bool isBeeping = false;
bool beepCompleted = false;
//// ----- end buzzer voice ------- ////



void setup() {
  Serial.begin(115200);
  //set the digital pin as output
  pinMode(buzzerPin,OUTPUT);
  startMillis2 = millis();
  isBeeping = true;

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  // Serial.begin(115200);
  Serial1.begin(1000000);
  sc.pSerial = &Serial1;

  //------cpg----------------//
  W11 = alpha * cos(phi);
  W12 = alpha * sin(phi);
  W21 = alpha * (-sin(phi));
  W22 = alpha * cos(phi);


  // Initialize arrays with zeros
  for (int i = 0; i < arraySize; i++) {
    sensor1Values[i] = 0;
    sensor2Values[i] = 0;
  }
}
void CPG_forword(){
    for(i=0;i<=Output;i++)
  {
    if (i == 0) {
      C1_Values[i] = C1;
      O1_Values[i] = tanh(C1_Values[i]);
      C2_Values[i] = C2;
      O2_Values[i] = tanh(C2_Values[i]);
    }
    if (i >= 1) {
      C1_Values[i] = (O1_Values[i - 1] * W11) + (O2_Values[i - 1] * W21);
      O1_Values[i] = tanh(C1_Values[i]);
      C2_Values[i] = (O2_Values[i - 1] * W22) + (O1_Values[i - 1] * W12);
      O2_Values[i] = tanh(C2_Values[i]);
    }
    //-----------------------เดินหน้า------------------------------------//
    //ขาหน้าขวา
    //ก้าวหน้า
    float Step_up_ID6 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID6, MAX_ID6);
    float Step_forward_ID8 = map(O2_Values[i], MIN_O2, MAX_O2, MIN_ID8, MAX_ID8);
    
    //ขาหลังขวา
    //ก้าวหน้า
    float Step_up_ID7 = map(O2_Values[i], MIN_O2, MAX_O2, MIN_ID7, MAX_ID7);
    float Step_forward_ID3 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID3, MAX_ID3);
  
    //ขาหน้าซ้าย
    //ก้าวหน้า
    float Step_up_ID1 = map(O2_Values[i], MIN_O2, MAX_O2, MIN_ID1, MAX_ID1);
    float Step_forward_ID9 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID9, MAX_ID9);

    //ขาหลังซ้าย
    //ก้าวหน้า
    float Step_up_ID4 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID4, MAX_ID4);
    float Step_forward_ID2 = map(O2_Values[i], MIN_O2, MAX_O2, MIN_ID2, MAX_ID2);


    //-----------------เดินหน้า--------------//
    if (!working1) {
      if (!work1) {
        sc.WritePos(6, Step_up_ID6, 0, 1500);
        sc.WritePos(7, Step_up_ID7, 0, 1500);
        sc.WritePos(8, Step_forward_ID8, 0, 1500);
        sc.WritePos(3, Step_forward_ID3, 0, 1500);
        work1 = true;
      }
      else if (work1) {
        sc.WritePos(6, Step_up_ID6, 0, 1500);
        sc.WritePos(7, Step_up_ID7, 0, 1500);
        sc.WritePos(8, Step_forward_ID8, 0, 1500);
        sc.WritePos(3, Step_forward_ID3, 0, 1500);
        working1 = true;
        doing1 = false;
      }
    } else if (working1) {
      if (!doing1) {
      sc.WritePos(4, Step_up_ID4, 0, 1500);
      sc.WritePos(1, Step_up_ID1, 0, 1500);
      sc.WritePos(2, Step_forward_ID2, 0, 1500);
      sc.WritePos(9, Step_forward_ID9, 0, 1500);
      doing1 = true;
      }
      else if (doing1) {
      sc.WritePos(4, Step_up_ID4, 0, 1500);
      sc.WritePos(1, Step_up_ID1, 0, 1500);
      sc.WritePos(2, Step_forward_ID2, 0, 1500);
      sc.WritePos(9, Step_forward_ID9, 0, 1500);
      working1 = false;
      work1 = false;
      }
    }
    delay(400);
  }
}
void CPG_backword(){
  for(i=0;i<=Output;i++)
  {
    if (i == 0) {
      C1_Values[i] = C1;
      O1_Values[i] = tanh(C1_Values[i]);
      C2_Values[i] = C2;
      O2_Values[i] = tanh(C2_Values[i]);
    }
    if (i >= 1) {
      C1_Values[i] = (O1_Values[i - 1] * W11) + (O2_Values[i - 1] * W21);
      O1_Values[i] = tanh(C1_Values[i]);
      C2_Values[i] = (O2_Values[i - 1] * W22) + (O1_Values[i - 1] * W12);
      O2_Values[i] = tanh(C2_Values[i]);
    }

    //-----------------------ถอยหลัง------------------------------------//
    //ขาหน้าขวา
    //ดันตัวไปข้างหน้า
    float Step_down_ID6 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID6, MAX_ID6);
    float Step_backward_ID8 = map(O2_Values[i], MIN_O2, MAX_O2, MIN_ID8, MAX_ID8);

    //ขาหลังขวา
    //ดันตัวไปข้างหน้า
    float Step_down_ID7 = map(O2_Values[i], MIN_O2, MAX_O2, MAX_ID7, MIN_ID7);
    float Step_backward_ID3 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID3,  MAX_ID3);

    //ขาหน้าซ้าย
    //ดันตัวไปข้างหน้า
    float Step_down_ID1 = map(O2_Values[i], MIN_O2, MAX_O2, MAX_ID1, MIN_ID1);
    float Step_backward_ID9 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID9,  MAX_ID9);

    //ขาหลังซ้าย
    //ดันตัวไปข้างหน้า
    float Step_down_ID4 = map(O1_Values[i], MIN_O1, MAX_O1, MIN_ID4, MAX_ID4);
    float Step_backward_ID2 = map(O2_Values[i], MIN_O2, MAX_O2, MIN_ID2,  MAX_ID2);

  //  -----------เดินถอยหลัง------------------//
    if (!working2) {
      if (!work2) {
        sc.WritePos(6, Step_down_ID6, 0, 1500);
        sc.WritePos(7, Step_down_ID7, 0, 1500);
        sc.WritePos(8, Step_backward_ID8, 0, 1500);
        sc.WritePos(3, Step_backward_ID3, 0, 1500);
        work2 = true;
        working2 = false;
        Serial.println("1 ");
      }
      else if (work2) {
        sc.WritePos(6, Step_down_ID6, 0, 1500);
        sc.WritePos(7, Step_down_ID7, 0, 1500);
        sc.WritePos(8, Step_backward_ID8, 0, 1500);
        sc.WritePos(3, Step_backward_ID3, 0, 1500);
        working2 = true;
        doing2 = false;
        Serial.println("2 ");
      }
    } else if (working2) {
      if (!doing2) {
      sc.WritePos(4, Step_down_ID4, 0, 1500);
      sc.WritePos(1, Step_down_ID1, 0, 1500);
      sc.WritePos(2, Step_backward_ID2, 0, 1500);
      sc.WritePos(9, Step_backward_ID9, 0, 1500);
      Serial.println("3");
      doing2 = true;
      working2 = true;
      }
      else if (doing2) {
      sc.WritePos(4, Step_down_ID4, 0, 1500);
      sc.WritePos(1, Step_down_ID1, 0, 1500);
      sc.WritePos(2, Step_backward_ID2, 0, 1500);
      sc.WritePos(9, Step_backward_ID9, 0, 1500);
      Serial.println("4 ");
      working2 = false;
      work2 = false;
      }
    }
    delay(400);
  }
}

void voice1(){
  if (isBeeping) {
    unsigned long currentMillis2 = millis();
    // Check if the beep duration has passed
      tone(buzzerPin, beepFrequency);
      beepCompleted = true;
      Serial.println("voice 1");
      isBeeping = false;
  }
     else{
      // Stop the beep
      noTone(buzzerPin);
      beepCompleted = true;
      Serial.println("stop voice 1");
      isBeeping = true;
    }
}

void voice2(){
  if (isBeeping) {
    unsigned long currentMillis2 = millis();
    // Check if the beep duration has passed
    if (currentMillis2 - startMillis2 >= beepDuration) {
      tone(buzzerPin, beepFrequency2);
      beepCompleted = true;
      Serial.println("voice 2");
      isBeeping = false;
    }
  }else{
      noTone(buzzerPin);
      beepCompleted = true;
      Serial.println("stop voice 2");
      isBeeping = true;
  }
}

void novoice(){
  if (isBeeping) {
    unsigned long currentMillis2 = millis();
    // Check if the beep duration has passed
    if (currentMillis2 - startMillis2 >= beepDuration) {
      // Stop the beep
      noTone(buzzerPin);
      beepCompleted = true;
      Serial.println("no voice");
      isBeeping = false;
    }
  }else{
      // Stop the beep
      noTone(buzzerPin);
      beepCompleted = true;
      Serial.println("stop no voice");
      isBeeping = true;
  }
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Sensor 1
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    cm1 = (duration1 / 2) / 29.1;

    // Sensor 2
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    cm2 = (duration2 / 2) / 29.1;

    // Map sensor 1 value in cm
    int mappedCm1;
    if (cm1 >= 20 && cm1 <= 40) {
      mappedCm1 = map(cm1, 20, 40, 10, 0);
    } else if (cm1 > 40) {
      mappedCm1 = 0;
    } else {
      mappedCm1 = 10;  // Set to 10 for values less than 20
    }

    // Map sensor 2 value in cm
    int mappedCm2;
    if (cm2 >= 20 && cm2 <= 40) {
      mappedCm2 = map(cm2, 20, 40, 10, 0);
    } else if (cm2 > 40) {
      mappedCm2 = 0;
    } else {
      mappedCm2 = 10;  // Set to 10 for values less than 20
    }

    // Store the mapped values in the arrays
    sensor1Values[index] = mappedCm1;
    sensor2Values[index] = mappedCm2;
   

    // Update the index, wrap around if necessary
    index = (index + 1) % arraySize;

    // Print the current values of the arrays
    // Serial.print("    Sensor 1 values: ");
    for (int i = 0; i < arraySize; i++) {
      // Serial.print(sensor1Values[i]);
      if (i < arraySize - 1) {
        // Serial.print(", ");
      }
    }
    // Print the current values of the arrays
    // Serial.print("    Sensor 2 values: ");
    for (int i = 0; i < arraySize; i++) {
      // Serial.print(sensor2Values[i]);
      if (i < arraySize - 1) {
        // Serial.print(", ");
      }
    }

     // Calculate the standard deviations
    float mean1 = 0;
    float mean2 = 0;

    ///---------- ผลรวมตัวเลข ----------///
    for (int i = 0; i < arraySize; i++) {
      mean1 += sensor1Values[i];
      mean2 += sensor2Values[i];
    }

    ///---------- ค่าเฉลี่ย ----------///
    mean1 /= arraySize;
    mean2 /= arraySize;

    float variance1 = 0;
    float variance2 = 0;

    ///---------- ผลรวม (Xi - X(เฉลี่ย)) ยกกำลัง 2 ----------///
    for (int i = 0; i < arraySize; i++) {
      variance1 += pow(sensor1Values[i] -mean1, 2);
      variance2 += pow(sensor2Values[i] - mean2, 2);
    }

   ///---------- ผลรวม (Xi - X(เฉลี่ย)) ยกกำลัง 2 หาร n-1  ----------///
    variance1 /= arraySize-1;
    variance2 /= arraySize-1;

///----------- ถอดสเเควรูท = ส่วนเบี่ยงเบนมาตรฐาน ----------------//
    float stddev1 = sqrt(variance1);
    float stddev2 = sqrt(variance2);

    // Store standard deviations in variables x1 and x2
    float x1 = stddev1;
    float x2 = stddev2;

    // Exponential calculations
    float e = 2.71828;
    float a = 0.7;
    float b = 0.25;
    int TH = 5;

    // ----- Store Map sensor 1 to Sensor1 , Store Map sensor 1 to Sensor1 -------/
    int Sensor1 = mappedCm1;
    int Sensor2 = mappedCm2;

    ///--------- e ยกกำลัง ของ Hc1 Hc2 --------------//
    float reX1 = pow(e, ((-1)*(x1)));
    float reX2 = pow(e, ((-1)*(x2)));

    // Calculate firstx1 and secx1 for Hc1
    float firstx1 = a * (1 / (1 + reX1));
    float secx1 = b * Hc1[0];  

    // Calculate firstx2 and secx2 for Hc2 
    float firstx2 = a * (1 /(1 + reX2));
    float secx2 = b * Hc2[0];
  
    // Add firstx1 and secx1 for store in Hc1[1] 
    Hc1[1] = firstx1 + secx1;

    // Add firstx2 and secx2 for store in Hc2[1]
    Hc2[1] = firstx2 + secx2;

    // Map Hc1[1] to R_Hc1
    float R_Hc1 = (Hc1[1] * 2.0f) - 1.0f;
    float R_Hc2 = (Hc2[1] * 2.0f) - 1.0f;

    /// strt area for loop hormones //

  if (Sensor1 < (TH - R_Hc1) && Sensor2 < (TH - R_Hc2)) {
      novoice();
      CPG_forword();
      // CPG_forward();
      Serial.print(Hc1[0]);
      Serial.print(", ");
      Serial.print(Hc1[1]);
      Serial.print("  R_HC1 = ");
      Serial.print(R_Hc1);
      Serial.print("  ");
      Serial.print(Hc2[0]);
      Serial.print(", ");
      Serial.print(Hc2[1]);
      Serial.print("  R_HC2 = ");
      Serial.print(R_Hc2);
      Serial.print("  Sensor 1 = ");
      Serial.print(Sensor1);
      Serial.print("  Sensor 2 = ");
      Serial.print(Sensor2);
      Serial.print("  ");
      Serial.print("    Normal + forward");
      Serial.print("\n");

    
    } 
    else if (Sensor1 > (TH - R_Hc1) && Sensor2 < (TH - R_Hc2)) {
      voice1();
      CPG_backword();
      // CPG_Backward();
      Serial.print(Hc1[0]);
      Serial.print(", ");
      Serial.print(Hc1[1]);
      Serial.print("  R_HC1 = ");
      Serial.print(R_Hc1);
      Serial.print("  ");
      Serial.print(Hc2[0]);
      Serial.print(", ");
      Serial.print(Hc2[1]);
      Serial.print("  R_HC2 = ");
      Serial.print(R_Hc2);
      Serial.print("  Sensor 1 = ");
      Serial.print(Sensor1);
      Serial.print("  Sensor 2 = ");
      Serial.print(Sensor2);
      Serial.print("  ");
      Serial.print("      Back + voice1");
      Serial.print("\n");

    } 
    else if (Sensor1 < (TH - R_Hc1) && Sensor2 > (TH - R_Hc2)) {
      // voice2();
      voice1();
      CPG_forword();
      Serial.print(Hc1[0]);
      Serial.print(", ");
      Serial.print(Hc1[1]);
      Serial.print("  R_HC1 = ");
      Serial.print(R_Hc1);
      Serial.print("  ");
      Serial.print(Hc2[0]);
      Serial.print(", ");
      Serial.print(Hc2[1]);
      Serial.print("  R_HC2 = ");
      Serial.print(R_Hc2);
      Serial.print("  Sensor 1 = ");
      Serial.print(Sensor1);
      Serial.print("  Sensor 2 = ");
      Serial.print(Sensor2);
      Serial.print("  ");
      Serial.print("      forward + voice1");
      Serial.print("\n");
    } 
    else if (Sensor1 > (TH - R_Hc1) && Sensor2 > (TH - R_Hc2)) {
      voice2();
      // CPG_backword();
      Serial.print(Hc1[0]);
      Serial.print(", ");
      Serial.print(Hc1[1]);
      Serial.print("  R_HC1 = ");
      Serial.print(R_Hc1);
      Serial.print("  ");
      Serial.print(Hc2[0]);
      Serial.print(", ");
      Serial.print(Hc2[1]);
      Serial.print("  R_HC2 = ");
      Serial.print(R_Hc2);
      Serial.print("  Sensor 1 = ");
      Serial.print(Sensor1);
      Serial.print("  Sensor 2 = ");
      Serial.print(Sensor2);
      Serial.print("  ");
      Serial.print("      Stop + voice2");
      Serial.print("\n");
    } 

    /// end area for loop hormones //


/// ---------- print test Hc1 ---------------------//
    // Serial.print("   Standard Deviation Sensor 1: ");
    // Serial.print(x1);
    // Serial.print("  ");
    // Serial.print(reX1);
    // Serial.print("  ");
    // // Serial.print("  mean 1: ");
    // Serial.print(firstx1);
    // Serial.print(" + ");
    // Serial.print(secx1);
    // Serial.print(" = ");
    // // Serial.print("  ");
    // Serial.print(Hc1[1]);
    // Serial.print(" Hc1  =  ");
    // Serial.print(Hc1[0]);
    // Serial.print(", ");
    // Serial.print(Hc1[1]);
    // Serial.print("  R_HC1 = ");
    // Serial.println(R_Hc1);
    
    // Serial.println("  ");

    /// ---------- print test Hc2 ---------------------//
    // Serial.print("   Standard Deviation Sensor 2: ");
    // Serial.print(x2);
    // Serial.print("  ");
    // Serial.print(reX2);
    // Serial.print("  ");
    // // Serial.print("  mean 2: ");
    // Serial.print(firstx2);
    // Serial.print(" + ");
    // Serial.print(secx2);
    // Serial.print(" = ");
    // // Serial.print("  ");
    // Serial.print(Hc2[1]);
    // Serial.print("  ");
    // Serial.print(Hc2[0]);
    // Serial.print(", ");
    // Serial.print(Hc2[1]);
    // Serial.println("  ");

    // Update Hc1[0] for the next iteration
    Hc1[0] = Hc1[1];
    Hc2[0] = Hc2[1];
    
    //---------------- cheack S.D ------------------------///
    // Serial.print("  mean 1: ");
    // Serial.print(mean1);
    // Serial.print("  varoance 1: ");
    // Serial.print(variance1);
    // Print the standard deviations and number of valid entries for debugging purposes
    // Serial.print("   Standard Deviation Sensor 1: ");
    // Serial.println(x1);
    // Serial.print("  mean 2: ");
    // Serial.print(mean2);
    // Serial.print("  varoance 2: ");
    // Serial.print(variance2);
    // Serial.print("    Standard Deviation Sensor 2: ");
    // Serial.println(x2);
    // Serial.print("Number of valid entries in sensor1Values: ");
    // Serial.println(validEntries);

    //---------------- cheack S.D ------------------------///
  }

}

