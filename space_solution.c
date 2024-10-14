#include "space_explorer.h"
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>  

#define MAX_PLANETS 1000 // Assuming that there are less than 1000 planets

// Define a structure to represent the ship's state
typedef struct{
    unsigned int planet[MAX_PLANETS]; // Keep a list of planets
    unsigned int numVisitedPlanets; // Number of visited planets
    unsigned int nextPlanetI; // Index of the next planet to visit
} ShipState;


// Function to simulate a spaceship hop
ShipAction space_hop(unsigned int crt_planet,
                   unsigned int *connections,
                   int num_connections,
                   double distance_from_mixer,
                   void *ship_state)
{
    // Get the ship state
    ShipState *state;

    // Allocate memory for ShipState if it's NULL
    if (ship_state == NULL){
        state = malloc(sizeof(ShipState)); 
        state->numVisitedPlanets = 0;
        state->nextPlanetI = 0;
        state->planet[state->numVisitedPlanets++] = crt_planet; // Store crt_planet
    }
    else{
        state = ship_state;
    }

    // Initialize the ship action to default values
    ShipAction next_action;
    next_action.next_planet = RAND_PLANET;
    next_action.ship_state = state;
    
    // If the distance from the mixer is greater than 4, just do a random hop
    if (distance_from_mixer > 4){
        return next_action;
    }

    // Iterate through the number of connections available
    for (int i = 0; i < num_connections; i++){
        int exists = 0;

        // Check if the planet exists in the visited planets list to avoid duplicates
        for (int j = 0; j < state->numVisitedPlanets; j++){
            if (connections[i] == state->planet[j])
            {
                exists = 1;
                break;
            }
        }

        // If the planet does not exist, add it to the list of visited planets
        if (!exists){
            state->planet[state->numVisitedPlanets++] = connections[i];
        }
    }

    // Update the ship action with the selected next planet
    next_action.next_planet = state->planet[state->nextPlanetI++]; // 
    
    // Calculate and print the distance from the mixer after the hop
    printf("Hopping from planet %u to %u. Distance from mixer: %.2f\n", 
           crt_planet, state->planet[state->nextPlanetI - 1], distance_from_mixer);
    
    return next_action;
}
