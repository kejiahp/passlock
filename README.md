# Implementation of Password Manager in C++ (Console Application)

This project was created in fulfilment of course work 1 for the module details listed below:

- **Module Code**: CS4D768
- **Module Title**: Object Oriented Programming with Data Structures and Algorithms
- **Submission Date**: 24th November, 2025
- **Module/Leader**: Prof Janusz Kulon / Dr Shiny Verghese
- **Student Name**: Morenikeji Elijah Popoola

## Assessment Description

This project involves creating an application to securely manage usernames and passwords for multiple users. It would include features such as:

- Multi-user account support with login system (normal users and admin)
- Storing and managing credentials for websites, desktop applications and games.
- Add, edit and delete credentials with audit of date created and last updated.
- Secure password storage with encryption and decryption algorithms.
- Random password generation.
- Ability to search credentials by name and sort them by last updated date.
- Masked display of passwords, with option to reveal in plain test on demand.

## Running the project locally

This project was setup using [CMake, a cross-platform build tool](https://cmake.org/) on a M1 Mac computer system.

Below are instructions to build and run the project on your local machine.

### CMake Installation

First check if CMake is installed on the system.

```sh
cmake --version # displays cmake version if its installed
```

If you see a message saying `cmake is not recognized` or something similar. Follow the steps below to install CMake on your computer.

#### CMake Installation MacOS and Windows

Install CMake (if not already installed)

```sh
brew install cmake #MacOS

https://cmake.org/download/ #Follow this URL for windows
```

#### Build Project and Run the executable

Follow this steps once CMake has been installed, do the following:

- Go to the root directory of the project.

- Create a `build` directory, change the active directory to `build`

```sh
# ./ `This is the root directory`

mkdir build && cd build
```

- Build Makefiles using CMake

```sh
# ./build

cmake ..
```

- Execute make files

```sh
# ./build

make
```

- Run the executable

```sh
# ./build

./src/passlock
```
