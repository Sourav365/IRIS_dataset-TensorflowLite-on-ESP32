#include <EloquentTinyML.h>
#include "iris.h"

#define NUMBER_OF_INPUTS 4
#define NUMBER_OF_OUTPUTS 3
// in future projects you may need to tweek this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 8*1024

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;


void setup() {
    Serial.begin(115200);
    ml.begin(iris);
}

void loop() {
  
    float x_test[4] = { 6.7,3.1,4.4, 1.4 };
    float y_pred[3] = {0};
    ml.predict(x_test,y_pred);

    
    Serial.print("Predicted class is: ");
    Serial.println(ml.probaToClass(y_pred));
    
    delay(1000);
}
