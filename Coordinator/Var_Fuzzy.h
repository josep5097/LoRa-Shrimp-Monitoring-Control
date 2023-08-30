/*
  Var_Fuzzy.h - Libreria para el uso de las variables relacionadas
  con Fuzzy descritas en el Main, usarlas como variables globales.
*/

#ifndef GLOBAL_VARS_FUZZY_H
#define GLOBAL_VARS_FUZZY_H

// Entrada Fuzzy --> Disolved Oxygen  ------------------------------
extern FuzzySet *Hipox_Acid;
extern FuzzySet *Bajo_DO;
extern FuzzySet *Normal_DO;
extern FuzzySet *Alto_DO;
// Entrada Fuzzy --> Temperature -----------------------------------
extern FuzzySet *Bajo_T;
extern FuzzySet *Normal_T;
extern FuzzySet *Alto_T;
// Salida Fuzzy ---> Aerator --------------------------------------
extern FuzzySet *Aireador_Off;
extern FuzzySet *Aireador_On;
extern Fuzzy *fuzzy;
#endif
