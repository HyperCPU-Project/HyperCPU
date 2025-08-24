"Find out current build info to fill in package name"

load("@rules_cc//cc:find_cc_toolchain.bzl", "find_cc_toolchain")
load("@rules_pkg//pkg:providers.bzl", "PackageVariablesInfo")

def _impl(ctx):
    values = {}

    # These are set from context - leave them configurable.
    values["version"] = ctx.attr.version
    values["platform"] = ctx.attr.platform
    values["product_name"] = ctx.attr.product_name

    # Some things we can fetch from current toolchain.
    tc = find_cc_toolchain(ctx)
    values["compiler"] = tc.compiler_executable.rsplit("/", 1)[-1]

    return PackageVariablesInfo(values = values)

pkg_vars = rule(
    implementation = _impl,
    attrs = {
        "product_name": attr.string(
            doc = "Placeholder for our final product name.",
        ),
        "platform": attr.string(
            doc = "Placeholder for our release platform",
        ),
        "version": attr.string(
            doc = "Placeholder for our release version.",
        ),
    },
    toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
)
