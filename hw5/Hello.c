#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BSU CS 452 HW5");
MODULE_AUTHOR("<buff@cs.boisestate.edu>");

typedef struct {
  dev_t devno;
  struct cdev cdev;
  char *seps;
  size_t sep_len;
} Device; /* per-init() data */

typedef struct {
  char *seps;
  size_t sep_len;
  int sep_mode;
  int eot;
  char *data;
  size_t data_len;
  size_t pos;
} File; /* per-open() data */

static Device device;

static int is_sep(File *file, char c) {
  size_t i;
  for (i = 0; i < file->sep_len; i++)
    if (file->seps[i] == c)
      return 1;
  return 0;
}

static int open(struct inode *inode, struct file *filp) {

  File *file = kmalloc(sizeof(*file), GFP_KERNEL);

  if (!file) {
    printk(KERN_ERR "%s: kmalloc() failed\n", DEVNAME);
    return -ENOMEM;
  }

  file->seps = kmalloc(device.sep_len, GFP_KERNEL);
  if (!file->seps) {
    kfree(file);
    return -ENOMEM;
  }

  memcpy(file->seps, device.seps, device.sep_len);

  file->sep_len = device.sep_len;
  file->data = NULL;
  file->data_len = 0;
  file->pos = 0;
  file->sep_mode = 0;
  file->eot = 0;
  filp->private_data = file;

  return 0;
}

static int release(struct inode *inode, struct file *filp) {
  File *file = filp->private_data;
  kfree(file->seps);
  kfree(file->data);
  kfree(file);
  return 0;
}

static ssize_t read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {

  File *file = filp->private_data;
  size_t start, n;

  if (count == 0)
    return 0;

  if (file->eot) {
    file->eot = 0;
    return 0;
  }

  while (file->pos < file->data_len && is_sep(file, file->data[file->pos])) {
    file->pos++;
  }

  if (file->pos >= file->data_len)
    return -1;

  start = file->pos;
  n = 0;
  while (file->pos < file->data_len && !is_sep(file, file->data[file->pos]) &&
         n < count) {
    file->pos++;
    n++;
  }

  if (file->pos >= file->data_len || is_sep(file, file->data[file->pos]))
    file->eot = 1;

  if (copy_to_user(buf, file->data + start, n))
    return -EFAULT;

  return (ssize_t)n;
}

static ssize_t write(struct file *filp, const char __user *buf, size_t count,
                     loff_t *f_pos) {
  File *file = filp->private_data;
  char *tmp;

  if (count == 0)
    return 0;

  tmp = kmalloc(count, GFP_KERNEL);
  if (!tmp) {
    printk(KERN_ERR "%s: kmalloc() failed\n", DEVNAME);
    return -ENOMEM;
  }
  if (copy_from_user(tmp, buf, count)) {
    kfree(tmp);
    return -EFAULT;
  }

  if (file->sep_mode) {
    kfree(file->seps);
    file->seps = tmp;
    file->sep_len = count;
    file->sep_mode = 0;
  } else {
    kfree(file->data);
    file->data = tmp;
    file->data_len = count;
    file->pos = 0;
    file->eot = 0;
  }
  return count;
}

static long ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
  File *file = filp->private_data;
  if (cmd == 0) {
    file->sep_mode = 1;
    return 0;
  }
  return -EINVAL;
}

static struct file_operations ops = {.open = open,
                                     .release = release,
                                     .read = read,
                                     .write = write,
                                     .unlocked_ioctl = ioctl,
                                     .owner = THIS_MODULE};

static int __init my_init(void) {
  const char *s = "Hello world!\n";
  static const char defaults[] = {' ', '\t', '\n', ':'};
  int err;

  device.sep_len = sizeof(defaults);
  device.seps = kmalloc(device.sep_len, GFP_KERNEL);
  if (!device.seps) {
    printk(KERN_ERR "%s: kmalloc() failed\n", DEVNAME);
    return -ENOMEM;
  }
  memcpy(device.seps, defaults, device.sep_len);

  err = alloc_chrdev_region(&device.devno, 0, 1, DEVNAME);
  if (err < 0) {
    printk(KERN_ERR "%s: alloc_chrdev_region() failed\n", DEVNAME);
    kfree(device.seps);
    return err;
  }

  cdev_init(&device.cdev, &ops);
  device.cdev.owner = THIS_MODULE;

  err = cdev_add(&device.cdev, device.devno, 1);
  if (err) {
    printk(KERN_ERR "%s: cdev_add() failed\n", DEVNAME);
    unregister_chrdev_region(device.devno, 1);
    kfree(device.seps);
    return err;
  }

  printk(KERN_INFO "%s: init\n", DEVNAME);
  return 0;
}

static void __exit my_exit(void) {
  cdev_del(&device.cdev);
  unregister_chrdev_region(device.devno, 1);
  kfree(device.seps);
  printk(KERN_INFO "%s: exit\n", DEVNAME);
}

module_init(my_init);
module_exit(my_exit);
