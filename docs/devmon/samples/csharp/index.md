# Logitech Input Device Monitor - C# code sample

Code sample is located in `devmon/samples/csharp/`.

This is a MS Visual Studio project with handy functions to see the API in action.

## Pre-requisites

Download and install [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/).

## Run
Run logi-devmon (WS server)

Open the `devmon-csharp` solution file to build and run the sample code.

This example shows how to get a list of devices. If a MX Keys keyboard is detected, the program activates the spy configuration to retrieve key events. 50 key events are logged to the console before the program stops.