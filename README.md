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
- Masked display of passwords, with option to reveal in plain text on demand.

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

##### Install CMake

```sh
brew install cmake # MacOS

https://cmake.org/download/ # Follow this URL for Windows
```

#### OpenSSL Installation MacOS and Windows

The project uses OpenSSL for hashing and encryption/decryption of credentials.

Check if OpenSSL is already installed

```sh
openssl --version # both MacOS and Windows
```

##### Install OpenSSL MacOS

```sh
brew install openssl
```

After installation, if openssl is still not found, ensure shell configuration file (.zshrc, .bash_profile, etc) is updated.

##### Install OpenSSL Windows

Follow this link [How to install OpenSSL (3.0.1) on Windows 10 (64-bit)](https://youtu.be/jrHnP6Gazf0?si=E7tmClrxQrJZ7h6h). Installing versions `3.5.2` and above should be fine.

#### Build Project and Run the executable

Follow this steps once CMake and OpenSSL have been installed, do the following:

- Go to the root directory of the project.

- Execute the build scripts:

  ```sh
  sh build.sh #MacOS

  ./winbuild.bat # Windows Powershell

  winbuild.bat # Windows Command Prompt (CMD)
  ```

- Windows Powershell and CMD Emoji Configuration (_OPTIONAL_)

  At times windows terminals need needs extra configurations allowing emojis to be displayed properlly the commands below help with that.

  ```sh
  [Console]::OutputEncoding = [System.Text.Encoding]::UTF8 # Windows Powershell

  chcp 65001 # Windows Command Prompt (CMD)
  ```

- Run the executable:

  ```sh
  ./build/src/passlock # MacOS

  .\build\src\Release\passlock.exe # Windows
  ```

## High-Level System Design (My Thought Process on the implementation)

In this section we will be going through the [assessment description](#assessment-description) and outlining how we will implement each feature.

Markdown tables were generated using [www.tablesgenerator.com](https://www.tablesgenerator.com/markdown_tables#)

We will be using [SQLiteC++](https://github.com/SRombauts/SQLiteCpp) as our sqlite cli. Its essentially a lightweight C++ wrapper around the SQLite (sqlite3) library. Its provides the following features which make it a great choice:

- RAII resource management.
- First class C++ support as opposed to SQLite(sqlite3) which is C-based.

### 1. Multi-user account support with login system (normal users and admin).

Solution:

- User database schema collecting minimal information along with user types e.g. `NORMAL` and `ADMIN`.

  - **User schema**: This represents the schema for storing user details.

    | id  | email  | password | type            | key    | iv     | createdAt | updatedAt |
    | --- | ------ | -------- | --------------- | ------ | ------ | --------- | --------- |
    | int | string | string   | NORMAL or ADMIN | string | string | datetime  | datetime  |

- Account creation process, information like email (unique), password (it will be hashed) is collected and saved in a datastore, We will be using SQlite for datastore ensuring data persistence.
- Login system where the user authenticates with their email and password. The password gets hashed and compared with the already stored hashed password. If they are same they are granted access to their data else an appropriate error message is displayed.

### 2. Storing and managing credentials for websites, desktop applications and games.

Solution:

- **Credentail schema**: This represents the schema for storing user credentails.

  | id  | userId | title  | email   | username | password | url     | createdAt | updatedAt |
  | --- | ------ | ------ | ------- | -------- | -------- | ------- | --------- | --------- |
  | int | int    | string | string? | string?  | string?  | string? | datetime  | datetime  |

### 3. Add, edit and delete credentials with audit of date created and last updated.

Solution:

- Basic CRUD operations on the **Credential** schema, ensuring this operations can only be performed by the user whom created the account.

### 4. Secure password storage with encryption and decryption algorithms.

Solution:

- Use [OpenSSL](https://openssl-library.org/) for Encryption/Decryption and Hashing.

### 5. Random password generation.

Solution:

- This will be done using the random password generator function provided by the static `utilities` library.

### 6. Ability to search credentials by name and sort them by last updated date.

Solution:

- Search: Credentials should be searchable via the `title` field of the `Credentails` table.
- Sort: Credential should be sortable using the `updatedAt` field of the `Credentials` table. The sorting by default should be in descending order.

### 7. Masked display of passwords, with option to reveal in plain text on demand.

Solution:

- This will use a unique key created for each user on sign up to decrypt their passwords, revealing it in a readable plain-text format.
