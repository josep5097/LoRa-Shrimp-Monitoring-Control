/*
  Setup_Fuzzy.cpp - Realizado para crear las variables
  en el setup del control difuso
  Creado por José Miguel Pereira Pontón
  Released into the public domain.
*/

#include "Setup_Fuzzy.h"
#include "Var_Fuzzy.h"
#include "VariablesGlobales.h"
void Fuzzy_Setup(){
  // ------------------------- Control Fuzzy Setup ------------------------
  // Configuraciones de las variables de entrada --------------------------
  // Entrada Fuzzy 1: Oxígeno Disuelto(OD) --------------------------------
  FuzzyInput *OD = new FuzzyInput(1);
  OD->addFuzzySet(Hipox_Acid);
  OD->addFuzzySet(Bajo_DO);
  OD->addFuzzySet(Normal_DO);
  OD->addFuzzySet(Alto_DO);
  fuzzy->addFuzzyInput(OD);
  // Entrada Fuzzy 2: Temperatura(TEMP) -----------------------------------
  FuzzyInput *TEMP = new FuzzyInput(2);
  TEMP->addFuzzySet(Bajo_T);
  TEMP->addFuzzySet(Normal_T);
  TEMP->addFuzzySet(Alto_T);
  fuzzy->addFuzzyInput(TEMP);
  // Configuraciones de la variable de Salida -----------------------------
  // Salida Fuzzy: Aireador -----------------------------------------------
  FuzzyOutput *Aireador = new FuzzyOutput(1);
  Aireador->addFuzzySet(Aireador_Off);
  Aireador->addFuzzySet(Aireador_On);
  fuzzy->addFuzzyOutput(Aireador);
  // ---------------------------- Reglas Fuzzy ----------------------------
  // REGLA 1 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempBajoANDDoHipox = new FuzzyRuleAntecedent();
  ifTempBajoANDDoHipox->joinWithAND(Hipox_Acid, Bajo_T);
  // Consecuentes
  FuzzyRuleConsequent *thenAireadorON = new FuzzyRuleConsequent();
  thenAireadorON->addOutput(Aireador_On);
  FuzzyRuleConsequent *thenAireadorOFF = new FuzzyRuleConsequent();
  thenAireadorON->addOutput(Aireador_Off);
  // REGLA 1 - Creación
  FuzzyRule *ReglaFuzzy1 = new FuzzyRule(1, ifTempBajoANDDoHipox, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy1);
  // REGLA 2 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempBajoANDDoBajo = new FuzzyRuleAntecedent();
  ifTempBajoANDDoBajo->joinWithAND(Bajo_DO, Bajo_T);
  // REGLA 2 - Creación
  FuzzyRule *ReglaFuzzy2 = new FuzzyRule(2, ifTempBajoANDDoBajo, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy2);
  // REGLA 3 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempBajoANDDoNormal = new FuzzyRuleAntecedent();
  ifTempBajoANDDoNormal->joinWithAND(Normal_DO, Bajo_T);
  // REGLA 3 - Creación
  FuzzyRule *ReglaFuzzy3 = new FuzzyRule(3, ifTempBajoANDDoNormal, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy3);
  // REGLA 4 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempBajoANDDoAlto = new FuzzyRuleAntecedent();
  ifTempBajoANDDoAlto->joinWithAND(Alto_DO, Bajo_T);
  // REGLA 4 - Creación
  FuzzyRule *ReglaFuzzy4 = new FuzzyRule(4, ifTempBajoANDDoAlto, thenAireadorOFF);
  fuzzy->addFuzzyRule(ReglaFuzzy4);
  // REGLA 5 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempNormalANDDoHipox = new FuzzyRuleAntecedent();
  ifTempNormalANDDoHipox->joinWithAND(Hipox_Acid, Normal_T);
  // REGLA 5 - Creación
  FuzzyRule *ReglaFuzzy5 = new FuzzyRule(5, ifTempNormalANDDoHipox, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy5);
  // REGLA 6 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempNormalANDDoBajo = new FuzzyRuleAntecedent();
  ifTempNormalANDDoBajo->joinWithAND(Bajo_DO, Normal_T);
  // REGLA 6 - Creación
  FuzzyRule *ReglaFuzzy6 = new FuzzyRule(6, ifTempNormalANDDoBajo, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy6);
  // REGLA 7 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempNormalANDDoNormal = new FuzzyRuleAntecedent();
  ifTempNormalANDDoNormal->joinWithAND(Normal_DO, Normal_T);
  // REGLA 7 - Creación
  FuzzyRule *ReglaFuzzy7 = new FuzzyRule(7, ifTempNormalANDDoNormal, thenAireadorOFF);
  fuzzy->addFuzzyRule(ReglaFuzzy7);
  // REGLA 8 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempNormalANDDoAlto = new FuzzyRuleAntecedent();
  ifTempNormalANDDoAlto->joinWithAND(Alto_DO, Normal_T);
  // REGLA 8 - Creación
  FuzzyRule *ReglaFuzzy8 = new FuzzyRule(8, ifTempNormalANDDoAlto, thenAireadorOFF);
  fuzzy->addFuzzyRule(ReglaFuzzy8);
  // REGLA 9 --------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempAltoANDDoHipox = new FuzzyRuleAntecedent();
  ifTempAltoANDDoHipox->joinWithAND(Hipox_Acid, Alto_T);
  // REGLA 9 - Creación
  FuzzyRule *ReglaFuzzy9 = new FuzzyRule(9, ifTempAltoANDDoHipox, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy9);
  // REGLA 10 -------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempAltoANDDoBajo = new FuzzyRuleAntecedent();
  ifTempAltoANDDoBajo->joinWithAND(Bajo_DO, Alto_T);
  // REGLA 10 - Creación
  FuzzyRule *ReglaFuzzy10 = new FuzzyRule(10, ifTempAltoANDDoBajo, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy10);
  // REGLA 11 -------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempAltoANDDoNormal = new FuzzyRuleAntecedent();
  ifTempAltoANDDoNormal->joinWithAND(Normal_DO, Alto_T);
  // REGLA 11 - Creación
  FuzzyRule *ReglaFuzzy11 = new FuzzyRule(11, ifTempAltoANDDoNormal, thenAireadorON);
  fuzzy->addFuzzyRule(ReglaFuzzy11);
  // REGLA 12 -------------------------------------------------------------
  // Antecedente
  FuzzyRuleAntecedent *ifTempAltoANDDoAlto = new FuzzyRuleAntecedent();
  ifTempAltoANDDoAlto->joinWithAND(Alto_DO, Alto_T);
  // REGLA 12 - Creación
  FuzzyRule *ReglaFuzzy12 = new FuzzyRule(12, ifTempAltoANDDoAlto, thenAireadorOFF);
  fuzzy->addFuzzyRule(ReglaFuzzy12);
}

// ------------------------ Control Difuso -----------------------
void controlDifuso(float DO_Val, float Temp_Val) {
  // Respuesta
  Serial.println("\n\n\nEntradas: ");
  Serial.print("\tOxìgeno Disuelto: ");
  Serial.print(DO_Val);
  Serial.print(" y Temperatura: ");
  Serial.print(Temp_Val);
  // Asignación: entradas -> variables difusas -------------------
  fuzzy->setInput(1, DO_Val);
  fuzzy->setInput(2, Temp_Val);
  // Fuzzificar
  fuzzy->fuzzify();
  // Relaciones de pertenencia -----------------------------------
  Serial.println("\nRelacion de Pertenencia en las entradas: ");
  Serial.print("DO: Hipoxia-> ");
  Serial.print(Hipox_Acid->getPertinence());
  Serial.print(", DO_Bajo-> ");
  Serial.print(Bajo_DO->getPertinence());
  Serial.print(", DO_Normal-> ");
  Serial.println(Normal_DO->getPertinence());
  Serial.print("y DO_Alto-> ");
  Serial.print(Alto_DO->getPertinence());
  Serial.print("\nTemperatura: Baja-> ");
  Serial.print(Bajo_T->getPertinence());
  Serial.print(",  Normal-> ");
  Serial.print(Normal_T->getPertinence());
  Serial.print(" y  Alta-> ");
  Serial.print(Alto_T->getPertinence());
  // Proceso de Defuzzificación ---------------------------------
  float output1 = fuzzy->defuzzify(1);
  Serial.print("\nRelación de pertenencia en la salida: ");
  Serial.print("\nAireador: Encender-> ");
  Serial.print(Aireador_On->getPertinence());
  Serial.print(", Apagar-> ");
  Serial.print(Aireador_Off->getPertinence());
  Serial.print("\nResultado, con un porcentaje de: ");
  Serial.println(output1);
  Serial.print("\t\tAireador: ");
  if (output1 <= 0.5) {
    Aireadores = 0;
    Serial.print("Apagado");
  }
  else {
    Aireadores = 1;
    Serial.print("Encendido");
  }
}
