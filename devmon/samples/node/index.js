'use strict';

// Import Websocket library.
const Websocket = require('ws');

// OS library
const os = require('os');

// Unit testing helpers.
const assert = require('chai').assert;

const serverUrl = 'ws://localhost:9876';

const sleep = timeoutMs => {
    return new Promise(resolve => {
        setTimeout(resolve, timeoutMs);
    });
};

describe('logi-devmon test', () => {

    it('can enumerate devices', done => {

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'get',
                path: 'devices'
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'get');
            assert.equal(message.path, 'devices');
            
            // Dump devices
            console.log('Devices:');
            for (const device of message.value) {
                console.log(device);
            }

            // Close connection
            ws.close();
        });
    });

    it('can get device info', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'get',
                path: 'device',
                args: { unitId }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'get');
            assert.equal(message.path, 'device');
            
            // Dump info
            console.log('Device info: %O', message.value);

            // Close connection
            ws.close();
        });
    });

    it('can get spy config', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'get',
                path: 'spyConfig',
                args: { unitId }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'get');
            assert.equal(message.path, 'spyConfig');
            
            // Dump config
            console.log('Spy config: %O', message.value);

            // Close connection
            ws.close();
        });
    });

    it('can spy device', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Spy all
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'spyConfig',
                args: { value: { unitId, spyButtons: true, spyKeys: true, spyWheel: true, spyThumbWheel: true, spyPointer: true } }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'event');
            
            // Dump event
            console.log('%O: %O', message.path, message.value);
        });

        // Test will end after 10 seconds
        setTimeout(() => {

            // Stop spying
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'spyConfig',
                args: { value: { unitId, spyButtons: false, spyKeys: false, spyWheel: false, spyThumbWheel: false, spyPointer: false } }
            }));

            console.log('Test ending');
            ws.close();
        }, 10000);
    });

    it('can get wheel config', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'get',
                path: 'wheelConfig',
                args: { unitId }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'get');
            assert.equal(message.path, 'wheelConfig');
            
            // Dump config
            console.log('Wheel config: %O', message.value);

            // Close connection
            ws.close();
        });
    });

    it('can get wheel events', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'wheelConfig',
                args: { value: { unitId, divert: true, hires: true } }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'event');
            assert.equal(message.path, 'wheel');
            
            // Dump event
            console.log(message.value);
        });

        // Test will end after 10 seconds
        setTimeout(() => {

            // Stop spying
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'wheelConfig',
                args: { value: { unitId, divert: false, hires: false } }
            }));

            console.log('Test ending');
            ws.close();
        }, 10000);
    });

    it('can get thumb wheel config', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'get',
                path: 'thumbWheelConfig',
                args: { unitId }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'get');
            assert.equal(message.path, 'thumbWheelConfig');
            
            // Dump config
            console.log('Thumb Wheel config: %O', message.value);

            // Close connection
            ws.close();
        });
    });

    it('can get thumb wheel events', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'thumbWheelConfig',
                args: { value: { unitId, divert: true } }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'event');
            assert.equal(message.path, 'thumbWheel');
            
            // Dump event
            console.log(message.value);
        });

        // Test will end after 10 seconds
        setTimeout(() => {

            // Stop spying
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'thumbWheelConfig',
                args: { value: { unitId, divert: false } }
            }));

            console.log('Test ending');
            ws.close();
        }, 10000);
    });

    it('can get special keys config', done => {

        const unitId = 1953575442; // Replace with your device's unitId

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'get',
                path: 'specialKeys',
                args: { unitId }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        let specialKeys = null;
        let specialKeyConfigCount = 0;

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'get');

            if (message.path == 'specialKeys') {
                specialKeys = message.value;
                console.log('Special keys: %O', specialKeys);

                for (const specialKey of specialKeys) {

                    // Get special key configuration
                    ws.send(JSON.stringify({
                        verb: 'get',
                        path: 'specialKeyConfig',
                        args: { unitId, controlId: specialKey.controlId }
                    }));
                }

            } else if (message.path == 'specialKeyConfig') {
                console.log('Special key config: %O', message.value);

                specialKeyConfigCount++;

                // We've done enumerating all special keys configuration
                if (specialKeyConfigCount === specialKeys.length) {

                    // Close connection
                    ws.close();
                }

            } else {
                assert.fail();
            }
        });
    });

    it('can divert special key', done => {

        const unitId = 1953575442; // Replace with your device's unitId
        const controlId = 82; // Middle button

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'specialKeyConfig',
                args: { value: { unitId, controlId, divert: true } }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'event');
            assert.equal(message.path, 'divertedButtons');
            
            // Dump event
            console.log(message.value);
        });

        // Test will end after 10 seconds
        setTimeout(() => {

            // Stop spying
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'specialKeyConfig',
                args: { value: { unitId, controlId, divert: false } }
            }));

            console.log('Test ending');
            ws.close();
        }, 10000);
    });

    it('can divert pointer when pressing middle button', done => {

        const unitId = 1953575442; // Replace with your device's unitId
        const controlId = 82; // Middle button

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'specialKeyConfig',
                args: { value: { unitId, controlId, divert: true, rawXY: true } }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'event');
            assert.isTrue(message.path === 'divertedButtons' || message.path === 'divertedRawXY');
            
            // Dump event
            console.log('%O: %O', message.path, message.value);
        });

        // Test will end after 10 seconds
        setTimeout(() => {

            // Stop spying
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'specialKeyConfig',
                args: { value: { unitId, controlId, divert: false, rawXY: false } }
            }));

            console.log('Test ending');
            ws.close();
        }, 10000);

    });

    it('can forcibly divert pointer', done => {

        const unitId = 1953575442; // Replace with your device's unitId
        const controlId = 215; // Virtual gesture button

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', () => {
            console.log('Connected to server');

            // Send command to server
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'specialKeyConfig',
                args: { value: { unitId, controlId, divert: true, rawXY: true, forceRawXY: true } }
            }));
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });

        ws.on('error', error => {
            console.log('An error occurred');
            console.error(error);
        });

        ws.on('message', messageJson => {
            
            // Parse received message
            const message = JSON.parse(messageJson);
            assert.isTrue(message.success);
            assert.equal(message.verb, 'event');
            assert.equal(message.path, 'divertedRawXY');
            
            // Dump event
            console.log(message.value);
        });

        // Test will end after 10 seconds
        setTimeout(() => {

            // Stop spying
            ws.send(JSON.stringify({
                verb: 'set',
                path: 'specialKeyConfig',
                args: { value: { unitId, controlId, divert: false, rawXY: false, forceRawXY: false } }
            }));

            console.log('Test ending');
            ws.close();
        }, 10000);
    });

    it('can type text', done => {

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', async () => {
            console.log('Connected to server');

            console.log('Sleep 3 seconds, grab a text editor!');
            await sleep(3000);
            
            console.log('send_input');
            ws.send(JSON.stringify({
                verb: 'send_input',
                path: 'text',
                args: { value: 'HackZürich 2019 rocks!' }
            }));

            console.log('Test ending');
            ws.close();
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });
    });

    it('can send keystroke', done => {

        const vkey = os.type() == 'Windows_NT' ? 0x34 : 21; // '4' on Windows
        const pressed = true;

        // Connect to websocket server
        const ws = new Websocket(serverUrl);

        ws.on('open', async () => {
            console.log('Connected to server');

            console.log('Sleep 3 seconds, grab a text editor!');
            await sleep(3000);

            console.log('send_input');
            ws.send(JSON.stringify({
                verb: 'send_input',
                path: 'key',
                args: { vkey, pressed }
            }));

            console.log('Test ending');
            ws.close();
        });

        ws.on('close', () => {
            console.log('Connection closed');

            // End test case
            done();
        });
    });
});
