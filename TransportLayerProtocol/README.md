## ECE 303 Communication Networks Projects
This folder contains the final project for course ECE 303 Communication Networks
The second project is a transport layer protocol to transmit data through an unreliable channel

`channelsimulation.py` contains a simple API for a mock connection over an unreliable channel. `sender.py` and `receiver.py` are mock sender and receivers that use this unreliable channel. These are examples that do not properly handle the bit errors in the channel.

The channel simulator will simulate random bit errors, packet loss, and packet duplication.

## Objective
The goal of this project is to develop a transport layer protocol that can successfully and quickly transmit bits over this unreliable channel. The protocol will be implemented in your versions `sender.py` and `receiver.py`. The implementations should inherit from the Bogo{Receiver,Sender} classes in from this repository and override the receive() and send() methods.The submitted sender and receiver implementations must be able to:
* Sucessfully transfer data over the noisy channel
* Be fast
* Keep channelsimulator.py unchanged in any submitted code.  

## Test Run
To run your code, you just have to use `make test` and to check if works, you can either diff the fiies or run `make diff`.



