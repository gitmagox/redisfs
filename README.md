
Homepage:
    http://www.steve.org.uk/Software/redisfs/

Source Repository:
    http://git.steve.org.uk/skx/redisfs



Introduction
------------

Redis is a high-performance key/value store which allows storing keys, and their values, in a fast memory-backed store.

Intuitively it might seem that basing a filesystem around a simple key=value store isn't such a practical endeavour, but happily redis also has several useful abilities built-in, including native support for other data-structures including:

* sets.
* hashes.
* lists.

Using only key&value pairs, and the notion of a set, we can implement a simple filesystem, which is ready for replication and snapshotting.



Storage
-------

This filesystem makes use of two of redis's abilities:

* KEY storage.
* SET storage.

Our filesystem is built around the notion that a directory contains entries, and these entries are members of a set named after the parent directory.

For example consider the directory tree which contains two entries:

* `/mnt/redis/foo/`
* `/mnt/redis/README`

For each filesystem entry, be it a file, symlink, or a directory, we allocate a unique identifier which we called an "INODE number". This may be used to store, retrieve, and search for information:

* `INODE:1:UID` - The owner of the inode with ID 1.
* `INODE:1:GID` - The owner of the inode with ID 1.
* `INODE:1:SIZE` - The size of the object with inode #1.
* `INODE:1:NAME` - The name of the object with inode #1.
   ..

So we might see this:

* `INODE:1:NAME`: "foo"
* `INODE:1:MODE`: "0755"
* `INODE:1:GID`: "0"
* `INODE:1:UID`: "0"
* `INODE:1:TYPE`: "dir"
* ..

Similarly the entry for "`/README`" might look like this:

* `INODE:2:NAME`: "README"
* `INODE:2:MODE`: "0644"
* `INODE:2:GID`: "0"
* `INODE:2:UID`: "0"
* `INODE:2:TYPE`: "file"

The actual contents of a directory are stored in a set, which has a name based upon the inode of the parent directory.  For example:

   SMEMBERS DIRENT:3 -> { "5", "6" }


In actual fact we add a prefix to each key and set name, which allows multiple filesystems to be mounted at the same time - and which is the key to our snapshotting facility.


Getting Started
---------------

To build the code, assuming you have the required build dependencies
installed, you should merely need to run:

     make
     make test

Once built the software can be installed via:

     make install

It is possible to run the filesystem without having installed the
software, via:

     # ./src/redisfs
     Connecting to redis server localhost:6379 and mounting at /mnt/redis.

By default this will attempt to connect to a redis server running upon
the same host - if you wish to connect to a remote machine please execute:

     # ./src/redisfs --host remote.example.org [--port=6379][--password=redispassword][--locktimeout=100000]

更新说明--magox
---------------
1.修改文件重命名不能复盖已有文件的bug;

2.更新最新的hiredis客户端,支持fuse版本30以上;

3.增加redis密码验证[--password=redispassword];

4.增加分布式redis锁机制,由原来的一写多读,升级为可多机写;

如何使用:(需要有C语言基础)
---------------
1.安装libfuse https://github.com/libfuse/libfuse;

2.调整锁的超时，适配项目 https://github.com/gitmagox/redisfs/blob/master/redis_lock/redisLock.h;

3.命令例子:./src/redisfs --host localhost --port=6379 --password=redispassword --locktimeout=100000 --mount=/mnt/redis
* 参数说明：

参数|是否必选|说明|
---|---|---|
*host*|是|redis服务器
*port*|是|redis端口
*password*|是|redis密码
*locktimeout*|是|分布式锁超时时间
*mount*|是|挂载目录 


建意:
--
配合redis集群使用