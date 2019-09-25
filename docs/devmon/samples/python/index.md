# Logitech Input Device Monitor - Python code sample

Code sample is located in `devmon/samples/python/`.

`logidevmon.py` contains a collection of functions to use the Device Monitor API in your Python scripts.  See `devmon-api.py` to see the API in action.

## Pre-requisites

Download and install [Anaconda](https://www.anaconda.com/distribution/#download-section).

Launch an Anaconda prompt and setup your environment:

    `conda create --name devmon python=3.7`
    
    `conda activate devmon`
    
    `conda install -c conda-forge websockets`

## Run
Run logi-devmon (WS server)

In your Anaconda environment, test basic functionality with :

    `python devmon-api.py`