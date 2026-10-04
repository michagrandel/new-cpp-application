---
name: document-code
description: Document code using Microsoft's XML documentation comment format. Use when adding, updating, or reviewing documentation for classes, methods, functions, variables, constants, and other declarations, or when cleaning up implementation comments. Require English documentation and rare, rationale-only single-line implementation comments.
---

# Document code

## Scope and priorities

- Document every declaration in the requested scope, including public, protected,
  private, and local declarations. Cover classes, structs, interfaces, methods,
  constructors, destructors, functions, operators, variables, fields, constants,
  properties, enums and their members, type aliases, and named namespaces.
- Document parameters and template parameters in their owning declaration's
  documentation rather than inserting comments into parameter lists.
- Write ALL documentation and comments in English, even when the request or
  application output uses another language. Do not translate application strings.
- Prefer readable names, clear control flow, and small, cohesive functions over
  implementation comments. Keep declaration documentation concise but meaningful;
  do not merely restate the identifier or its type.
- Preserve behavior, signatures, visibility, and platform compatibility. Do not
  refactor code solely to document it unless the user also requests refactoring.
- Do not edit generated code, vendored dependencies, or build output. Report any
  exclusions from a request to document an entire project.

## File purpose comment

- Begin every source file in the requested scope with a short English `// ...`
  comment explaining WHAT the file is for: its responsibility or role.
- Place this comment in the first lines, before includes or declarations.
  Preserve mandatory leading legal notices or tool directives when present;
  place the purpose comment immediately after them.
- Follow the purpose comment with a blank line.
- This file-level comment is distinct from declaration XML documentation and
  implementation comments. It describes the file's purpose, not a code block's
  rationale, and needs no preceding blank line when it starts the file.
- For file formats that do not support `//`, ask how to adapt the convention
  rather than inserting invalid syntax.

```cpp
// Provides the application entry point and demonstrates colored console logging.

#include <spdlog/spdlog.h>
```

## Microsoft documentation format

For this C++ project, "docstrings" means Microsoft's XML documentation comments,
not Python string literals, Javadoc, or Doxygen tags.

- Place documentation immediately before the declaration, with matching
  indentation. Prefix every documentation line with `///`.
- Use `<summary>` for every declaration. Describe its purpose and contract.
- Use `<param name="...">` for every parameter and `<typeparam name="...">`
  for every template parameter. Match actual names exactly. Describe units,
  valid ranges, nullability, ownership, and direction where relevant.
- Use `<returns>` for functions and methods returning a value. Describe its
  meaning and relevant sentinel values. Omit it for `void`, constructors, and
  destructors.
- Use `<value>` for properties when applicable.
- Use `<remarks>` only for important constraints, side effects, lifetime,
  threading, platform restrictions, or rationale not covered by the summary.
- Use `<exception cref="...">` only for exceptions verified from the
  implementation and called APIs. Never invent guarantees or failure modes.
- Use `<see cref="..."/>`, `<paramref name="..."/>`, and
  `<typeparamref name="..."/>` for relevant references where supported.
- Keep XML well-formed. Escape special characters in text, including `&amp;`
  and `&lt;`. Do not use `/** ... */`, `@brief`, `@param`, or `@return`.
- Document a symbol at its canonical declaration, usually in its header.
  Avoid duplicating the same documentation on an out-of-line definition.
  Document separately any new local declarations in that definition.
- For variables and constants, describe their role and relevant units, valid
  values, ownership, or lifetime. This includes local variables and loop
  variables; do not replace their documentation with implementation comments.
- If a declaration is embedded in a loop or another expression, place its
  documentation directly above the containing statement and identify the
  variable explicitly. Do not restructure executable code just to attach XML.

XML comments can be written for all these declarations, but compiler-generated
documentation and IntelliSense support vary. In particular, do not promise
MSVC `/doc` extraction for local variables or templates. Do not enable `/doc`
or change the build configuration unless requested. For a language without
`///` comments, ask how to adapt this convention instead of emitting invalid
syntax or silently switching to a different documentation style.

### Examples

```cpp
/// <summary>Tracks how many work items have completed.</summary>
class CompletionCounter {
public:
    /// <summary>Records additional completed work items.</summary>
    /// <param name="count">The number of newly completed work items.</param>
    void add(unsigned int count);

    /// <summary>Gets the total number of completed work items.</summary>
    /// <returns>The number recorded since this counter was created.</returns>
    unsigned int total() const;

private:
    /// <summary>The number of work items recorded as completed.</summary>
    unsigned int completed_count_ = 0;
};
```

```cpp
/// <summary>The maximum time, in milliseconds, to wait for a response.</summary>
constexpr unsigned int response_timeout_ms = 5000;
```

## Implementation comments

These rules apply to comments inside executable code, not to the declaration
documentation required above:

- Prefer no implementation comment. Add one only for a complex, multiline code
  block whose non-obvious rationale cannot be conveyed by readable code alone.
- Use only single-line `// ...` comments. Never use block comments. Keep the
  comment adjacent to the block it explains.
- Always place a blank line immediately before each implementation comment.
  This applies to `// ...`, not to `///` declaration documentation. Put each
  implementation comment on its own line above its block, never after code on
  the same line. Prefer one concise comment; if several are needed, each must
  have its own preceding blank line.
- Explain WHY the block is necessary: a constraint, invariant, compatibility
  requirement, or deliberate trade-off. Never explain HOW the code works.
- Include no code, pseudocode, commented-out statements, or executable examples.
- Do not narrate assignments, calls, conditions, or obvious control flow.
- Remove obsolete, redundant, non-English, or how-oriented implementation
  comments in the requested scope. Preserve any verified, necessary rationale
  by rewriting it concisely in English.
- Preserve mandatory legal notices and tool directives. They are not explanatory
  implementation comments; report conflicts rather than deleting them.

## Workflow and verification

1. Identify the requested files or symbols and read their declarations,
   definitions, callers, and existing documentation as needed to establish facts.
2. Inventory every declaration in scope, including private members and locals.
3. Add or update XML documentation using only verified behavior. If an important
   contract cannot be established, ask for clarification instead of guessing.
4. Add or update each file's purpose comment and its following blank line.
   Review implementation comments against the rationale-only rules and ensure
   each has a preceding blank line.
5. Check declaration coverage, English language, XML syntax, exact parameter
   names, accurate return descriptions, and the absence of prohibited comments.
6. Review the diff to ensure no executable behavior or application strings changed.
   Use existing documentation validation if available. Run relevant build or
   tests if executable code changed; do not add tooling solely for this skill.
7. Summarize the scope documented, verification performed, and any exclusions or
   documentation-tool limitations. Never claim checks that were not run.

## References

- [Microsoft XML documentation for Visual C++](https://learn.microsoft.com/en-us/cpp/build/reference/xml-documentation-visual-cpp)
- [Microsoft recommended documentation tags](https://learn.microsoft.com/en-us/cpp/build/reference/recommended-tags-for-documentation-comments-visual-cpp)
