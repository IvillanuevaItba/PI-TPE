#include <stdlib.h>
#include "AirportADT.h"
#include "ListADT.h"
#include <string.h>
#include "../ProcessData.h"

typedef struct AirportCDT {
    tLocal local;
    tOACI oaci;
    tIATA iata;
    tDenomination denomination;
    MovementList movements;
    int totalMovements;
    int internationalArrivals;
    int internationalDepartures;
    int unknownDepartures;
    int unknownArrivals;
 } AirportCDT;

 AirportADT newAirport(OACI oaci, IATA iata, Local local, Denomination denomination){
 	AirportADT retVal = malloc(sizeof(AirportCDT));
 	strcpy(retVal->oaci, oaci);
 	strcpy(retVal -> local, local);
 	strcpy(retVal -> iata, iata);
 	strcpy(retVal -> denomination, denomination);
 	retVal->movements =  newMovementList();
 	retVal -> unknownArrivals = retVal -> unknownDepartures = retVal -> totalMovements = retVal -> internationalDepartures = retVal -> internationalArrivals = 0;
 	return retVal;
 }

/// ---- SETTERS & GETTERS ----
/*
 * Setters & Getters are used in order to facilitate any future modifications to any specific Airport.
 */

OACI getAirportOACI(AirportADT airport){
 	return airport->oaci;
}

Local getAirportLocal(AirportADT airport){
    return airport->local;
}

Denomination getAirportDenomination(AirportADT airport){
    return airport->denomination;
}

int getAirportTotalMovements(AirportADT airport){
    return airport->totalMovements;
}

int getAirportInternationalArrivals(AirportADT airport){
    return airport->internationalArrivals;
}

int getAirportUnknownDepartures(AirportADT airport){
    return airport->unknownDepartures;
}

int getAirportUnknownArrivals(AirportADT airport){
    return airport->unknownArrivals;
}

int getAirportInternationalDepartures(AirportADT airport){
    return airport->internationalDepartures;
}

IATA getAirportIATA(AirportADT airport){
    return airport->iata;
}

MovementList getMovementList(AirportADT airport){
     return airport->movements;
 }

/// ---- ----

void addMovement(AirportADT airport, OACI oaci, bool isOaciKnown, bool isNational, bool isDeparture){

     if(isOaciKnown) {

         MovementADT movement = getMovementElem(airport->movements, oaci);
         if (movement == NULL) {
             movement = newMovement(oaci);
             addMovementElem(airport->movements, movement);
         }

         if (isDeparture) {
             addDeparture(movement, 1);
         } else {
             addArrival(movement, 1);
         }

     } else {

         if(isDeparture)
             airport->unknownDepartures++;
         else
             airport->unknownArrivals++;

     }

     if(!isNational) {
         if (isDeparture) {
             airport->internationalDepartures++;
         } else {
             airport->internationalArrivals++;
         }
     }

     airport->totalMovements++;

 }


void addAirport (AirportList airportList, OACI oaci, Local local, IATA iata ,Denomination denomination){

    AirportADT airportAux = getAirportElem(airportList, oaci);

    //	If there is no airport with that OACI code, it adds it to the airport list
    if (airportAux == NULL){

        //	Creating a new airport with all its fields complete
        airportAux = newAirport(oaci, iata, local, denomination);

        //	Adds the new airport to the airport list
        addAirportElem(airportList, airportAux);

    }
 }

void freeAirportADT(AirportADT airport) {
     freeListADT(airport -> movements);
     free(airport);
}


/// --- LIST FUNCTIONS ---

AirportList newAirportList(){
	return newList((OACI (*) (void *)) getAirportOACI, (void (*)(void *)) freeAirportADT);
}

bool addAirportElem(AirportList list, AirportADT elem){
	return addElem(list,elem);
}

AirportADT getAirportElem(AirportList list, OACI oaci){
	return getElem(list,oaci);
}

/// --- ---