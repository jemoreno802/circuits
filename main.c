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

//Matt method to test INVERTER to make a 1 input NOT circuit
static Circuit* Circuit_not1() {
	Value* in0 = new_Value(false);
	Gate* not0 = new_Inverter(in0);

	Value** inputs = new_Value_array(1);
	inputs[0] = in0;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(not0);
	Gate** gate = new_Gate_array(1);
	gate[0] = not0;
	return new_Circuit(1, inputs, 1, outputs, 1, gate);
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

//Matt method to test NOT gate
static void test1In1Out(Circuit* circuit, bool in0) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s -> %s\n", b2s(in0), b2s(out0));
}

//Matt method to create Circuit(a)
static Circuit* Circuits_ca() {
	Value* x = new_Value(false);
	Value* y = new_Value(false);
	Value* z = new_Value(false);
	Gate* notY = new_Inverter(y);

	Value** inputs = new_Value_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;
	Value** outputs = new_Value_array(4);
	outputs[0] = Gate_getOutput(notY); //Storing value of !y
	Value_print(outputs[0]);

	Gate* xAndNoty = new_AndGate(x, outputs[0]); //AND gate for x AND !y
	outputs[1] = Gate_getOutput(xAndNoty); //Storing value for x AND !y

	Gate* yAndz = new_AndGate(y, z); //AND gate of y AND z
	outputs[2] = Gate_getOutput(yAndz); //Storing value for y AND z

	Gate* finalOr = new_OrGate(outputs[1], outputs[2]); //OR gate for (x!y + yz)
	outputs[3] = Gate_getOutput(finalOr);

	Gate** gates = new_Gate_array(4);
	gates[0] = notY;
	gates[1] = xAndNoty;
	gates[2] = yAndz;
	gates[3] = finalOr;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

static void testCircuita(Circuit* circuit, bool x, bool y, bool z) {
	Circuit_setInput(circuit, 0, x);
	Circuit_setInput(circuit, 1, y);
	Circuit_setInput(circuit, 2, z);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out3 = Circuit_getOutput(circuit, 3);
	printf("%s %s %s -> %s\n", b2s(x), b2s(y), b2s(z), b2s(out3));
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

	printf("Circuit(a) all inputs true: should be true\n");
	Circuit* cA = Circuits_ca();
	testCircuita(cA, true, true, true);
	//End Matt test cases
}
