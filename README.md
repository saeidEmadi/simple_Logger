# Qt Simple logger
This is a ready-made code to facilitate logging Qt Applications outputs (with QDebug)
## Installation
-  copy Logger folder in your code path

- Add the `Logger.pri` file to the `*.pro` file in your project
```cpp
include($$PWD/Logger/Logger.pri)
```
- Add Logger Header in `main.cpp` ***(Application Entery Point)***
```cpp
#include "Logger.h"
```
## Usage
- Add the configuration codes in the main file ***e.g*** `main.cpp` ***(Application Entery Point)***
```cpp
Logger::attach();
Logger::logging = true;
```
> [!NOTE]  
>You can see where the log is stored by printing `Logger::logFileName`


------------
### Enjoy it :)
