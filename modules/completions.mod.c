#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x93d6dd8c, "complete_all" },
	{ 0x6008689f, "kthread_complete_and_exit" },
	{ 0x608741b5, "__init_swait_queue_head" },
	{ 0x5d626f20, "kthread_create_on_node" },
	{ 0xbca77c8c, "wake_up_process" },
	{ 0x908dcd2e, "kthread_stop" },
	{ 0x25974000, "wait_for_completion" },
	{ 0x122c3a7e, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x2fa5cadd, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "EF50AB8FD9226123E51E02F");
