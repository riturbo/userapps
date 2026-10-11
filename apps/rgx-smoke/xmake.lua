add_rules("mode.debug", "mode.release")

local rogue_usr_dir = path.join(os.projectdir(), "..", "..", "rogue_usr")
local rogue_usr_target_dir = path.join(rogue_usr_dir, "binary_rtsmart_nullws_release", "target_aarch64")
local rogue_usr_neutral_dir = path.join(rogue_usr_dir, "binary_rtsmart_nullws_release", "target_neutral")
local rogue_usr_bvnc = "22.102.54.38"
local rogue_usr_mips_elf_root = "/home/wy/tools/mips-mti-elf/2014.07-1"
local rogue_usr_firmware_name = "rgx.fw." .. rogue_usr_bvnc

target("rogue_usr_artifacts")
do
    set_kind("phony")
    on_build(function (_)
        os.execv("make", {
            "PVR_BUILD_DIR=rtsmart",
            "CROSS_COMPILE=aarch64-linux-musleabi-",
            "RGX_BVNC=" .. rogue_usr_bvnc,
            "MIPS_ELF_ROOT=" .. rogue_usr_mips_elf_root,
            "rgxfw_target",
            "libsrv_um",
            "rgx_smoke"
        }, {curdir = rogue_usr_dir})
    end)
end
target_end()

target("rogue_usr_srv_um")
do
    set_kind("shared")
    set_filename("libsrv_um.so")
    add_values("rt.rootfs.prefixdir", "/lib")
    add_deps("rogue_usr_artifacts")
    on_build(function (target)
        local src = path.join(rogue_usr_target_dir, "libsrv_um.so")
        local dst = target:targetfile()
        os.mkdir(path.directory(dst))
        os.cp(src, dst)
    end)
end
target_end()

target("rgx_smoke")
do
    set_kind("binary")
    add_deps("rogue_usr_artifacts")
    on_build(function (target)
        local src = path.join(rogue_usr_target_dir, "rgx_smoke")
        local dst = target:targetfile()
        os.mkdir(path.directory(dst))
        os.cp(src, dst)
    end)
end
target_end()

target("rogue_usr_firmware")
do
    set_kind("binary")
    set_filename(rogue_usr_firmware_name)
    add_values("rt.rootfs.prefixdir", "/lib/firmware")
    add_deps("rogue_usr_artifacts")
    on_build(function (target)
        local src = path.join(rogue_usr_neutral_dir, rogue_usr_firmware_name)
        local dst = target:targetfile()
        os.mkdir(path.directory(dst))
        os.cp(src, dst)
    end)
end
target_end()
