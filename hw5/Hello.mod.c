#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xcb8b6ec6, "kfree" },
	{ 0xab70d38f, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0xe8213e80, "_printk" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0x7fea776b, "kmalloc_caches" },
	{ 0x8e17af09, "__kmalloc_cache_noprof" },
	{ 0xe54e0a6b, "__fortify_panic" },
	{ 0xfbe7861b, "memcpy" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xe089f5db, "cdev_init" },
	{ 0x96d7c06d, "cdev_add" },
	{ 0xd710adbf, "__kmalloc_noprof" },
	{ 0x546c19d9, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x0e9cab28, "memset" },
	{ 0xaa47b76e, "__arch_copy_from_user" },
	{ 0x9c4ed43a, "alt_cb_patch_nops" },
	{ 0xaa47b76e, "__arch_copy_to_user" },
	{ 0xdc1bea0d, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xcb8b6ec6,
	0xab70d38f,
	0x0bc5fb0d,
	0xe8213e80,
	0xbd03ed67,
	0x7fea776b,
	0x8e17af09,
	0xe54e0a6b,
	0xfbe7861b,
	0x9f222e1e,
	0xe089f5db,
	0x96d7c06d,
	0xd710adbf,
	0x546c19d9,
	0xa61fd7aa,
	0x0e9cab28,
	0xaa47b76e,
	0x9c4ed43a,
	0xaa47b76e,
	0xdc1bea0d,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"kfree\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"_printk\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"__fortify_panic\0"
	"memcpy\0"
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"__kmalloc_noprof\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"memset\0"
	"__arch_copy_from_user\0"
	"alt_cb_patch_nops\0"
	"__arch_copy_to_user\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "5CAD2862687E8AA73662A9D");
