```cpp
std::vector<Object>

std::vector<std::shared_ptr<Object>>

std::vector<std::unique_ptr<Object>>

std::variant<int, float, char> var;
// If we are certain we know what type it is, we can get it:
auto str = std::get<std::string>(var);
// but this will throw if we get it wrong. get_if:
auto* str  = std::get_if<std::string>(&var);
```