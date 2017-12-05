/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* Circuits_and3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* and0 = new_AndGate(in0, in1);
	Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(and1);
	Gate** gates = new_Gate_array(2);
	gates[0] = and0;
	gates[1] = and1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

//Matt method to test two OR gates connnected to make a 3-input OR circuit
static Circuit* Circuits_or3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* or0 = new_OrGate(in0, in1);
	Gate* or1 = new_OrGate(Gate_getOutput(or0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or1);
	Gate** gates = new_Gate_array(2);
	gates[0] = or0;
	gates[1] = or1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

//Matt method to test INVERTER to make a 1 input NOT circuit
static Circuit* Circuit_not1() {
	Value* in0 = new_Value(false); //Value to be INVERTED
	Gate* not0 = new_Inverter(in0); //Inverting in0

	Value** inputs = new_Value_array(1); //Only one input for this circuit
	inputs[0] = in0; //Setting input
	Value** outputs = new_Value_array(1); //Only one output for this circuit
	outputs[0] = Gate_getOutput(not0); //Setting output
	Gate** gate = new_Gate_array(1); //Only one gate used in this circuit
	gate[0] = not0; //Setting gate used
	return new_Circuit(1, inputs, 1, outputs, 1, gate);
}

//Matt method to test NOT gate
static void test1In1Out(Circuit* notCircuit, bool in0) {
	Circuit_setInput(notCircuit, 0, in0); //Setting the input specified by user
	Circuit_update(notCircuit); //Updating circuit
	bool out0 = Circuit_getOutput(notCircuit, 0); //Setting the result from !in0
	printf("%s -> %s\n", b2s(in0), b2s(out0));
}

//Matt method to create Circuit(a)
static Circuit* Circuits_ca() {
	Value* x = new_Value(false);
	Value* y = new_Value(false);
	Value* z = new_Value(false);
	Gate* noty = new_Inverter(y); //First !y gate
	Gate* xAndNoty = new_AndGate(Gate_getOutput(noty), x); //Second x(!y) gate
	Gate* yAndz = new_AndGate(y, z); //Third yz gate
	Gate* finalOR = new_OrGate(Gate_getOutput(xAndNoty), Gate_getOutput(yAndz)); //Fourth (x!(y))+(yz) gate

	Value** inputs = new_Value_array(3); //Only three inputs for this circuit
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	Value** outputs = new_Value_array(1); //Only one output for this circuit
	outputs[0] = Gate_getOutput(finalOR); //Setting final output
	Gate** gates = new_Gate_array(4); //Setting all 4 gates used
	gates[0] = noty;
	gates[1] = xAndNoty;
	gates[2] = yAndz;
	gates[3] = finalOR;
	return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

static void testCircuita(Circuit* circuitA, bool x, bool y, bool z) {
	Circuit_setInput(circuitA, 0, y);
	Circuit_setInput(circuitA, 1, x);
	Circuit_setInput(circuitA, 2, z);
	Circuit_update(circuitA);
	bool out0 = Circuit_getOutput(circuitA, 0);
	printf("((!%s)%s)+((%s)%s) -> %s\n", b2s(y), b2s(x), b2s(y), b2s(z), b2s(out0));
}

static Circuit* Circuits_cb(){
	Value* x = new_Value(false);
	Value* y = new_Value(false);
	Value* z = new_Value(false);
	Gate* A = new_Inverter(y);
	Gate* preB = new_AndGate(Gate_getOutput(A),x); //the AND of x and NOTy
	Gate* B = new_Inverter(Gate_getOutput(preB)); //inversion of preB
	Gate* preC = new_AndGate(y,z);					//the AND of y and z
	Gate* C = new_Inverter(Gate_getOutput(preC)); //inversion of preC
	Gate* preD = new_OrGate(Gate_getOutput(B),Gate_getOutput(C)); //or of C and B
	Gate* D = new_Inverter(Gate_getOutput(preD));

	Value** inputs = new_Value_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	Value** outputs = new_Value_array(1); 
	outputs[0] = Gate_getOutput(D);
	Gate** gates = new_Gate_array(7);
	gates[0] = A;
	gates[1] = preB;
	gates[2] = B;
	gates[3] = preC;
	gates[4] = C;
	gates[5] = preD;
	gates[6] = D;
	return new_Circuit(3,inputs,1,outputs,7,gates);
}

static void testCircuitB(Circuit* circuitB, bool x, bool y, bool z){
	Circuit_setInput(circuitB,0,x);
	Circuit_setInput(circuitB,1,y);
	Circuit_setInput(circuitB,2,z);
	Circuit_update(circuitB);
	bool out0 = Circuit_getOutput(circuitB,0);
	printf("!((!%s)%s)+!((%s)%s) -> %s\n", b2s(y), b2s(x), b2s(y), b2s(z), b2s(out0));

}

int main(int argc, char **argv) {
	Circuit* c = Circuits_and3();
	printf("Some input(s) false: should be false\n");
	test3In1Out(c, true, true, false);
	printf("All inputs true: should be true\n");
	test3In1Out(c, true, true, true);

	//Matt test cases
	printf("All inputs false: should be false\n");
	test3In1Out(c, false, false, false);

	printf("One input true: should be true\n");
	Circuit* cO = Circuits_or3();
	test3In1Out(cO, true, false, false);

	printf("All input false: should be false\n");
	Circuit* c1 = Circuits_or3();
	test3In1Out(c1, false, false, false);

	printf("Inverting true: shoule be false\n");
	Circuit* cNOT0 = Circuit_not1();
	test1In1Out(cNOT0, true);

	printf("Circuit(a) inputs true: should be true\n");
	Circuit* cA = Circuits_ca();
	testCircuita(cA, false, true, true); //Passing in inputs to test in circuit(a)
	//End Matt test cases

	printf("Circuit(b) any combination of inputs: should be false\n");
	Circuit* cB = Circuits_cb();
	testCircuitB(cB, true,true,true);
	Circuit_dump(cB);
}
