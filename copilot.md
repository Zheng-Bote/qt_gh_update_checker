# Toolchain & Build

- Standard: C++23
- Compiler:
  - GCC/Clang: -std=c++23 -Wall -Wextra -Wpedantic -Wshadow -Wconversion
  - MSVC: /std:c++latest /W4
- CMake ≥ 3.28 for module support
- Structure:
  - include/Model, include/View, include/Controller, include/Utils
  - src/Model, src/View, src/Controller, src/Utils
  - main.cpp remains minimal and delegates only to Controller/Bootstrap

# 🔧 C++23 Feature Usage

## Formatted Output (<print>)

- Standard for logging, debugging, CLI output
- Use std::print / std::println instead of std::cout

## std::expected

- Standard mechanism for error handling
- No exceptions for controllable error cases
- Use .and_then(), .transform(), .or_else()

## Modules (import std)

- Use when toolchain is stable
- Fallback: classic headers

## Deducing this

- For recursive lambdas
- For CRTP boilerplate reduction

### std::mdspan

- For multi-dimensional views without ownership
- Ideal for performance-critical areas

### Ranges

- Use std::views + std::ranges::to<>() for pipeline style
- No manual loops if ranges are clearer

### Strings

- Parameters generally std::string_view
- Only with ownership: std::string

# 🏛️ Architecture (MVC + Utils)

## Model

- Pure data structures
- Business logic, validation, domain functions
- No IO, no logging

## View

- CLI output, rendering, formatting
- Uses <print>
- No logic

## Controller

- Orchestrates Model + View
- Contains program flow
- Main logic starts here, not in main.cpp

## Utils

- Helper functions, tools, helpers
- No dependencies on Model/View/Controller

## main.cpp

- Minimal: bootstrapping only

Example:

```cpp
import app.controller;

int main() {
    return app::Controller{}.run();
}
```

# 🧹 Coding Style

## Naming

- Functions/variables: snake_case
- Classes/structs: PascalCase
- Constants: SCREAMING_SNAKE_CASE or kCamelCase

## Modern C++ Idioms

- auto for clear types
- [[nodiscard]] for pure functions
- constexpr/consteval where possible
- No raw pointers except for non-owning
- Smart pointers only with ownership

# 📁 File Structure & Modules

- Header: .hpp
- Source: .cpp
- Module: .cppm or .ixx (depending on compiler)

# 📚 Documentation (Doxygen)

Each file starts with:

```cpp
/**
 * SPDX-FileComment: <Description of the file>
 * SPDX-FileType: SOURCE
 * SPDX-FileContributor: ZHENG Robert
 * SPDX-FileCopyrightText: <2026> ZHENG Robert
 * SPDX-License-Identifier: <MIT>
 *
 * @file <filename.hpp>
 * @brief <Description of the file>
 * @version <0.1.0>
 * @date <YYYY-MM-DD>
 *
 * @author ...
 * @license MIT License
 */
```

Each function, class, method:

- Doxygen comment
- English
- Short, precise, technical
