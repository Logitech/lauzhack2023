# Logitech Device Monitor Python API

import asyncio
import websockets
import json

LOGITECH_DEVICES = {}
DEVMON_URI = "ws://localhost:9876"
RESULT = {}

async def send_ws_msg(verb, path, args=0):
    global DEVMON_URI    
    async with websockets.connect(DEVMON_URI) as websocket:
        request = {
                "verb": verb,
                "path": path
            }

        if (args != 0) :
            request["args"] = args
                

        await websocket.send(json.dumps(request))

        r = await websocket.recv()

        global RESULT
        RESULT = json.loads(r)       

async def send_ws_msg_and_forget(verb, path, args=0):
    global DEVMON_URI    
    async with websockets.connect(DEVMON_URI) as websocket:
        request = {
                "verb": verb,
                "path": path
            }

        if (args != 0) :
            request["args"] = args
                
        await websocket.send(json.dumps(request))

def list_devices():
    asyncio.get_event_loop().run_until_complete(send_ws_msg("get","devices"))
    global RESULT
    if RESULT["success"]: 
        global LOGITECH_DEVICES
        LOGITECH_DEVICES = RESULT["value"]
    else:
        print(f"Error: no Logitech devices found")

def get_device_info(unitId):
    asyncio.get_event_loop().run_until_complete(send_ws_msg("get","device",{"unitId":unitId}))
    global RESULT
    if RESULT["success"]: 
        return RESULT["value"]
    else:
        print(f"Error: couldn't find a Logitech device with ID: {unitId}")

def get_config(config,unitId):
    asyncio.get_event_loop().run_until_complete(send_ws_msg("get",config,{"unitId":unitId}))
    global RESULT
    if not RESULT["success"]: 
        print(f"Error: couldn't find a Logitech device with ID: {unitId}")
    return RESULT["value"] 

def get_specialKey_config(unitId,controlId):
    asyncio.get_event_loop().run_until_complete(send_ws_msg("get","specialKeyConfig",{"unitId":unitId, "controlId":controlId}))
    global RESULT
    if not RESULT["success"]: 
        print(f"Error: couldn't find a Logitech device with ID: {unitId}")
    return RESULT["value"] 

def get_spy_config(unitId):
    return get_config("spyConfig",unitId)

def get_wheel_config(unitId):
    return get_config("wheelConfig",unitId)

def get_thumbWheel_config(unitId):
    return get_config("thumbWheelConfig",unitId)

def get_specialKeys(unitId):
    return get_config("specialKeys",unitId)

def set_spyConfig(unitId, spyButtons, spyKeys, spyPointer, spyThumbWheel, spyWheel):    
    args = {
        "value":{
            "unitId":unitId,
            "spyButtons":spyButtons,
            "spyKeys":spyKeys,
            "spyPointer":spyPointer,
            "spyThumbWheel":spyThumbWheel,
            "spyWheel":spyWheel
        }
    }
    asyncio.get_event_loop().run_until_complete(send_ws_msg_and_forget("set","spyConfig",args))

def set_specialKey_config(unitId, controlId, divert, rawXY = -1):    
    args = {
        "value":{
            "unitId":unitId,
            "controlId":controlId, 
            "divert":divert
        }
    }

    if (rawXY != -1):
        args["value"]["rawXY"] = rawXY

    asyncio.get_event_loop().run_until_complete(send_ws_msg_and_forget("set","specialKeyConfig",args))

def set_immediate_pointer_redirection_config(unitId, divert, rawXY, forceRawXY):    
    args = {
        "value":{
            "unitId":unitId,
            "controlId":215, #As of now, the only controlId supported is 215 (Virtual Gesture Button)
            "divert":divert,
            "rawXY":rawXY,
            "forceRawXY":forceRawXY
        }
    }

    asyncio.get_event_loop().run_until_complete(send_ws_msg_and_forget("set","specialKeyConfig",args))


def set_wheel_config(unitId, divert, hires, invert):
    args = {
        "value":{
            "unitId":unitId,
            "divert":divert, 
            "hires":hires, 
            "invert":invert
        }
    }
    asyncio.get_event_loop().run_until_complete(send_ws_msg_and_forget("set","wheelConfig",args))

def set_thumbWheel_config(unitId, divert, hires, invert):
    args = {
        "value":{
            "unitId":unitId,
            "divert":divert, 
            "invert":invert
        }
    }
    asyncio.get_event_loop().run_until_complete(send_ws_msg_and_forget("set","thumbWheelConfig",args))

async def _read_events(callback):
    global DEVMON_URI    
    async with websockets.connect(DEVMON_URI) as websocket:        
        async for message in websocket:
            keepReading = callback(message)
            if not keepReading:
                return    

def read_events(callback):
    asyncio.get_event_loop().run_until_complete(_read_events(callback))
