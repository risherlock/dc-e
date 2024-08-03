# Practical considerations of the digital PID controller

The documentation, as it is, is not complete because the second presentation has yet to take place.

## Abstract

The goal of these presentations is to study PID algorithm and its practical implications. Theoretical discourse is followed by design and development of C++ PID library for embedded system and its implementation for angular rate control of DC brushed motor.

We start with the PID control in its standard form $$u(t)=k_{\text{p}}+k_{\text{i}}\int_{0}^{t}e(\tau)\text{d}\tau+k_{\text{d}}\frac{\text{d}}{\text{d}t}e(t)$$ and explore the necessary steps that need to be considered for a robust digital implementation of the algorithm. We begin with the discretization of PID for software implementation followed by detailed analysis of derivative action in response to noisy input and to the step response; formal leads to the use of LPF and the latter to the notion of setpoint weighing. Windup effect of integrator is considered with its remedies.

## Resources

1. [Slides: Practical considerations of the digital PID controller - I](https://docs.google.com/presentation/d/1D3b5DKBIZ9c9zFgfUgT3De1V4krvGlq5N0wZwVRe7Ws)
1. [Slides: Practical considerations of the digital PID controller - II](https://docs.google.com/presentation/d/1D3b5DKBIZ9c9zFgfUgT3De1V4krvGlq5N0wZwVRe7Ws)
2. [Report on the PID controller based on the presentation](https://www.overleaf.com/read/wmkhdnhyztcy#711179)
3. [Source code to the demonstration project on PID control of DC brushed motor](motor_control)
