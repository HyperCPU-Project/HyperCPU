"Aspects for linting"

load("@aspect_rules_lint//lint:clang_tidy.bzl", "lint_clang_tidy_aspect")
load("@aspect_rules_lint//lint:ruff.bzl", "lint_ruff_aspect")

ruff = lint_ruff_aspect(
    binary = Label("@aspect_rules_lint//format:ruff"),
    configs = [
        Label("@//:.ruff.toml"),
    ],
)

clang_tidy = lint_clang_tidy_aspect(
    binary = Label("//tools/bazel:clang_tidy"),
    configs = [
        Label("@//:.clang-tidy"),
    ],
)
