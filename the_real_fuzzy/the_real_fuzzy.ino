#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>
#include <SoftwareSerial.h>
 
// Step 1 -  Instantiating an object library
Fuzzy* fuzzy = new Fuzzy();
SoftwareSerial bt(2,3);

 
void setup(){
 Serial.begin(9600);
 bt.begin(9600);
 // Step 2 - Creating a FuzzyInput distance
 FuzzyInput* indicacion = new FuzzyInput(1);// With its ID in param
 
 //creating FuzzySet
 FuzzySet* muyFrio = new FuzzySet(0, 10, 10, 15);
 indicacion->addFuzzySet(muyFrio);
 FuzzySet* frio = new FuzzySet(15, 20, 20, 25);
 indicacion->addFuzzySet(frio);
 FuzzySet* caliente = new FuzzySet(25, 30, 30, 35);
 indicacion->addFuzzySet(caliente);
 FuzzySet* muyCaliente = new FuzzySet(35, 40, 40, 45);
 indicacion->addFuzzySet(muyCaliente);
 
 fuzzy->addFuzzyInput(indicacion);
 
 FuzzyOutput* velocity = new FuzzyOutput(1);
 
 FuzzySet* superSlow = new FuzzySet(0, 10, 10, 20); // Super Slow velocity
 velocity->addFuzzySet(superSlow); // Add FuzzySet slow to velocity
 FuzzySet* slow = new FuzzySet(10, 20, 20, 30);
 velocity->addFuzzySet(slow);
 FuzzySet* average = new FuzzySet(20, 30, 30, 40); // Average velocity
 velocity->addFuzzySet(average); // Add FuzzySet average to velocity
 FuzzySet* fast = new FuzzySet(30, 40, 40, 50); // Fast velocity
 velocity->addFuzzySet(fast); // Add FuzzySet fast to velocity
 
 fuzzy->addFuzzyOutput(velocity); // Add FuzzyOutput to Fuzzy object
 
 //Passo 4 - Assembly the Fuzzy rules
 // FuzzyRule "IF indicacion = muyCaliente THEN velocity = Superslow"
 FuzzyRuleAntecedent* ifIndicacionMuyCaliente = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionMuyCaliente->joinSingle(muyCaliente); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocitySuperSlow = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocitySuperSlow->addOutput(superSlow);// Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifIndicacionMuyCaliente, thenVelocitySuperSlow); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule01); // Adding FuzzyRule to Fuzzy object
 
 // FuzzyRule "IF indicacion = caliente THEN velocity = slow"
 FuzzyRuleAntecedent* ifIndicacionCaliente = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionCaliente->joinSingle(caliente); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocitySlow = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocitySlow->addOutput(slow); // Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifIndicacionCaliente, thenVelocitySlow); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule02); // Adding FuzzyRule to Fuzzy object
 
  
 // FuzzyRule "IF indicacion = frio THEN velocity = normal"
 FuzzyRuleAntecedent* ifIndicacionFrio = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionFrio->joinSingle(frio); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocityAverage = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocityAverage->addOutput(average); // Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifIndicacionFrio, thenVelocityAverage); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule03); // Adding FuzzyRule to Fuzzy object
  
 // FuzzyRule "IF indicacion = muyFrio THEN velocity = fast"
 FuzzyRuleAntecedent* ifIndicacionMuyFrio = new FuzzyRuleAntecedent(); // Instantiating an Antecedent to expression
 ifIndicacionMuyFrio->joinSingle(muyFrio); // Adding corresponding FuzzySet to Antecedent object
 FuzzyRuleConsequent* thenVelocityFast = new FuzzyRuleConsequent(); // Instantiating a Consequent to expression
 thenVelocityFast->addOutput(fast);// Adding corresponding FuzzySet to Consequent object
 // Instantiating a FuzzyRule object
 FuzzyRule* fuzzyRule04 = new FuzzyRule(4, ifIndicacionMuyFrio, thenVelocityFast); // Passing the Antecedent and the Consequent of expression
  
 fuzzy->addFuzzyRule(fuzzyRule04); // Adding FuzzyRule to Fuzzy object
}

void loop(){
  float output = 0.0;
 if (bt.available() > 0){
   int indication = bt.read(); 
   // Step 5 - Report inputs value, passing its ID and value
   fuzzy->setInput(1, indication); 
   // Step 6 - Exe the fuzzification
   fuzzy->fuzzify(); 
   // Step 7 - Exe the desfuzzyficação for each output, passing its ID
    output = fuzzy->defuzzify(1);
 Serial.println(output);
 }
 if(ouput==40){
   digitalWrite(IN4, 200);
 }if else(output==30){
   digitalWrite(IN4,200);
   digitalWrite(IN3, 200);
   digitalWrite(IN9, 200);
   digitalWrite(IN10, 200);
   
 }if else(output==20){
   analogWrite(PWM_Derecho, 50);
   analogWrite(PWM_Izquierdo, 50);
 }if else(output==10){
   analogWrite(PWM_Derecho, 25);
   analogWrite(PWM_Izquierdo, 25);
 }
 
 delay(100);
}

