# HyperCPU Contributing Guidelines

This file describes the contributing guidelines of the project.

If you are going to work with code, we strongly recommend reading [Coding style](#coding-style) section at the end of file.

## Project collaborators

Clone repository locally and create a new branch from `master` with some senseful name.

> [!TIP]
> Ask yourself: what are you going to do? What feature are you going to implement (or what bug are you going to fix)?
> 
> **Examples of BAD branch names:** `r0ego03rg750yt3w4p37w8ypt98bo4wy49wyeuys9o49suebs9o84y3p47304p34bt3tb5o94ba0843twp`, `vasyapupkinwashere`.
>
> **Examples of GOOD branch names:** `fix-zero-division-error`, `implement-windows-support`.

Do your work on that branch, but **do not** touch others. Every push to any branch except `master` starts a CI workflow with minimal tests.

When you are ready, make a pull request (PR) to `master` branch. When the PR gets created, you have to track following checks: `CodeQL`, `Codacy`, main CI workflow that runs extended tests, and the job that builds the project on multiple platforms.

If MentatBot tells you what can be improved, it is better that you improve it :)

When all CI jobs finish successfully, just wait for project owner to review and approve your work and, finally, merge your PR.

Voila! Your changes have been merged and accepted to the project.

## Contributors

The same stuff as for project collaborators, except that you also have to fork the repository and work there. You will probably have to disable GitHub Actions or connect the self-hosted runner (no guarantee that HyperCPU workflows will execute successfully on custom runner).

## Coding style

### Identifiers

Use *PascalCase* for namespaces, class names and functions; *snake_case* for local variables and class fields.

### Tabs

2 spaces long.

### Whitespaces

A single space should be between operators, and no spaces should be between parenthesis and arguments.

```cpp
namespace HyperCPU {
  ...
}

class CPU {
  private:
    bool is_hypercpu_cool = true;
}

void HyperCPU::CPU::CPU() {
  int magic_number = 0xDEADBEEF;
  std::exit(1337 * 42);
}
```
