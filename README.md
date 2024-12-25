# simple logging , cos aint no way im `printf`-ing every mf time bruh

## usage
```c
#include "simple_af_logger.h"

int main() {
  SAFL_LOG_INFO("info log");
  SAFL_LOG_WARN("warning log");
  SAFL_LOG_ERROR("error log");
  return 0;
}
```
