# Logitech Input Device Monitor API

This is the documentation for `logi-devmon` websocket API (works on Windows / Mac / Linux)

Purpose of it is to provide access to Logitech input device events (e.g. key presses) the easy way.

With the API can spy device and trap a couple of events.

## Pre-requisites

Ensure you have a Logitech mouse or Keyboard connected to your computer. Supported devices for this hackathon are MX Master 3 (mouse) and MX Keys (keyboard).

Download [logi-devmon executable](https://github.com/Logitech/hackzurich2019/tree/master/devmon/bin) and run it from a terminal.

You will need to allow websocket server through your firewall.

*Note*: `logi-devmon` dumps received data in standard output, which will help you debugging your code.

## TL;DR; Let me try!

Launch `logi-devmon`, and open your web browser at [this URL](https://logitech.github.io/hackzurich2019/devmon/test/).

You will experiment with the possibilities of the API.

For understanding the API, please read API documentation and play with code samples.

## API documentation

### Connecting to websocket server

Using your favorite language, connect to `ws://localhost:9876`.

### Message format

Messages are serialized in JSON format, and are of the following types:

1. Command invocation
2. Command results
3. Events (notifications)

You shall send 1. to websocket server, and then you will receive 2. and/or 3. depending on the command(s) you've previously sent.

### Error handling

Error handling is basic.

You should check for `success` boolean value in incoming messages (commands and events) to be equal to `true`.

### Enumerate devices

Send the following command:

```
{
    "verb": "get",
    "path": "devices"
}
```

You should receive following result:

```
{
    "verb": "get",
    "path": "devices",
    "success": true,
    "value": an array of device JSON objects
}
```

Example of a device object:

```
{
    "hasSpecialKeys":true,
    "hasThumbWheel":true,
    "hasWheel":true,
    "isConnected":true,
    "name":"Wireless Mouse MX Master 3",
    "type":"mouse",
    "unitId":1953575442
}
```

*Note*: ```unitId``` is unique per device (serial number).

### Get device info

This is a shorthand of previous command, but targetted to a particular device.

Send the following command:

```
{
    "verb": "get",
    "path": "device",
    "args": { "unitId": unit id of the device }
}
```

Example:

```
{
    "verb": "get",
    "path": "device",
    "args": { "unitId": 1953575442 }
}
```

Returned object is same as described above.

### Device connection status changed event

When your device is turned ON/OFF, you will receive the following event:

```
{
    "success": true,
    "verb": "event",
    "path": "deviceConnectionChanged",
    "value":
    {
        "isConnected": true or false,
        "unitId": unit id of the device
    }
}
```

Please ensure that your device is connected before sending commands.

### Get device spy configuration

Send the following command:

```
{
    "verb": "get",
    "path": "spyConfig",
    "args": { "unitId": unit id of the device }
}
```

You should receive following result:

```
{
    "unitId": unit id of the device
    "spyButtons": true or false,
    "spyKeys": true or false,
    "spyPointer": true or false,
    "spyThumbWheel": true or false,
    "spyWheel": true or false,
}
```

For example:

```
{
    "unitId":1953575442,
    "spyButtons":false,
    "spyKeys":false,
    "spyPointer":false,
    "spyThumbWheel":false,
    "spyWheel":false
}
```

### Spy device events

Send the following command:

```
{
    "verb": "set",
    "path": "spyConfig",
    "args":
    {
        "value":
        {
            "unitId": unit id of the device,
            "spyButtons": true or false,
            "spyKeys": true or false,
            "spyPointer": true or false,
            "spyThumbWheel": true or false,
            "spyWheel": true or false,
        }
    }
}
```

You should now receive events coming from the device, with the following format:

```
{
    "success": true,
    "verb": "event",
    "path": one of "button", "key", "pointer", "hwheel" or "wheel",
    "value": depends on "path"
}
```

* `button` event example `value`:

```
{
    "number":0,
    "pressed":true,
    "unitId":1953575442
}
```

`number` take the following value:

0. Left button
1. Right button
2. Middle button
3. Back button
4. Forward button

* `key` event example `value`:

```
{
    "pressed":true,
    "unitId":1953575442,
    "vkey":32
}
```

`vkey` is an OS-dependent virtual key code.

See [Windows documentation](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) and look for *Virtual key codes* in [Macintosh Toolbox Essentials](https://developer.apple.com/library/archive/documentation/mac/pdf/MacintoshToolboxEssentials.pdf).

* `pointer` event example `value`:

```
{
    "unitId":1953575442,
    "x":464,
    "y":822
}
```

x and y are absolute screen coordinates.

* `hwheel` event example `value`:

```
{
    "delta":120,
    "unitId":1953575442
}
```

* `wheel` event example `value`:

```
{
    "delta":120,
    "unitId":1953575442
}
```

**Notes**

* On MacOS you should run `logi-devmon` as sudo, and add it to accessibility exceptions to be able to inject keys.
* On Linux, you can update your udev rules to allow interacting with hidraw and input devices, or simply run as sudo.

**Limitation**

If you connect devices through a same Unifying receiver, API is not able to determine from which device the event comes from.

### Get wheel configuration

Send the following command:

```
{
    "verb": "get",
    "path": "wheelConfig",
    "args": { "unitId": unit id of the device }
}
```

You should receive following result:

```
{
    "verb": "get",
    "path": "wheelConfig",
    "success": true,
    "value":
    { 
        "unitId": unit id of the device,
        "divert": true or false,
        "hires": true or false,
        "invert": true or false
    }
}
```

*Notes*

* Invering wheel event is to mimic Apple's natural scrolling.
* When ```hires``` is set to ```true```, mouse will report much more wheel increments than when set to ```false```.

### Divert wheel events

Send the following command:

```
{
    "verb": "set",
    "path": "wheelConfig",
    "args":
    {
        "value":
        {
            "unitId": unit id of the device,
            "divert": true,
            "hires": true or false,
            "invert": true or false
        }
    }
}
```

You should now receive events coming from the device, with the following format:

```
{
    "success": true,
    "verb": "event",
    "path": "wheel",
    "value":
    {
        "unitId": unit id of the device,
        "delta": integer
        "hires": true or false
        "periods": integer
    }
}
```

*Note*: ```periods``` is the number of sampling periods combined in the event.

### Get thumb wheel configuration

Send the following command:

```
{
    "verb": "get",
    "path": "thumbWheelConfig",
    "args": { "unitId": unit id of the device }
}
```

You should receive following result:

```
{
    "verb": "get",
    "path": "thumbWheelConfig",
    "success": true,
    "value":
    { 
        "unitId": unit id of the device,
        "divert": true or false,
        "invert": true or false
    }
}
```

*Note*: Inverting wheel event is to mimic Apple's natural scroll.

### Divert thumb wheel events

Send the following command:

```
{
    "verb": "set",
    "path": "thumbWheelConfig",
    "args":
    {
        "value":
        {
            "unitId": unit id of the device,
            "divert": true,
            "invert": true or false
        }
    }
}
```

You should now receive events coming from the device, with the following format:

```
{
    "success": true,
    "verb": "event",
    "path": "thumbWheel",
    "value":
    {
        "unitId": unit id of the device,
        "proxy": true or false
        "singleTap": true or false
        "touch": true or false
        "rotation": integer,
        "rotationStatus": integer
    }
}
```

```rotation``` is the relative wheel rotation.

```rotationStatus``` applies to wheel rotation. The following values are possible:

0. Inactive (no rotation)
1. Start    (first rotation report)
2. Active   (next rotation reports)
3. Stop     (release, no touch)

Thumb wheel also detects proximity (`proxy` set to `true`), tap gesture (`singleTap` set to `true`), and when user finger touches it (`touch` set to `true`).

### Get special keys configuration

Send the following command:

```
{
    "verb": "get",
    "path": "specialKeys",
    "args": { "unitId": unit id of the device }
}
```

You should receive following result:

```
{
    "verb": "get",
    "path": "specialKeys",
    "success": true,
    "value": an array of specialKey JSON objects
}
```

Example of a specialKey object:

```
{
    "unitId":1953575442
    "controlId":82,
    "type":"mouse",
    "divert":true,
    "persist":false,
    "fpos":0,
    "fntog":false,
    "rawXY:true,
    "forceRawXY":false,
}
```

- `controlId` is a key identifier. Possible values are found in [control IDs table](./controlids.md).
- `type` is the type of key. One of:
  -  `mouse`: a mouse button.
  -  `fkey`: a function key. In this case, `fpos` is the position of the key, e.g. `8` for F8.
  -  `hotkey`: the key is a nonstandard key which doesn't reside on a function key. It may be anywhere on the device, including the function key row.
  -  `virtual`: this is a special key which does not exist, but enables to divert mouse pointer.   
- `divert`: the key can be diverted, so that events are trapped by the API and not forwarded to the operating system.
- `persist`: if the key is diverted (`divert` set to `true`), it can remain diverted after device is turned OFF then ON.
- `rawXY`: this key supports pointer redirection when pressing it (see below).
- `forceRawXY`: this key supports immediate pointer redirection (see below).

Then, for each special key, you should obtain its configuration by issuing:

```
{
    "verb": "get",
    "path": "specialKeyConfig",
    "args":
    {
        "unitId": unit id of the device,
        "controlId": the control id of the special key you want to configure
    }
}
```

You should receive following result:

```
{
    "verb": "get",
    "path": "specialKeyConfig",
    "success": true,
    "value": a specialKeyConfig object
}
```

Example of a specialKeyConfig object:

```
{
    "unitId":1953575442
    "controlId":82,
    "divert":false,
    "persist":false,
    "rawXY:false,
    "forceRawXY":false,
}
```

- `divert`: the key is diverted.
- `persist`: the key is persisted. Valid only if `divert` equals `true`.
- `rawXY`: the key is in pointer redirection mode. Valid only if `divert` equals `true`.
- `forceRawXY`: the key is diverted. Valid only if `divert` and `rawXY` equals `true`.

### Divert a special key

You should send the following command:

```
{
    "verb": "set",
    "path": "specialKeyConfig",
    "args":
    {
        "value":
        {
            "unitId": unit id of the device,
            "controlId": the control id of the special key you want to configure,
            "divert": true
        }
    }
}
```

You should now receive events coming from the device, with the following format:

```
{
    "success": true,
    "verb": "event",
    "path": "divertedButtons",
    "value":
    {
        "unitId": unit id of the device,
        "cid1": 1st pressed control id (0 if none),
        "cid2": 2nd pressed control id (0 if none),
        "cid3": 3rd pressed control id (0 if none),
        "cid4": 4th pressed control id (0 if none)
    }
}
```

The pressed control IDs are filled in historical order.

So if you first press 83 then 82, then release 83, you will get:

```
{ "cid1": 83, "cid2": 0, "cid3": 0, "cid4": 0, "unitId": 1953575442 }
{ "cid1": 83, "cid2": 82, "cid3": 0, "cid4": 0, "unitId": 1953575442 }
{ "cid1": 82, "cid2": 0, "cid3": 0, "cid4": 0, "unitId": 1953575442 }
{ "cid1": 0, "cid2": 0, "cid3": 0, "cid4": 0, "unitId": 1953575442 }
```

### Divert pointer while pressing on a special key (rawXY)

You should send the following command:

```
{
    "verb": "set",
    "path": "specialKeyConfig",
    "args":
    {
        "value":
        {
            "unitId": unit id of the device,
            "controlId": the control id of the special key you want to configure,
            "divert": true,
            "rawXY:true
        }
    }
}
```

The special key should support pointer redirection (`rawXY` equals `true` in specialKey object).

You should receive `divertedButtons` events with the control ID you configure, as soon as you press or release it, as well as the following events when you will move your device:

```
{
    "success": true,
    "verb": "event",
    "path": "divertedButtons",
    "value":
    {
        "dx": relative displacement on X axis,
        "dy": relative displacement on Y axis,
        "unitId": unit id of the device
    }
}
```

### Immediate pointer redirection (forceRawXY)

You should send the following command:

```
{
    "verb": "set",
    "path": "specialKeyConfig",
    "args":
    {
        "value":
        {
            "unitId": unit id of the device,
            "controlId": 215,
            "divert": true,
            "rawXY:true,
            "forceRawXY:true,
        }
    }
}
```

The special key should support pointer redirection (`rawXY` and `forceRawXY` equals `true` in specialKey object), and its `type` should be `virtual`.

As of now, the only `controlId` supported is 215 (Virtual Gesture Button). 

See [control IDs table](./controlids.md)

### Send text input (Mac OS and Windows)

You should send the following command:

```
{
    "verb": "send_input",
    "path": "text",
    "args":
    {
        "value": <a string to inject>
    }
}
```

Then `<a string to inject>` should be printed to foreground application (e.g. a text editor).

You can use it to inject say a code snippet.

*Note*: on Mac OS, you add logi-devmon to accessibility menu.