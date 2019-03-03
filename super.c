
static int romfs_read_super(struct super_block *sb,
	const char *dev_name, void *data, int silent)
{
	
}


static int romfs_fill_super(struct super_block *sb,
	void *_priv, int silent)
{
	return romfs_read_super(sb, NULL,
		NULL, silent);
}

static struct dentry *romfs_mount(
	struct file_system_type *fs_type, int flags,
	const char *dev_name, void *data)
{
	return mount_bdev(fs_type, flags, dev_name,
		NULL, romfs_fill_super);
}

static void romfs_kill_sb(struct super_block *sb)
{
	kill_block_super(sb);
}

static struct file_system_type romfs_fs_type = {
	.owner          = THIS_MODULE,
	.name           = "romfs",
	.mount          = romfs_mount,
	.kill_sb        = romfs_kill_sb,
	.fs_flags       = FS_REQUIRES_DEV,
};
MODULE_ALIAS_FS("romfs");


static int __init romfs_module_init(void)
{
	int err;
	err = register_filesystem(&romfs_fs_type);
	if (err)
		goto fs_err;
	printk("successfully to initialize romfs");
	return 0;
fs_err:
	return err;
}




module_init(romfs_module_init);
module_exit(romfs_module_exit);
MODULE_DESCRIPTION("EXTERN Read only filesystem");
MODULE_AUTHOR("Chen Lifeng lifeng88chen@gmail.com");
MODULE_LICENSE("GPL");
