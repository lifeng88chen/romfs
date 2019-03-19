#ifndef __INTERNAL_H
#define __INTERNAL_H
/*discription filesystem sb for memory,VFS super_block.
  sb->s_fs_info 
  romfs_sb_info form to romfs_super_block of disk super block. 
*/
struct romfs_sb_info {
        struct list_head list;// point to superblock
        u32 blocks;
        u32 meta_blkaddr;
        u64 root_nid;/*get root inode to hash list*/
        u8 uuid[16];
        u8 volume_name[16];
};
#endif
