export type OS = "windows" | "linux" | "android" | "macosx" | "ios"
export type Platform = "android" | "appletvos" | "applexros" | "bsd" | "cross" | "cygwin" | "haiku" | "iphoneos" | "linux" | "macosx" | "mingw" | "msys" | "wasm" | "watchos" | "windows"
export type Host = "windows" | "linux" | "macosx"
export type Subhost = "msys" | "sygwin"

declare function is_os(os: OS): boolean
declare function is_arch(...: string): boolean
declare function is_plat(...: Platform): boolean
declare function is_host(host: Host): boolean
declare function is_subhost(...: Subhost): boolean
declare function is_cross(): boolean
declare function is_mode(...: string): boolean
declare function is_kind(kind: string): boolean
declare function is_config(name: string, ...: string): boolean
declare function has_config(...: string): boolean
declare function has_package(package: string): boolean

declare function includes(includes: string): ()
declare function set_project(name: string): ()
declare function set_version(version: string, config: any?): ()
declare function set_xmakever(xmakeMinVersion: string): ()
declare function add_moduledirs(...: string): ()
declare function add_plugindirs(...: string): ()
declare function get_config(config: string): string?
declare function set_config(config: string, value: string): ()
declare function add_requires(...: any): ()
declare function add_repositories(...: string): ()
declare function set_defaultplat(platform: Platform): ()
declare function set_defaultarchs(arch: string): ()
declare function set_defaultmode(mode: string): ()
declare function set_allowedplats(...: Platform): ()
declare function set_allowedarchs(...: Platform): ()
declare function set_allowedmodes(...: Platform): ()

declare function target(target: string): ()
declare function set_kind(kind: string): ()

declare function add_files(...: string): ()
