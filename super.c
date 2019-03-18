/*
   1.init sb->sb_info;
   2.init sb->uuid;
*/

static int superblock_read(struct super_block *sb)
{
	struct buffer_head *bh;
	bh = sb_read(sb,0);
	struct erofs_super_block *layout;
	layout = (struct romfs_super_block *)(bh->data+EROFS_SUPER_OFFSET);
}

static int romfs_read_super(struct super_block *sb,
	const char *dev_name, void *options, int silent)
{
        
	/*1.read super block on the disk*/
	bh = sb_read(sb,0);
}


static int romfs_fill_super(struct super_block *sb,
	void *priv, int silent)
{
	return romfs_read_super(sb, priv->dev_name,
		priv->options, silent);
}
/*int (*fill_super)(struct super_block *, void *, int)*/
static struct dentry *romfs_mount(
	struct file_system_type *fs_type, int flags,
	const char *dev_name, void *data)
{
        struct erofs_mount_private priv = {
		.dev_name = dev_name,
		.options = data
		};
	return mount_bdev(fs_type, flags, dev_name,
		priv, romfs_fill_super);
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