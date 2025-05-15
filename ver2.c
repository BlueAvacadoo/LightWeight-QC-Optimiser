#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants and data types
#define MAX_GATES  100
#define MAX_QUBITS  3

// Define a structure for a quantum gate
struct gate {
    char name[5];
    float theta;
    int target;
    int control;
};

// Define a structure for a quantum circuit
struct circuit {
    struct gate gates[MAX_GATES];
    int numgates;
    int num_qubits;
};
void makeckt(struct circuit *c){
    printf("how many qubits?");
    scanf("%d", &c->num_qubits);
    printf("how many gates?");
    scanf("%d", &c->numgates);

    for(int i =0; i< c->numgates; i++){
        printf("\n Gate: %d\n", i+1);
        printf("Enter gate name: ");
        scanf("%s", c->gates[i].name);

        if(strcmp(c->gates[i].name, "Rz")==0 || strcmp(c->gates[i].name, "Rx")==0){
            printf("enter theta value:");
            scanf("%f", &c->gates[i].theta);
        }
        else{
            c->gates[i].theta = 0;

        }
        printf("Target qubit: ");
        scanf("%d", &c->gates[i].target);

        if(strcmp(c->gates[i].name, "Cx")==0 || strcmp(c->gates[i].name, "Cz")==0){
            printf("Control qubit: ");
            scanf("%d", &c->gates[i].control);
        }
        else{
            c->gates[i].control = -1;
            }
    
    
        }
    }



//Self-inverse gates
void self_inverse(struct circuit *c) {
    for (int i = 0; i < c->numgates - 1; i++) {
        if (strcmp(c->gates[i].name, c->gates[i+1].name) == 0 &&
            c->gates[i].target == c->gates[i+1].target &&
            c->gates[i].control == c->gates[i+1].control &&
            (strcmp(c->gates[i].name, "X") == 0 || strcmp(c->gates[i].name, "H") == 0 || strcmp(c->gates[i].name, "Z") == 0|| strcmp(c->gates[i].name, "CX") == 0)) {
            for (int j = i; j < c->numgates - 2; j++) {
                c->gates[j] = c->gates[j + 2];
            }
            c->numgates -= 2;
            i = -1;
        }
    }
}

//Commutation
void commutation(struct circuit *c) {
    for (int i = 0; i < c->numgates - 1; i++) {
        if (c->gates[i].target != c->gates[i+1].target) {
            struct gate temp = c->gates[i];
            c->gates[i] = c->gates[i+1];
            c->gates[i+1] = temp;
        }
    }
}

//Gate fusion for Rz or Rx
void gate_fusion(struct circuit *c) {
    for (int i = 0; i < c->numgates - 1; i++) {
        if (strcmp(c->gates[i].name, c->gates[i+1].name) == 0 &&
            (strcmp(c->gates[i].name, "Rz") == 0 || strcmp(c->gates[i].name, "Rx") == 0) &&
            c->gates[i].target == c->gates[i+1].target) {
            c->gates[i].theta += c->gates[i+1].theta;
            for (int j = i+1; j < c->numgates - 1; j++) {
                c->gates[j] = c->gates[j+1];
            }
            c->numgates--;
            i = -1;
        }
    }
}

 //Layering (grouping gates by depth)
void layering(struct circuit *c) {
    printf("\nGate Layers (by qubit):\n");
    for (int q = 0; q < c->num_qubits; q++) {
        printf("Qubit %d: ", q);
        for (int i = 0; i < c->numgates; i++) {
            if (c->gates[i].target == q || c->gates[i].control == q) {
                printf("%s ", c->gates[i].name);
            }
        }
        printf("\n");
    }
} 

void print(struct circuit *c) {
    printf("\nOptimized Circuit:\n");
    for (int i = 0; i < c->numgates; i++) {
        printf("%s ", c->gates[i].name);
        if (strcmp(c->gates[i].name, "Rz") == 0 || strcmp(c->gates[i].name, "Rx") == 0)
            printf("%.2f ", c->gates[i].theta);
        printf("(target: %d", c->gates[i].target);
        if (c->gates[i].control != -1)
            printf(", control: %d", c->gates[i].control);
        printf(")\n");
    }
}


int main(void){
     struct circuit c;
    makeckt(&c);
    self_inverse(&c);
    commutation(&c);
    gate_fusion(&c);
    layering(&c);
    print(&c);
    return 0;
}