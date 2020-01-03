# cpp-indicators

A very simple, easy-to-use, and single-header-only C++ library for console based indicators (loading spinners)

## Pre-made frames (indicator types)
| Type | Preview                                                                                          |
|------|--------------------------------------------------------------------------------------------------|
| 0    | ![ScreenShot](https://raw.githubusercontent.com/AmyrAhmady/cpp-indicators/master/previews/0.gif) |
| 1    | ![ScreenShot](https://raw.githubusercontent.com/AmyrAhmady/cpp-indicators/master/previews/1.gif) |
| 2    | ![ScreenShot](https://raw.githubusercontent.com/AmyrAhmady/cpp-indicators/master/previews/2.gif) |
| 3    | ![ScreenShot](https://raw.githubusercontent.com/AmyrAhmady/cpp-indicators/master/previews/3.gif) |
| 4    | ![ScreenShot](https://raw.githubusercontent.com/AmyrAhmady/cpp-indicators/master/previews/4.gif) |
| 5    | ![ScreenShot](https://raw.githubusercontent.com/AmyrAhmady/cpp-indicators/master/previews/5.gif) |
| 6    | ![ScreenShot](https://raw.githubusercontent.com/AmyrAhmady/cpp-indicators/master/previews/6.gif) |

## Examples

### Basic usage:

```cpp
#include <iostream>
#include <chrono>
#include "indicators.hpp"
using namespace std::chrono;

int main()
{
    auto spin = std::make_unique<indicator::indicator>(200ms, 0);
    spin->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    spin->stop();
    return 0;
}
```


### Including prefix, suffix, and final message:

```cpp
#include <iostream>
#include <chrono>
#include "indicators.hpp"
using namespace std::chrono;

int main()
{
    auto spin = std::make_unique<indicator::indicator>(200ms, 0, "Finished loading some data", "Process info: ", " Loading data...");
    spin->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    spin->stop();
    return 0;
}
```

You can decide if you want to hide the loading line after process or keep it
by setting `hide_on_end` parameter to `true` or `false` in `indicator` constructor. Example:
```cpp
// this hides loading line after process
auto spin = std::make_unique<indicator::indicator>(200ms, 0, "Finished loading some data", "Process info: ", " Loading data...", true);

// this keeps the loading line
auto spin = std::make_unique<indicator::indicator>(200ms, 0, "Finished loading some data", "Process info: ", " Loading data...", false);
```

### Indicator with custom frames

```cpp
std::vector<std::string> custom_indicator = 
{"aaaaa", "aaaa ", "aaa  ", "aa   ", "a    ", "     ", "aa   ", "aaa  ", "aaaa ", "aaaaa", " aaaa", "  aaa", "   aa", "    a", "     ", "   aa", "  aaa", " aaaa"};
auto spin = std::make_unique<indicator::indicator>(100ms, 0, "Final msg", "prefix", "suffix", false, custom_indicator);
```

### Changes during the process

You can change prefix, suffix, and final message during the indicator process as well, not just on initialization.
Or even changing the timer interval (delay value). Example:
(it can be useful for stuff like downloading files or something that needs updating messages like pecent or speed)
```cpp
auto spin = std::make_unique<indicator::indicator>(200ms, 0);
spin->start();
spin->set_suffix(" Downloading files...");
spin->set_prefix("Download info: ");
spin->set_end_msg("Okay seems like we're done");
spin->set_delay(500ms);
```