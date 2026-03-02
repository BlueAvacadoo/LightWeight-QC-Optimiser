This is a basic quantum circuit transpiler written in bare bone C. It accepts a quantum circuit
consisting of gates performs a series of basic quantum gate optimisations to simplify the circuit.
This is useful for reducing circuit depth and gate count before which subsequently reduces error in
the probabilistic system.

Quantum Computers have a high sensitivity to environment which makes them susceptible
to error. For such sensitive computers it is necessary for the circuits to be as efficient as
possible.

How to Compile and Run

- Ensure you have a C compiler installed (e.g., GCC).
- Compile the code: gcc main.c -o transpiler -lm (the -lm flag links the math library).
- Run the executable: ./transpiler.
- Follow the prompts to input the number of qubits and the gates (e.g., gate name, target qubit, control qubit if applicable, theta value for rotations).


The project is currently at basic functionality, here are some future improvements I am
looking forward to:
• Add support for more gates (S, T, Y, Sdg, Tdg, U3)
• Add deferred measurement feature and subsequently more advanced identities
• Add a graphical front end
• Adding a python script to directly export optimised circuit to a notebook that
converts the circuit into qiskit based format, readable by IBM’s quantum simulator.