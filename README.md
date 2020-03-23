# teaching-confour
This project is based on a framework for my advanced artificial intelligence class. In analogy to the referenced framework in which an artificial chess player is ought to be implemented, this project does analogous provide a framework for connect four.

## overview
The repository contains the framework itself, as well as multiple empty clients in various languages. The framework provides a generic scaffolding, while a fully implemented client represents an artificial connect four player. Therefore, the framework as well as a client need to be executed concurrently in order to have a running system.

The framework provides a graphical user interface that is accessible through a webbrowser. However, it does, unlike the chess framework, not provide any test cases. Similarly, the network interoperability of the chess framework has not been converted either.

<p align="center"><img src="http://content.sniklaus.com/confour/screenshot.png" alt="Screenshot"></p>

## usage
While this project implements most of the features of the chess framework, it is only being used for the purpose of demonstrating the applicability of adversary searches. No further explanation is therefore given and it is instead recommended to consult the chess framework.

## dependencies
Since the framework consists of several components and each component has individual dependencies, they are being listed separately.

### `framework`
* `zeromq`
* `cjson`
* `mongoose`

### `framework-webinterface`
* `jquery` / `moment`
* `bootstrap` / `fontawesome`
* `plotly`

### `client-c`
* `zeromq`
* `cjson`

### `client-java`
* `jeromq`
* `json`

### `client-python`
* `zmq`

## license
Please refer to the appropriate file within this repository.