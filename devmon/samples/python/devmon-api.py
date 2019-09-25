#!/usr/bin/env python

import logidevmon

messagesToRead = 30

def processEvents(message):
    global messagesToRead
    print (f"{messagesToRead}: {message}")
    messagesToRead = messagesToRead -1
    return (messagesToRead>0)

mouseUnitId = 0
keyboardUnitId = 0

print ("Devices list")
logidevmon.list_devices()
for device in logidevmon.LOGITECH_DEVICES:
    print (f"{device['unitId']} {device['type']} : {device['name']}")
    
    if (device["type"] == "keyboard"):
        keyboardUnitId = device['unitId']
    
    if (device["type"] == "mouse"):
        mouseUnitId = device['unitId']

logidevmon.set_thumbWheel_config(mouseUnitId,False,False,False)
logidevmon.set_wheel_config(mouseUnitId,False,False,False)

if (len(logidevmon.LOGITECH_DEVICES)>0 and mouseUnitId != 0):    
    print(f"Using device id: {mouseUnitId}")

    print ("Get Device info")
    devinfo = logidevmon.get_device_info(mouseUnitId)
    print(devinfo)

    print ("Get spyConfig")
    config = logidevmon.get_spy_config(mouseUnitId)
    print(config)

    print ("Get specialKeys")
    config = logidevmon.get_specialKeys(mouseUnitId)

    if (config):
        for specialKey in config:
            print(specialKey["controlId"])
    else:
        print(f"No special Keys detected for {logidevmon.LOGITECH_DEVICES[selectedDevice]['name']}")

    print ("Divert wheel")
    logidevmon.set_wheel_config(mouseUnitId,True,True,True)    
    config = logidevmon.get_wheel_config(mouseUnitId)
    print(config)

    print ("Diverted wheel events")    
    logidevmon.read_events(processEvents)

    print ("Switch off divert wheel")
    logidevmon.set_wheel_config(mouseUnitId,False,False,False)
    config = logidevmon.get_wheel_config(mouseUnitId)
    print(config)

if (keyboardUnitId != 0):
    print ("Set spykeys on keyboard to true")
    logidevmon.set_spyConfig(keyboardUnitId,False,True,False,False,False)
    messagesToRead = 30
    logidevmon.read_events(processEvents)
    print ("Set spykeys to false")
    logidevmon.set_spyConfig(keyboardUnitId,False,False,False,False,False)

print ("End")