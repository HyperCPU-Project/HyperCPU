#pragma once

#include <cstdint>
#include <mapbox/eternal.hpp>

#include "Common/LanguageSpec/Registers.hpp"
#include "PCH/CStd.hpp"

constexpr inline const auto registers_assoc = mapbox::eternal::hash_map<mapbox::eternal::string, HyperCPU::Reg>(
    {
        {"x0", HyperCPU::Reg::X0},
        {"x1", HyperCPU::Reg::X1},
        {"x2", HyperCPU::Reg::X2},
        {"x3", HyperCPU::Reg::X3},
        {"x4", HyperCPU::Reg::X4},
        {"x5", HyperCPU::Reg::X5},
        {"x6", HyperCPU::Reg::X6},
        {"x7", HyperCPU::Reg::X7},
        {"xh0", HyperCPU::Reg::XH0},
        {"xh1", HyperCPU::Reg::XH1},
        {"xh2", HyperCPU::Reg::XH2},
        {"xh3", HyperCPU::Reg::XH3},
        {"xh4", HyperCPU::Reg::XH4},
        {"xh5", HyperCPU::Reg::XH5},
        {"xh6", HyperCPU::Reg::XH6},
        {"xh7", HyperCPU::Reg::XH7},
        {"xl0", HyperCPU::Reg::XL0},
        {"xl1", HyperCPU::Reg::XL1},
        {"xl2", HyperCPU::Reg::XL2},
        {"xl3", HyperCPU::Reg::XL3},
        {"xl4", HyperCPU::Reg::XL4},
        {"xl5", HyperCPU::Reg::XL5},
        {"xl6", HyperCPU::Reg::XL6},
        {"xl7", HyperCPU::Reg::XL7},
        {"xll0", HyperCPU::Reg::XLL0},
        {"xll1", HyperCPU::Reg::XLL1},
        {"xll2", HyperCPU::Reg::XLL2},
        {"xll3", HyperCPU::Reg::XLL3},
        {"xllh0", HyperCPU::Reg::XLLH0},
        {"xllh1", HyperCPU::Reg::XLLH1},
        {"xllh2", HyperCPU::Reg::XLLH2},
        {"xllh3", HyperCPU::Reg::XLLH3},
        {"xlll0", HyperCPU::Reg::XLLL0},
        {"xlll1", HyperCPU::Reg::XLLL1},
        {"xlll2", HyperCPU::Reg::XLLL2},
        {"xlll3", HyperCPU::Reg::XLLL3},
        {"xbp", HyperCPU::Reg::XBP},
        {"xsp", HyperCPU::Reg::XSP},
        {"xip", HyperCPU::Reg::XIP},
        {"xgdp", HyperCPU::Reg::XGDP},
        {"xivt", HyperCPU::Reg::XIVT},
        {"xfst", HyperCPU::Reg::XFST},
    });
