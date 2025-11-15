add_library(hcpu-core STATIC
    Core/CPU/Decoders/StdDecoder.cpp
    Core/CPU/InstructionsImpl/CALLGR.cpp
    Core/CPU/InstructionsImpl/WRITE.cpp
    Core/CPU/InstructionsImpl/OR.cpp
    Core/CPU/InstructionsImpl/SHFR.cpp
    Core/CPU/InstructionsImpl/JML.cpp
    Core/CPU/InstructionsImpl/READ.cpp
    Core/CPU/InstructionsImpl/HALT.cpp
    Core/CPU/InstructionsImpl/CMP.cpp
    Core/CPU/InstructionsImpl/HID.cpp
    Core/CPU/InstructionsImpl/CALL.cpp
    Core/CPU/InstructionsImpl/PUSH.cpp
    Core/CPU/InstructionsImpl/POP.cpp
    Core/CPU/InstructionsImpl/INTR.cpp
    Core/CPU/InstructionsImpl/MOV.cpp
    Core/CPU/InstructionsImpl/ANDN.cpp
    Core/CPU/InstructionsImpl/INC.cpp
    Core/CPU/InstructionsImpl/CALLL.cpp
    Core/CPU/InstructionsImpl/MUL.cpp
    Core/CPU/InstructionsImpl/CUDF.cpp
    Core/CPU/InstructionsImpl/LOIVT.cpp
    Core/CPU/InstructionsImpl/AND.cpp
    Core/CPU/InstructionsImpl/DEC.cpp
    Core/CPU/InstructionsImpl/DIV.cpp
    Core/CPU/InstructionsImpl/COVF.cpp
    Core/CPU/InstructionsImpl/CALLE.cpp
    Core/CPU/InstructionsImpl/SHFL.cpp
    Core/CPU/InstructionsImpl/JMGR.cpp
    Core/CPU/InstructionsImpl/CCRF.cpp
    Core/CPU/InstructionsImpl/ADD.cpp
    Core/CPU/InstructionsImpl/BSWAP.cpp
    Core/CPU/InstructionsImpl/JME.cpp
    Core/CPU/InstructionsImpl/JMP.cpp
    Core/CPU/InstructionsImpl/ADC.cpp
    Core/CPU/InstructionsImpl/SUB.cpp
    Core/CPU/InstructionsImpl/LODSB.cpp
    Core/CPU/InstructionsImpl/STDSB.cpp
    Core/CPU/Interrupts/InterruptHandler.cpp
    Core/CPU/IO/Simple.cpp
    Core/CPU/CPU.cpp
    Core/CPU/OperandsEvaluation.cpp
    Core/CPU/Stack.cpp
)
target_include_directories(hcpu-core PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(hcpu-core PUBLIC hcpu-common spdlog::spdlog)

add_executable(hcemul Main.cpp)
target_link_libraries(hcemul PUBLIC
    hcpu-core
    argparse::argparse
    re2::re2
)