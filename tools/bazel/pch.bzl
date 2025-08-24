"Precompile Headers. Note: this is quite experimental."

load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")
load("@rules_cc//cc:action_names.bzl", "CPP_COMPILE_ACTION_NAME")

def _feature_conf(ctx, cc_toolchain):
    return cc_common.configure_features(ctx = ctx, cc_toolchain = cc_toolchain)

def _global_flags(ctx, cc_toolchain, feature_configuration):
    compile_variables = cc_common.create_compile_variables(
        feature_configuration = feature_configuration,
        cc_toolchain = cc_toolchain,
        user_compile_flags = ctx.fragments.cpp.cxxopts + ctx.fragments.cpp.copts,
    )
    flags = cc_common.get_memory_inefficient_command_line(
        feature_configuration = feature_configuration,
        action_name = CPP_COMPILE_ACTION_NAME,
        variables = compile_variables,
    )
    if cc_toolchain.needs_pic_for_dynamic_libraries(feature_configuration = feature_configuration):
        flags = flags + ["-fPIC"]
    return flags

def _precompiled_headers_impl(ctx):
    files = ctx.attr.main.files.to_list()
    if len(files) != 1:
        fail("expected a single aggregated header to compile, got: {}".format(files))
    main_file = files[0]

    cc_toolchain = find_cpp_toolchain(ctx)
    feature_configuration = _feature_conf(ctx, cc_toolchain)

    dep_ctxs = []
    for d in ctx.attr.deps:
        if CcInfo in d:
            dep_ctxs.append(d[CcInfo].compilation_context)
        else:
            fail("dep arguments must provide CcInfo (e.g. cc_library): {}".format(d))

    merged_ctx = cc_common.merge_compilation_contexts(
        compilation_contexts = dep_ctxs,
    )

    args = ctx.actions.args()
    args.add_all(_global_flags(ctx, cc_toolchain, feature_configuration))

    for define in merged_ctx.defines.to_list():
        args.add("-D" + define)
    for define in getattr(merged_ctx, "local_defines", depset()).to_list():
        args.add("-D" + define)

    args.add_all(merged_ctx.system_includes.to_list(), before_each = "-isystem")
    args.add_all(merged_ctx.includes.to_list() + merged_ctx.quote_includes.to_list(), before_each = "-I")

    args.add_all(ctx.attr.copts)
    args.add("-xc++-header")
    args.add(main_file.path)

    output = ctx.actions.declare_file("{}.pch".format(main_file.basename))
    args.add("-o", output.path)

    args.add("-MD")
    args.add("-MF", "/dev/null")

    inputs = depset(
        direct = [main_file],
        transitive = [merged_ctx.headers, cc_toolchain.all_files],
    )

    compiler_tool = cc_common.get_tool_for_action(
        feature_configuration = feature_configuration,
        action_name = CPP_COMPILE_ACTION_NAME,
    ) or cc_toolchain.compiler_executable

    ctx.actions.run(
        inputs = inputs,
        outputs = [output],
        executable = compiler_tool,
        arguments = [args],
        mnemonic = "PrecompileHdrs",
        progress_message = "Pre-compiling header: {}".format(main_file.basename),
    )

    pch_ctx = cc_common.create_compilation_context(
        headers = depset(direct = [output, main_file]),
        includes = depset(direct = [output.dirname]),
    )

    merged_headers = depset(transitive = [merged_ctx.headers, pch_ctx.headers])
    merged_includes = depset(transitive = [
        merged_ctx.includes,
        merged_ctx.quote_includes,
        pch_ctx.includes,
    ])

    merged_quote_includes = depset(transitive = [
        merged_ctx.quote_includes,
    ])

    merged_system_includes = depset(transitive = [
        merged_ctx.system_includes,
    ])

    merged_out_compilation_ctx = cc_common.create_compilation_context(
        headers = merged_headers,
        includes = merged_includes,
        quote_includes = merged_quote_includes,
        system_includes = merged_system_includes,
        defines = merged_ctx.defines,
        local_defines = getattr(merged_ctx, "local_defines", depset()),
        framework_includes = getattr(merged_ctx, "framework_includes", depset()),
    )

    dep_cc_infos = [d[CcInfo] for d in ctx.attr.deps if CcInfo in d]
    merged_linking_ctx = cc_common.merge_linking_contexts(
        linking_contexts = [
            i.linking_context
            for i in dep_cc_infos
            if hasattr(i, "linking_context") and i.linking_context
        ],
    )

    return [CcInfo(
        compilation_context = merged_out_compilation_ctx,
        linking_context = merged_linking_ctx,
    )]

precompiled_headers = rule(
    implementation = _precompiled_headers_impl,
    attrs = {
        "main": attr.label(allow_files = True, mandatory = True),
        "deps": attr.label_list(),
        "copts": attr.string_list(),
        "_cc_toolchain": attr.label(
            default = Label("@bazel_tools//tools/cpp:current_cc_toolchain"),
        ),
    },
    toolchains = ["@bazel_tools//tools/cpp:toolchain_type"],
    fragments = ["cpp"],
)
