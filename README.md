# IRIS_dataset-TensorflowLite-on-ESP32

Run any ML model on ESP32 board.

## Steps:

### 1. Create ML tensorflow model using Pithon code.
Create your own ML model

### 2. Convert tensorflow model to tensorflowLite model for microcontroller.
```
#Convert Keras model to a tflite model

converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

#Save the model to disk
open(tflite_model_name + '.tflite', "wb").write(tflite_model)
```

### 3. Copy the c-array file. (".h" file)
```
#Function: Convert some hex value into an array for C programming
def hex_to_c_array(hex_data, var_name):

  c_str = ''

  #Create header guard
  c_str += '#ifndef ' + var_name.upper() + '_H\n'
  c_str += '#define ' + var_name.upper() + '_H\n\n'

  #Add array length at top of file
  c_str += '\nunsigned int ' + var_name + '_len = ' + str(len(hex_data)) + ';\n'

  #Declare C variable
  c_str += 'unsigned char ' + var_name + '[] = {'
  hex_array = []
  for i, val in enumerate(hex_data) :

    #Construct string from hex
    hex_str = format(val, '#04x')

    #Add formatting so each line stays within 80 characters
    if (i + 1) < len(hex_data):
      hex_str += ','
    if (i + 1) % 12 == 0:
      hex_str += '\n '
    hex_array.append(hex_str)

  #Add closing brace
  c_str += '\n ' + format(' '.join(hex_array)) + '\n};\n\n'

  #Close out header guard
  c_str += '#endif //' + var_name.upper() + '_H'

  return c_str
```



```
#Write TFLite model to a C source (or header) file
with open(c_model_name + '.h', 'w') as file:
  file.write(hex_to_c_array(tflite_model, c_model_name))
```
  
### 4. Run Arduino code.
```
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
```



