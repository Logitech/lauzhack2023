# Logitech Input Device Monitor - Node.js code sample

Code sample is located in `devmon/samples/node/index.js`.

It is a collection (suite) of test cases which demonstrate how the API works.

API for building the test suite is [Mocha](https://mochajs.org).

## Pre-requisites

Download and install [Node.js](http://nodejs.org/download/).

(Optional) Download and install [Visual Studio Code](https://code.visualstudio.com/) IDE.

## Build

From `devmon/samples/node` folder, open a terminal and run `npm i`.

It should create a `node_modules` folder with all required depdencies.

## Run

To run (without debugging) code sample, open a terminal in `devmon/samples/node` folder:

```
npm run test -- index.js --grep <test case selector>
```

where `<test case selector>` matches a test case name in `index.js`

Example:

```
npm run test -- index.js --grep enumerate
```

Will run ```it('can enumerate devices', done => {``` test case content.

## Debug

Open Visual Studio Code in root folder (the one with a `.vscode/` folder).

You should see a few debug configurations within debug menu.

You will find for instance `node: Enumerate Devices`, and can run it / add breakpoints in code etc.
